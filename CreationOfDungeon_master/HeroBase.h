#pragma once
#include "CharaBase.h"
class HeroBase : public CharaBase
{
public:
    HeroBase();

//  template<class Chara>
//  HeroBase(Chara target) : p_(new HeroHolder<Chara>(target)) {}

    ~HeroBase();

protected:
    virtual void Update() = 0;
    virtual void Draw() = 0;

    bool IsDefeated(int _hp);
/*
private:
    typedef std::tr1::shared_ptr<CharaBase> holder_ptr;

    template <class T>
    class HeroHolder : public CharaBase {
        HeroHolder(T target) :target_(target) {}
        virtual ~HeroHolder() throw() {}
        virtual void run() {}
    private:
        T target_;
    };

    holder_ptr p_;
    */
};

