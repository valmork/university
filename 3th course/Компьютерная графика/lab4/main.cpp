// g++ -o lighting_lab main.cpp -framework GLUT -framework OpenGL -Wno-deprecated-declarations

// почитать про direction источника и как включать выключать и менять источники

/*
  OpenGL/GLUT Лабораторная работа: Освещение
  Задания 1-5 по освещению в OpenGL
 
  Управление:
    1-5 — переключение между заданиями
    ESC/Q — выход
 
  Задание 1:
    A/D — Фоновый: уменьшить/увеличить
    S/W — Рассеянный: уменьшить/увеличить
    Z/X — Зеркальный: уменьшить/увеличить
    M — переключение режима: фоновый/рассеянный/зеркальный/все/конус
    [/] — угол конуса -/+
    I/K — направление конуса по Y (вверх/вниз)
    J/L — позиция источника по X
    U/O — позиция источника по Y
 
  Задание 2:
    P — вкл/выкл позиционный источник
    N — вкл/выкл направленный источник
 
  Задание 3:
    R — вращение источника вокруг оси Y
 
  Задание 4:
    R — вращение направленного источника
 
  Задание 5:
    Стрелки  — вращение сцены вокруг источника в начале координат
 */

#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*  Глобальное состояние  */

static int   task = 1;              /* Текущее задание (1..5) */

/* Задание 1 — режимы и параметры источника */
typedef enum { MODE_AMBIENT=0, MODE_DIFFUSE, MODE_SPECULAR, MODE_ALL, MODE_CONE } Task1Mode;
static Task1Mode t1mode = MODE_AMBIENT;
static float t1ambient  = 0.3f;
static float t1diffuse  = 0.8f;
static float t1specular = 1.0f;
static float coneAngle  = 30.0f;
static float coneDirX   = 0.0f;
static float coneDirY   = -1.0f;
static float coneDirZ   = -1.0f;
static float lightX     = 0.0f;
static float lightY     = 3.0f;
static float lightZ     = 0.0f;

/* Задание 2 */
static int   t2posOn  = 1;
static int   t2dirOn  = 1;

/* Задание 3 */
static float t3angle  = 0.0f;
static int   t3rotate = 0;

/* Задание 4 */
static float t4angle  = 0.0f;
static int   t4rotate = 1;

/* Задание 5 */
static float t5rotX   = 0.0f;
static float t5rotY   = 0.0f;

/*  Вспомогательные функции  */

static void setMaterial(float r, float g, float b, float shininess) {
    GLfloat amb[]  = {r*0.3f, g*0.3f, b*0.3f, 1};
    GLfloat dif[]  = {r, g, b, 1};
    GLfloat spe[]  = {1,1,1,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

/* Нарисовать набор разнородных объектов сцены */
static void drawScene(void) {
    /* Пол — тусклый серый */
    setMaterial(0.4f, 0.4f, 0.4f, 5.0f);
    glPushMatrix();
    glTranslatef(0, -1.5f, 0);
    glScalef(6, 0.1f, 6);
    glutSolidCube(1.0);
    glPopMatrix();

    /* Сфера — красная, зеркальная */
    setMaterial(0.9f, 0.1f, 0.1f, 128.0f);
    glPushMatrix();
    glTranslatef(-2.0f, 0, 0);
    glutSolidSphere(0.7, 32, 32);
    glPopMatrix();

    /* Тор — синий, матовый */
    setMaterial(0.1f, 0.2f, 0.9f, 8.0f);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.25, 0.6, 24, 24);
    glPopMatrix();

    /* Куб — зелёный, средний блеск */
    setMaterial(0.1f, 0.8f, 0.2f, 32.0f);
    glPushMatrix();
    glTranslatef(2.0f, -0.5f, 0);
    glRotatef(30, 0, 1, 0);
    glutSolidCube(0.9);
    glPopMatrix();

    /* Конус — жёлтый, матовый */
    setMaterial(0.9f, 0.8f, 0.1f, 4.0f);
    glPushMatrix();
    glTranslatef(0, -1.4f, -2.0f);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.5, 1.2, 24, 16);
    glPopMatrix();

    /* Чайник — белый, очень зеркальный */
    setMaterial(0.95f, 0.95f, 0.95f, 200.0f);
    glPushMatrix();
    glTranslatef(0, -0.6f, 2.0f);
    glScalef(0.6f, 0.6f, 0.6f);
    glutSolidTeapot(1.0);
    glPopMatrix();
}

/* Маленький жёлтый шарик — маркер позиции источника */
static void drawLightMarker(float x, float y, float z) {
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.08, 12, 12);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

