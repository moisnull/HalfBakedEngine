#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<GL/glew.h>

class EBO
{
public:
    GLuint ID{};
    EBO(const GLuint* indices, GLsizeiptr size);

    void Bind() const;
    static void Unbind();
    void Delete() const;
};

#endif