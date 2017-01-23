#include "AstarPathFinder.h"
#include "../Character.h"
#include "../TileField.h"
#include "../../DebugDraw.h"

AstarPathFinder::AstarPathFinder(Character& owner, std::vector<TiledVector> &pathRef, bool diagonal)
: _diagonal(diagonal)
, _pathStack(pathRef)
, _owner(owner)
{
    auto fieldSize = FIELD->GetFieldSize();
    
    for (int i = 0; i < fieldSize._y; ++i)
    {
        _nodeTable.push_back(std::move(std::vector<std::unique_ptr<AstarNode>>()));

        for (int j = 0; j < fieldSize._x; ++j)
        {
            _nodeTable[i].push_back(std::make_unique<AstarNode>(TiledVector(j, i)));
        }
    }
    
    _additionalFunc = [&](TiledObject* obj){ return false; };
}


AstarPathFinder::~AstarPathFinder()
{
}


void AstarPathFinder::Reset()
{
    _pathStack.clear();
    _pathStack.resize(0);
}


std::vector<TiledVector> AstarPathFinder::GetPathToTarget(TiledVector startPos, TiledVector targetPos, int searchRange)
{
    //指定した最大探索距離より遠ければ検索せずに酋長
    TiledVector offset = startPos - targetPos;
    int length = offset.GetBresenhamLength(true);
    if (searchRange < length)
        return _pathStack;
    
    //初期化してから
    Reset();
    //経路計算
    Search(startPos, targetPos);
    
    return _pathStack;
}


void AstarPathFinder::Search(TiledVector startPos, TiledVector targetPos)
{
    auto fieldSize = FIELD->GetFieldSize();
    //すべてのノードを初期化する
    for (int i = 0; i < fieldSize._y; ++i)
    {
        for (int j = 0; j < fieldSize._x; ++j)
        {
            _nodeTable[i][j]->Init();
        }
    }
    _openList.resize(0);
    
    //検索開始
    AstarNode *origin = nullptr;
    //自身の位置からスタート
    AstarNode *startNode = _nodeTable[startPos._y][startPos._x].get();
    AstarNode *targetNode = _nodeTable[targetPos._y][targetPos._x].get();
    //最初だけは手動で
    startNode->Open(nullptr, targetNode);
    _openList.push_back(startNode);
    
    //移動の必要が無ければ終了
    if (startNode->GetHeuristicCost() == 0)
        return;
    
    CalcAstar(startNode, origin, targetNode);
}


void AstarPathFinder::CalcAstar(AstarNode *node, AstarNode *parentNode, AstarNode *targetNode)
{
    auto it = std::find(_openList.begin(), _openList.end(), node);
    _openList.erase(it);
    
    //周りをOpen
    OpenAround(node, targetNode);
    
    //自分をClose
    node->Close();
    
    AstarNode *nearest = nullptr;
    int minScore = AstarNode::MAX_SCORE;
    int minCost = AstarNode::MAX_SCORE;
    
    //コストが既知のマスの中で最もスコアが小さいマスを選ぶ
    for (auto _node : _openList)
    {
        if (_node == nullptr)
            continue;
        
        if (minScore < _node->GetScore())
            continue;
        
        if (_node->GetScore() == minScore)
        {
            if (minCost <= _node->GetCost())
                continue;
        }
        
        nearest = _node;
        minScore = _node->GetScore();
        minCost = _node->GetCost();
    }
    
    //袋小路にたどり着いたら終了
    if (nearest == nullptr)
    {
        int i=0;
        auto ptr = node;
        while (ptr != nullptr)
        {
            ptr = ptr->GetParentPtr();
            i++;
        }
        return;
    }
    
    //目的のノードにたどり着いたら終了
    if (nearest->GetHeuristicCost() == 0)
    {
        //目的地は手動で追加
        _pathStack.push_back(targetNode->GetChipPos());
        
        int i=0;
        auto ptr = nearest;
        while (ptr != nullptr)
        {
            _pathStack.insert(_pathStack.begin(), ptr->GetChipPos());
            ptr = ptr->GetParentPtr();
            i++;
        }
        _pathStack.erase(_pathStack.begin());
        return;
    }
    
    //繰り返し
    CalcAstar(nearest, node, targetNode);
}


void AstarPathFinder::OpenAround(AstarNode *node, AstarNode *targetNode)
{
    TiledVector nextPos = node->GetChipPos();
    
    int x = nextPos._x;
    int y = nextPos._y;
    
    TiledVector aroundPos[4] =
    {
        TiledVector(x - 1, y)
        ,TiledVector(x + 1, y)
        ,TiledVector(x, y - 1)
        ,TiledVector(x, y + 1)
    };
    
    for (auto pos : aroundPos)
    {
        //範囲外をOpenしようとしたら終了
        if( !FIELD->IsInside(pos) )
            continue;
        
        AstarNode *nextNode = _nodeTable[pos._y][pos._x].get();
        
        //次の位置に
        auto objects = FIELD->GetTiledObjects(pos);
        
        //何もなければ移動できる
        bool isMovable = (objects.size() == 0);
        //何かあるなら
        bool overwritable = true;
        for (auto obj : objects)
        {
            //そのオブジェクトのうえに移動できるか
            overwritable &= (obj != nullptr) && (obj->IsOverwritable(&_owner));
        }

        isMovable |= overwritable;
        for (auto obj : objects)
        {
            //到達目標の地点かどうか
            isMovable |= (obj != nullptr) && (obj->GetTilePos() == targetNode->GetChipPos());
            //その他条件式
            isMovable |= _additionalFunc(obj);
        }
        if (nextNode->IsReady() && isMovable)
        {
            nextNode->Open(node, targetNode);
            _openList.push_back(nextNode);
        }
    }
}


void AstarPathFinder::Draw()
{
    for (size_t i=0; i<_pathStack.size(); ++i)
    {
        Debug::DrawRectWithSize(_pathStack[i].GetWorldPos(), Vector2D(TILE_SIZE, TILE_SIZE),
                                Color4(0.5, 1.0, 1.0, 0.1), true);
    }
}