static void setupProjection(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(45.0, (double)w/h, 0.5, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

static void setupCamera(void) {
    glLoadIdentity();
    gluLookAt(0, 3, 8,   0, 0, 0,   0, 1, 0);
}

/* HUD — вывод строки текста на экран */
static void drawText(const char *s, int x, int y) {
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1,1,0);
    glRasterPos2i(x, h - y);
    for (const char *c = s; *c; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
}

/*  Отрисовка каждого задания  */

static void renderTask1(void) {
    setupCamera();

    /* Глобальный фоновый свет сцены */
    GLfloat gAmb[] = {0.25f, 0.25f, 0.25f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gAmb);

    if (t1mode == MODE_AMBIENT) {
        /* Только фоновый: выключаем GL_LIGHT0 */
        glDisable(GL_LIGHT0);
    } else {
        /* Позиционный источник */
        GLfloat pos[] = {lightX, lightY, lightZ, 1.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, pos);

        GLfloat zero[] = {0,0,0,1};

        if (t1mode == MODE_DIFFUSE) {
            GLfloat amb[] = {0,0,0,1};
            GLfloat dif[] = {t1diffuse,t1diffuse,t1diffuse,1};
            glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
            glLightfv(GL_LIGHT0, GL_SPECULAR, zero);
        } else if (t1mode == MODE_SPECULAR) {
            GLfloat spe[] = {t1specular,t1specular,t1specular,1};
            glLightfv(GL_LIGHT0, GL_AMBIENT,  zero);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  zero);
            glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
        } else { /* ВСЕ or КОНУС */
            GLfloat amb[] = {t1ambient, t1ambient, t1ambient, 1};
            GLfloat dif[] = {t1diffuse, t1diffuse, t1diffuse, 1};
            GLfloat spe[] = {t1specular,t1specular,t1specular,1};
            glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
            glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
        }

        if (t1mode == MODE_CONE) {
            GLfloat dir[] = {coneDirX, coneDirY, coneDirZ};
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
            glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, coneAngle);
            glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f);
        } else {
            glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f); /* без конуса */
        }
        glEnable(GL_LIGHT0);
        drawLightMarker(lightX, lightY, lightZ);
    }

    drawScene();

    /* HUD */
    char buf[256];
    const char *mnames[] = {"ТОЛЬКО ФОНОВЫЙ","ТОЛЬКО РАССЕЯННЫЙ","ТОЛЬКО ЗЕРКАЛЬНЫЙ","ВСЕ КОМПОНЕНТЫ","ВСЕ + КОНУС"};
    snprintf(buf, sizeof buf, "Задание 1 | Режим [M]: %s", mnames[t1mode]);
    drawText(buf, 8, 20);
    if (t1mode == MODE_CONE)
        snprintf(buf,sizeof buf,"Угол конуса: %.0f  Направление:(%.2f,%.2f,%.2f)  Позиция источника:(%.1f,%.1f,%.1f)",
                 coneAngle,coneDirX,coneDirY,coneDirZ,lightX,lightY,lightZ);
    else
        snprintf(buf,sizeof buf,"Фоновый=%.2f  Рассеянный=%.2f  Зеркальный=%.2f  Позиция:(%.1f,%.1f,%.1f)",
                 t1ambient,t1diffuse,t1specular,lightX,lightY,lightZ);
    drawText(buf, 8, 36);
    drawText("Клавиши: M-режим  A/D-фон  S/W-рассеянный  Z/X-зеркальный  [/]-угол  IJKL/UO-направление/позиция", 8, 52);
}

static void renderTask2(void) {
    setupCamera();

    GLfloat gAmb[] = {0.1f,0.1f,0.1f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gAmb);

    /* Позиционный источник — LIGHT0 */
    if (t2posOn) {
        GLfloat pos[] = {2.0f, 3.0f, 2.0f, 1.0f};
        GLfloat amb[] = {0.1f, 0.1f, 0.1f, 1};
        GLfloat dif[] = {1.0f, 0.6f, 0.1f, 1};  /* тёплый */
        GLfloat spe[] = {1.0f, 1.0f, 1.0f, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
        glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
        glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
        glEnable(GL_LIGHT0);
        drawLightMarker(2.0f, 3.0f, 2.0f);
    } else glDisable(GL_LIGHT0);

    /* Направленный источник — LIGHT1 */
    if (t2dirOn) {
        GLfloat dir[] = {-1.0f, -1.0f, -0.5f, 0.0f}; /* w=0 → направленный */
        GLfloat amb[] = {0.05f, 0.05f, 0.15f, 1};
        GLfloat dif[] = {0.3f,  0.3f,  1.0f,  1};  /* холодный синий */
        GLfloat spe[] = {0.8f,  0.8f,  1.0f,  1};
        glLightfv(GL_LIGHT1, GL_POSITION, dir);
        glLightfv(GL_LIGHT1, GL_AMBIENT,  amb);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,  dif);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spe);
        glEnable(GL_LIGHT1);
    } else glDisable(GL_LIGHT1);

    drawScene();

    char buf[128];
    snprintf(buf,sizeof buf,"Задание 2 | Позиционный[P]:%s  Направленный[N]:%s",
             t2posOn?"ВКЛ":"ВЫКЛ", t2dirOn?"ВКЛ":"ВЫКЛ");
    drawText(buf, 8, 20);
    drawText("P - вкл/выкл позиционный (тёплый)   N - вкл/выкл направленный (холодный)", 8, 36);
}

