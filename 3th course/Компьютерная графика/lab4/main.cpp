#include <GL/glut.h>
#include <cmath>

const float OFFSET_SPEED = 0.03f;
const int ANGLE_SPEED = 3;
const float DIRECTION_SPEED = 0.05f;

int sceneAngleY = 0;
int sceneAngleX = 0;

int currentScene = 1;

bool isScene1LightTypeSpot = false;

bool isScene2Light1Enabled = true;
bool isScene2Light2Enabled = true;

float scene3LightOffsetX = 0.0f;
float scene3LightOffsetY = 0.0f;

bool isScene4Light1Enabled = true;
bool isScene4Light2Enabled = true;

int scene5LightAngleX = 0;
int scene5LightAngleY = 0;

float scene6Light1DirectionX = 0.0f;
float scene6Light1DirectionY = 0.0f;
float scene6Light2DirectionX = 0.0f;
float scene6Light2DirectionY = 0.0f;
bool isScene6Light1Enabled = true;
bool isScene6Light2Enabled = true;

const char *sceneTitles[] = {
    "Сцена 1: Один источник",
    "Сцена 2: Два направленных источника",
    "Сцена 3: Один позиционный источник + блики",
    "Сцена 4: Два позиционных источника",
    "Сцена 5: Один движущийся позиционный источник",
    "Сцена 6: Два позиционных источника + конусы"};

void glSwitch(GLenum cap)
{
    if (glIsEnabled(cap)) glDisable(cap); else glEnable(cap);
}

void keyboardCallback(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
    {
        switch (currentScene)
        {
            case 1:
                isScene1LightTypeSpot = !isScene1LightTypeSpot;
                break;
        }
        break;
    }
    case '1':
    {
        switch (currentScene)
        {
        case 2:
            isScene2Light1Enabled = !isScene2Light1Enabled;
            break;
        case 4:
            isScene4Light1Enabled = !isScene4Light1Enabled;
            break;
        case 6:
            isScene6Light1Enabled = !isScene6Light1Enabled;
            break;
        }
        break;
    }
    case '2':
    {
        switch (currentScene)
        {
        case 2:
            isScene2Light2Enabled = !isScene2Light2Enabled;
            break;
        case 4:
            isScene4Light2Enabled = !isScene4Light2Enabled;
            break;
        case 6:
            isScene6Light2Enabled = !isScene6Light2Enabled;
            break;
        }
        break;
    }
    case 'w':
    {
        switch (currentScene)
        {
        case 3:
            scene3LightOffsetY += OFFSET_SPEED;
            break;
        case 5:
            scene5LightAngleX = (scene5LightAngleX - ANGLE_SPEED) % 360;
            break;
        case 6:
            scene6Light1DirectionY += DIRECTION_SPEED;
            break;
        }
        break;
    }
    case 'W':
    {
        switch (currentScene)
        {
        case 6:
            scene6Light2DirectionY += DIRECTION_SPEED;
            break;
        }
        break;
    }
    case 'a':
    {
        switch (currentScene)
        {
        case 3:
            scene3LightOffsetX -= OFFSET_SPEED;
            break;
        case 5:
            scene5LightAngleY = (scene5LightAngleY - ANGLE_SPEED) % 360;
            break;
        case 6:
            scene6Light1DirectionX -= DIRECTION_SPEED;
            break;
        }
        break;
    }
    case 'A':
    {
        switch (currentScene)
        {
        case 6:
            scene6Light2DirectionX -= DIRECTION_SPEED;
            break;
        }
        break;
    }
    case 's':
    {
        switch (currentScene)
        {
        case 3:
            scene3LightOffsetY -= OFFSET_SPEED;
            break;
        case 5:
            scene5LightAngleX = (scene5LightAngleX + ANGLE_SPEED) % 360;
            break;
        case 6:
            scene6Light1DirectionY -= DIRECTION_SPEED;
            break;
        }
        break;
    }
    case 'S':
    {
        switch (currentScene)
        {
        case 6:
            scene6Light2DirectionY -= DIRECTION_SPEED;
            break;
        }
        break;
    }
    case 'd':
    {
        switch (currentScene)
        {
        case 3:
            scene3LightOffsetX += OFFSET_SPEED;
            break;
        case 5:
            scene5LightAngleY = (scene5LightAngleY + ANGLE_SPEED) % 360;
            break;
        case 6:
            scene6Light1DirectionX += DIRECTION_SPEED;
            break;
        }
        break;
    }
    case 'D':
    {
        switch (currentScene)
        {
        case 6:
            scene6Light2DirectionX += DIRECTION_SPEED;
            break;
        }
        break;
    }
    }
    glutPostRedisplay();
}

