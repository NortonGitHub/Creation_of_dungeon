#pragma once
#include <vector>
#include "TiledVector.h"

void Bresenham(TiledVector target, TiledVector pos, std::vector<TiledVector> &path, bool diagonal = false, int length = 0)
{
    int deltaX = target._x - pos._x;
    int deltaY = target._y - pos._y;
    
    //長さに指定がなければ差分だけ取得
    if (length == 0)
    {
        TiledVector delta(deltaX, deltaY);
        length = delta.GetBresenhamLength(diagonal);
    }
    
    //
    int count = 0;
    //
    int minX = (pos._x < target._x) ? pos._x : target._x;
    int minY = (pos._y < target._y) ? pos._y : target._y;
    int maxX = (pos._x < target._x) ? target._x : pos._x;
    int maxY = (pos._y < target._y) ? target._y : pos._y;
    
    //垂直は0除算になるので手動で値を返す
    int countX = pos._x;
    int countY = pos._y;
    if (deltaX == 0)
    {
        for (; minY <= maxY; )
        {
            (deltaY < 0) ? countY-- : countY++;
            path.push_back(TiledVector(countX, countY));
            
            count++;
            if (length == count)
                return;
        }
        return;
    }
    
    //
    double d = 0;
    double delta = abs(deltaY / deltaX);
    
    //ひとつ隣にいくごとに
    for ( ; minX <= maxX; )
    {
        //傾きを加える
        d += delta;
        
        bool flag = false;
        
        //マスの下半分を越えたら
        if (0.5 <= d)
        {
            if (!diagonal)
                flag = true;
            
            //さらに1つずらす
            (deltaY < 0) ? countY-- : countY++;
            
            //マス超えの基準値を1つ上に戻す
            d = d - 1.0;
        }
        
        if (!flag)
            (deltaX < 0) ? countX-- : countX++;
        
        path.push_back(TiledVector(countX, countY));
        
        count++;
        if (length <= count)
            return;
    }
}