static void renderTask3(void) {
    setupCamera();

    GLfloat gAmb[] = {0.15f,0.15f,0.15f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gAmb);

    /* Вычислить позицию вращающегося источника */
    float rad = (float)(t3angle * M_PI / 180.0);
    float lx  = 3.0f * sinf(rad);
    float ly  = 2.0f;
    float lz  = 3.0f * cosf(rad);

    GLfloat pos[] = {lx, ly, lz, 1.0f};
    GLfloat amb[] = {0.1f,0.1f,0.1f,1};
    GLfloat dif[] = {1.0f,1.0f,1.0f,1};
    GLfloat spe[] = {1.0f,1.0f,1.0f,1};
    // Конус направлен вдоль −Z мирового пространства
    GLfloat spotDir[] = {0.0f, 0.0f, -1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 35.0f);
    glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, 6.0f);
    glEnable(GL_LIGHT0);

    drawLightMarker(lx, ly, lz);
    drawScene();

    char buf[128];
    snprintf(buf,sizeof buf,"Задание 3 | Вращающийся прожектор (конус вдоль -Z)  Угол=%.1f  [R] вкл/выкл вращение", t3angle);
    drawText(buf, 8, 20);
    drawText("R - запустить/остановить вращение", 8, 36);
}

static void renderTask4(void) {
    setupCamera();

    GLfloat gAmb[] = {0.1f,0.1f,0.1f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gAmb);

    /* Направленный источник «обходит» сцену по кругу */
    float rad = (float)(t4angle * M_PI / 180.0);
    /* Направление от источника к центру (0,0,0) */
    float dx = -sinf(rad);
    float dy = -0.5f;       /* чуть сверху вниз */
    float dz = -cosf(rad);
    /* w=0 → направленный (бесконечно далёкий) */
    GLfloat dir[] = {dx, dy, dz, 0.0f};

    GLfloat amb[] = {0.1f, 0.05f,0.0f, 1};
    GLfloat dif[] = {1.0f, 0.85f,0.5f, 1};  /* тёплый солнечный */
    GLfloat spe[] = {1.0f, 1.0f, 1.0f, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, dir);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
    glEnable(GL_LIGHT0);

    /* Нарисуем маркер «далёкого» источника */
    float mx = 5.0f * sinf(rad);
    float my = 3.0f;
    float mz = 5.0f * cosf(rad);
    drawLightMarker(mx, my, mz);

    drawScene();

    char buf[128];
    snprintf(buf,sizeof buf,"Задание 4 | Направленный источник вращается вокруг сцены  Угол=%.1f", t4angle);
    drawText(buf, 8, 20);
    drawText("Автоматическое вращение направленного света, всегда направлен на центр", 8, 36);
}

static void renderTask5(void) {
    glLoadIdentity();
    gluLookAt(0, 3, 8,   0, 0, 0,   0, 1, 0);

    GLfloat gAmb[] = {0.15f,0.15f,0.15f,1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gAmb);

    /* Источник в начале мировых координат — задаём до вращения сцены */
    GLfloat pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat amb[] = {0.15f,0.15f,0.15f,1};
    GLfloat dif[] = {1.0f, 1.0f, 1.0f, 1};
    GLfloat spe[] = {1.0f, 1.0f, 1.0f, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
    glEnable(GL_LIGHT0);

    drawLightMarker(0, 0, 0);  /* маркер источника */

    /* Вращаем сцену вокруг источника */
    glRotatef(t5rotX, 1, 0, 0);
    glRotatef(t5rotY, 0, 1, 0);

    drawScene();

    char buf[128];
    snprintf(buf,sizeof buf,"Задание 5 | Источник в центре координат, сцена вращается  ВращX=%.1f  ВращY=%.1f", t5rotX, t5rotY);
    drawText(buf, 8, 20);
    drawText("Стрелки - вращать сцену вокруг неподвижного источника света", 8, 36);
}

/*  Колбэки GLUT  */

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Выключить все источники по умолчанию перед каждым кадром */
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

    setupProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (task) {
        case 1: renderTask1(); break;
        case 2: renderTask2(); break;
        case 3: renderTask3(); break;
        case 4: renderTask4(); break;
        case 5: renderTask5(); break;
    }

    /* Заголовок задания */
    char title[64];
    snprintf(title, sizeof title, "Задание %d/5  [1-5 переключение, ESC выход]", task);
    drawText(title, 8, glutGet(GLUT_WINDOW_HEIGHT) - 10);

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
}

