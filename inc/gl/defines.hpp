#pragma once

#define GEN_AND_SEND_VBO(vbo, verts, usage) \
    glGenBuffers(1, &vbo);    \
    glBindBuffer(GL_ARRAY_BUFFER, vbo);   \
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, usage);
