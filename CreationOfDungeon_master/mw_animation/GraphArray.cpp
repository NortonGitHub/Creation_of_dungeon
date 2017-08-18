#include "GraphArray.h"

#include <string>
#include <assert.h>
#include "DxLib.h"

GraphArray::GraphArray()
    : _graphPtr(nullptr)
    , _speed(1)
    , _index(0)
    , _currentTime(0)
    , _endTime(30)
    , _isLoop(true)
    , _isPlaying(true)
    , _isCreatedInside(false)
    , _hasEnd(false)
{
}

GraphArray::GraphArray(Sprite *arg_graph
    , const int divNumH, const int divNumV
    , const int sizeH, const int sizeV
    , const int allDivNum, const int endTime)
{
    Set(arg_graph, divNumH, divNumV, sizeH, sizeV, allDivNum, endTime);
}

GraphArray::GraphArray(Sprite *arg_graph
    , const int sizeH, const int sizeV
    , const int allDivNum, const int endTime)
    : _graphPtr(nullptr)
    , _speed(1)
    , _index(0)
    , _currentTime(0)
    , _endTime(30)
    , _isLoop(true)
    , _isPlaying(true)
    , _isCreatedInside(false)
    , _hasEnd(false)
{
    Set(arg_graph, sizeH, sizeV, allDivNum, endTime);
}

GraphArray::GraphArray(std::string name
    , const int divNumH, const int divNumV
    , const int sizeH, const int sizeV
    , const int allDivNum, const int endTime)
    : _graphPtr(nullptr)
    , _speed(1)
    , _index(0)
    , _currentTime(0)
    , _endTime(30)
    , _isLoop(true)
    , _isPlaying(true)
    , _isCreatedInside(false)
    , _hasEnd(false)
{
    SetWithCreate(name, divNumH, divNumV, sizeH, sizeV, allDivNum, endTime);
}

GraphArray::GraphArray(std::string name
    , const int sizeH, const int sizeV
    , const int allDivNum, const int endTime)
    : _graphPtr(nullptr)
    , _speed(1)
    , _index(0)
    , _currentTime(0)
    , _endTime(30)
    , _isLoop(true)
    , _isPlaying(true)
    , _isCreatedInside(false)
    , _hasEnd(false)
{
    SetWithCreate(name, sizeH, sizeV, allDivNum, endTime);
}

GraphArray::GraphArray(std::string name
    , const int size, const int endTime)
    : _graphPtr(nullptr)
    , _speed(1)
    , _index(0)
    , _currentTime(0)
    , _endTime(30)
    , _isLoop(true)
    , _isPlaying(true)
    , _isCreatedInside(false)
    , _hasEnd(false)
{
    SetWithCreate(name, size, endTime);
}


GraphArray::GraphArray(std::string name)
    : _graphPtr(nullptr)
    , _speed(1)
    , _index(0)
    , _currentTime(0)
    , _endTime(30)
    , _isLoop(true)
    , _isPlaying(true)
    , _isCreatedInside(false)
    , _hasEnd(false)
{
    SetWithCreate(name);
}

GraphArray::~GraphArray()
{
    //配列に一時生成された画像リソースを削除
    for (auto handle : _handleArray)
    {
        DeleteGraph(handle);
    }

    //このクラス内でGraphクラスが作られた場合、ここでGraphクラスを削除
    if (_isCreatedInside)
    {
        if (_graphPtr == nullptr)
            return;

        delete _graphPtr;

        _graphPtr = nullptr;
        _isCreatedInside = false;
    }
}

void GraphArray::Set(Sprite *arg_graph
    , const int divNumH, const int divNumV
    , const int sizeH, const int sizeV
    , const int allDivNum, const int endTime)
{
    _graphPtr = arg_graph;
    _endTime = endTime;

    CreateArray(divNumH, divNumV, sizeH, sizeV, allDivNum);
}

