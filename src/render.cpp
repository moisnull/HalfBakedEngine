#include <fstream>
#include <GL/glew.h>
#include "render.h"
#include <iostream>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

char* readShaderFile(const std::string &fileName) {
    std::ifstream shaderFile(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!shaderFile.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + fileName);
    }

    const std::streamsize size = shaderFile.tellg();
    shaderFile.seekg(0, std::ios::beg);

    char* shaderCode = new char[size + 1];
    if (!shaderFile.read(shaderCode, size)) {
        delete[] shaderCode;
        throw std::runtime_error("Failed to read shader file: " + fileName);
    }
    shaderCode[size] = '\0';

    shaderFile.close();
    return shaderCode;
}

void render() {
    unsigned int VAO, VBO;

    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // Load and compile vertex shader
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = readShaderFile("../src/shaders/vertexShader.glsl");
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    delete[] vertexShaderSource; // Free memory after usage

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Load and compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = readShaderFile("../src/shaders/fragmentShader.glsl");
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    delete[] fragmentShaderSource; // Free memory after usage

    // Create shader program and link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use the shader program and draw
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Clean up (optional, for later use or when program terminates)
    glBindVertexArray(0);
}
