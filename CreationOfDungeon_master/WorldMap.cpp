#include "WorldMap.h"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <typeinfo>
#include "DxLib.h"
#include "Game.h"
#include "Title.h"
#include "EditMap.h"
#include "ShopScene.h"
#include <regex>
#include "cd_666s\Utility\CSVReader.h"
#include "cd_666s/DebugDraw.h"


WorldMap::WorldMap()
	: class_name("world_map")
	, _bgm("resource/sound/world1.wav", true)
{

	Init();
	_bgm.Play();

}



WorldMap::~WorldMap()
{

}

SceneBase* WorldMap::Update(UIManager _ui)
{
	//_ui.Update();
	return Update();
}


SceneBase * WorldMap::Update()
{

	char Buf[256];

	GetHitKeyStateAll(Buf);

	if (Buf[KEY_INPUT_ESCAPE] == 1)
	{
		if (keyFlag == false) {
			isPause = !isPause;
			keyFlag = true;
		}

	}
	else {
		keyFlag = false;
	}

	int mx, my;

	GetMousePoint(&mx, &my);

	if (isPause == false) {
		/*
		if (blendFlag == 0) {
			blend += 10;
		}
		else {
			blend -= 10;
		}

		if (blend > 255) {
			blend = 255;
			blendFlag = 1;
		}
		if (blend < 0) {
			blend = 0;
			blendFlag = 0;
		}
		*/

		if (movePointList.empty() == true) {

			if (!worldMap_Menu->GetIsActive()) {

				for (int i = 0; i < nowAreaPointList.size(); i++) {

					if (nowAreaPointList[i]->isPoint == 1 && nowAreaPointList[i]->isStayPoint == 1) {

						int hit = 0;

						if (nowAreaPointList[i]->hitType == 0) {

							hit += ClickCheckCircle(nowAreaPointList[i]->x, nowAreaPointList[i]->y, pointR);
							hit += ClickCheckCircle(nowAreaPointList[i]->x - 5, nowAreaPointList[i]->y, pointR - 1);
							hit += ClickCheckCircle(nowAreaPointList[i]->x - 5 - 4, nowAreaPointList[i]->y, pointR - 2);
							hit += ClickCheckCircle(nowAreaPointList[i]->x - 5 - 4 - 3, nowAreaPointList[i]->y, pointR - 3);
							hit += ClickCheckCircle(nowAreaPointList[i]->x + 5, nowAreaPointList[i]->y, pointR - 1);
							hit += ClickCheckCircle(nowAreaPointList[i]->x + 5 + 4, nowAreaPointList[i]->y, pointR - 2);
							hit += ClickCheckCircle(nowAreaPointList[i]->x + 5 + 4 + 3, nowAreaPointList[i]->y, pointR - 3);

						}
						else if (nowAreaPointList[i]->hitType == 100) {
							if (typeid(*nowAreaPointList[i]) == typeid(AreaConnectPoint)) {
								hit += ClickCheckCircle(std::dynamic_pointer_cast<AreaConnectPoint>(nowAreaPointList[i])->buttonX, std::dynamic_pointer_cast<AreaConnectPoint>(nowAreaPointList[i])->buttonY, 15);
							}
						}


						if (hit >= 1) {

							if (nowMyPointNum == nowAreaPointList[i]->pointNum) {
								if (nowAreaPointList[i]->stageNum.find("shop") != std::string::npos) {
									//std::regex regex("shop");
									//std::string shopNum = std::regex_replace(nowAreaPointList[i]->stageNum, regex, "");
									stageNum = nowAreaPointList[i]->stageNum;
									return new ShopScene(stageNum);
								}
								else {
									stageNum = nowAreaPointList[i]->stageNum;
									//return new Game(stageNum);

									worldMap_Menu.reset();

									return new EditMap(std::to_string(nowMyAreaNum), stageNum);
								}
							}
							else {
								searchPath(nowAreaPointList[i]->pointNum);
								//nowMyPointNum = nowAreaPointList[i]->pointNum;
							}
						}

					}
				}

				if (ClickCheck(_shopIcon.GetPosition(), _shopIcon.GetTexturePtr().lock()->GetBaseSize())) {
					return new ShopScene("shop1");
				}


			}

			

			if (ClickCheck(_MenuButton.GetPosition(), _MenuButton.GetTexturePtr().lock()->GetBaseSize())) {
				worldMap_Menu->SetActive(!worldMap_Menu->GetIsActive());
			}


		}
		else {
			movePoint();
		}







	}
	else {

		//ここから「タイトルに戻る」のクリック判定

		int hit = 0;

		hit += ClickCheckBox(530, 300, 30 * 7 + 15, 30);

		if (hit >= 1) {
			return new Title();
		}

		//ここまで

		//ここから「ゲームを再開する」のクリック判定

		hit = 0;

		hit += ClickCheckBox(530, 400, 30 * 8 + 15, 30);

		if (hit >= 1) {
			isPause = !isPause;
		}

		//ここまで

	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{

		if (clickFlag == false) {
			clickFlag = true;
		}

	}
	else {
		clickFlag = false;
	}


	worldMap_Menu->Update();


	printfDx("x:%d y:%d", mx, my);

	return this;
}

void WorldMap::Draw()
{

	clsDx();


	if (isPause == false) {

		DrawMap();

		worldMap_Menu->Draw();

	}
	else {

		DrawMap();
		worldMap_Menu->Draw();

		Debug::DrawRectWithPoint(0, 0, 1280, 720, Color4(0, 0, 0, 0.8), true);

		SetFontSize(60);
		Debug::DrawString(Vector2D(550, 100), "ポーズ", Color4(1, 1, 1, 1), 60);

		SetFontSize(30);
		Debug::DrawString(Vector2D(530, 300), "タイトルに戻る", Color4(1, 1, 1, 1), 30);
		Debug::DrawRectWithPoint(530, 300, 530 + 30 * 7 + 15, 300 + 30, Color4(1, 1, 1, 1), false);

		Debug::DrawString(Vector2D(530, 400), "ゲームを再開する", Color4(1, 1, 1, 1), 30);
		Debug::DrawRectWithPoint(530, 400, 530 + 30 * 8 + 15, 400 + 30, Color4(1, 1, 1, 1), false);



	}



}



void WorldMap::Init() {


	/*

	finishPointNum = -1;

	isMyMove = false;

	myMoveDirection = -1;

	myVx = 0;

	myVy = 0;


	myPointSet(1);

	mySpeed = 3;

	*/


	AreaGrBuffer[0] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
	/*
	AreaGrBuffer[1] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
	AreaGrBuffer[2] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
	AreaGrBuffer[3] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
	AreaGrBuffer[4] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
	AreaGrBuffer[5] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
	AreaGrBuffer[6] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
	AreaGrBuffer[7] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
	*/
	AreaGr = &AreaGrBuffer[0];

	std::string fileName = "resource/graph/worldMap//DevilGirlMini/DevilGirl";

	_animator.AddAnimation("front", std::make_shared<GraphArray>(fileName + "Front.png", 32, 48));
	_animator.AddAnimation("right", std::make_shared<GraphArray>(fileName + "Right.png", 32, 48));
	_animator.AddAnimation("left", std::make_shared<GraphArray>(fileName + "Left.png", 32, 48));
	_animator.AddAnimation("back", std::make_shared<GraphArray>(fileName + "Back.png", 32, 48));

	auto currentGraph = _animator.GetCurrentGraph();
	currentGraph->SetDisplayMode(true);
	_animator.Transform([&](GraphArray* animation)
	{
		animation->GetGraphPtr()->SetPosition(Vector2D(0, 0));
		animation->GetGraphPtr()->SetRenderType(Texture2D::RenderType::UI);
	});


	blend = 0;
	blendFlag = 0;

	isPause = false;
	keyFlag = false;

	clickFlag = false;

	nowMyAreaNum = 1;
	nowMyPointNum = 1;



	mySpeed = 0.0;
	mySpeedFrameNum = 90.0;

	myVx = 0.0;
	myVy = 0.0;

	debugFlag = false;

	setNowAreaPointList();

	setNowRoadConnect();

	movePointList.clear();

	AreaGr = &AreaGrBuffer[nowMyAreaNum - 1];

	CSVReader reader;

	fileName = "csv/WorldMap/ShopPosition.csv";
	std::vector<std::string> Array;
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, Array, 1);

	_shopIcon.Load("resource/graph/worldMap/IconShop.png");
	_shopIcon.SetPosition(Vector2D(std::stoi(Array[0]), std::stoi(Array[1])));
	_shopIcon.SetPriority(Sprite::Priority::UI);


	_MenuButton.Load("resource/graph/worldMap/menuButton.png");
	_MenuButton.SetPosition(Vector2D(1100, 10));
	_MenuButton.SetPriority(static_cast<int>(Sprite::Priority::UI) + 1);

	worldMap_Menu = std::make_shared<WorldMap_Menu>();

	worldMap_Menu->SetActive(false);

}


