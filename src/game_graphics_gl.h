/*
 * Copyright (C) 2011 Stian Ellingsen <stiell@stiell.org>
 *
 * This file is part of Limbs Off.
 *
 * Limbs Off is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Limbs Off is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Limbs Off.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GAME_GRAPHICS_GL_H_
#define GAME_GRAPHICS_GL_H_

#include <GL/gl.h>
#include "graphics.h"
#include "physics.h"

class BodyGraphic: public Graphic {
public:
    BodyGraphic(Body* body, Graphic* graphic, GLfloat ox, GLfloat oy,
            GLfloat oa);
    void draw();
private:
    Body* body_;
    Graphic* graphic_;
    GLfloat ox_, oy_, oa_;
};

class Sprite: public Graphic {
public:
    Sprite(GLuint texture, GLfloat w, GLfloat h);
    void draw();
private:
    GLuint texture_;
    GLfloat w_, h_;
};

class Disk: public Graphic {
public:
    Disk(GLfloat r, int n);
    void draw();
private:
    GLfloat r_;
    int n_;
    GLuint displayList_;
    void makeDisplayList();
};

class TestDisk: public Graphic {
public:
    TestDisk(GLfloat r, int n);
    void draw();
private:
    Disk disk_, square_;
};

class TextureLoader {
public:
    static TextureLoader* getInstance();
    GLuint loadTexture(const char* filename, bool premultiply);
protected:
    TextureLoader();
private:
    static TextureLoader* instance_;
};

class Screen {
public:
    static const int DM_FRONT_TO_BACK = 1, DM_PREMUL = 2, DM_SMOOTH = 4;
    static Screen* getInstance();
    static void setVideoMode(int screenWidth, int screenHeight, int screenDepth);
    void setDrawingMode(int mode, int mask = -1, bool update = true);
    int getDrawingMode();
    void updateDrawingMode();
protected:
    Screen();
private:
    static Screen* instance_;
    // Video mode
    static int screenWidth_, screenHeight_, screenDepth_;
    int drawingMode_;
    static bool initialize();
};

class Camera {
public:
    Camera(vector2p position, double radius, double rotation);
    // Update pos/rad/rot
    void update(double deltaTime);
    // Set pos/rad/rot
    void apply();
    // Get pos/rad/rot
    vector2p getPosition();
    double getRadius();
    double getRotation();
    // Set desired pos/rad/rot
    void setTargetPosition(vector2p target);
    void setTargetRadius(double target);
    void setTargetRotation(double target);
private:
    // Pos and desired pos
    vector2p position_, targetPosition_;
    // Rad and desired rad
    double radius_, targetRadius_;
    // Rot and desired rot
    double rotation_, targetRotation_;
};

#endif /* GAME_GRAPHICS_GL_H_ */
