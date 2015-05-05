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


SPLayer Layer::create()
{
    return SPLayer(new Layer());
}

Layer::Layer(){}

void Layer::resume()
{

}

void Layer::pause()
{

}

void Layer::addSprite(SPSprite sprite)
{
    _sprites.push_back(sprite);
}

//void Layer::addSprite(SPImageSprite& sprite)
//{
//    _sprites.push_back(sprite);
//}

void Layer::draw(SPRenderer renderer)
{
    for (auto iter = _sprites.begin(); iter != _sprites.end(); iter++) {
        (*iter)->draw(renderer);
    }
    
//    for (auto iter = _imageSprites.begin(); iter != _imageSprites.end(); iter++){
//        (*iter)->draw(renderer);
//    }
}

NS_L2D_END