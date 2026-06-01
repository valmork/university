//g++ -o snowman main.cpp -framework OpenGL -framework GLUT -arch arm64 -Wno-deprecated

#include <math.h>

#include <cstdio>

#include <tuple>

#include <GLUT/glut.h>


int rot = 0;
int ro = 0;
int ex = 0;
inline constexpr float smRad = 0.38;
inline constexpr float smRadH = 0.125f;
inline constexpr float smRadMin = 0.02f;
inline constexpr float coneHeight = 0.2f;
inline constexpr float coneBase = 0.03f;
float S = 0.7;

void specialkeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:  rot -= 5; break;
        case GLUT_KEY_RIGHT: rot += 5; break;
        case GLUT_KEY_UP:    ro  += 5; break;
        case GLUT_KEY_DOWN:  ro  -= 5; break;
        default:
            ex = key;  // только F-клавиши меняют сцену
            break;
    }
    glutPostRedisplay();
}


void drawAxes() {
    // Длина осей = радиус сферы + небольшой выступ
    float axisLength = smRad + 0.15f;  // 0.38 + 0.15 = 0.53
    
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    
    // Ось X — красная (от -radius до +radius)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-axisLength, 0.0f, 0.0f);
    glVertex3f( axisLength, 0.0f, 0.0f);
    
    // Ось Y — зелёная
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -axisLength, 0.0f);
    glVertex3f(0.0f,  axisLength, 0.0f);
    
    // Ось Z — синяя (добавим для полноты)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -axisLength);
    glVertex3f(0.0f, 0.0f,  axisLength);
    
    glEnd();
    glLineWidth(1.0f);
}


