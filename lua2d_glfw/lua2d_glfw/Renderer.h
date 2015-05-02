//
//  Renderer.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/30.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__Renderer__
#define __Lua2d__Renderer__

#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Scene.h"

namespace l2d
{
    class Renderer
    {
    public:
        void init(int width, int height);
        void drawScene(std::shared_ptr<Scene> scene);
        void testDraw();

    private:
        int _width;
        int _height;
    };
}

#endif /* defined(__Lua2d__Renderer__) */
