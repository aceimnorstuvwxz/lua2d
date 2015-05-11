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

    void lookAt(const glm::vec3& eye);
    void lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4& getView();
    glm::mat4& getProj();
    void setProj(float fovy, float aspect, float zNear, float zFar);

    void mainLoop();
private:
    static Director _instance;

    int _width;
    int _height;
    std::string _appName;
    glm::mat4 _view = glm::mat4(1.0f);
    glm::mat4 _proj = glm::mat4(1.0f);
    SPScene _scene;
    SPRenderer _renderer;

    //window context
    GLFWwindow* _glfwWindow;
    long _frameInterval = 1.0f/60.0f*1000.0f*1000.0f; // microsecond
};

NS_L2D_END
#endif /* defined(__Lua2d__Director__) */
