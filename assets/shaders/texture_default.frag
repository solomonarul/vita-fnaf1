precision mediump float;

uniform sampler2D u_texture;
uniform vec4 u_color;

varying vec2 v_texture_coords;

void main() {
    vec4 tex = texture2D(u_texture, v_texture_coords);
    gl_FragColor = tex * u_color;
}