void WorldMap::DrawMap() {

	DrawGraph(0, 0, *AreaGr, TRUE);


	for (int i = 0; i < nowRoadConnect.size(); i++) {

		int road1 = PointSearch(nowRoadConnect[i]->road[0]);
		int road2 = PointSearch(nowRoadConnect[i]->road[1]);

		DrawLine(nowAreaPointList[road1]->x, nowAreaPointList[road1]->y, nowAreaPointList[road2]->x, nowAreaPointList[road2]->y, GetColor(243, 237, 226), 15);

	}


	for (int i = 0; i < nowAreaPointList.size(); i++) {

		if (nowAreaPointList[i]->isPoint == 1) {

			if (nowAreaPointList[i]->isStayPoint == 1) {
				if (typeid(*nowAreaPointList[i]) == typeid(AreaConnectPoint)) {
					DrawCircle(std::dynamic_pointer_cast<AreaConnectPoint>(nowAreaPointList[i])->buttonX, std::dynamic_pointer_cast<AreaConnectPoint>(nowAreaPointList[i])->buttonY, 15, GetColor(255, 0, 0), TRUE);
				}
				else {

					/*
					DrawCircle(nowAreaPointList[i]->x, nowAreaPointList[i]->y, pointR, GetColor(255, 0, 0), TRUE);
					DrawCircle(nowAreaPointList[i]->x - 5, nowAreaPointList[i]->y, pointR - 1, GetColor(255, 0, 0), TRUE);
					DrawCircle(nowAreaPointList[i]->x - 5 - 4, nowAreaPointList[i]->y, pointR - 2, GetColor(255, 0, 0), TRUE);
					DrawCircle(nowAreaPointList[i]->x - 5 - 4 - 3, nowAreaPointList[i]->y, pointR - 3, GetColor(255, 0, 0), TRUE);
					DrawCircle(nowAreaPointList[i]->x + 5, nowAreaPointList[i]->y, pointR - 1, GetColor(255, 0, 0), TRUE);
					DrawCircle(nowAreaPointList[i]->x + 5 + 4, nowAreaPointList[i]->y, pointR - 2, GetColor(255, 0, 0), TRUE);
					DrawCircle(nowAreaPointList[i]->x + 5 + 4 + 3, nowAreaPointList[i]->y, pointR - 3, GetColor(255, 0, 0), TRUE);
					*/
				}
			}
			else {
				DrawCircle(nowAreaPointList[i]->x, nowAreaPointList[i]->y, pointR, GetColor(255, 0, 0), TRUE);
			}

		}

		if (nowAreaPointList[i]->pointNum == nowMyPointNum) {
			myX = nowAreaPointList[i]->x;
			myY = nowAreaPointList[i]->y;
		}

	}


	if (nowMyPointNum != -1 || (myVx == 0 && myVy == 0)) {
		_animator.SwitchWithReset("front");
	}
	else if (fabs(myVx) > fabs(myVy)) {
		if (myVx > 0) {
			_animator.SwitchWithReset("right");
		}
		else {
			_animator.SwitchWithReset("left");
		}
	}
	else {
		if (myVy > 0) {
			_animator.SwitchWithReset("front");
		}
		else {
			_animator.SwitchWithReset("back");
		}
	}

	_animator.Transform([&](GraphArray* animation)
	{
		animation->GetGraphPtr()->SetPosition(Vector2D(myX - animation->GetSingleSize()._x / 2, myY - animation->GetSingleSize()._y / 2 - 12));
	});

	_animator.Update();


}


