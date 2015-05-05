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
static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW error: " << description << std::endl;
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
GLFWwindow* makeContext(int width, int height, const std::string& title)
{
    // using GLFW to generate window and GL context
    GLFWwindow* glfwWindow;
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()){
        std::cerr << "GLFW init failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!glfwWindow){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(1);

    glfwSetKeyCallback(glfwWindow, glfw_key_callback);

    return glfwWindow;
}
Director Director::_instance;

Director& Director::getInstance()
{
    return Director::_instance;
};

void Director::init(int width, int height, const std::string& appName)
{
    _width = width;
    _height = height;
    _appName = appName;

    _glfwWindow = makeContext(_width, _height, appName);

    // init renderer
    _renderer = Renderer::create();
    _renderer->init(_width, _height, _appName);
};

void Director::runWithScene(SPScene scene)
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

        _renderer->getContext()->clear();
        _scene->draw(_renderer);
        glfwSwapBuffers(_glfwWindow);
        glfwPollEvents();

        long curTime = getCurrentMicroSecond();

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

