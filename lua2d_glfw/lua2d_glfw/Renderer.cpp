//
//  Renderer.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/30.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Renderer.h"

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
static GLFWwindow* _glfwWindow;
void makeContext(int width, int height, const std::string& title)
{
    // using GLFW to generate window and GL context

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()){
        std::cerr << "GLFW init failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!_glfwWindow){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_glfwWindow);
    glfwSwapInterval(1);

    glfwSetKeyCallback(_glfwWindow, glfw_key_callback);

}


SPRenderer Renderer::create()
{
    return SPRenderer(new Renderer());
}

Renderer::Renderer(){}

void Renderer::init(int width, int height, const std::string& title)
{
    _width = width;
    _height = height;

    LOG("GL_RENDERER", glGetString(GL_RENDERER),  " GL_VERSION = ",glGetString(GL_VERSION));

    makeContext(_width, _height, title);

    _context = cppgl::Context::Create();
    _context->clearColor({1.0f, 1.0f, 1.0f, 1.0f});
    _context->enable(cppgl::Capability::Blend);
    _context->blendFunc(cppgl::BlendFactor::SRC_ALPHA, cppgl::BlendFactor::ONE_MINUS_SRC_ALPHA);
}

cppgl::SPContext Renderer::getContext()
{
    return _context;
}

NS_L2D_END