//g++ -o snowman2 vers2.cpp -framework OpenGL -framework GLUT -arch arm64 -Wno-deprecated
// используется OpenGl версии 1.x с фиксированным конвейером

#include <math.h>
#include <cstdio>
#include <functional>
#include <GLUT/glut.h>

// Переменные управления вращением и состоянием
int rot = 0;  // Угол вращения вокруг оси Y (управляется стрелками влево/вправо)
int ro  = 0;  // Дополнительный угол вращения (управляется стрелками вверх/вниз)
int ex  = 0;  // Текущая сцена (F1-F10)

// Константы размеров снеговика
inline constexpr float smRad    = 0.38f;   // Радиус основного тела
inline constexpr float smRadH   = 0.125f;  // Радиус головы
inline constexpr float smRadMin = 0.02f;   // Радиус глаз
inline constexpr float coneHeight = 0.2f;  // Высота носа (конуса)
inline constexpr float coneBase   = 0.03f; // Радиус основания носа
float S = 0.7f;  // Коэффициент масштабирования для каждого следующего снеговика

// Обработка специальных клавиш (стрелки и F1-F10)
void specialkeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:  rot -= 5; break;   // Вращение влево
        case GLUT_KEY_RIGHT: rot += 5; break;   // Вращение вправо
        case GLUT_KEY_UP:    ro  += 5; break;   // Дополнительное вращение вверх
        case GLUT_KEY_DOWN:  ro  -= 5; break;   // Дополнительное вращение вниз
        default: ex = key;   break;             // Переключение сцены (F1-F10)
    }
    glutPostRedisplay();  // Перерисовать сцену
}

// Рисование координатных осей (красная X, зелёная Y, синяя Z) 
void drawAxes() {
    float L = smRad + 0.15f;  // Длина осей
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glColor3f(1,0,0); glVertex3f(-L,0,0); glVertex3f(L,0,0);   // Ось X (красная)
        glColor3f(0,1,0); glVertex3f(0,-L,0); glVertex3f(0,L,0);   // Ось Y (зелёная)
        glColor3f(0,0,1); glVertex3f(0,0,-L); glVertex3f(0,0,L);   // Ось Z (синяя)
    glEnd();
    glLineWidth(1.0f);
}

// Рисование снеговика с произвольными трансформациями 
// Параметры:
//   transform — лямбда-функция с трансформациями (translate/rotate/scale)
//   drawLocalAxes — показывать ли локальные оси координат
//   axisCounterRot — инверсия вращения для осей (чтобы они не вращались)
void drawSnowman(std::function<void()> transform,
                 bool drawLocalAxes = false,
                 std::function<void()> axisCounterRot = nullptr)
{
    float y = 0.0f;

    // Рисование локальных осей (если нужно)
    if (drawLocalAxes) {
        glPushMatrix();
        transform();
        if (axisCounterRot) axisCounterRot();  // Отменяем вращение для осей
        drawAxes();
        glPopMatrix();
    }

    //  Тело снеговика (большая сфера) 
    glPushMatrix();
    transform();
    glColor3f(1,1,1);  // Белый цвет
    glutSolidSphere(smRad, 30, 30);  // Сфера с 30x30 сегментами
    glPopMatrix();

    y += smRad + smRadH;  // Смещение для головы

    //  Голова снеговика (средняя сфера) 
    glPushMatrix();
    transform();
    glTranslatef(0, y, 0);  // Поднимаем голову над телом
    glColor3f(1,1,1);
    glutSolidSphere(smRadH, 20, 20);
    glPopMatrix();

    y += smRadMin;  // Смещение для носа и глаз

    //  Нос (красный конус) 
    glPushMatrix();
    transform();
    glColor3f(1, 0.3f, 0.3f);  // Красный цвет
    glTranslatef(0, y - coneBase/2, coneHeight/2 - 0.01f);
    glutSolidCone(coneBase, coneHeight, 20, 2);  // Конус
    glPopMatrix();

    //  Левый глаз (чёрная сфера) 
    glPushMatrix();
    transform();
    glColor3f(0,0,0);  // Чёрный цвет
    glTranslatef(-0.035f, y + 0.035f, coneHeight/2);
    glutSolidSphere(smRadMin, 10, 10);
    glPopMatrix();

    //  Правый глаз (чёрная сфера) 
    glPushMatrix();
    transform();
    glColor3f(0,0,0);
    glTranslatef( 0.035f, y + 0.035f, coneHeight/2);
    glutSolidSphere(smRadMin, 10, 10);
    glPopMatrix();
}

