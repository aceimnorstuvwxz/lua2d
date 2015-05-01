//
//  Director.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Director.h" 

namespace l2d
{
    Director Director::_instance;

    Director& Director::getInstance()
    {
        return Director::_instance;
    };

    void Director::init(const int width, const int height)
    {
        _width = width;
        _height = height;

        //
    };
    
    void Director::runWithScene(Scene* scene)
    {
        _scene = scene;

    }
}


