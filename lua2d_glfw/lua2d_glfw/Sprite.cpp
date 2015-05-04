//
//  Sprite.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Sprite.h"

NS_L2D_BEGIN

void Sprite::hide()
{
    _isVisible = false;
}

void Sprite::show()
{
    _isVisible = true;
}

void Sprite::setX(int x)
{
    _x = x;
}

void Sprite::setY(int y)
{
    _y = y;
}

void Sprite::setZ(int z)
{
    _z = z;
}

void Sprite::rotate(int degree)
{
    _rotate = degree;
}

void Sprite::setAlpha(float alpha)
{
    _alpha = alpha;
}

void Sprite::scale(float scaler)
{
    _scale = scaler;
}

NS_L2D_END