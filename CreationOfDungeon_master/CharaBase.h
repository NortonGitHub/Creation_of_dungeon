#pragma once

#include "Vector2D.h"
#include <string>
#include <memory>

class CharaBase
{
public:
	CharaBase();

	CharaBase(std::string _chara_num) {
		chara_num = _chara_num;
	}

	//	template<class Chara>
	//	CharaBase(const Chara& target): : p_(new HeroHolder<Chara>(target)) {}
	virtual ~CharaBase();

	virtual void Update() = 0;
	virtual void Draw() = 0;

#if 0
	virtual CharaManagerBase* GetManagerInstance() = 0;
#endif

private:
	std::string chara_num;

	/*
	class CharaTypeBase {
	public:
		~CharaTypeBase() {}
	};

	typedef std::tr1::shared_ptr<CharaTypeBase> holder_ptr;


	template<class Chara>
	class CharaDerived : public CharaTypeBase
	{
	public:
		CharaDerived(Chara const &target) :_target(target) {}
	private:
		Chara _target;
	};

	holder_ptr p_;

	/*
	https://mmiyano.blogspot.jp/2012/10/blog-post.html 参考
	また作り直すん・・・・？ﾌﾞﾜｯ
	HeroBaseのErasureTypeをCharaBaseに移動させる
	*/
	
};

