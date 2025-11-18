precision mediump float;

uniform sampler2D u_texture;

varying vec2 v_texture_coords;

void main() {
    gl_FragColor = texture2D(u_texture, v_texture_coords);
}
