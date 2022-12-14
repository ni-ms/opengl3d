#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat Clength, GLfloat Cbreadth, GLfloat Cheight);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Cuboid", NULL, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;


    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Render OpenGL here
        glPushMatrix();
        glLoadIdentity();

        glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);

        DrawCube(halfScreenWidth, halfScreenHeight, -500, 100, 200, 500);

        glPopMatrix();


        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }


    glfwTerminate();

    return 0;
}



void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << key << std::endl;

    const GLfloat rotationSpeed = 10;

    // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_UP:
                rotationX -= rotationSpeed;
                break;
            case GLFW_KEY_DOWN:
                rotationX += rotationSpeed;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += rotationSpeed;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= rotationSpeed;
                break;
        }


    }
}


void DrawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat Clength, GLfloat Cbreadth, GLfloat Cheight)
{
    GLfloat halfLength = Clength * 0.5f;
    GLfloat halfbreadth = Cbreadth * 0.5f;
    GLfloat halfheight = Cheight * 0.5f;

    GLfloat colour[] = { 0.0f, 1.0f, 0.0f };

    GLfloat vertices[] =
            {
                    // front face
                    centerPosX - halfLength, centerPosY + halfheight, centerPosZ + halfbreadth, // top left
                    centerPosX + halfLength, centerPosY + halfheight, centerPosZ + halfbreadth, // top right
                    centerPosX + halfLength, centerPosY - halfheight, centerPosZ + halfbreadth, // bottom right
                    centerPosX - halfLength, centerPosY - halfheight, centerPosZ + halfbreadth, // bottom left

                    // back face
                    centerPosX - halfLength, centerPosY + halfheight, centerPosZ - halfbreadth, // top left
                    centerPosX + halfLength, centerPosY + halfheight, centerPosZ - halfbreadth, // top right
                    centerPosX + halfLength, centerPosY - halfheight, centerPosZ - halfbreadth, // bottom right
                    centerPosX - halfLength, centerPosY - halfheight, centerPosZ - halfbreadth, // bottom left

                    // left face
                    centerPosX - halfLength, centerPosY + halfheight, centerPosZ + halfbreadth, // top left
                    centerPosX - halfLength, centerPosY + halfheight, centerPosZ - halfbreadth, // top right
                    centerPosX - halfLength, centerPosY - halfheight, centerPosZ - halfbreadth, // bottom right
                    centerPosX - halfLength, centerPosY - halfheight, centerPosZ + halfbreadth, // bottom left

                    // right face
                    centerPosX + halfLength, centerPosY + halfheight, centerPosZ + halfbreadth, // top left
                    centerPosX + halfLength, centerPosY + halfheight, centerPosZ - halfbreadth, // top right
                    centerPosX + halfLength, centerPosY - halfheight, centerPosZ - halfbreadth, // bottom right
                    centerPosX + halfLength, centerPosY - halfheight, centerPosZ + halfbreadth, // bottom left

                    // top face
                    centerPosX - halfLength, centerPosY + halfheight, centerPosZ + halfbreadth, // top left
                    centerPosX - halfLength, centerPosY + halfheight, centerPosZ - halfbreadth, // top right
                    centerPosX + halfLength, centerPosY + halfheight, centerPosZ - halfbreadth, // bottom right
                    centerPosX + halfLength, centerPosY + halfheight, centerPosZ + halfbreadth, // bottom left

                    // top face
                    centerPosX - halfLength, centerPosY - halfheight, centerPosZ + halfbreadth, // top left
                    centerPosX - halfLength, centerPosY - halfheight, centerPosZ - halfbreadth, // top right
                    centerPosX + halfLength, centerPosY - halfheight, centerPosZ - halfbreadth, // bottom right
                    centerPosX + halfLength, centerPosY - halfheight, centerPosZ + halfbreadth  // bottom left
            };

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.9f, 0.9f, 0.9f, 1);
    // reset matrix
    // fill display list
    // glColor3f(150, 255, 255);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
    //glColor3f(0, 0, 0);

    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    // glVertex3f(0.5f, 0.5f, -0.5f);

    // Bottom face (y = -1.0f)
    // glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    // glVertex3f(0.5f, -0.5f, 0.5f);

    // Front face  (z = 1.0f)
    // glColor3f(1.0f, 0.0f, 0.0f);     // Red
    // glVertex3f(0.5f, 0.5f, 0.5f);

    // Back face (z = -1.0f)
    // glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    //glVertex3f(0.5f, -0.5f, -0.5f);

    // Left face (x = -1.0f)
    // glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    // glVertex3f(-0.5f, 0.5f, 0.5f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
}