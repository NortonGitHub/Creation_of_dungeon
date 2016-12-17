#pragma once
#include "SceneBase.h"
#include <vector>

//構造体の宣言　実態は下に
struct Point;
struct Road;
struct RoadTurnPoint;



class Map :
    public SceneBase
{
private:

    int nowMyMapNum;  //現在いるマップの番号
    int nowMyStageNum;    //現在いるステージ　中継地点の場合は-1、移動中は-2
    int nowMyPointNum;    //現在いるポイント　ステージとは違う番号
    bool isMyMove;    //移動しているかどうか、移動中はtrue、移動していなければfalse
    
    
    std::vector<RoadTurnPoint> targetTurnPointList;   //移動する場合に移動先までの道のうち、曲がる座標を順番に指定し、ここにプッシュする
    int finishPointNum; //移動した場合の最終目標ポイントの番号 移動していなければ-1

    double myX; //現在のX座標
    double myY; //現在のY座標
    double mySpeed; //自分の移動スピード

    double myVx;    //x方向の速度
    double myVy;    //y方向の速度

    int myMoveDirection;    //移動するときの方向を表す　方向はnowMapRoadListのstartPoint→endPointなら1、endPoint→startPointなら2、移動していない場合は-1、start

    const double pointR = 20;   //ポイントの描写する円の半径　デバック用　多分消える


    std::vector<Point> nowMapPointList;   //現在いるマップのポイントのリスト
    std::vector<Road> nowMapRoadList;   //現在いるマップの道のリスト

    bool checkMoveReach();

public:
    Map();
    ~Map();

    SceneBase* Update();
    void Draw();

    void Init();    //初期化
    void Moving();  //動いているときの処理
    void KeyJudge();//キー判定
    void setNowMapPointList();
    void setNowMapRoadList();
    bool myPointSet(int PointNum);  //自分のポイントを設定する　マップ移動はしない　失敗（移動するポイントが別のマップ等）したらfalse、成功でtrueを返す
    int PointSearch(int pointNum);  //ポイント番号からそのポイント番号の一致するポイント情報のnowMapPointListの配列番号を返す　違うマップのポイントの場合失敗する
    int RoadSearch(int startPointNum,int endPointNum);   //二つのポイント番号からそのポイント番号を結ぶ道の情報のnowMapRoadListの配列番号を返す　違うマップの道の場合失敗する
    
    
    int MoveDirection(int startPointNum, int endPointNum); //二つのポイント番号からそのポイント番号のうち、nowMapRoadListのstartからendへの方向を返す　関数の引数であるstartPointNum→endPointNumの方向に移動する際、nowMapRoadListでstartPoint→endPointなら1、endPoint→startPointなら2を返す　違うマップの道の場合失敗する
};




//使う構造体を以下に
struct Point    //ポイントの情報を表す　ポイントは移動し、止まることが出来る場所
{

    int mapNum;     //ポイントがあるマップの番号
    int pointNum;   //ポイント番号　ステージとは違い中継地点にも割り振られる番号
    int stageNum;   //ステージ番号　中継地点の場合は-1
    
    int mapMove_mapNum;    //マップを移動するポイントの場合、移動先のマップ番号を入れる。マップを移動しない場合-1
    int mapMove_pointNum;    //マップを移動するポイントの場合、移動先のポイント番号を入れる。マップを移動しない場合-1
    int mapMove_movePointNum;   //マップを移動するポイントの場合、マップ移動後、すぐに移動するポイント番号を入れる。マップを移動しない場合-1

    double x;   //ポイントのX位置
    double y;   //ポイントのY位置

    int upMovePoint; //上キーを押した場合に移動するポイントの番号　どこにも繋がっていなければ-1
    int downMovePoint; //上キーを押した場合に移動するポイントの番号　どこにも繋がっていなければ-1
    int leftMovePoint; //上キーを押した場合に移動するポイントの番号　どこにも繋がっていなければ-1
    int rightMovePoint; //上キーを押した場合に移動するポイントの番号　どこにも繋がっていなければ-1



};

struct Road    //道の情報を表す　道は移動することが出来る道　道の情報はは一つの道につき一種類ある（１番→２番と１番←２番は一緒） 全く同じ場所から始まり、全く同じ場所で終わる道は存在しないと仮定する
{
    int mapNum; //道があるマップの番号　将来はポイント情報から自動生成するようにしたい

    int roadNum;   //ロード番号　道番号

    int startPointNum;  //繋がっているポイント番号のうちの片方　分岐の情報は、このstartPointNumのポイントから順番に曲がる場所の情報を格納する
    int endPointNum;  //繋がっているポイント番号のうちの片方　分岐の情報は、このendPointNumのポイントから逆の順番に曲がる場所の情報を格納する

    std::vector<RoadTurnPoint> roadTurnPoint;   //道の曲がる場所の座標　startPointNumから順番に曲がる場所を格納

};


struct RoadTurnPoint  //道の曲がる場所の座標の情報を表す
{
    double x;   //曲がる場所のX座標
    double y;   //曲がる場所のY座標
};