bool WorldMap::myPointSet_PointNum(int PointNum) {

	std::vector<Point>::iterator itr;


	for (auto itr = nowAreaPointList.begin(); itr != nowAreaPointList.end(); itr++) {

		if ((*itr)->pointNum == PointNum) {
			nowMyPointNum = (*itr)->pointNum;
			myX = (*itr)->x;
			myY = (*itr)->y;
			return true;
		}

	}

	return false;


}

bool WorldMap::myPointSet_StageNum(std::string StageNum) {

	std::vector<Point>::iterator itr;


	for (auto itr = nowAreaPointList.begin(); itr != nowAreaPointList.end(); itr++) {

		if ((*itr)->stageNum == StageNum) {
			nowMyPointNum = (*itr)->pointNum;
			myX = (*itr)->x;
			myY = (*itr)->y;
			return true;
		}

	}

	return false;


}


int WorldMap::PointSearch(int pointNum) {


	for (int vec = 0; vec < nowAreaPointList.size(); vec++) {

		if (nowAreaPointList[vec]->pointNum == pointNum) {
			return vec;
		}

	}



	return -1;



}






bool WorldMap::checkMoveReach(std::weak_ptr<WorldMap::Point> point) {



	double margin = 5.0;

	if (point.lock()->x - margin <= myX && point.lock()->x + margin >= myX && point.lock()->y - margin <= myY && point.lock()->y + margin >= myY) {

		myX = point.lock()->x;
		myY = point.lock()->y;

		return true;
	}



	return false;



}

