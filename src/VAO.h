#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<GL/glew.h>
#include"VBO.h"

class VAO
{
public:
    // ID reference for the Vertex Array Object
    GLuint ID{};
    // Constructor that generates a VAO ID
    VAO();

    // Links a VBO Attribute such as a position or color to the VAO
    static void LinkAttrib(const VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const void* offset);
    // Binds the VAO
    void Bind() const;
    // Unbinds the VAO
    static void Unbind();
    // Deletes the VAO
    void Delete() const;
};

#endif