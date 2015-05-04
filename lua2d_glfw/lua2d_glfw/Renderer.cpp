//
//  Renderer.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/30.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Renderer.h"

#include <OpenGl/gl3.h>
#include <math.h>
#include <unistd.h>

#include "cppgl/cppgl.h"
#include "utils.h"

namespace l2d
{
    void Renderer::init(int width, int height)
    {
        _width = width;
        _height = height;

        LOG("GL_RENDERER", glGetString(GL_RENDERER),  " GL_VERSION = ",glGetString(GL_VERSION));
    }

    void Renderer::drawScene(std::shared_ptr<Scene> scene)
    {
        scene->draw();
    }
}