void WorldMap::setNowAreaPointList() {

	//nowAreaPointList.reserve(100);

	//ここからポイント情報の読み込み
	//ファイルの読み込み

	nowAreaPointList.clear();

	std::string path = "csv/WorldMap/Area" + std::to_string(nowMyAreaNum) + ".csv";

	if (debugFlag == true) {
		path = "csv/WorldMap/Area_debug.csv";
	}

	std::ifstream ifs(path);
	if (ifs.fail()) {
		printfDx("fail\n");
		return;
	}

	int dataType = 0;   //読み込むデータ　ポイント情報か、エリア移動か

	//csvファイルを1行ずつ読み込む
	std::string str;
	while (getline(ifs, str)) {
		std::string::size_type index = str.find("#");  // "#"を検索
													   //"#"が入っていた行は飛ばす
		if (index != std::string::npos) {
			continue;
		}

		index = str.find("end");  // "end"を検索

		if (index != std::string::npos) {
			dataType++;
			continue;
		}

		std::string token;
		std::istringstream stream(str);

		std::shared_ptr<Point> point = std::make_shared<Point>();

		std::shared_ptr<AreaConnectPoint> areaConnectPoint = std::make_shared<AreaConnectPoint>();

		int num = 0;
		//1行のうち、文字列とコンマを分割する
		while (getline(stream, token, ',')) {

			if (dataType == 0) {

				switch (num) {
				case 0:
					point->pointNum = stoi(token);
					break;
				case 1:
					point->stageNum = token;
					break;
				case 2:
					point->x = stoi(token);
					break;
				case 3:
					point->y = stoi(token);
					break;
				case 4:
					point->hitType = stoi(token);
					break;
				case 5:
					point->isStayPoint = stoi(token);
					break;

				default:

					if (num > 5) {
						PointConnect* pc = new PointConnect();
						pc->connectPointNum = stoi(token);
						pc->PointCost = -1;
						point->pointConect.push_back(pc);
					}

					break;
				}
			}
			else {

				switch (num) {
				case 0:
					areaConnectPoint->pointNum = stoi(token);
					break;
				case 1:
					areaConnectPoint->moveArea = stoi(token);
					break;
				case 2:
					areaConnectPoint->buttonX = stoi(token);
					break;
				case 3:
					areaConnectPoint->buttonY = stoi(token);
					break;
				case 4:
					areaConnectPoint->x = stoi(token);
					break;
				case 5:
					areaConnectPoint->y = stoi(token);
					break;
				case 6:
					areaConnectPoint->firstMovePoint = stoi(token);
					break;
				case 7:
					areaConnectPoint->firstX = stoi(token);
					break;
				case 8:
					areaConnectPoint->firstY = stoi(token);
					break;

				default:

					if (num > 8) {
						PointConnect* pc = new PointConnect();
						pc->connectPointNum = stoi(token);
						pc->PointCost = -1;
						areaConnectPoint->pointConect.push_back(pc);
					}

					break;

				}
			}
			num++;
		}

		if (num != -1 && dataType == 0) {
			point->isPoint = 1;
			point->AreaNum = nowMyAreaNum;
			point->_stageIcon = std::make_shared<Sprite>();
			point->_stageIcon->Load("resource/graph/worldMap/" + GetFieldType(point->stageNum));
			point->_stageIcon->SetPosition(Vector2D(point->x - point->_stageIcon->GetTexturePtr().lock()->GetBaseSize()._x / 2, point->y - point->_stageIcon->GetTexturePtr().lock()->GetBaseSize()._y / 2 - 80));
			point->_stageIcon->SetPriority(Sprite::Priority::UI);
			point->_stagePoint = std::make_shared<Sprite>();
			point->_stagePoint->Load("resource/graph/worldMap/Mark_1.png");
			point->_stagePoint->SetPosition(Vector2D(point->x - point->_stagePoint->GetTexturePtr().lock()->GetBaseSize()._x / 2, point->y - point->_stagePoint->GetTexturePtr().lock()->GetBaseSize()._y / 2));
			point->_stagePoint->SetPriority(Sprite::Priority::FIELD_BASE);
			nowAreaPointList.push_back(point);
		}
		else if (num != -1 && dataType == 1) {
			areaConnectPoint->AreaNum = nowMyAreaNum;
			areaConnectPoint->hitType = 100;
			areaConnectPoint->isPoint = 1;
			areaConnectPoint->isStayPoint = 1;
			areaConnectPoint->stageNum = "";
			areaConnectPoint->_stageIcon = nullptr;
			areaConnectPoint->_stagePoint = std::make_shared<Sprite>();
			areaConnectPoint->_stagePoint->Load("resource/graph/worldMap/Mark_1.png");
			areaConnectPoint->_stagePoint->SetPosition(Vector2D(areaConnectPoint->x - areaConnectPoint->_stagePoint->GetTexturePtr().lock()->GetBaseSize()._x / 2, areaConnectPoint->y - areaConnectPoint->_stagePoint->GetTexturePtr().lock()->GetBaseSize()._y / 2));
			areaConnectPoint->_stagePoint->SetPriority(Sprite::Priority::FIELD_BASE);
			nowAreaPointList.push_back(areaConnectPoint);
		}

	}


	setPointCost();


}