//  Сцена F1: разобранный снеговик (все части в ряд) 
void drawSnowManDecomposed() {
    drawAxes();
    float x = 0;

    // Тело
    glPushMatrix(); glTranslatef(x, smRad, 0);
        glColor3f(1,1,1); glutSolidSphere(smRad, 30, 30);
    glPopMatrix();
    x += smRad + smRadH + 0.02f;

    // Голова
    glPushMatrix(); glTranslatef(x, smRadH, 0);
        glColor3f(1,1,1); glutSolidSphere(smRadH, 20, 20);
    glPopMatrix();
    x += smRadH + smRadMin + 0.02f;

    // Левый глаз
    glPushMatrix(); glTranslatef(x, smRadMin, 0);
        glColor3f(0,0,0); glutSolidSphere(smRadMin, 10, 10);
    glPopMatrix();
    x += smRadMin*2 + 0.01f;

    // Правый глаз
    glPushMatrix(); glTranslatef(x, smRadMin, 0);
        glColor3f(0,0,0); glutSolidSphere(smRadMin, 10, 10);
    glPopMatrix();
    x += 2*smRadMin + coneBase + 0.02f;

    // Нос
    glPushMatrix();
        glTranslatef(x, 0, 0);
        glColor3f(1, 0.3f, 0.3f);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(coneBase, coneHeight, 20, 2);
    glPopMatrix();
}

