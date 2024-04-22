#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>
#include <glfw/glfw3.h>

typedef struct Buffer {
  GLuint handle;
  GLenum target;
  GLsizeiptr size;
  GLvoid* data;

  GLsizei count;
  GLenum usage;
} Buffer_t;

void Buffer_CreateBuffer(Buffer_t* buff);
void Buffer_Unbind(Buffer_t* buff);
void Buffer_Bind(Buffer_t* buff);
void Buffer_Init(Buffer_t* buff);
void Buffer_SetStruct(Buffer_t* buff, GLsizei count, GLsizeiptr size, GLvoid* data, GLenum usage, GLenum target);

#endif // !BUFFER_H
