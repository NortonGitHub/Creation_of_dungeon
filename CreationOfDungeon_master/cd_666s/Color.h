//
//  Color.h
//  OpenGLTest
//
//  Created by 666 on 2016/09/19.
//  Copyright c 2016”N 666. All rights reserved.
//

#ifndef Color_h
#define Color_h

struct Color4
{
    Color4(float r, float g, float b, float a)
    : _r(r)
    , _g(g)
    , _b(b)
    , _a(a)
    {}
    
    float _r, _g, _b, _a;
};

namespace ColorPalette
{
    static const Color4 RED4 = Color4(1, 0, 0 ,1);
    static const Color4 GREEN4 = Color4(0, 1, 0 ,1);
    static const Color4 BLUE4 = Color4(0, 0, 1, 1);
    static const Color4 WHITE4 = Color4(1, 1, 1, 1);
    static const Color4 BLACK4 = Color4(0, 0, 0, 1);
	static const Color4 LIGHTBLUE4 = Color4(0.39, 0.75, 1, 1);
	static const Color4 ORANGE4 = Color4(1, 0.47, 0.24, 1);
	static const Color4 PURPLE4 = Color4(0.47, 0.31, 1, 1);
};

#endif /* Color_h */
