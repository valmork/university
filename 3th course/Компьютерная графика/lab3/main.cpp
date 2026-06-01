/* 
g++ main.cpp glad/src/glad.c \
    -I glad/include \
    -o app \
    $(pkg-config --cflags --libs glfw3) \
    -framework OpenGL \
    -arch arm64 \
    -Wno-deprecated
    
*/

#include "glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

constexpr float pi = 3.14159265359f;

float rotateX = 0.0f; // Rotation angle around X-axis
float rotateY = 0.0f; // Rotation angle around Y-axis

// Рисование сферы с радиусом 0.3 в позиции (0, 0, 0)
void drawSphere(float radius, int slices, int stacks) {
    float x, y, z, alpha, beta; // Хранилище для координат и углов
    float stackStep = pi / stacks;
    float sliceStep = 2.0f * pi / slices;

    for (int i = 0; i < stacks; ++i) {
        alpha = i * stackStep;
        beta = (i + 1) * stackStep;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float sliceAngle = j * sliceStep;
            
            // Вычисление позиций
            x = radius * sin(beta) * cos(sliceAngle);
            y = radius * cos(beta);
            z = radius * sin(beta) * sin(sliceAngle);
            
            glColor3f(0.5, 1.0, 0.5);
            glVertex3f(x, y, z);
            
            x = radius * sin(alpha) * cos(sliceAngle);
            y = radius * cos(alpha);
            z = radius * sin(alpha) * sin(sliceAngle);
            
            glColor3f(0.5, 1.0, 0.5);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void draw_model()
{
    glPushMatrix();

    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0.5);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0, -0.5, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0, 0.5, 0.5);
    glVertex3f(0, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.7f, 0.9f);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0, 0.5, -0.5);
    glVertex3f(0, 0.5, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0.5);
    glVertex3f(0, 0.5, 0.5);
    glVertex3f(0, 0.5, -0.5);
    glVertex3f(0, 0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, -0.5);
    glVertex3f(0, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0, -0.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0, -0.5, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 1);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 1, 1);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(0, 0, 0.5);
    glVertex3f(0, 0, -0.5);
    glVertex3f(0.5, 0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();

    glPushMatrix();
    glTranslatef(0.2f, 0.2f, 0.2f);
    glColor3f(1.0f, 0.8f, 0.2f);
    drawSphere(0.2f, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        rotateX = rotateY = 0.0f;
    }
    
    // Обработка нажатий клавиш стрелок для изменения углов вращения
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rotateX = fmod(rotateX + 0.1f, 360.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rotateX = fmod(rotateX - 0.1f, 360.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rotateY = fmod(rotateY + 0.1f, 360.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rotateY = fmod(rotateY - 0.1f, 360.0f);
    }
}

int main()
{
    // Инициализация GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // OpenGL версия 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE); 

    // Создание окна
    GLFWwindow *window = glfwCreateWindow(800, 600, "3", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Вставляем окно в контекст
    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);

    // Зарегистрировать колбэк для определения размера фреймбуфера
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Главный цикл
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1
        glViewport(0, 800, 400, 400);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2, 2);
        GLfloat matrix2[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            -0.5f * cosf(pi / 4), -0.5f * sinf(pi / 4), 1, 0,
            0, 0, 0, 1};
        glMultMatrixf(matrix2);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(rotateX, 1, 0, 0);  // вращение стрелками вверх/вниз
        glRotatef(rotateY, 0, 1, 0);  // вращение стрелками влево/вправо
        draw_model();

        // 2
        glViewport(400, 800, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2.0, 2.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        draw_model();

        // 3
        glViewport(800, 800, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2.0, 2.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(-90, 0, 1, 0); 
        draw_model();

        // 4
        glViewport(1200, 800, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2.0, 2.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(90, 1, 0, 0); 
        draw_model();

        // 5
        glViewport(0, 400, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glTranslatef(0.5, 0.5, 0.0);
        glFrustum(-0.6, 0.6, -0.6, 0.6, 1, 20);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(-0.5, -0.5, -3.0);
        draw_model();

        // 6
        glViewport(400, 400, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2, 2);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(30, 1, 0, 0);
        glRotatef(20, 0, 1, 0);
        draw_model();

        // 7
        glViewport(800, 400, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2, 2);
        
        constexpr float f = 5.0f / 8.0f;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(asinf(f / sqrtf(2 - f * f)) * 180 / pi, 1, 0, 0);
        glRotatef(-asinf(f / sqrtf(2)) * 180 / pi, 0, 1, 0);
        draw_model();

        // 8
        glViewport(1200, 400, 400, 400);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2, 2);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(35.264f, 1, 0, 0);
        glRotatef(-45, 0, 1, 0);  // было 45, поменяй на -45
        draw_model();

        // 9
        glViewport(0, 0, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-0.6, 0.6, -0.6, 0.6, 1, 20);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, -3.0);
        glRotatef(30, 1, 0, 0);
        draw_model();

        // 10
        glViewport(400, 0, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-0.6, 0.6, -0.6, 0.6, 1, 20);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, -3.0);
        glRotatef(-45, 0, 1, 0);
        glRotatef(30, 1, 0, 0);
        draw_model();

        // 11
        glViewport(800, 0, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2, 2);
        GLfloat matrix[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            -cosf(pi / 4), -sinf(pi / 4), 1, 0,
            0, 0, 0, 1};
        glMultMatrixf(matrix);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        draw_model();

        // 12
        glViewport(1200, 0, 400, 400);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2, -2, 2);
        GLfloat matrix3[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            -0.5f * cosf(pi / 4), -0.5f * sinf(pi / 4), 1, 0,
            0, 0, 0, 1};
        glMultMatrixf(matrix3);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        draw_model();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}