//
//  Renderer.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/30.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__Renderer__
#define __Lua2d__Renderer__

#include <stdio.h>
#include "Scene.h"


namespace l2d
{
    // all opengl calls stand here
    class Renderer
    {
    public:
        void initContext(int width, int height);
        void drawScene(Scene* scene);
        void releaseContext();
        // no reshape
        void testDraw();

    private:
        int _width;
        int _height;

        void _init();
    };
}

#endif /* defined(__Lua2d__Renderer__) */