void specialCallback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        sceneAngleX = (sceneAngleX - ANGLE_SPEED) % 360;
        break;
    case GLUT_KEY_DOWN:
        sceneAngleX = (sceneAngleX + ANGLE_SPEED) % 360;
        break;
    case GLUT_KEY_LEFT:
        sceneAngleY = (sceneAngleY - ANGLE_SPEED) % 360;
        break;
    case GLUT_KEY_RIGHT:
        sceneAngleY = (sceneAngleY + ANGLE_SPEED) % 360;
        break;
    case GLUT_KEY_F1:
        currentScene = 1;
        break;
    case GLUT_KEY_F2:
        currentScene = 2;
        break;
    case GLUT_KEY_F3:
        currentScene = 3;
        break;
    case GLUT_KEY_F4:
        currentScene = 4;
        break;
    case GLUT_KEY_F5:
        currentScene = 5;
        break;
    case GLUT_KEY_F6:
        currentScene = 6;
        break;
    }

    glutSetWindowTitle(sceneTitles[currentScene - 1]);
    glutPostRedisplay();
}

void drawTori()
{
    float spacing = 0.3f;
    float offset = 0.6f;

    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            for (int z = 0; z < 5; z++)
            {
                glPushMatrix();
                glTranslatef(x * spacing - offset, y * spacing - offset, z * spacing - offset);
                glutSolidTorus(0.05f, 0.1f, 20, 20);
                glPopMatrix();
            }
        }
    }
}

