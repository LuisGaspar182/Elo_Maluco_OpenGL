#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <vector>
#include <string>
#include <iostream>

class TextureManager {
public:
    TextureManager() {
        textures.resize(12);
    }

    void loadTextures() {
        std::vector<std::string> paths = {
            "imagens/vms.png", "imagens/brs.png",
            "imagens/vrs.png", "imagens/ams.png",
            "imagens/vmm.png", "imagens/brm.png",
            "imagens/vrm.png", "imagens/amm.png",
            "imagens/vmi.png", "imagens/bri.png",
            "imagens/vri.png", "imagens/ami.png"
        };

        for (size_t i = 0; i < paths.size(); ++i) {
            textures[i] = SOIL_load_OGL_texture(
                paths[i].c_str(),
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_INVERT_Y
            );

            if (textures[i] == 0) {
                std::cerr << "Erro ao carregar textura: " << paths[i] << std::endl;
            }
        }
    }

    GLuint getTexture(int index) const {
        return textures[index];
    }

private:
    std::vector<GLuint> textures;
};

#endif // TEXTURE_MANAGER_H