//  Главная функция рисования сцены 
void scene() {
    glPushMatrix();

    switch (ex) {

    //  F1: разобранный снеговик 
    case 0:
    case GLUT_KEY_F1:
        drawSnowManDecomposed();
        break;

    //  F2: один снеговик, вращение вокруг оси Y 
    case GLUT_KEY_F2:
        drawAxes();
        drawSnowman([&]{ glRotatef(rot, 0,1,0); });
        break;

    // F3: три снеговика вдоль оси X, каждый меньше и вращается 
    case GLUT_KEY_F3: {
        struct { float shift, scale; } cfg[3] = {
            { 0,                                    1      },  // 1й: на месте
            { (1+0.7f)*smRad,                       S      },  // 2й: сдвинут и масштабирован
            { (1+2*0.7f+0.7f*0.7f)*smRad,          S*S    },  // 3й: ещё дальше и меньше
        };
        for (auto& c : cfg) {
            drawSnowman(
                [&]{ glRotatef(rot,0,1,0); glTranslatef(c.shift,0,0);
                     glScalef(c.scale,c.scale,c.scale); },
                true,
                [&]{ glRotatef(-rot,0,1,0); }  // Оси не вращаются
            );
        }
        drawAxes();  // Глобальные оси
        break;
    }

    // F9: три снеговика вдоль оси Y (вертикально) 
    case GLUT_KEY_F9: {

        drawAxes();

        float s1 = S;
        float s2 = S * S;

        // Смещения по Y
        // снеговики касаются:
        // голова нижнего ↔ большая сфера верхнего

        float y0 = 0.0f;

        float y1 =
            smRad + 2 * smRadH + smRad * s1;

        float y2 =
            y1 + (smRad + smRadH) * s1 + smRad * s2 + smRadH - 0.05f;

        // 1-й снеговик вращение вокруг мировой Z
        drawSnowman([&]{

            glRotatef(rot, 0,0,1);
            glTranslatef(0, y0, 0);

        }, true, nullptr);

        // 2-й снеговик мировая Z + локальная Y
        drawSnowman([&]{

            // движение вокруг мировой Z
            glRotatef(rot, 0,0,1);

            // положение снеговика
            glTranslatef(0, y1, 0);

            // компенсируем наклон локальной системы
            glRotatef(-rot, 0,0,1);

            // собственное вращение вокруг локальной Y
            glRotatef(ro, 0,1,0);

            // возвращаем мировой поворот
            glRotatef(rot, 0,0,1);

            // масштаб
            glScalef(s1, s1, s1);

        }, true,
        [&]{

            // компенсация вращений для осей
            glRotatef(-rot,0,0,1);
            glRotatef(-ro,0,1,0);
            glRotatef(rot,0,0,1);

        });

        // 3-й снеговик неподвижен
        drawSnowman([&]{

            glTranslatef(0, y2, 0);
            glScalef(s2, s2, s2);

        }, true, nullptr);

        break;
    }

    // F4: вращение вокруг оси Z через точку носа
    case GLUT_KEY_F4: {
        drawAxes();
        // 1й снеговик: вращение вокруг Z
        drawSnowman([&]{ glRotatef(-rot,0,0,1); });

        float scale = S;
        float shift = (1+0.7f)*smRad;
        const float noseY = (smRad+smRadH+smRadMin)*scale;
        const float noseZ = shift;

        // 2й снеговик: вращение вокруг точки носа 1го
        drawSnowman([&]{
            glTranslatef(0,noseY,noseZ);
            glRotatef(rot,0,0,1);
            glTranslatef(0,-noseY,-noseZ);
            glTranslatef(0,0,shift);
            glScalef(scale,scale,scale);
        }, true, nullptr);

        // 3й снеговик: неподвижен
        float sh3 = (1+2*0.7f+0.7f*0.7f)*smRad;
        float sc3 = S*S;
        drawSnowman([&]{
            glTranslatef(0,0,sh3);
            glScalef(sc3,sc3,sc3);
        }, true, nullptr);
        break;
    }

    // F5: вращение вокруг диагонали (1,1,1)
    case GLUT_KEY_F5: {
        drawAxes();
        auto base = [&]{ glRotatef(rot,1,1,1); glRotatef(ro,0,1,0); };

        drawSnowman(base);

        float sc1 = S;
        float sh1 = (1+sc1)*smRad/sqrtf(3);
        drawSnowman([&]{
            base();
            glTranslatef(sh1,sh1,sh1);
            glScalef(sc1,sc1,sc1);
        }, true, [&]{ glRotatef(-ro,0,1,0); glRotatef(-rot,1,1,1); });

        float sc2 = S*S;
        float sh2 = (1+2*S+S*S)*smRad/sqrtf(3);
        drawSnowman([&]{
            base();
            glTranslatef(sh2,sh2,sh2);
            glScalef(sc2,sc2,sc2);
        }, true, [&]{ glRotatef(-ro,0,1,0); glRotatef(-rot,1,1,1); });
        break;
    }

    case GLUT_KEY_F6: {
        float mid = (1+0.7f)*smRad;

        auto pivot = [&]{ 
            glTranslatef(mid,0,0); 
            glRotatef(rot,0,1,0); 
            glTranslatef(-mid,0,0); 
        };

        drawAxes();

        // 1-й снеговик — теперь с локальными осями, которые вращаются вместе с ним
        drawSnowman([&]{ 
            pivot();
            glTranslatef(0, smRad, 0);
        }, true, nullptr);   // ← nullptr вместо дефолта: оси НЕ компенсируются

        // 2-й снеговик
        float sh1 = (1+0.7f)*smRad;
        float sc1 = S;

        drawSnowman([&]{
            pivot();
            glTranslatef(sh1, smRad * sc1, 0);
            glRotatef(90, 0, 1, 0);
            glScalef(sc1, sc1, sc1);
        }, true, [&]{ glRotatef(-rot,0,1,0); });

        // 3-й снеговик
        float sh3 = (1+2*0.7f+0.7f*0.7f)*smRad;
        float sc3 = S*S;

        drawSnowman([&]{
            pivot();
            glTranslatef(sh3, smRad * sc3, 0);
            glRotatef(-90, 0, 1, 0);
            glScalef(sc3, sc3, sc3);
        }, true, [&]{ glRotatef(-rot,0,1,0); });

        break;
    }

    // F7: три снеговика с независимым вращением
    case GLUT_KEY_F7: {
        drawAxes();

        // 1-й снеговик: нижний край на оси X → центр поднят на smRad
        drawSnowman([&]{
            glTranslatef(0, smRad, 0);
            glRotatef(rot, 0,1,0);
        }, true, [&]{ glRotatef(-rot,0,1,0); });

        // 2-й снеговик: сдвиг по X, масштаб S, нижний край тоже на оси X
        float sh1 = (1+S)*smRad;
        float sc1 = S;
        drawSnowman([&]{
            glTranslatef(sh1, smRad*sc1, 0);
            glRotatef(rot, 0,1,0);
            glScalef(sc1, sc1, sc1);
        }, true, [&]{ glRotatef(-rot,0,1,0); });

        // 3-й снеговик: ещё дальше по X, масштаб S², нижний край на оси X
        float sh3 = (1+2*S+S*S)*smRad;
        float sc3 = S*S;
        drawSnowman([&]{
            glTranslatef(sh3, smRad*sc3, 0);
            glRotatef(rot, 0,1,0);
            glScalef(sc3, sc3, sc3);
        }, true, [&]{ glRotatef(-rot,0,1,0); });
        break;
    }

    // F8: вращение вокруг точки на оси X (другой центр)
    case GLUT_KEY_F8: {
        float mid=(1+2*0.7f+0.7f*0.7f)*smRad;
        auto pivot=[&]{ glTranslatef(mid,0,0); glRotatef(rot,0,1,0); glTranslatef(-mid,0,0); };

        drawAxes();

        // 1-й снеговик: нижний край на оси X
        drawSnowman([&]{
            pivot();
            glTranslatef(0, smRad, 0);
        }, true, [&]{ glRotatef(-rot,0,1,0); });

        // 2-й снеговик: сдвиг по X, масштаб S, нижний край на оси X
        float sh1 = (1+S)*smRad;
        float sc1 = S;
        drawSnowman([&]{
            pivot();
            glTranslatef(sh1, smRad*sc1, 0);
            glScalef(sc1, sc1, sc1);
        }, true, [&]{ glRotatef(-rot,0,1,0); });

        // 3-й снеговик: ещё дальше по X, масштаб S², нижний край на оси X
        float sh3 = (1+2*S+S*S)*smRad;
        float sc3 = S*S;
        drawSnowman([&]{
            pivot();
            glTranslatef(sh3, smRad*sc3, 0);
            glScalef(sc3, sc3, sc3);
        }, true, [&]{ glRotatef(-rot,0,1,0); });
        break;
    }

    // F10: сложная цепочка вращений (Y, Z, Y)
    case GLUT_KEY_F10: {
        float x = -0.6f;
        float sh = (2+0.7f)*smRad;
        float shY3 = (2+0.7f)*smRad*0.7f;
        float sh4 = 1.5f*smRad, shY4=(smRad+smRadH)*0.7f;

        // 1й: неподвижен
        drawAxes();
        drawSnowman([&]{ glTranslatef(x,0,0); });

        // 2й: вращение вокруг Y
        drawSnowman([&]{
            glTranslatef(x,0,0);
            glRotatef(rot,0,1,0);
            glTranslatef(sh,0,0);
            glRotatef(-rot,0,1,0);
            glScalef(S,S,S);
        }, true, nullptr);

        // 3й: вращение вокруг Z от позиции 2го
        float sc3=S*S;
        drawSnowman([&]{
            glTranslatef(x,0,0);
            glRotatef(rot,0,1,0);
            glTranslatef(sh,0,0);
            glRotatef(-rot,0,1,0);
            glRotatef(rot,0,0,1);
            glTranslatef(0,shY3,0);
            glRotatef(-rot,0,0,1);
            glScalef(sc3,sc3,sc3);
        }, true, nullptr);

        // 4й: вращение вокруг Y от позиции 3го
        float sc4=S*S*S;
        drawSnowman([&]{
            glTranslatef(x,0,0);
            glRotatef(rot,0,1,0);
            glTranslatef(sh,0,0);
            glRotatef(-rot,0,1,0);
            glRotatef(rot,0,1,0);
            glTranslatef(sh4,shY4,0);
            glRotatef(-rot,0,1,0);
            glScalef(sc4,sc4,sc4);
        }, true, nullptr);
        break;
    }

    } // switch

    glPopMatrix();
}

// Функция отрисовки (вызывается каждый кадр)
void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Левая половина экрана: вид спереди
    glViewport(0, 0, 800, 800);
    glLoadIdentity();
    scene();

    // Правая половина экрана: вид сверху (повёрнут на 90° вокруг X)
    if (ex != GLUT_KEY_F1 && ex != 0) {
        glViewport(800, 0, 800, 800);
        glRotatef(90, 1, 0, 0);
        scene();
    }

    glutSwapBuffers();  // Обмен буферов (двойная буферизация)
}

// Инициализация OpenGL
void Initialize() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  // Серый фон
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);  // Ортографическая проекция
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);  // Включить тест глубины
}

// Главная функция
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1600, 800);  // Два окна рядом (800x800 каждое)
    glutInitWindowPosition(10, 20);
    glutCreateWindow("Our first GLUT application!");
    glutDisplayFunc(Display);
    glutSpecialFunc(specialkeys);
    glEnable(GL_DEPTH_TEST);
    Initialize();
    glutMainLoop();  // Основной цикл событий
    return 0;
}