//
//  Layer.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Layer.h"
#include <algorithm>

NS_L2D_BEGIN

void Layer::resume()
{

}

void Layer::pause()
{

}

void Layer::addSprite(std::shared_ptr<Sprite> sprite)
{
    _sprites.push_back(sprite);
}

void Layer::draw()
{
    std::for_each(_sprites.begin(), _sprites.end(), std::mem_fn(&Sprite::draw));
}

NS_L2D_END