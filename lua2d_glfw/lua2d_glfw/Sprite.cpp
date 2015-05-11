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

#include "Sprite.h"

NS_L2D_BEGIN

void Sprite::hide()
{
	_isVisible = false;
}

void Sprite::show()
{
    _isVisible = true;
}

void Sprite::setX(float x)
{
    _x = x;
    _isDirty = true;
}

void Sprite::setY(float y)
{
    _y = y;
    _isDirty = true;
}

void Sprite::setZ(float z)
{
    _z = z;
    _isDirty = true;
}

void Sprite::rotate(float degree)
{
    _rotate = degree;
    _isDirty = true;
}

void Sprite::setAlpha(float alpha)
{
    _alpha = alpha;
    _isDirty = true;
}

void Sprite::scale(float scaler)
{
    _scale = scaler;
    _isDirty = true;
}

glm::mat4& Sprite::getModel()
{
    if (!_isDirty) return _model;

    _model = glm::mat4(1.0f);

    _model = glm::scale(_model, glm::vec3(_scale));
    _model = glm::translate(_model, glm::vec3(_x, _y, _z));
    _model = glm::rotate(_model, glm::radians(_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    _isDirty = false;
    return _model;
}

NS_L2D_END