void WorldMap::setNowRoadConnect() {

	nowRoadConnect.clear();

	for (int i = 0; i < nowAreaPointList.size(); i++) {

		if (nowAreaPointList[i]->isPoint == 1) {

			for (int j = 0; j < nowAreaPointList[i]->pointConect.size(); j++) {

				bool isConnect = true;

				for (int n = 0; n < nowRoadConnect.size(); n++) {

					for (int b = 0; b < 2; b++) {
						if (nowRoadConnect[n]->road[(b + 2) % 2] == nowAreaPointList[i]->pointNum && nowRoadConnect[n]->road[(b + 1 + 2) % 2] == nowAreaPointList[i]->pointConect[j]->connectPointNum) {
							isConnect = false;
							break;
						}
					}
					if (isConnect == false) {
						break;
					}

				}

				if (isConnect == true) {
					RoadConnect* rc = new RoadConnect();
					rc->road[0] = nowAreaPointList[i]->pointNum;
					rc->road[1] = nowAreaPointList[i]->pointConect[j]->connectPointNum;
					nowRoadConnect.push_back(rc);
				}

			}



		}


	}
}

void WorldMap::setPointCost() {

	for (int i = 0; i < nowAreaPointList.size(); i++) {
		for (int j = 0; j < nowAreaPointList[i]->pointConect.size(); j++) {

			if (nowAreaPointList[i]->pointConect[j]->PointCost == -1) {

				std::weak_ptr<Point> tempPoint = getPoint(nowAreaPointList[i]->pointConect[j]->connectPointNum);
				nowAreaPointList[i]->pointConect[j]->PointCost = std::hypot(nowAreaPointList[i]->x - tempPoint.lock()->x, nowAreaPointList[i]->y - tempPoint.lock()->y);

				for (int n = 0; n < tempPoint.lock()->pointConect.size(); n++) {
					if (tempPoint.lock()->pointConect[n]->connectPointNum == nowAreaPointList[i]->pointNum) {
						tempPoint.lock()->pointConect[n]->PointCost = nowAreaPointList[i]->pointConect[j]->PointCost;
					}
				}

			}

		}
	}

}



