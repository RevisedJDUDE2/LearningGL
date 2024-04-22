#include "Buffer.h"

void Buffer_CreateBuffer(Buffer_t* buff) {
  glGenBuffers(buff->count, &buff->handle);
  glBindBuffer(buff->target, buff->handle);
  glBufferData(buff->target, buff->size, buff->data, buff->usage);
}

void Buffer_Unbind(Buffer_t* buff) {
  glBindBuffer(buff->target, 0);
}

void Buffer_Bind(Buffer_t* buff) {
  glBindBuffer(buff->target, buff->handle);
}
