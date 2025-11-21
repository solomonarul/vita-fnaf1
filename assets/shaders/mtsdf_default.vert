attribute vec2 a_position;
attribute vec2 a_texture_coords;

varying vec2 v_texture_coords;

void main() {
    gl_Position = vec4(a_position, 0.0, 1.0);
    v_texture_coords = a_texture_coords;
}
