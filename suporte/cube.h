#ifndef CUBE_H
#define CUBE_H

#include <GL/glut.h>
#include "texture_manager.h"

class Cube {
public:
    Cube(TextureManager& textureManager, float x, float y, float z, int textureIndices[6])
        : textureManager(textureManager), x(x), y(y), z(z) {
        for (int i = 0; i < 6; ++i) {
            this->textureIndices[i] = textureIndices[i];
        }
    }

    void draw() {
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(x, y, z);

        drawFace(textureIndices[0], -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f); // Front
        drawFace(textureIndices[1], -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f); // Back
        drawFace(textureIndices[2], -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f); // Top
        drawFace(textureIndices[3], -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f); // Bottom
        drawFace2(textureIndices[4], 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f); // Right
        drawFace2(textureIndices[5], -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f); // Left

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

private:
    TextureManager& textureManager;
    float x, y, z;
    int textureIndices[6];

    void drawFace(int textureIndex, float x1, float y1, float z1, float x2, float y2, float z2) {
        glBindTexture(GL_TEXTURE_2D, textureManager.getTexture(textureIndex));
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y1, z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2, z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y2, z2);
        glEnd();
    }
    void drawFace2(int textureIndex, float x1, float y1, float z1, float x2, float y2, float z2) {
        glBindTexture(GL_TEXTURE_2D, textureManager.getTexture(textureIndex));
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y2, z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y2, z2);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z2);
        glEnd();
    }
};

#endif // CUBE_H