static void timer(int v) {
    (void)v;
    if (task == 3 && t3rotate) t3angle += 0.8f;
    if (task == 4 && t4rotate) t4angle += 0.5f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

static void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;
    switch (key) {
    /* Переключение заданий */
    case '1': task = 1; break;
    case '2': task = 2; break;
    case '3': task = 3; break;
    case '4': task = 4; break;
    case '5': task = 5; break;

    case 27: case 'q': case 'Q': exit(0); break;

    /*  Задание 1  */
    case 'm': case 'M':
        t1mode = (Task1Mode)((t1mode + 1) % 5); break;
    case 'a': t1ambient  -= 0.05f; if (t1ambient  < 0) t1ambient  = 0; break;
    case 'd': t1ambient  += 0.05f; if (t1ambient  > 1) t1ambient  = 1; break;
    case 's': t1diffuse  -= 0.05f; if (t1diffuse  < 0) t1diffuse  = 0; break;
    case 'w': t1diffuse  += 0.05f; if (t1diffuse  > 1) t1diffuse  = 1; break;
    case 'z': t1specular -= 0.05f; if (t1specular < 0) t1specular = 0; break;
    case 'x': t1specular += 0.05f; if (t1specular > 1) t1specular = 1; break;
    case '[': coneAngle -= 2.0f; if (coneAngle <  5) coneAngle =  5; break;
    case ']': coneAngle += 2.0f; if (coneAngle > 90) coneAngle = 90; break;
    case 'i': coneDirY += 0.1f; break;
    case 'k': coneDirY -= 0.1f; break;
    case 'j': lightX -= 0.2f; break;
    case 'l': lightX += 0.2f; break;
    case 'u': lightY += 0.2f; break;
    case 'o': lightY -= 0.2f; break;

    /*  Задание 2  */
    case 'p': case 'P': t2posOn = !t2posOn; break;
    case 'n': case 'N': t2dirOn = !t2dirOn; break;

    /* Задания 3, 4 */
    case 'r': case 'R':
        if (task == 3) t3rotate = !t3rotate;
        break;
    }
    glutPostRedisplay();
}

static void specialKey(int key, int x, int y) {
    (void)x; (void)y;
    if (task == 5) {
        switch (key) {
        case GLUT_KEY_UP:    t5rotX -= 3.0f; break;
        case GLUT_KEY_DOWN:  t5rotX += 3.0f; break;
        case GLUT_KEY_LEFT:  t5rotY -= 3.0f; break;
        case GLUT_KEY_RIGHT: t5rotY += 3.0f; break;
        }
        glutPostRedisplay();
    }
}

/* Инициализация */

static void init(void) {
    glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    /* Нормали автоматически нормализуются */
    glEnable(GL_NORMALIZE);

    /* Параметры LIGHT1 (для задания 2) */
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Лабораторная работа: Освещение в OpenGL (Задания 1-5)");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutTimerFunc(16, timer, 0);

    printf("\n=== Лабораторная работа: Освещение в OpenGL ===\n");
    printf("Нажмите 1-5 для переключения заданий, ESC для выхода\n\n");
    printf("Задание 1: M - переключение режимов (фоновый/рассеянный/зеркальный/все/конус)\n");
    printf("        A/D - фоновый, S/W - рассеянный, Z/X - зеркальный\n");
    printf("        [ / ] - угол конуса, I/K - направление конуса по Y\n");
    printf("        J/L - позиция источника X, U/O - позиция источника Y\n");
    printf("Задание 2: P - вкл/выкл позиционный, N - вкл/выкл направленный\n");
    printf("Задание 3: R - вкл/выкл вращение прожектора вокруг Y\n");
    printf("Задание 4: Направленный источник автоматически вращается вокруг сцены\n");
    printf("Задание 5: Стрелки - вращение сцены вокруг неподвижного источника в центре\n\n");

    glutMainLoop();
    return 0;
}