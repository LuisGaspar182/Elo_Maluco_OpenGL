#include <GL/glut.h>
#include "suporte/texture_manager.h"
#include "suporte/cube.h"
#include "XML_Reader.cpp"

// Variáveis globais para controle de rotação
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

// Variáveis globais para controle de rotação com o mouse
bool mouseDown = false;
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;

// Posição inicial da câmera no eixo Z
float cameraZ = -5.0f;

// Índice do cubo selecionado
int selectedCube = 0;

// Texturas atuais
int linhavalor20 = -1;
int colunavalor20 = -1;

std::vector<std::vector<int>> matrizDoXml;

TextureManager textureManager;
Cube* cubes[4];

void init(std::vector<std::vector<int>> matrizDoXml) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, 1.0f, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    textureManager.loadTextures();

    
    int textures1[6] = {matrizDoXml[0][0], matrizDoXml[0][1], 20, 20, matrizDoXml[0][2], matrizDoXml[0][3]}; // Frente, trás, topo, base, direita, esquerda
    int textures2[6] = {matrizDoXml[1][0], matrizDoXml[1][1], 20, 20, matrizDoXml[1][2], matrizDoXml[1][3]}; // Frente, trás, topo, base, direita, esquerda
    int textures3[6] = {matrizDoXml[2][0], matrizDoXml[2][1], 20, 20, matrizDoXml[2][2], matrizDoXml[2][3]}; // Frente, trás, topo, base, direita, esquerda
    int textures4[6] = {matrizDoXml[3][0], matrizDoXml[3][1], 20, 20, matrizDoXml[3][2], matrizDoXml[3][3]}; // Frente, trás, topo, base, direita, esquerda

    // Ajustar as posições dos cubos para que eles se toquem
    cubes[0] = new Cube(textureManager, 0.0f, 0.5f, 0.0f, textures1);
    cubes[1] = new Cube(textureManager, 0.0f, -0.5f, 0.0f, textures2);
    cubes[2] = new Cube(textureManager, 0.0f, -1.5f, 0.0f, textures3);
    cubes[3] = new Cube(textureManager, 0.0f, -2.5f, 0.0f, textures4);
}

   void mouse(int button, int state, int x, int y) {
       if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
           mouseDown = true;
           xdiff = x - yrot;
           ydiff = -y + xrot;
       } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
           mouseDown = false;
       }

       // Simular rolagem do mouse com botões do mouse
       if (button == 3) { // Scroll up
           cameraZ += 0.5f; // Aproxima a câmera
       } else if (button == 4) { // Scroll down
           cameraZ -= 0.5f; // Afasta a câmera
       }

       glutPostRedisplay();
   }

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;
        glutPostRedisplay();
    }
}

void atualizarTexturasCubos() {
    for (int i = 0; i < 4; i++) {
        if (cubes[i] != nullptr) {
            int textures[6] = {matrizDoXml[i][0], matrizDoXml[i][1], 20, 20, matrizDoXml[i][2], matrizDoXml[i][3]};
            cubes[i]->updateTextures(textures);
        }
    }
}

void trocarTexturaAbaixo() {
    if (linhavalor20 < 3 && linhavalor20 >= 0 && colunavalor20 >= 0 && colunavalor20 < 4) {
        int texturaBaixo = matrizDoXml[linhavalor20 + 1][colunavalor20];
        matrizDoXml[linhavalor20 + 1][colunavalor20] = 20;
        matrizDoXml[linhavalor20][colunavalor20] = texturaBaixo;
        linhavalor20++;
        atualizarTexturasCubos();
    } else {
        std::cerr << "Erro ao trocar textura abaixo: índices fora dos limites." << linhavalor20 << " " << colunavalor20 << std::endl;
    }
}

void trocarTexturaAcima() {
    if (linhavalor20 > 0) {
        int texturaAcima = matrizDoXml[linhavalor20 - 1][colunavalor20];
        matrizDoXml[linhavalor20 - 1][colunavalor20] = 20;
        matrizDoXml[linhavalor20][colunavalor20] = texturaAcima;
        linhavalor20--;
        atualizarTexturasCubos();
    } else {
        std::cerr << "Erro ao trocar textura acima: índices fora dos limites." << linhavalor20 << " " << colunavalor20 << std::endl;
    }
}

void keyboard(unsigned char key, int x, int y) {
    int texture;
    switch(key) {
        case 'w':
        case 'W':
            // Seleciona o cubo de cima
            selectedCube = (selectedCube > 0) ? selectedCube - 1 : 0;
            break;
        case 's':
        case 'S':
            // Seleciona o cubo de baixo
            selectedCube = (selectedCube < 3) ? selectedCube + 1 : 3;
            break;
        case 'a':
        case 'A':
            // Rotaciona o cubo selecionado em 90 graus
            texture = matrizDoXml[selectedCube][0];
            matrizDoXml[selectedCube][0] = matrizDoXml[selectedCube][1];
            matrizDoXml[selectedCube][1] = matrizDoXml[selectedCube][2];
            matrizDoXml[selectedCube][2] = matrizDoXml[selectedCube][3];
            matrizDoXml[selectedCube][3] = texture;
            if(linhavalor20 == selectedCube){
                if(colunavalor20 > 0){
                    colunavalor20--;
                } else {
                    colunavalor20 = 3;
                }
            }
            atualizarTexturasCubos();
            break;
        case 'd':
        case 'D':
            // Rotaciona o cubo selecionado em -90 graus
            texture = matrizDoXml[selectedCube][0];
            matrizDoXml[selectedCube][0] = matrizDoXml[selectedCube][3];
            matrizDoXml[selectedCube][3] = matrizDoXml[selectedCube][2];
            matrizDoXml[selectedCube][2] = matrizDoXml[selectedCube][1];
            matrizDoXml[selectedCube][1] = texture;
            if(linhavalor20 == selectedCube){
                if(colunavalor20 < 3){
                    colunavalor20++;
                } else {
                    colunavalor20 = 0;
                }
            }
            atualizarTexturasCubos();
            break;
        case ' ':
            // Troca a textura abaixo da textura 20
            trocarTexturaAbaixo();
            break;
        case 'c':
        case 'C':
            // Troca a textura acima da textura 20
            trocarTexturaAcima();
            break;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Ajustar a posição da câmera com base na rolagem do mouse
    glTranslatef(0.0f, 0.0f, cameraZ);

    // Aplicar rotações baseadas no movimento do mouse
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    for (Cube* cube : cubes) {
        cube->draw();
    }

    glutSwapBuffers();
}

void encontrarValor20(const std::vector<std::vector<int>>& matrizDoXml) {
    for (int i = 0; i < matrizDoXml.size(); i++) {
        for (int j = 0; j < matrizDoXml[i].size(); j++) {
            if (matrizDoXml[i][j] == 20) {
                linhavalor20 = i;
                colunavalor20 = j;
            }
        }
    }
}

int main(int argc, char** argv) {
    // Obtenha a matriz do XML
    matrizDoXml = obterMatrizDoXml("EloMaluco_estadoAtual_exemplo.xml");
    encontrarValor20(matrizDoXml);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Elo Maluco 3D");

    init(matrizDoXml);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    for (Cube* cube : cubes) {
        delete cube;
    }

    return 0;
}