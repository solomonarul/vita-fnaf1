precision mediump float;

uniform sampler2D u_texture;
uniform sampler2D u_static_texture;
uniform float u_alpha;
uniform float u_static_alpha;

varying vec2 v_texture_coords;

void main() {
    vec3 background_color = (texture2D(u_texture, v_texture_coords) * u_alpha).rgb;
    vec3 static_color = (texture2D(u_static_texture, v_texture_coords) * u_static_alpha).rgb;
    gl_FragColor = vec4(background_color + static_color, 1.0);
}
