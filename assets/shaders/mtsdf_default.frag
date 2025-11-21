precision mediump float;

uniform sampler2D u_texture;
uniform vec4 u_color;

varying vec2 v_texture_coords;

// TODO: Make this a proper uniform, I should only be using 32x32px fonts anyways for which this value is all right.
const float pxRange = 8.0;

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
    vec4 sample = texture2D(u_texture, v_texture_coords);
    float sd = median(sample.r, sample.g, sample.b);
    float screenPxDistance = pxRange * 960.0 * (sd - 0.5);  // TODO: replace 960.0 with actual canvas width.
    float opacity = smoothstep(-0.5, 0.5, screenPxDistance);
    vec4 result = mix(vec4(0.0, 0.0, 0.0, 0.0), u_color, opacity);
    gl_FragColor = result;
}