int WorldMap::ClickCheckBox(int x, int y, int rx, int ry) {

	int mx, my;

	GetMousePoint(&mx, &my);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{

		if (clickFlag == false) {
			if (mx > x && mx < x + rx && my > y && my < y + ry) {
				return 1;
			}
		}

	}

	return 0;

}


int WorldMap::ClickCheckCircle(int x, int y, int r) {

	int mx, my;

	GetMousePoint(&mx, &my);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{

		if (clickFlag == false) {
			if (pow((x - mx)*(x - mx) + (y - my)*(y - my), 0.5) < r) {
				return 1;
			}
		}

	}

	return 0;

}




std::weak_ptr<WorldMap::Point> WorldMap::getPoint(int pointNum) {

	for (int i = 0; i < nowAreaPointList.size(); i++) {
		if (nowAreaPointList[i]->pointNum == pointNum) {
			return nowAreaPointList[i];
		}
	}

	return shared_ptr<WorldMap::Point>();

}



void WorldMap::movePoint() {

	std::weak_ptr<WorldMap::Point> point;

	point = getPoint(movePointList[0]);

	bool isArrive = false;

	isArrive = checkMoveReach(point);

	if (isArrive == true) {

		if (typeid(point.lock()) == typeid(AreaConnectPoint)) {

			std::weak_ptr<WorldMap::AreaConnectPoint> areaPoint = std::dynamic_pointer_cast<AreaConnectPoint>(point.lock());

			setAreaNum(areaPoint.lock()->moveArea);

			myX = areaPoint.lock()->firstX;
			myY = areaPoint.lock()->firstY;

			movePointList.push_back(areaPoint.lock()->firstMovePoint);


		}
		else {
			movePointList.erase(movePointList.begin());

			if (movePointList.empty()) {
				nowMyPointNum = point.lock()->pointNum;
				mySpeed = 0.0;
				myVx = 0.0;
				myVy = 0.0;
				_animator.GetCurrentAnimation()->SetCurrentTime(0);
			}
		}


	}
	else {

		//mySpeed = mySpeedMax;

		double radian = 0.0;

		radian = atan2(point.lock()->y - myY, point.lock()->x - myX);

		myVx = cos(radian) * mySpeed;
		myVy = sin(radian) * mySpeed;

		if (CheckLineOfPoint(Vector2D(point.lock()->x, point.lock()->y), Vector2D(myX, myY), Vector2D(myX + myVx, myY + myVy))) {
			myX = point.lock()->x;
			myY = point.lock()->y;
		}
		else {

			myX += myVx;
			myY += myVy;

		}

	}


}


void WorldMap::searchPath(int pointNum) {

	movePointList.clear();

	std::vector<SearchPointConnect*> spc;
	spc.clear();

	SearchPointConnect* sss = new SearchPointConnect();
	sss->connectPointNum = -1;
	sss->isSearch = false;
	sss->PointCost = 0;
	sss->pointNum = pointNum;

	spc.push_back(sss);

	setSearchPointConnect(pointNum, &spc);


	setMovePath(nowMyPointNum, &spc);


	/*
	Point* point;

	point = getPoint(nowMyPointNum);

	for (PointConnect* connectPoint : point->pointConect) {
		if (pointNum == connectPoint->connectPointNum) {
			movePointList.push_back(connectPoint->connectPointNum);
		}
	}
	*/



	int moveCost = 0;
	for (SearchPointConnect* temp : spc) {
		if (nowMyPointNum == temp->pointNum) {
			moveCost = temp->PointCost;
			break;
		}
	}

	mySpeed = moveCost / mySpeedFrameNum;



	if (movePointList.empty()) {

	}
	else {
		nowMyPointNum = -1;
		_animator.GetCurrentAnimation()->SetCurrentTime(0);
	}





}




