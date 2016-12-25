#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:
	static T *GetInstance()
	{
		static T instance;	    // ‚Ü‚¾À‘Ô‚ªì‚ç‚ê‚Ä‚¢‚È‚¢‚Ì‚İì¬
		return &instance;		// À‘Ì‚ğ•Ô‚·
	}

protected:
	Singleton();
	virtual ~Singleton();

private:
	//ƒRƒs[‚Æ‘ã“ü‚Ì‹Ö~
	Singleton(const Singleton &arg);
	Singleton &operator = (const Singleton &arg);
};

#include "Singleton_Private.h"

#endif