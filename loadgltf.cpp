#include <GL/glew.h>
#include <GL/freeglut.h>
#include <tiny_gltf.h>

#include <iostream>

GLuint vbo, vao;
using namespace std;int main(int argc, char** argv)
{
    // Initialize freeglut and create a window
    glutInit(&argc, argv);
    glutCreateWindow("glTF Viewer");
    GLenum err1 = glewInit();
    if (GLEW_OK != err1)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err1));

    }
    // Load the glTF file using tinygltf
    tinygltf::Model model;
    tinygltf::TinyGLTF gltf_loader;
    std::string err, warn;
    bool res = gltf_loader.LoadASCIIFromFile(&model, &err, &warn, "tree.gltf");

    if (!warn.empty()) {
        std::cout << "Warn: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "Err: " << err << std::endl;
    }

    if (!res) {
        std::cerr << "Failed to load glTF file" << std::endl;
        return 1;
    }

    // Create a vertex buffer object (VBO) and a vertex array object (VAO)
    // to store the model data in the graphics card's memory

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Copy the model data into the VBO
    glBufferData(GL_ARRAY_BUFFER, model.buffers[0].data.size(), model.buffers[0].data.data(), GL_STATIC_DRAW);

    // Set up the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set up the shaders and other rendering parameters


    // Register the display callback function
    glutDisplayFunc([]() {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind the VAO and draw the model
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the front and back buffers
        glutSwapBuffers();
    });

    // Enter the main rendering loop
    glutMainLoop();

    return 0;
}