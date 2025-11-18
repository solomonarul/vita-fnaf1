#include "gl/window.hpp"

#ifdef __psp2__
int _newlib_heap_size_user   = 100 * 1024 * 1024;   // 100MB
unsigned int sceLibcHeapSize = 50 * 1024 * 1024;    // 50MB
#endif

// Simple passthrough shader
const char *vertexShaderSrc =
    "attribute vec2 aPos;"
    "void main() {"
    "    gl_Position = vec4(aPos, 0.0, 1.0);"
    "}";

const char *fragmentShaderSrc =
    "precision mediump float;"
    "void main() {"
    "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";

GLuint compile(GLenum type, const char *src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader; // no error checks for brevity
}

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;

    // Create and use window.
    GL::Window window(GL::WindowConfig{.title = "Five Nights at Freddy's 1", .w = 960, .h = 544});
    window.use();

    // Build shaders
    GLuint vs = compile(GL_VERTEX_SHADER,   vertexShaderSrc);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);

    // Rectangle in NDC
    float x = -0.5f;
    float y = -0.5f;
    float w = 1.0f;
    float h = 1.0f;

    float verts[] = {
        x,     y,
        x+w,   y,
        x,     y+h,
        x+w,   y+h
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    GLint aPos = glGetAttribLocation(program, "aPos");
    glEnableVertexAttribArray(aPos);
    glVertexAttribPointer(aPos, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Draw loop (single frame)
    glViewport(0, 0, 960, 544);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    window.swap();
    SDL_Delay(4000);

    // Cleanup
    glDeleteProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteBuffers(1, &vbo);
    return 0;
}
