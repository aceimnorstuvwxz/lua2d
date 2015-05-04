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

SPScene Scene::create()
{
    return SPScene(new Scene());
}

void Scene::resume(){};

void Scene::pause(){};

void Scene::addLayer(SPLayer layer, const int zOrder)
{
    _layers.push_back(layer);
    //TODO zOrder
};

Scene::Scene(){}

void Scene::draw(SPRenderer& renderer)
{
    for(auto iter = _layers.begin(); iter != _layers.end(); iter++){
        (*iter)->draw(renderer);
    }
}

NS_L2D_END