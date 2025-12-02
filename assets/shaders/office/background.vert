attribute vec2 a_position;
attribute vec2 a_texture_coords;

uniform float u_view_offset;

varying vec2 v_texture_coords;
varying vec2 v_position;

void main() {
    gl_Position = vec4(a_position, 0.0, 1.0);
    v_position = a_position * 0.5 + 0.5;
    v_texture_coords = vec2((a_texture_coords.x + u_view_offset / 4.0) / 1210.0 * 960.0, a_texture_coords.y);  // TODO: make this an uniform?
}
