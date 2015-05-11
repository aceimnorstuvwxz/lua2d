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

#include "Director.h"
#include <chrono>
#include <thread>

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

void Director::lookAt(const glm::vec3 &eye)
{
    lookAt(eye, glm::vec3(eye.x, eye.y, 0.0f));
}

void Director::lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
{
    _view = glm::lookAt(eye, center, up);
}

glm::mat4& Director::getView()
{
    return _view;
}

glm::mat4& Director::getProj()
{
    return _proj;
}

void Director::setProj(float fovy, float aspect, float zNear, float zFar)
{
    _proj = glm::perspective(fovy, aspect, zNear, zFar);
}

void Director::mainLoop()
{
	std::chrono::microseconds frameInterval{ (long long)(1.0f / 60.0f * 1000.0f * 1000.0f) };
    while (!glfwWindowShouldClose(_glfwWindow))
    {
		auto last = std::chrono::steady_clock::now();
        _renderer->getContext()->clear();
        _scene->draw(_renderer);
        glfwSwapBuffers(_glfwWindow);
        glfwPollEvents();

		auto now = std::chrono::steady_clock::now();
		std::this_thread::sleep_for(frameInterval - (now - last));
    }

    glfwDestroyWindow(_glfwWindow);
    glfwTerminate();
}

NS_L2D_END

