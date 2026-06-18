
#include <cmath>
#include <string>
#include <array>

#define _USE_MATH_DEFINES
#include <math.h>

#define _UNICODE
#include "../lib/glut.h"
#include "../lib/il.h"

GLuint diceSide1Texture, diceSide2Texture, diceSide3Texture, diceSide4Texture, diceSide5Texture, diceSide6Texture;
GLuint carpetTexture, catTexture;

int currentScene = 0;
const int MAX_SCENE = 11;

const char *sceneTitles[] = {
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12"};

const int SPEED = 5;
int leftRightRotation = 45;
int upDownRotation = 45;

float catScale = 1.0;
GLuint catMinFilter = GL_NEAREST_MIPMAP_NEAREST;
GLuint catMagFilter = GL_NEAREST;

void loadTexture(const wchar_t *path, GLuint *textureID)
{
    glGenTextures(1, textureID);

    if (!ilLoadImage(path))
        return;

    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    glBindTexture(GL_TEXTURE_2D, *textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
}

void loadMipmaps(const wchar_t *path, const wchar_t *ext, GLuint *textureID)
{
    glGenTextures(1, textureID);
    glBindTexture(GL_TEXTURE_2D, *textureID);

    int level = 0;

    while (true)
    {
        std::wstring filename = std::wstring(path) + L"/level" + std::to_wstring(level) + L"." + ext;

        if (!ilLoadImage(filename.c_str()))
            break;

        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        int width = ilGetInteger(IL_IMAGE_WIDTH);
        int height = ilGetInteger(IL_IMAGE_HEIGHT);

        glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

        level++;
    }
}

void loadAllTextures()
{
    loadTexture(L"bmp/1.bmp", &diceSide1Texture);
    loadTexture(L"bmp/2.bmp", &diceSide2Texture);
    loadTexture(L"bmp/3.bmp", &diceSide3Texture);
    loadTexture(L"bmp/4.bmp", &diceSide4Texture);
    loadTexture(L"bmp/5.bmp", &diceSide5Texture);
    loadTexture(L"bmp/6.bmp", &diceSide6Texture);
    loadTexture(L"bmp/128.bmp", &carpetTexture);

    loadMipmaps(L"bmp/mipmaps", L"bmp", &catTexture);
}

void keyboardCallback(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        leftRightRotation -= SPEED;
        break;
    case 'd':
        leftRightRotation += SPEED;
        break;
    case 'w':
        upDownRotation -= SPEED;
        break;
    case 's':
        upDownRotation += SPEED;
        break;
    case '=':
        catScale *= 1.1f;
        break;
    case '-':
        catScale /= 1.1f;
        break;
    case '1':
        catMinFilter = GL_NEAREST_MIPMAP_NEAREST;
        break;
    case '2':
        catMinFilter = GL_LINEAR_MIPMAP_NEAREST;
        break;
    case '3':
        catMinFilter = GL_NEAREST_MIPMAP_LINEAR;
        break;
    case '4':
        catMinFilter = GL_LINEAR_MIPMAP_LINEAR;
        break;
    case '9':
        catMagFilter = GL_NEAREST;
        break;
    case '0':
        catMagFilter = GL_LINEAR;
        break;
    }
    leftRightRotation %= 360;
    upDownRotation %= 360;
    glutPostRedisplay();
}

void specialCallback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        currentScene--;
        if (currentScene < 0)
            currentScene = MAX_SCENE;
        break;
    case GLUT_KEY_RIGHT:
        currentScene++;
        if (currentScene > MAX_SCENE)
            currentScene = 0;
        break;
    }
    glutSetWindowTitle(sceneTitles[currentScene]);
    glutPostRedisplay();
}

void scene_1_carpet_1x1_manual()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
    glEnd();
}

void scene_2_carpet_2x2_manual()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 2); glVertex3f(-1, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
    glTexCoord2f(2, 0); glVertex3f(1, -1, 0);
    glTexCoord2f(2, 2); glVertex3f(1, 1, 0);
    glEnd();
}

void scene_3_carpet_4x4_manual()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 4); glVertex3f(-1, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
    glTexCoord2f(4, 0); glVertex3f(1, -1, 0);
    glTexCoord2f(4, 4); glVertex3f(1, 1, 0);
    glEnd();
}

