#version 400 core

out vec4 FragColor;

const int gradient_points_max = 5;

struct Point {
    vec4 color;
    vec2 location;
    float radius;
    int factor;
};

uniform int points_count;
uniform Point points[gradient_points_max];

float point_effect(Point point) {
    float distance = min(length(point.location - gl_PointCoord), point.radius);
    return pow(1.f - distance/point.radius, point.factor) * point.color.a; // 2 should be a factor (point field)
}

void main() {
    vec3 color = vec3(0.f);
    float effect = 0.f;

    for (int i = 0; i < min(points_count, gradient_points_max); i++) {
        float ef = point_effect(points[i]);
        color += vec3(points[i].color.rgb * ef);
        effect += ef;
    }

    FragColor = vec4(normalize(color), effect);
}