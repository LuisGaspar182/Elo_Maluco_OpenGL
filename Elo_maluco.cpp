#include <GL/glut.h>
#include <SOIL/SOIL.h>

GLuint texture[11]; // Armazena as texturas para as 6 faces do cubo

void loadTextures() {
    // Carregando texturas
    texture[0] = SOIL_load_OGL_texture("imagens/corrente1_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[1] = SOIL_load_OGL_texture("imagens/corrente1_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[2] = SOIL_load_OGL_texture("imagens/corrente1_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[3] = SOIL_load_OGL_texture("imagens/corrente1_4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    texture[4] = SOIL_load_OGL_texture("imagens/corrente2_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[5] = SOIL_load_OGL_texture("imagens/corrente2_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[6] = SOIL_load_OGL_texture("imagens/corrente2_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[7] = SOIL_load_OGL_texture("imagens/corrente2_4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    texture[8] = SOIL_load_OGL_texture("imagens/corrente3_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[9] = SOIL_load_OGL_texture("imagens/corrente3_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    texture[10] = SOIL_load_OGL_texture("imagens/corrente3_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    // Configuração das texturas
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

// Variáveis globais para controle de rotação
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

float cube1Angle = 0.0f; // Ângulo de rotação do primeiro cubo
float cube2Angle = 0.0f; // Ângulo de rotação do segundo cubo
float cube3Angle = 0.0f; // Ângulo de rotação do terceiro cubo

bool rotateCube1 = false; // Flag para controlar se o primeiro cubo deve rotacionar
bool rotateCube2 = false; // Flag para controlar se o segundo cubo deve rotacionar
bool rotateCube3 = false; // Flag para controlar se o terceiro cubo deve rotacionar


void drawCube() {

    glPushMatrix();
    
    if (rotateCube1) {
        cube1Angle -= 2.0f; // Ajuste o valor para a velocidade desejada
        if (cube1Angle < -360) cube1Angle += 360;
    }
    
    glRotatef(cube1Angle, 1.0f, 0.0f, 0.0f);

    glEnable(GL_TEXTURE_2D); // Habilita a textura

    glBindTexture(GL_TEXTURE_2D, texture[4]); // Face frontal
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[5]); // Face traseira
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();

    
    
    // Face superior
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); // Branco
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5, -0.5);
    glEnd();

    // Face inferior
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // Branco
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f(-0.5, -0.5,  0.5);
    glEnd();



    glBindTexture(GL_TEXTURE_2D, texture[6]); // Face lateral direita
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[7]); // Face lateral esquerda
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D); // Desabilita a textura
}

void drawSecondCube() {


    glEnable(GL_TEXTURE_2D); // Habilita a textura

    glPushMatrix(); // Salva a matriz de transformação atual

    if (rotateCube2) {
        cube2Angle += 2.0f; // Ajuste o valor para a velocidade desejada
        if (cube2Angle > 360) cube2Angle -= 360;
    }

    // Translada o segundo cubo para uma posição abaixo do primeiro
    glTranslatef(0.0f, 1.5f, 0.0f);
    
    glRotatef(cube2Angle, 1.0f, 0.0f, 0.0f);
    

glBindTexture(GL_TEXTURE_2D, texture[0]); // Face frontal
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[1]); // Face traseira
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();

    
    
    // Face superior
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); // Branco
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5, -0.5);
    glEnd();

    // Face inferior
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // Branco
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f(-0.5, -0.5,  0.5);
    glEnd();



    glBindTexture(GL_TEXTURE_2D, texture[2]); // Face lateral direita
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[3]); // Face lateral esquerda
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glEnd();

    glDisable(GL_TEXTURE_2D); // Desabilita a textura

    glPopMatrix(); // Restaura a matriz de transformação anterior

    glDisable(GL_TEXTURE_2D); // Desabilita a textura
}

void drawThirdCube() {
    glEnable(GL_TEXTURE_2D); // Habilita a textura

    glPushMatrix(); // Salva a matriz de transformação atual

    if (rotateCube3) {
        cube3Angle -= 2.0f; // Ajuste o valor para a velocidade desejada
        if (cube3Angle < 360) cube3Angle += 360;
    }

    // Translada o segundo cubo para uma posição abaixo do primeiro
    glTranslatef(0.0f, -1.5f, 0.0f);
    glRotatef(cube3Angle, 1.0f, 0.0f, 0.0f);

    

    glBindTexture(GL_TEXTURE_2D, texture[8]); // Face frontal
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[9]); // Face traseira
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();

    
    
    // Face superior
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); // Branco
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5, -0.5);
    glEnd();

    // Face inferior
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // Branco
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f(-0.5, -0.5,  0.5);
    glEnd();



    glBindTexture(GL_TEXTURE_2D, texture[10]); // Face lateral direita
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
    glEnd();

    // Face lateral esquerda
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // Branco
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glEnd();

    glDisable(GL_TEXTURE_2D); // Desabilita a textura

    glPopMatrix(); // Restaura a matriz de transformação anterior

    glDisable(GL_TEXTURE_2D); // Desabilita a textura
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Movendo o cubo para que ele seja visível na tela
    glTranslatef(0.0f, 0.0f, -5.0f); 
    
    // Aplicando rotações
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

    drawCube();
    drawSecondCube();
    drawThirdCube();

    glutSwapBuffers();
}

void update(int value) {
    angleX += 0.0f;
    angleY += 0.0f;
    angleZ += 0.0f;
    
    if (angleX > 360) angleX -= 360;
    if (angleY > 360) angleY -= 360;
    if (angleZ > 360) angleZ -= 360;

    // Controle de rotação dos cubos
    static int lastUpdate = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);

    if (currentTime - lastUpdate > 2000) { // 2 segundos
        rotateCube1 = !rotateCube1;
        rotateCube2 = !rotateCube2;
        rotateCube3 = !rotateCube3;
        lastUpdate = currentTime;
    }
    
    glutPostRedisplay();
    glutTimerFunc(36, update, 0);
}

void init() {
    // Habilitar teste de profundidade
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); // Habilita o mapeamento de textura
    
    // Definir o modo de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, 1.0f, 1.0f, 100.0f);
    
    // Definir a matriz de modelo/vista
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    loadTextures(); // Carrega as texturas
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Elo Maluco 3D");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
