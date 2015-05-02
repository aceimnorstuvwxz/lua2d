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
#include <vector>
#include <memory>

#include "Node.h"
#include "Layer.h"
#include "utils.h"

NS_L2D_BEGIN
    class Scene :public Node
    {
    public:
        // resume the scene, all layer will be resumed.
        void resume();
        
        // pause the scene, all layer will be paused.
        void pause();
        
        // add a layer with a zOrder
        void addLayer(std::shared_ptr<Layer> layer, const int zOrder);

        void draw();
    private:
        std::vector<std::shared_ptr<Layer>> _layers;
    };
NS_L2D_END
#endif /* defined(__Lua2d__Scene__) */
