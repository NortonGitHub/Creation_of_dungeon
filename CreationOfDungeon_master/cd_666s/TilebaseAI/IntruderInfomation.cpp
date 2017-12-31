#include "IntruderInfomation.h"
#include "ObjectInformationDrawer.h"
#include "StartPoint.h"
#include "Character.h"
#include "../DebugDraw.h"

IntruderInfomation::IntruderInfomation(const TiledObjectDictionary& dictionary)
	: _position(754, 248)
	, _dictionary(dictionary)
	, startTime(0)
	, _hand("resource/graph/ui/etClockHand.png")
{
	_icon = std::make_unique<Sprite>();
	_icon->SetPriority(101);
	_icon->SetPosition(Vector2D(754 + 30, 248 + 175));

	//_hand.GetTexturePtr().lock()->SetAnchorType(Texture2D::AnchorType::CENTER);
	_hand.SetPosition(Vector2D(754 + 54, 248 + 36));
	_hand.SetRenderType(Texture2D::RenderType::UI);
}


IntruderInfomation::~IntruderInfomation()
{
	_icon = nullptr;
}


void IntruderInfomation::InitWithSetup(const std::weak_ptr<StartPoint>& intrudePoint)
{
	_intrudePoint.reset();
	if (intrudePoint.expired())
		return;

	_intrudePoint = intrudePoint;


	_count = 0;

	//ƒQ[ƒ€ŽžŠÔŠ·ŽZ‚Å•b’PˆÊ‚É•ÏŠ·
	_waveInterval *= 60;

	_hand.Rotate(0);
}


void IntruderInfomation::Draw()
{
	//Debug::DrawString(_position + Vector2D(25, 155), "NEXT");

	if (_intrudePoint.expired())
		return;

	auto argIntrudePoint = _intrudePoint.lock();
	if (argIntrudePoint->GetTimeUnitlNext() != -1)
	{
		auto chara = argIntrudePoint->GetNextEnemy();
		if (chara != nullptr)
		{
			std::string name = chara->GetName();
			_icon->SetResource(_dictionary.GetImageFromName(name));
			_icon->SetPriority(101);
			_icon->SetScale(Vector2D(1.5, 1.5));
			_icon->SetPosition(Vector2D(754 + 35, 248 + 160));

		}
		//Debug::DrawString(_position + Vector2D(65, 170), "‚ ‚Æ");
		//Debug::DrawString(_position + Vector2D(48, 55), std::to_string(argIntrudePoint->GetTimeUnitlNext() / 60),
		//	Color4(0.0, 0.0, 0.0, 0.0), 32);

		// chuusin 57,181   r=35
		auto now_time = argIntrudePoint->GetTimeUnitlNext() / 60;
		auto startTime = argIntrudePoint->GetTimeUnitNextFrom() / 60;
		int dist = 360 / startTime;

		//Debug::DrawString(_position + Vector2D(65, 170), std::to_string(argIntrudePoint->GetTimeUnitNextFrom() / 60));

		auto offset = 90;
		auto timeRatio = static_cast<double>(_count - now_time) / static_cast<double>(now_time);
		//_hand.Rotate(timeRatio * (90 - offset));

		_hand.Rotate(dist * (startTime - now_time));

	}
	else
	{
		_icon->SetResource(nullptr);
	}
}