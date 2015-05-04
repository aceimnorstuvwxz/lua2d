//
//  Renderer.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/30.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__Renderer__
#define __Lua2d__Renderer__

#include <memory>
#include <string>

#include "utils.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Scene.h"
#include "cppgl/cppgl.h"

NS_L2D_BEGIN

class Renderer;
typedef std::shared_ptr<Renderer> SPRenderer;

class Renderer
{
public:
    static SPRenderer create();

    void init(int width, int height, const std::string& titile);
    int getWidth();
    int getHeight();
    cppgl::SPContext getContext();

private:
    Renderer();
    int _width;
    int _height;
    cppgl::SPContext _context;
};

NS_L2D_END

#endif /* defined(__Lua2d__Renderer__) */