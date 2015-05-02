//
//  Sprite.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__Sprite__
#define __Lua2d__Sprite__

#include <stdio.h>
#include "Node.h"

namespace l2d
{
    class Sprite :public Node
    {
    protected:
        bool _isVisible;
        float _alpha; //[0.0f, 1.0f]
        
        int _x; // x position in parent
        int _y; // y position in parent
        int _z; // z position in parent, [0, 99]

        // anchor is the center of rotating and scaling
        int _anchorX; // anchor position x in self
        int _anchorY; // anchor position y in self
        int _rotate; // rotate degree in clockwise
        float _scale; //default 1

    public:
        void hide();
        void show();
        void setX(int x);
        void setY(int y);
        void setZ(int z);
        void rotate(int degree);
        void setAlpha(float alpha);
        void scale(float scaler);

        // load resource and init GL things, make ready for draw
        // it may cost some time.
        virtual void load() = 0;

        // draw in GL context.
        virtual void draw() = 0;
    };
}

#endif /* defined(__Lua2d__Sprite__) */