void GraphArray::Set(Sprite *arg_graph, const int sizeH, const int sizeV
    , const int allDivNum, const int endTime)
{
    _graphPtr = arg_graph;
    _endTime = endTime;

    Vector2D graphSize = _graphPtr->GetSize();

    //元画像と指定分割サイズから分割数を算出
    int divNumH = graphSize._x / sizeH;
    int divNumV = graphSize._y / sizeV;

    CreateArray(divNumH, divNumV, sizeH, sizeV, allDivNum);
}

Sprite* GraphArray::SetWithCreate(std::string name
    , const int divNumH, const int divNumV
    , const int sizeH, const int sizeV
    , const int allDivNum, const int endTime)
{
    _graphPtr = new Sprite(std::move(name));
    _endTime = endTime;

    CreateArray(divNumH, divNumV, sizeH, sizeV, allDivNum);

    _isCreatedInside = true;

    return _graphPtr;
}

Sprite* GraphArray::SetWithCreate(std::string name
    , const int sizeH, const int sizeV
    , const int allDivNum, const int endTime)
{
    _graphPtr = new Sprite(std::move(name));
    _endTime = endTime;

    Vector2D graphSize = _graphPtr->GetSize();

    //元画像と指定分割サイズから分割数を算出
    int divNumH = graphSize._x / sizeH;
    int divNumV = graphSize._y / sizeV;

    CreateArray(divNumH, divNumV, sizeH, sizeV, allDivNum);

    _isCreatedInside = true;

    return _graphPtr;
}

//縦と横の分割幅が同じで一列に並んでいる場合
//画像を生成して、そこからアニメーションも生成
Sprite* GraphArray::SetWithCreate(std::string name
    , const int size, const int endTime)
{
    _graphPtr = new Sprite(std::move(name));
    _endTime = endTime;

    Vector2D graphSize = _graphPtr->GetSize();

    //元画像と指定分割サイズから分割数を算出
    int divNumH = graphSize._x / size;
    int divNumV = graphSize._y / size;

    CreateArray(divNumH, divNumV, size, size, divNumH * divNumV);

    _isCreatedInside = true;

    return _graphPtr;
}

Sprite* GraphArray::SetWithCreate(std::string name)
{
    _graphPtr = new Sprite(std::move(name));
    _endTime = 1;

    Vector2D graphSize = _graphPtr->GetSize();

    CreateArray(1, 1, graphSize._x, graphSize._y, 1);

    _isCreatedInside = true;

    return _graphPtr;
}

void GraphArray::CreateArray(const int divNumH, const int divNumV
    , const int sizeH, const int sizeV, const int allDivNum)
{
    Vector2D upperLeft;

    //描画している回数
    int drawCellH = 0;
    int drawCellV = 0;

    for (int i = 0; i < allDivNum; i++)
    {
        upperLeft._x = drawCellH * sizeH;
        upperLeft._y = drawCellV * sizeV;

        int handle = DerivationGraph(
            static_cast<int>(upperLeft._x),
            static_cast<int>(upperLeft._y),
            sizeH, sizeV,
            _graphPtr->GetResourceHandle()
            );

        _handleArray.push_back(handle);

        drawCellH++;

        if (divNumH == drawCellH)
        {
            drawCellH = 0;
            drawCellV++;
        }
    }

    _singleSize = Vector2D(sizeH, sizeV);

    //画像に設定
    _graphPtr->GetTexturePtr().lock()->_handle = _handleArray[_index];
}

void GraphArray::Update()
{
    assert(_handleArray.size() != 0
        && "画像配列に指定された画像が無効です");

    if (!_isPlaying)
        return;

    _hasEnd = false;

    _currentTime += _speed;

    if (_endTime <= _currentTime)
    {
        _hasEnd = true;
        if (_isLoop)
        {
            _currentTime = 0;
        }
        else
        {
            _isPlaying = false;
            if (_handleArray.size() < 1)
                _index = 0;
            else
                _index = _handleArray.size() - 1;

            SetIndex(_index);
            return;
        }
    }

    //今の時間からインデクスを算出し
    _index = _currentTime / (_endTime / static_cast<int>(_handleArray.size()));

    //範囲外参照にならないようにして
    _index = min(_handleArray.size() - 1, max(0, _index));

    //画像に設定
    _graphPtr->GetTexturePtr().lock()->_handle = _handleArray[_index];
}