/*
 Copyright (c) 2015 chenbingfeng (iichenbf#gmail.com)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

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

    void draw(SPRenderer renderer);
private:
    Scene();

    std::vector<SPLayer> _layers;
};

NS_L2D_END
#endif /* defined(__Lua2d__Scene__) */
