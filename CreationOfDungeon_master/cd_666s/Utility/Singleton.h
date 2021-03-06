#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:
	static T *GetInstance()
	{
		static T instance;	    // まだ実態が作られていない時のみ作成
		return &instance;		// 実体を返す
	}

protected:
	Singleton();
	virtual ~Singleton();

private:
	//コピーと代入の禁止
	Singleton(const Singleton &arg);
	Singleton &operator = (const Singleton &arg);
};

#include "Singleton_Private.h"

#endif