//
//  Scene.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Scene.h"

#include <algorithm>

NS_L2D_BEGIN

void Scene::resume(){};

void Scene::pause(){};

void Scene::addLayer(std::shared_ptr<Layer> layer, const int zOrder)
{
    _layers.push_back(layer);
    //TODO zOrder
};

void Scene::draw()
{
    std::for_each(_layers.begin(), _layers.end(), std::mem_fn(&Layer::draw));
}

NS_L2D_END