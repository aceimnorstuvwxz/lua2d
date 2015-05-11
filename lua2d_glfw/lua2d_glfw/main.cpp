//
//  main.cpp
//  luaformac
//
//  Created by chenbingfeng on 15/4/22.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//
#include <math.h>

#include <iostream>
#include <chrono>

#include "cppgl/cppgl.h"
#include "utils.h"
#include "lua2d.h"

extern "C" {

#include "lua53/lua.h"
#include "lua53/lauxlib.h"
#include "lua53/lualib.h"

}

static void lua2d_demo()
{
    auto director = l2d::Director::getInstance();
    director.init(142, 198, "appName");

    auto scene = l2d::Scene::create();
    auto layer = l2d::Layer::create();
    auto imageSprite = l2d::ImageSprite::create("shooting_arrow.png",71, 98);
    imageSprite->load();

    auto cube = l2d::MeshSprite::create("cube.obj", "cube.png");
    cube->load();

    auto tank = l2d::MeshSprite::create("tank.obj", "tank.jpg");
    tank->load();


    layer->addSprite(cube);
    layer->addSprite(imageSprite);
    layer->addSprite(tank);

    scene->addLayer(layer, 0);
    director.runWithScene(scene);
    director.mainLoop();
}

int main(int argc, const char * argv[])
{
    std::cout << "hello world!" << std::endl;
//    cppgl::cppgl_test();
    lua2d_demo();
    return 0;
}