// Include the Assimp and FreeGLUT headers


#include <assimp/scene.h>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <GL/freeglut.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640


GLuint vao;
const aiScene* scene;
// Function to load a GLTF file using Assimp and create the corresponding OpenGL objects
void loadGLTF(const std::string& filename) {
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // Use the Importer class to read the given GLTF file
    scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    // If the file was not successfully imported, print an error message and return
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error: Failed to import GLTF file: " << importer.GetErrorString() << std::endl;
        return;
    }

    // Loop through all of the meshes in the scene and create the corresponding OpenGL objects
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];

        // Create a vertex array object (VAO) to store the vertex data for the mesh

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create a vertex buffer object (VBO) to store the vertex positions for the mesh
        GLuint vboPositions;
        glGenBuffers(1, &vboPositions);
        glBindBuffer(GL_ARRAY_BUFFER, vboPositions);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        // Create a VBO to store the vertex normals for the mesh
        GLuint vboNormals;
        glGenBuffers(1, &vboNormals);
        glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);

        // Create a VBO to store the vertex texture coordinates for the mesh
        GLuint vboTexCoords;
        glGenBuffers(1, &vboTexCoords);
        glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mTextureCoords[0], GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);

        // Create a VBO to store the vertex colors for the mesh
        GLuint vboColors;
        glGenBuffers(1, &vboColors);
        glBindBuffer(GL_ARRAY_BUFFER, vboColors);
        glBufferData(GL_ARRAY_BUFFER, sizeof(aiColor4D) * mesh->mNumVertices, mesh->mColors[0], GL_STATIC_DRAW);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(3);

        // Create an element array buffer (EBO) to store the vertex indices for the mesh
        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, mesh->mFaces, GL_STATIC_DRAW);

        // Unbind the VAO
        glBindVertexArray(0);
    }
}

// Function to draw the GLTF file
void drawGLTF() {
    // Loop through all of the meshes in the scene and draw them
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];

        // Bind the VAO for the mesh
        glBindVertexArray(vao);

        // Draw the mesh
        glDrawElements(GL_TRIANGLES, mesh->mNumFaces * 3, GL_UNSIGNED_INT, NULL);

        // Unbind the VAO
        glBindVertexArray(0);
    }
}

// Function to draw the scene
void drawScene() {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the GLTF file
    drawGLTF();

    // Swap the front and back buffers
    glutSwapBuffers();
}

// Function to handle window resizing
void resizeWindow(int width, int height) {
    // Set the viewport size
    glViewport(0, 0, width, height);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Function to handle key presses
void handleKeyPress(unsigned char key, int x, int y) {
    // Check if the escape key was pressed
    if (key == 27) {
        // Exit the program
        exit(0);
    }
}

// Function to initialize OpenGL

void initOpenGL() {
    // Set the background color
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

// Function to initialize GLUT

void initGLUT(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GLTF Viewer");

    // Set the callback functions
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(handleKeyPress);
}

// Main function

int main(int argc, char** argv) {
    // Initialize GLUT
    initGLUT(argc, argv);

    // Initialize OpenGL
    initOpenGL();

    // Load the GLTF file
    loadGLTF("tree.gltf");

    // Start the main loop
    glutMainLoop();

    return 0;
}


