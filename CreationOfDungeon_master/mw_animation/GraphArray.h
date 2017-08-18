#ifndef GRAPH_ARRAY_H
#define GRAPH_ARRAY_H

#include "../cd_666s/Render/Sprite.h"
#include <vector>

/*
画像を特定の感覚で区切り
配列で管理する Spriteクラスの拡張モジュール
*/

class GraphArray
{
    friend class Animator;
    typedef int Handle;
    typedef std::pair<Vector2D, Vector2D> PixelInset;

public:
    GraphArray();

    GraphArray(Sprite *arg_graph
        , const int divNumH, const int divNumV
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    GraphArray(Sprite *arg_graph
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    GraphArray(std::string name
        , const int divNumH, const int divNumV
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    GraphArray(std::string name
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    //縦と横の分割幅が同じで一列に並んでいる場合
    GraphArray(std::string name
        , const int size, const int endTime);

    //1x1しかない場合
    GraphArray(std::string name);

    ~GraphArray();

    //画像を設定してそれを分割してアニメーション生成
    void Set(Sprite *arg_graph
        , const int divNumH, const int divNumV
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    //画像を設定してそれを分割してアニメーション生成
    void Set(Sprite *arg_graph, const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    //画像を生成して、そこからアニメーションも生成
    Sprite* SetWithCreate(std::string name
        , const int divNumH, const int divNumV
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    //画像を生成して、そこからアニメーションも生成
    Sprite* SetWithCreate(std::string name
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    //画像を生成して、そこからアニメーションも生成
    //縦と横の分割幅が同じで一列に並んでいる場合
    Sprite* SetWithCreate(std::string name
        , const int size, const int endTime);

    //画像を生成して、そこからアニメーションも生成
    //1x1しかない場合
    Sprite* SetWithCreate(std::string name);


    void SetIndex(int index)
    {
        _index = index;
        _currentTime = index * (_endTime / _handleArray.size());
        _graphPtr->GetTexturePtr().lock()->_handle = _handleArray[_index];
    }
    void SetSpeed(int speed) { _speed = speed; }

    void SetCurrentTime(int time)
    {
        if (time < 0 || _endTime < time)
            return;

        _currentTime = time;
    }

    Vector2D GetSingleSize() const { return _singleSize; }

    Sprite* GetGraphPtr() const { return _graphPtr; }

    //アニメーションをループさせるときはこれを呼ぶ
    void Update();

    bool HasEndedUp() const { return (_hasEnd); }

    //これを有効/無効にするとUpdateが動く/動かなくなる
    bool _isLoop;

    bool _isPlaying;

private:

    void CreateArray(const int divNumH, const int divNumV
        , const int sizeH, const int sizeV, const int allDivNum);

    //画像を分割して保持する
    std::vector<Handle> _handleArray;

    //1枚当たりの画像サイズ
    Vector2D _singleSize;

    //画面に表示する画像本体
    Sprite *_graphPtr;

    //このクラス内で画像が生成されたかどうか
    bool _isCreatedInside;

    //ループ終わりの時間(フレーム指定)
    int _endTime;

    //現在の時間(フレーム指定)
    int _currentTime;

    //時間が増える倍率(通常は1)
    int _speed;

    //現在表示するインデクス
    int _index;

    bool _hasEnd;
};

#endif