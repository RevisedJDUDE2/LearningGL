#include "Buffer.h"
#include <stdio.h>
#include <memory.h>

void Buffer_CreateBuffer(Buffer_t* buff) {
  glBindBuffer(buff->target, buff->handle);
  glBufferData(buff->target, buff->size, buff->data, buff->usage);
  printf("Count = %u\n", buff->count);
}

void Buffer_Unbind(Buffer_t* buff) {
  glBindBuffer(buff->target, 0);
}

void Buffer_Init(Buffer_t* buff) {
  glGenBuffers(buff->count, &buff->handle);
}

void Buffer_SetStruct(Buffer_t* buff, GLsizei count, GLsizeiptr size, GLvoid* data, GLenum usage, GLenum target) {
  Buffer_t temp = { 0, target, size, data, count, usage };
  //basically : buff = {temp} or {count, ....}
  memcpy(buff, &temp, sizeof(temp));
}

void Buffer_Bind(Buffer_t* buff) {
  glBindBuffer(buff->target, buff->handle);
}
