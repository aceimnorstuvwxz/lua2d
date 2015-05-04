//
//  Director.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__Director__
#define __Lua2d__Director__

#include "utils.h"
#include "Scene.h"
#include "Renderer.h"
#include "cppgl/cppgl.h"

NS_L2D_BEGIN

class Director
{
public:
    static Director& getInstance();
    static int getA();
    // init the window, the OpenGL context attach to it and other things
    // should be called once only ad the begin of your program.
    void init(int width, int height, const std::string& appName);

    // running with the scene, if another scene is running, it will pause
    // the new scene must take the place. At any time, there cloud be only
    // one scene is running.
    void runWithScene(SPScene scene);

    cppgl::SPContext& getContext();
    
    void mainLoop();
private:
    static Director _instance;

    int _width;
    int _height;
    std::string _appName;
    SPScene _scene;
    SPRenderer _renderer;

    //window context
    GLFWwindow* _glfwWindow;
    long _frameInterval = 1.0f/60.0f*1000.0f*1000.0f; // microsecond

};

NS_L2D_END
#endif /* defined(__Lua2d__Director__) */
