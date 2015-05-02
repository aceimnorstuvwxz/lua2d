//
//  Director.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Director.h"
#include <unistd.h>
#include <sys/time.h>

NS_L2D_BEGIN

Director Director::_instance;

Director& Director::getInstance()
{
    return Director::_instance;
};

static void glfw_error_callback(int error, const char* description)
{
    LOG("GLFW error: ", description);
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void Director::init(const int width, const int height)
{
    _width = width;
    _height = height;

    // init glfw window
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()){
        LOG("GLFW init failed.");
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _glfwWindow = glfwCreateWindow(width, height, "Lua2d", NULL, NULL);
    if (!_glfwWindow){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_glfwWindow);
    glfwSwapInterval(1);

    glfwSetKeyCallback(_glfwWindow, glfw_key_callback);

    // init renderer
    _renderer = std::make_shared<Renderer>();
    _renderer->init(_width, _height);
};

void Director::runWithScene(std::shared_ptr<Scene> scene)
{
    LOG("runWithScene");
    _scene = scene;
}
// millisecond 毫秒 microsecond微秒 nonosecond纳秒
long getCurrentMicroSecond()
{
    long lLastTime = 0;
    struct timeval stCurrentTime;

    gettimeofday(&stCurrentTime,NULL);
    lLastTime = stCurrentTime.tv_sec*1000+stCurrentTime.tv_usec*0.001;
    return lLastTime;
}
void Director::mainLoop()
{

    while (!glfwWindowShouldClose(_glfwWindow))
    {
        long lastTime = getCurrentMicroSecond();

        _renderer->drawScene(_scene);
        glfwSwapBuffers(_glfwWindow);
        glfwPollEvents();

        long curTime = getCurrentMicroSecond();
        //            LOG("execution time=", curTime - lastTime, " frameInterval=", _frameInterval);

        if (curTime - lastTime < _frameInterval){
            usleep(static_cast<useconds_t>((_frameInterval - curTime + lastTime)));//usleep在微秒工作
        } else {
            LOG("frame time overflow.");
        }
    }

    glfwDestroyWindow(_glfwWindow);
    glfwTerminate();
}

NS_L2D_END

