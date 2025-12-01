precision mediump float;

uniform sampler2D u_texture;
uniform vec4 u_color;

varying vec2 v_texture_coords;
varying vec2 v_position;

float vdistance(float s, float t) {
    return abs(s - t);
}

void main() {
    // I stole this from the internet, should work to project the rendered texture to a cylinder.
    vec2 dist = vec2(vdistance(v_position.x, 0.5), vdistance(v_position.y, 0.5));
    float offset = dist.x * 0.2 * dist.y;
    if(v_texture_coords.y > 0.5)
        offset = -offset;
    vec2 v_coords = vec2(v_texture_coords.x, v_texture_coords.y + dist.x * offset * 8.0);
    gl_FragColor = u_color * texture2D(u_texture, v_coords);
}
