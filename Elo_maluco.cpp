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

int main(int argc, char** argv) {
    // Obtenha a matriz do XML
    std::vector<std::vector<int>> matrizDoXml = obterMatrizDoXml("EloMaluco_estadoAtual_exemplo.xml");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Elo Maluco 3D");

    init(matrizDoXml);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();

    for (Cube* cube : cubes) {
        delete cube;
    }

    return 0;
}