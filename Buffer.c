#include "Buffer.h"
#include <stdio.h>

void Buffer_CreateBuffer(Buffer_t* buff) {
  if (buff->count == NULL) {
    printf("Here\n");
    glGenBuffers(1, &buff->handle);
  }
  glGenBuffers(buff->count, &buff->handle);
  glBindBuffer(buff->target, buff->handle);
  glBufferData(buff->target, buff->size, buff->data, buff->usage);
  printf("Count = %u\n", buff->count);
}

void Buffer_Unbind(Buffer_t* buff) {
  glBindBuffer(buff->target, 0);
}

void Buffer_Bind(Buffer_t* buff) {
  glBindBuffer(buff->target, buff->handle);
}
