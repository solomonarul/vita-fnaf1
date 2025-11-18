#include "gl/window.hpp"
#include "gl/shader.hpp"

#ifdef __psp2__
int _newlib_heap_size_user   = 100 * 1024 * 1024;   // 100MB
unsigned int sceLibcHeapSize = 50 * 1024 * 1024;    // 50MB
#endif

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;

    // Create and use window.
    GL::Window window(GL::WindowConfig{.title = "Five Nights at Freddy's 1", .w = 960, .h = 544});
    window.use();

    // Build shaders
    std::ifstream shader_in("assets/shaders/bg.vert");
    GL::VertexShader vs(shader_in);
    shader_in.close();
    shader_in.open("assets/shaders/bg.frag");
    GL::FragmentShader fs(shader_in);
    shader_in.close();

    GL::Shader shader(vs, fs);

    // Background buffers.
    float verts[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    GLint a_position = glGetAttribLocation(shader.id, "a_position");
    GLint a_texture_coords = glGetAttribLocation(shader.id, "a_texture_coords");

    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glEnableVertexAttribArray(a_texture_coords);
    glVertexAttribPointer(a_texture_coords, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));    

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    unsigned char pixels[] = {
        255, 255, 0, 255,   0, 255, 255, 255,
        255, 0, 0, 255,   255, 0, 255, 255
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Draw.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    GLint u_texture = glGetUniformLocation(shader.id, "u_texture");
    glUniform1i(u_texture, 0);

    glViewport(0, 0, 960, 544);
    shader.use();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    window.swap();
    SDL_Delay(4000);

    // Cleanup.
    glDeleteTextures(1, &tex);
    glDeleteBuffers(1, &vbo);
    return 0;
}
