//
//  Scene.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__Scene__
#define __Lua2d__Scene__

#include <stdio.h>
#include "Node.h"
#include "Layer.h"
namespace l2d
{
    class Scene :public Node
    {
    public:
        // resume the scene, all layer will be resumed.
        void resume();
        
        // pause the scene, all layer will be paused.
        void pause();
        
        // add a layer with a zOrder
        void addLayer(const Layer& layer, const int zOrder);
    };
}
#endif /* defined(__Lua2d__Scene__) */
