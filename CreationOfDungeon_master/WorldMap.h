#pragma once
#include "SceneBase.h"
#include "cd_666s/Sound/Sound.h"
#include <vector>

//構造体の宣言　実態は下に
struct Point;
struct PointConnect;


class WorldMap :
    public SceneBase
{
private:
    
    int nowMyStageNum;    //現在いるステージ　中継地点の場合は-1、移動中は-2
    int nowMyPointNum;    //現在いるポイント　ステージとは違う番号
    bool isMyMove;    //移動しているかどうか、移動中はtrue、移動していなければfalse
    
    int finishPointNum; //移動した場合の最終目標ポイントの番号 移動していなければ-1

    double myX; //現在のX座標
    double myY; //現在のY座標
    double mySpeed; //自分の移動スピード

    double myVx;    //x方向の速度
    double myVy;    //y方向の速度


    const double pointR = 20;   //ポイントの描写する円の半径　デバック用　多分消える


    std::vector<Point> MapPointList;   //ポイントのリスト

    bool checkMoveReach();



    int Area1Gr;
    int blend;
    int blendFlag;

    bool isPause;
    bool keyFlag;
    bool clickFlag;

    int stageNum;

    std::string class_name;

    Sound _bgm;

public:
    WorldMap();
    ~WorldMap();


    std::string GetClassNameData() const {
        return class_name;
    }

    SceneBase* Update();
    SceneBase* Update(UIManager _ui) override;
    void Draw() override;

    void Init();    //初期化
    void Moving();  //動いているときの処理
    void KeyJudge();//キー判定
    bool myPointSet(int PointNum);  //自分のポイントを設定する　マップ移動はしない　失敗（移動するポイントが別のマップ等）したらfalse、成功でtrueを返す
    int PointSearch(int pointNum);  //ポイント番号からそのポイント番号の一致するポイント情報のnowMapPointListの配列番号を返す　ポイントの場合失敗する
    int RoadSearch(int startPointNum,int endPointNum);   //二つのポイント番号からそのポイント番号を結ぶ道の情報のnowMapRoadListの配列番号を返す　違うマップの道の場合失敗する
    void setNowMapPointList();

    void setNowMapRoadList();
    int MoveDirection(int startPointNum, int endPointNum);

    int ClickCheckBox(int x, int y, int rx, int ry);    //クリックしたときの判定（四角形）
    int ClickCheckCircle(int x, int y, int r);    //クリックしたときの判定（円形）

};




//使う構造体を以下に
struct Point    //ポイントの情報を表す　ポイントは移動し、止まることが出来る場所
{

    int AreaNum;

    int pointNum;   //ポイント番号　ステージとは違い中継地点にも割り振られる番号
    int stageNum;   //ステージ番号　中継地点の場合は-1
    

    double x;   //ポイントのX位置
    double y;   //ポイントのY位置




    bool isStayPoint;   //止まれるポイントかどうか



};


struct PointConnect {

    int connectPointNum;    //繋がっているポイント番号
    int PointCost;          //そのポイントとの距離


};