void scene_4_carpet_rotated_1_manual()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();

    glRotatef(leftRightRotation, 0, 0, 1);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
    glEnd();

    glPopMatrix();
}

void scene_5_carpet_rotated_2_manual()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glMatrixMode(GL_TEXTURE);

    glPushMatrix();

    glTranslatef(0.5, 0.5, 0);
    glRotatef(leftRightRotation, 0, 0, 1);
    glTranslatef(-0.5, -0.5, 0);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glRotatef(leftRightRotation, 0, 0, 1);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
    glEnd();

    glPopMatrix();

    glMatrixMode(GL_TEXTURE);

    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

void scene_6_carpet_1x1_auto()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Для S: от -1 до 1 в X должно давать от 0 до 1 в текстуре
    GLfloat planeS[] = {0.5, 0.0, 0.0, 0.5}; // s = 0.5*x + 0.5
    GLfloat planeT[] = {0.0, 0.5, 0.0, 0.5}; // t = 0.5*y + 0.5

    glTexGenfv(GL_S, GL_OBJECT_PLANE, planeS);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, planeT);

    glBegin(GL_POLYGON);
    glVertex3f(-1, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(1, 1, 0);
    glEnd();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void scene_7_carpet_2x2_auto()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Для S: от -1 до 1 в X должно давать от 0 до 2 в текстуре
    GLfloat planeS[] = {1.0, 0.0, 0.0, 1.0}; // s = 1*x + 1
    GLfloat planeT[] = {0.0, 1.0, 0.0, 1.0}; // t = 1*y + 1

    glTexGenfv(GL_S, GL_OBJECT_PLANE, planeS);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, planeT);

    glBegin(GL_POLYGON);
    glVertex3f(-1, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(1, 1, 0);
    glEnd();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void scene_8_carpet_4x4_auto()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Для S: от -1 до 1 в X должно давать от 0 до 4 в текстуре
    GLfloat planeS[] = {2.0, 0.0, 0.0, 2.0}; // s = 2*x + 2
    GLfloat planeT[] = {0.0, 2.0, 0.0, 2.0}; // t = 2*y + 2

    glTexGenfv(GL_S, GL_OBJECT_PLANE, planeS);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, planeT);

    glBegin(GL_POLYGON);
    glVertex3f(-1, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(1, 1, 0);
    glEnd();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void scene_9_carpet_rotated_1_auto()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Базовые плоскости для 1x1 текстуры
    GLfloat planeS[] = {0.5f, 0.0f, 0.0f, 0.5f}; // s = 0.5*x + 0.5
    GLfloat planeT[] = {0.0f, 0.5f, 0.0f, 0.5f}; // t = 0.5*y + 0.5

    glTexGenfv(GL_S, GL_OBJECT_PLANE, planeS);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, planeT);

    glPushMatrix();

    glRotatef(leftRightRotation, 0, 0, 1);

    glBegin(GL_POLYGON);
    glVertex3f(-1, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(1, 1, 0);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void scene_10_carpet_rotated_2_auto()
{
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Поворот на угол A - умножение на матрицу:
    //   cos(A) -sin(A)
    //   sin(A)  cos(A)

    float angle = leftRightRotation * M_PI / 180;
    float cosA = cos(angle);
    float sinA = sin(angle);

    float scale = 0.5 / sqrt(2);

    // s = scale * cosA * x - scale * sinA * y + 0.5
    GLfloat planeS[] = {
        scale * cosA,  // A: cos компонента для X
        -scale * sinA, // B: sin компонента для Y
        0.0,           // C: Z компонента
        0.5            // D: смещение
    };

    // t = scale * sinA * x + scale * cosA * y + 0.5
    GLfloat planeT[] = {
        scale * sinA,  // A: sin компонента для X
        scale * cosA,  // B: -cos компонента для Y
        0.0,           // C: Z компонента
        0.5            // D: смещение
    };

    glTexGenfv(GL_S, GL_OBJECT_PLANE, planeS);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, planeT);

    glPushMatrix();

    glRotatef(leftRightRotation, 0, 0, 1);

    glBegin(GL_POLYGON);
    glVertex3f(-1, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(1, 1, 0);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void scene_11_dice()
{
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Массив текстур для каждой грани
    GLuint diceTextures[6] = {
        diceSide1Texture, diceSide2Texture, diceSide3Texture,
        diceSide4Texture, diceSide5Texture, diceSide6Texture};
    // GLuint diceTextures[6] = {
    //     catTexture, catTexture, catTexture,
    //     catTexture, catTexture, catTexture};

    // Вершины для каждой грани куба [грань][вершина][координата x,y,z]
    float vertices[6][4][3] = {
        // Передняя грань (Z = 1)
        {{-1, 1, 1}, {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}},
        // Задняя грань (Z = -1)
        {{1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1}},
        // Правая грань (X = 1)
        {{1, 1, 1}, {1, -1, 1}, {1, -1, -1}, {1, 1, -1}},
        // Левая грань (X = -1)
        {{-1, 1, -1}, {-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}},
        // Верхняя грань (Y = 1)
        {{-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}, {1, 1, -1}},
        // Нижняя грань (Y = -1)
        {{-1, -1, 1}, {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}}};

    // Плоскости генерации для каждой грани [грань][S/T][A,B,C,D]
    float planes[6][2][4] = {
        // Передняя грань (X для S, Y для T)
        {{0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, 0.5f, 0.0f, 0.5f}},
        // Задняя грань (-X для S, Y для T)
        {{-0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, 0.5f, 0.0f, 0.5f}},
        // Правая грань (-Z для S, Y для T)
        {{0.0f, 0.0f, -0.5f, 0.5f}, {0.0f, 0.5f, 0.0f, 0.5f}},
        // Левая грань (Z для S, Y для T)
        {{0.0f, 0.0f, 0.5f, 0.5f}, {0.0f, 0.5f, 0.0f, 0.5f}},
        // Верхняя грань (X для S, -Z для T)
        {{0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, 0.0f, -0.5f, 0.5f}},
        // Нижняя грань (X для S, Z для T)
        {{0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.5f, 0.5f}}};

    glPushMatrix();

    glRotatef(leftRightRotation, 0, 1, 0);
    glRotatef(upDownRotation, 1, 0, 0);

    for (int face = 0; face < 6; face++)
    {
        glBindTexture(GL_TEXTURE_2D, diceTextures[face]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexGenfv(GL_S, GL_OBJECT_PLANE, planes[face][0]);
        glTexGenfv(GL_T, GL_OBJECT_PLANE, planes[face][1]);

        glBegin(GL_QUADS);
        for (int vertex = 0; vertex < 4; vertex++)
        {
            glVertex3f(vertices[face][vertex][0], vertices[face][vertex][1], vertices[face][vertex][2]);
        }
        glEnd();
    }

    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void scene_12_cat()
{
    glBindTexture(GL_TEXTURE_2D, catTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, catMinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, catMagFilter);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

    // Для S: от -1 до 1 в X должно давать от 0 до 1 в текстуре
    GLfloat planeS[] = {0.5, 0.0, 0.0, 0.5}; // s = 0.5*x + 0.5
    GLfloat planeT[] = {0.0, 0.5, 0.0, 0.5}; // t = 0.5*y + 0.5

    glTexGenfv(GL_S, GL_OBJECT_PLANE, planeS);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, planeT);

    glPushMatrix();

    glScalef(catScale, catScale, 1);

    glBegin(GL_POLYGON);
    glVertex3f(-1, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(1, 1, 0);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

std::array scenes {
    scene_1_carpet_1x1_manual,
    scene_2_carpet_2x2_manual,
    scene_3_carpet_4x4_manual,
    scene_4_carpet_rotated_1_manual,
    scene_5_carpet_rotated_2_manual,
    scene_6_carpet_1x1_auto,
    scene_7_carpet_2x2_auto,
    scene_8_carpet_4x4_auto,
    scene_9_carpet_rotated_1_auto,
    scene_10_carpet_rotated_2_auto,
    scene_11_dice,
    scene_12_cat};

void displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 800, 800);
    glLoadIdentity();

    scenes[currentScene]();

    glutSwapBuffers();
}

void setupOpenGL()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setupGLUT(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow(sceneTitles[currentScene]);

    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialCallback);
}

void initialize(int argc, char **argv)
{
    setupGLUT(argc, argv);
    ilInit();
    setupOpenGL();
    loadAllTextures();
}

int main(int argc, char **argv)
{
    initialize(argc, argv);
    glutMainLoop();
    return 0;
}