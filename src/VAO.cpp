#include"VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(const VBO& VBO, const GLuint layout, const GLuint numComponents, const GLenum type, const GLsizeiptr stride, const void* offset)
{
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO::Unbind();
}

void VAO::Bind() const {
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete() const {
    glDeleteVertexArrays(1, &ID);
}