void drawSnowManDecomposed() {

	drawAxes();

    float x = 0; // начинаем с начала координат

    // Тело — большая сфера
    glPushMatrix();
    glTranslatef(x, smRad, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(smRad, 30, 30);
    glPopMatrix();

    x += smRad + smRadH + 0.02f; // сдвиг вправо

    // Голова — маленькая сфера
    glPushMatrix();
    glTranslatef(x, smRadH, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(smRadH, 20, 20);
    glPopMatrix();

    x += smRadH + smRadMin + 0.02f;

    // Глаз левый
    glPushMatrix();
    glTranslatef(x, smRadMin, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(smRadMin, 10, 10);
    glPopMatrix();

    x += smRadMin * 2 + 0.01f;

    // Глаз правый
    glPushMatrix();
    glTranslatef(x, smRadMin, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(smRadMin, 10, 10);
    glPopMatrix();

    x += 2 * smRadMin + coneBase + 0.02f;

    // Нос — конус
    glPushMatrix();
    glTranslatef(x, 0.0f, 0.0f);
    glColor3f(1.0f, 0.3f, 0.3f);
    // поворачиваем конус чтобы смотрел вверх
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(coneBase, coneHeight, 20, 2);
    glPopMatrix();
}

void drawSnowManComposed() {

	drawAxes();

    float y = 0.0f;

    // Тело
    glPushMatrix();
    glRotatef(rot, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, y, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(smRad, 30, 30);
    glPopMatrix();

    y += smRad + smRadH;

    // Голова
    glPushMatrix();
    glRotatef(rot, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, y, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(smRadH, 20, 20);
    glPopMatrix();

    y += smRadMin;

    // Нос
    glPushMatrix();
    glRotatef(rot, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.3f, 0.3f);
    glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
    glutSolidCone(coneBase, coneHeight, 20, 2);
    glPopMatrix();

    // Глаз левый
    glPushMatrix();
    glRotatef(rot, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-0.035f, y + 0.035f, coneHeight / 2);
    glutSolidSphere(smRadMin, 10, 10);
    glPopMatrix();

    // Глаз правый
    glPushMatrix();
    glRotatef(rot, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.035f, y + 0.035f, coneHeight / 2);
    glutSolidSphere(smRadMin, 10, 10);
    glPopMatrix();
}



void scene() {
	glPushMatrix();
	switch (ex) {
	case 0:
	case GLUT_KEY_F1: {
		drawSnowManDecomposed();
		break;
	}
	case GLUT_KEY_F2: {
		drawSnowManComposed();
		break;
	}
	case GLUT_KEY_F3: {
		//Первый снеговик
		float y = 0.0f;

		glPushMatrix();
		glTranslatef(0.0f, y, 0.0f);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Второй снеговик
		float shift = (1 + 0.7f) * smRad;
		float scale = S;

		y = 0.0f;

		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Третий снеговик
		shift = (1 + 2 * 0.7f + 0.7f * 0.7f) * smRad;
		scale = S * S;
		y = 0.0f;

		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();
		break;
	}
	case GLUT_KEY_F4: {
		float y = 0.0f;

		// === Первый снеговик ===
		// Вращение вокруг оси Z его ГКС
		glPushMatrix();
		drawAxes();
		glRotatef(-rot, 0, 0, 1); // вращение вокруг Z, противоположное второму
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(smRad, 30, 30);
		glPopMatrix();

		y += smRad + smRadH;
		glPushMatrix();
		glRotatef(-rot, 0, 0, 1);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin;
		glPopMatrix();
		glPushMatrix();
		glRotatef(-rot, 0, 0, 1);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		glutSolidCone(coneBase, coneHeight, 20, 2);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-rot, 0, 0, 1);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f, y + 0.035f, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-rot, 0, 0, 1);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f, y + 0.035f, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		glPopMatrix();

		// === Второй снеговик ===
		// Вращается вокруг оси проходящей через его нос
		float shift = (1 + 0.7f) * smRad;
		float scale = S;
		y = 0.0f;

		// Позиция носа второго снеговика в ГКС
		// нос находится на оси Z на расстоянии shift
		// по Y: (smRad + smRadH + smRadMin) * scale
		const float noseY = (smRad + smRadH + smRadMin) * scale;
		const float noseZ = shift;

		// Ось вращения проходит через нос вдоль Z
		// Сдвигаемся к носу -> вращаем -> возвращаемся

		glPushMatrix();
		// переносим начало координат в точку носа
		glTranslatef(0.0f, noseY, noseZ);
		// вращаем вокруг Z
		glRotatef(rot, 0, 0, 1);
		// возвращаемся обратно
		glTranslatef(0.0f, -noseY, -noseZ);
		// рисуем второй снеговик
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		drawAxes();
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(smRad, 30, 30);
		glPopMatrix();

		y += smRad + smRadH;
		glPushMatrix();
		glTranslatef(0.0f, noseY, noseZ);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0.0f, -noseY, -noseZ);
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(smRadH, 20, 20);
		glPopMatrix();

		y += smRadMin;
		glPushMatrix();
		glTranslatef(0.0f, noseY, noseZ);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0.0f, -noseY, -noseZ);
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		glutSolidCone(coneBase, coneHeight, 20, 2);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, noseY, noseZ);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0.0f, -noseY, -noseZ);
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f, y + 0.035f, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, noseY, noseZ);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0.0f, -noseY, -noseZ);
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f, y + 0.035f, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		glPopMatrix();

		// === Третий снеговик — неподвижен ===
		shift = (1 + 2 * 0.7f + 0.7f * 0.7f) * smRad;
		scale = S * S;
		y = 0.0f;

		glPushMatrix();
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		drawAxes();
		glColor3f(1.0f, 1.0f, 1.0f);
		glutSolidSphere(smRad, 30, 30);
		glPopMatrix();

		y += smRad + smRadH;
		glPushMatrix();
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);
		glPopMatrix();

		y += smRadMin;
		glPushMatrix();
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		glutSolidCone(coneBase, coneHeight, 20, 2);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035f, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0, 0, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035f, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		glPopMatrix();

		break;
	}
	case GLUT_KEY_F9: 
	{		
		float y = 0.0f;

		glPushMatrix();
		drawAxes();
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Второй снеговик
		float scale = S;
		float shift = smRad + 2 * smRadH + smRad * scale;

		y = 0.0f;

		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();
		
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Третий снеговик
		shift = smRad + 2 * smRadH + (2 * (smRad + smRadH) * scale) + smRad * scale * scale;
		scale = scale * scale;
		y = 0.0f;

		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();
		
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0, shift, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();
		break;
	}
	case GLUT_KEY_F5: {		
		float y = 0.0f;

		glPushMatrix();
		drawAxes();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Второй снеговик
		float scale = S;
		float shift = (1 + scale) * smRad / sqrtf(3);

		y = 0.0f;

		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-ro, 0, 1, 0);
		glRotatef(-rot, 1, 1, 1);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Третий снеговик
		shift = (1 + 2 * scale + scale * scale) * smRad / sqrtf(3);
		scale = scale * scale;
		y = 0.0f;

		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-ro, 0, 1, 0);
		glRotatef(-rot, 1, 1, 1);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 1, 1, 1);
		glRotatef(ro, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shift, shift);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();
		break;
	}
	case GLUT_KEY_F6:
	{	
		float y = 0.0f;
		const float middlePosition = (1 + 0.7f) * smRad;		

		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Второй снеговик
		float shift = (1 + 0.7f) * smRad;
		float shiftY = -(1 - 0.7f) * smRad;
		float scale = S;

		y = 0.0f;

		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Третий снеговик
		shift = (1 + 2 * 0.7f + 0.7f * 0.7f) * smRad;
		shiftY = -(1 - 0.7f * 0.7f) * smRad;
		scale = S * S;
		y = 0.0f;
		
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, shiftY, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();
		break;
	}
	case GLUT_KEY_F7:
	{	
		float y = 0.0f;
		float middlePosition = 0.0f;		

		glPushMatrix();
		drawAxes();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Второй снеговик
		float shift = (1 + 0.7f) * smRad;
		float shiftY = -(1 - 0.7f) * smRad;
		float scale = S;

		y = 0.0f;

		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Третий снеговик
		shift = (1 + 2 * 0.7f + 0.7f * 0.7f) * smRad;
		shiftY = -(1 - 0.7f * 0.7f) * smRad;
		scale = S * S;
		y = 0.0f;
		
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(shift, shiftY, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();
		break;
	}
	case GLUT_KEY_F8:
	{	
		float y = 0.0f;
		const float middlePosition = (1 + 2 * 0.7f + 0.7 * 0.7) * smRad;		

		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Второй снеговик
		float shift = (1 + 0.7f) * smRad;
		float shiftY = -(1 - 0.7f) * smRad;
		float scale = S;

		y = 0.0f;

		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Третий снеговик
		shift = (1 + 2 * 0.7f + 0.7f * 0.7f) * smRad;
		shiftY = -(1 - 0.7f * 0.7f) * smRad;
		scale = S * S;
		y = 0.0f;
		
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glRotatef(-rot, 0, 1, 0);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(middlePosition, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(-middlePosition, 0, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();
		break;
	}
	case GLUT_KEY_F10: 
	{
		float x = -0.6f;
		float y = 0.0f;
		const float middlePosition = (1 + 2 * 0.7f + 0.7 * 0.7) * smRad;	

		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		drawAxes();
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(x, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(-0.035f + x, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(0.035f + x, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Второй снеговик
		float shift = (2 + 0.7f) * smRad;
		float shiftY = 0.0f;
		float scale = S;

		y = 0.0f;

		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		drawAxes();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glTranslatef(shift, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glTranslatef(shift, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Третий снеговик
		shiftY = (2 + 0.7f) * smRad * 0.7;
		scale = S * S;
		y = 0.0f;

		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0, shiftY, 0);
		glRotatef(-rot, 0, 0, 1);
		drawAxes();
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0, shiftY, 0);
		glRotatef(-rot, 0, 0, 1);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0, shiftY, 0);
		glRotatef(-rot, 0, 0, 1);
		glColor3f(1.0f, 0.3f, 0.3f);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0, shiftY, 0);
		glRotatef(-rot, 0, 0, 1);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0, shiftY, 0);
		glRotatef(-rot, 0, 0, 1);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
		
		glPopMatrix();

		//Четвёртый снеговик
		auto shift2 = 1.5f * smRad;
		shiftY = (smRad + smRadH) * 0.7f;
		scale = S * S * S;
		y = 0.0f;
		
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift2, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		drawAxes();
		glColor3f(1.0f, 1.0f, 1.0f);	
		glutSolidSphere(smRad, 30, 30);

		y += smRad + smRadH;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift2, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y, 0.0f);
		glutSolidSphere(smRadH, 20, 20);

		y += smRadMin; 
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift2, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glColor3f(1.0f, 0.3f, 0.3f);
		glScalef(scale, scale, scale);
		glTranslatef(0.0f, y - coneBase / 2, coneHeight / 2 - 0.01f);
		
		glutSolidCone(coneBase, coneHeight, 20, 2);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift2, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(scale, scale, scale);
		glTranslatef(-0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);
			
		glPopMatrix();
		glPushMatrix();
		glTranslatef(x, 0, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift, 0, 0);
		glRotatef(-rot, 0, 1, 0);
		glRotatef(rot, 0, 1, 0);
		glTranslatef(shift2, shiftY, 0);
		glRotatef(-rot, 0, 1, 0);
		glColor3f(0.0f, 0.0f, 0.0f);
		glScalef(scale, scale, scale);
		glTranslatef(0.035f, y + 0.035, coneHeight / 2);
		glutSolidSphere(smRadMin, 10, 10);

		glPopMatrix();
		break;
	}

	}
	glPopMatrix();

}



void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (ex == GLUT_KEY_F1 || ex == 0) {
        // Только левый вид, правая половина остаётся пустой
        glViewport(0, 0, 800, 800);
        glLoadIdentity();
        scene();
    } else {
        // Левый вид — обычный
        glViewport(0, 0, 800, 800);
        glLoadIdentity();
        scene();

        // Правый вид — сверху
        glViewport(800, 0, 800, 800);
        glRotatef(90, 1, 0, 0);
        scene();
    }

    glutSwapBuffers();
}

void Initialize() {
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1600, 800);
	glutInitWindowPosition(10, 20);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);
	glutSpecialFunc(specialkeys);
	glEnable(GL_DEPTH_TEST);
	Initialize();
	glutMainLoop();
	return 0;
}