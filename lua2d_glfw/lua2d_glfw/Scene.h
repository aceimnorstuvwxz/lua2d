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
#include "Renderer.h"
#include "utils.h"

NS_L2D_BEGIN

class Scene;
class Sprite;
class Renderer;
class Layer;
typedef std::shared_ptr<Scene> SPScene;
typedef std::shared_ptr<Sprite> SPSprite;
typedef std::shared_ptr<Renderer> SPRenderer;
typedef std::shared_ptr<Layer> SPLayer;

class Scene :public Node
{
public:
    static SPScene create();

    // resume the scene, all layer will be resumed.
    void resume();

    // pause the scene, all layer will be paused.
    void pause();

    // add a layer with a zOrder
    void addLayer(SPLayer layer, const int zOrder);

    void draw(SPRenderer& renderer);
private:
    Scene();

    std::vector<SPLayer> _layers;
};

NS_L2D_END
#endif /* defined(__Lua2d__Scene__) */