void WorldMap::setSearchPointConnect(int pointNum, std::vector<SearchPointConnect*>* spc) {

	double cost = 0;

	for (SearchPointConnect* ss : *spc) {
		if (ss->pointNum == pointNum && ss->isSearch == true) {
			return;
		}
		else if (ss->pointNum == pointNum && ss->isSearch == false) {
			ss->isSearch = true;
			cost = ss->PointCost;
		}
	}



	std::weak_ptr<Point> point;

	point = getPoint(pointNum);

	for (PointConnect* connectPoint : point.lock()->pointConect) {

		bool is = false;

		for (SearchPointConnect* ss : *spc) {
			if (connectPoint->connectPointNum == ss->pointNum) {
				is = true;
				if (cost + connectPoint->PointCost < ss->PointCost) {
					ss->connectPointNum = pointNum;
					ss->PointCost = cost + connectPoint->PointCost;
				}
			}
		}

		if (is == false) {
			SearchPointConnect* ssq = new SearchPointConnect();
			ssq->connectPointNum = pointNum;
			ssq->isSearch = false;
			ssq->PointCost = cost + connectPoint->PointCost;
			ssq->pointNum = connectPoint->connectPointNum;
			spc->push_back(ssq);
		}

	}

	int pn = -1;
	int minCost = -1;

	for (SearchPointConnect* ss : *spc) {

		if (minCost == -1 && ss->isSearch == false) {
			pn = ss->pointNum;
			minCost = ss->PointCost;
		}
		else if (minCost > ss->PointCost && ss->isSearch == false) {
			pn = ss->pointNum;
			minCost = ss->PointCost;
		}

	}

	if (minCost == -1 && pn == -1) {
		return;
	}
	else {
		setSearchPointConnect(pn, spc);
	}


}



void WorldMap::setMovePath(int pointNum, std::vector<SearchPointConnect*>* spc) {

	for (SearchPointConnect* ss : *spc) {
		if (ss->pointNum == pointNum) {
			if (ss->connectPointNum == -1) {
				return;
			}
			else {
				movePointList.push_back(ss->connectPointNum);
				setMovePath(ss->connectPointNum, spc);
			}
		}
	}

}



void WorldMap::setAreaNum(int areaNum) {

	nowMyAreaNum = areaNum;
	nowMyPointNum = -1;



	mySpeed = 0.0;

	myVx = 0.0;
	myVy = 0.0;

	_animator.GetCurrentAnimation()->SetCurrentTime(0);

	setNowAreaPointList();

	setNowRoadConnect();

	movePointList.clear();

	AreaGr = &AreaGrBuffer[areaNum - 1];

}


bool WorldMap::ClickCheck(Vector2D pos, Vector2D size) {

	if (!MOUSE->ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
		return false;

	//クリック位置を取得
	auto cursorPos = MOUSE->GetCursorPos();

	if (cursorPos._x < pos._x)
		return false;
	if (cursorPos._y < pos._y)
		return false;
	if (pos._x + size._x < cursorPos._x)
		return false;
	if (pos._y + size._y < cursorPos._y)
		return false;

	return true;

}



std::string WorldMap::GetFieldType(std::string stageNum) {

	//ダンジョンの地形の設定

	CSVReader reader;

	std::vector<std::string> FieldTypeArray;
	std::string fileName = "csv/StageData/DungeonType.csv";
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, FieldTypeArray, 2);

	int s = 0;
	std::smatch results;
	if (std::regex_search(stageNum, results, std::regex("\\d+"))) {
		s = stoi(results.str());
	}

	int FieldTypeNum = stoi(FieldTypeArray[s * 2 - 1]);

	switch (FieldTypeNum) {
	case 0:
		return "IconCave.png";
		break;
	case 1:
		return "IconForest.png";
		break;
	case 2:
		return "IconStone.png";
		break;
	case 3:
		return "IconWood.png";
		break;
	default:
		return "IconCave.png";
		break;
	}

}

//点Pと線分(AB)の距離
bool WorldMap::CheckLineOfPoint(Vector2D P, Vector2D A, Vector2D B)
{
	Vector2D temp = B - A;

	if (temp._x >= 0 && temp._y >= 0) {
		if (P._x >= A._x && P._y >= A._y && P._x <= B._x && P._y <= B._y) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (temp._x >= 0 && temp._y < 0) {
		if (P._x >= A._x && P._y <= A._y && P._x <= B._x && P._y >= B._y) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (temp._x < 0 && temp._y >= 0) {
		if (P._x <= A._x && P._y >= A._y && P._x >= B._x && P._y <= B._y) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (temp._x < 0 && temp._y < 0) {
		if (P._x <= A._x && P._y <= A._y && P._x >= B._x && P._y >= B._y) {
			return true;
		}
		else {
			return false;
		}
	}

}







