#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Point {
    float x;
    float y;

    char* describe() {
        char* s;
        sprintf(s, "(%f, %f)", this->x, this->y);
        return s;
    }
};

struct Dimensions {
    int width;
    int height;
};

class Ball {
    Point* vector;
    Point* position;
    Point last_position;
    int motion_state;
    unsigned char* image;

    

    //Dimensions dimensions() {
    //}
};

int main(void) {
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "NFT Slimeball", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Ball properties
    float ballRadius = 0.05f;
    float ballPosX = 0.5f; // Middle of the window
    float ballPosY = 0.0f; // Start at the top of the window
    float ballVelocityY = 0.0f; // Initial Y velocity
    float gravity = -0.0005f; // Gravity effect
    float bounceFactor = -2.7f; // Bounce factor

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        ballVelocityY += gravity; // Apply gravity to velocity
        ballPosY += ballVelocityY; // Update ball position with velocity

        std::cout << "Ball position " << ballPosY << " and radius " << ballRadius << '\n';

        // Check for bounce
        if (ballPosY - ballRadius < 0) {
            ballPosY = ballRadius; // Reset position to floor level
            ballVelocityY *= bounceFactor; // Apply bounce factor to velocity
        }

        // Render the ball
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= 360; i++) { // Draw a circle
            float degInRad = i * M_PI / 180;
            glColor3f(1.0f, 0.0f, 0.0f); // Red color 
            float x, y;
            x = cos(degInRad) * ballRadius + ballPosX;
            y = sin(degInRad) * ballRadius + ballPosY;
            glVertex2f(x, y);
        }
        glEnd();


        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