void scene_1_one_source()
{
    glEnable(GL_LIGHT0);

    GLfloat offsetZ = 1.2f;

    glTranslatef(0, 0, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    glTranslatef(0, 0, -offsetZ);

    GLfloat position[] = {0, 0, offsetZ, isScene1LightTypeSpot ? 1.0f : 0.0f};
    GLfloat direction[] = {0.0f, 0.0f, -1.0f};
    GLfloat ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spotCutoff = isScene1LightTypeSpot ? 20.0f : 180.0f;
    GLfloat spotExponent = isScene1LightTypeSpot ? 10.0f : 0.0f;

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

    GLfloat matAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat matDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat matSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat matShininess = 0.0f;
    GLfloat matEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

    drawTori();

    glDisable(GL_LIGHT0);
}

void scene_2_two_directional_sources()
{
    if (isScene2Light1Enabled) glEnable(GL_LIGHT0);
    if (isScene2Light2Enabled) glEnable(GL_LIGHT1);

    GLfloat offsetZ = 1.2f;

    GLfloat offsetX0 = -1.0f;

    glTranslatef(offsetX0, 0, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 1.0f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    glTranslatef(-offsetX0, 0, -offsetZ);

    GLfloat position0[] = {offsetX0, 0, offsetZ, 0};
    GLfloat direction0[] = {0.0f, 0.0f, -1.0f};
    GLfloat ambient0[] = {0.3f, 0.3f, 1.0f, 1.0f};
    GLfloat diffuse0[] = {0.3f, 0.3f, 1.0f, 1.0f};
    GLfloat specular0[] = {0.3f, 0.3f, 1.0f, 1.0f};
    GLfloat spotCutoff0 = 180.0f;
    GLfloat spotExponent0 = 0.0f;

    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent0);

    GLfloat offsetX1 = 1.0f;

    glTranslatef(offsetX1, 0, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.3f, 0.3f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    glTranslatef(-offsetX1, 0, -offsetZ);

    GLfloat position1[] = {offsetX1, 0, offsetZ, 0};
    GLfloat direction1[] = {0.0f, 0.0f, -1.0f};
    GLfloat ambient1[] = {1.0f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuse1[] = {1.0f, 0.3f, 0.3f, 1.0f};
    GLfloat specular1[] = {1.0f, 0.3f, 0.3f, 1.0f};
    GLfloat spotCutoff1 = 180.0f;
    GLfloat spotExponent1 = 0.0f;

    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff1);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent1);

    GLfloat matAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat matDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat matSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat matShininess = 0.0f;
    GLfloat matEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

    drawTori();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
}

void scene_3_one_spot_source_with_specular()
{
    glEnable(GL_LIGHT0);

    GLfloat offsetZ = 1.2f;

    glTranslatef(scene3LightOffsetX, scene3LightOffsetY, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    glTranslatef(-scene3LightOffsetX, -scene3LightOffsetY, -offsetZ);

    GLfloat position[] = {scene3LightOffsetX, scene3LightOffsetY, offsetZ, 1};
    GLfloat direction[] = {0.0f, 0.0f, -1.0f};
    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spotCutoff = 180.0f;
    GLfloat spotExponent = 0.0f;

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

    GLfloat matAmbient[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat matDiffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matShininess = 100.0f;
    GLfloat matEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

    drawTori();

    glDisable(GL_LIGHT0);
}

void scene_4_two_spot_sources()
{
    if (isScene4Light1Enabled) glEnable(GL_LIGHT0);
    if (isScene4Light2Enabled) glEnable(GL_LIGHT1);

    GLfloat offsetZ = 1.2f;

    GLfloat offsetX0 = -0.3f;

    glTranslatef(offsetX0, 0, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 1.0f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    glTranslatef(-offsetX0, 0, -offsetZ);

    GLfloat position0[] = {offsetX0, 0, offsetZ, 1};
    GLfloat direction0[] = {0.0f, 0.0f, -1.0f};
    GLfloat ambient0[] = {0.2f, 0.2f, 0.5f, 1.0f};
    GLfloat diffuse0[] = {0.2f, 0.2f, 0.5f, 1.0f};
    GLfloat specular0[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat spotCutoff0 = 45.0f;
    GLfloat spotExponent0 = 10.0f;

    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent0);

    GLfloat offsetX1 = 0.3f;

    glTranslatef(offsetX1, 0, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.3f, 0.3f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    glTranslatef(-offsetX1, 0, -offsetZ);

    GLfloat position1[] = {offsetX1, 0, offsetZ, 1};
    GLfloat direction1[] = {0.0f, 0.0f, -1.0f};
    GLfloat ambient1[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse1[] = {0.5f, 0.2f, 0.2f, 1.0f};
    GLfloat specular1[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat spotCutoff1 = 45.0f;
    GLfloat spotExponent1 = 10.0f;

    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff1);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent1);

    GLfloat matAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matShininess = 100.0f;
    GLfloat matEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

    drawTori();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
}

void scene_5_one_moving_spot_source()
{
    glEnable(GL_LIGHT0);

    GLfloat offsetZ = 1.2f;

    glPushMatrix();

    glRotatef(scene5LightAngleX, 1, 0, 0);
    glRotatef(scene5LightAngleY, 0, 1, 0);
    glTranslatef(0, 0, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    GLfloat position[] = {0, 0, 0, 1};
    GLfloat direction[] = {0.0f, 0.0f, -1.0f};
    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spotCutoff = 180.0f;
    GLfloat spotExponent = 0.0f;

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

    glPopMatrix();

    GLfloat matAmbient[] = {0.3f, 1.0f, 0.3f, 1.0f};
    GLfloat matDiffuse[] = {0.3f, 1.0f, 0.3f, 1.0f};
    GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matShininess = 100.0f;
    GLfloat matEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

    drawTori();

    glDisable(GL_LIGHT0);
}

void scene_6_two_spot_sources_with_cones()
{
    if (isScene6Light1Enabled) glEnable(GL_LIGHT0);
    if (isScene6Light2Enabled) glEnable(GL_LIGHT1);

    GLfloat offsetZ = 1.2f;

    GLfloat offsetX0 = -0.3f;

    glTranslatef(offsetX0, 0, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 1.0f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    glTranslatef(-offsetX0, 0, -offsetZ);

    GLfloat position0[] = {offsetX0, 0, offsetZ, 1};
    GLfloat direction0[] = {scene6Light1DirectionX, scene6Light1DirectionY, -1.0f};
    GLfloat ambient0[] = {0.2f, 0.2f, 0.5f, 1.0f};
    GLfloat diffuse0[] = {0.2f, 0.2f, 0.5f, 1.0f};
    GLfloat specular0[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat spotCutoff0 = 20.0f;
    GLfloat spotExponent0 = 10.0f;

    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent0);

    GLfloat offsetX1 = 0.3f;

    glTranslatef(offsetX1, 0, offsetZ);

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.3f, 0.3f);
    glutSolidSphere(0.05f, 10, 10);
    glEnable(GL_LIGHTING);

    glTranslatef(-offsetX1, 0, -offsetZ);

    GLfloat position1[] = {offsetX1, 0, offsetZ, 1};
    GLfloat direction1[] = {scene6Light2DirectionX, scene6Light2DirectionY, -1.0f};
    GLfloat ambient1[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuse1[] = {0.5f, 0.2f, 0.2f, 1.0f};
    GLfloat specular1[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat spotCutoff1 = 20.0f;
    GLfloat spotExponent1 = 10.0f;

    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff1);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent1);

    GLfloat matAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matShininess = 100.0f;
    GLfloat matEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

    drawTori();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
}

void (*scenes[])() = {
    scene_1_one_source,
    scene_2_two_directional_sources,
    scene_3_one_spot_source_with_specular,
    scene_4_two_spot_sources,
    scene_5_one_moving_spot_source,
    scene_6_two_spot_sources_with_cones};

void scene()
{
    scenes[currentScene - 1]();
}

void displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1000, 1000);
    glLoadIdentity();

    glRotatef(sceneAngleY, 0, 1, 0);
    glRotatef(sceneAngleX, 1, 0, 0);

    scene();

    glutSwapBuffers();
}

void setupOpenGL()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1, 10);
    glTranslatef(0.0f, 0.0f, -4.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setupGLUT(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow(sceneTitles[currentScene - 1]);

    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialCallback);
}

void initialize(int argc, char **argv)
{
    setupGLUT(argc, argv);
    setupOpenGL();
}

int main(int argc, char **argv)
{
    initialize(argc, argv);
    glutMainLoop();
    return 0;
}