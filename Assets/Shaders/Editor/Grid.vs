#version 420 core

uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 pos;

layout(location = 1) out float near;
layout(location = 2) out float far;

layout(location = 3) out vec3 nearPoint;
layout(location = 4) out vec3 farPoint;

layout(location = 5) out mat4 fragView;
layout(location = 9) out mat4 fragProj;

vec3 UnprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

// normal vertice projection
void main() {
    vec3 p = pos.xyz;
    nearPoint = UnprojectPoint(p.x, p.y, 0.0, view, projection).xyz; // unprojecting on the near plane
    farPoint = UnprojectPoint(p.x, p.y, 1.0, view, projection).xyz; // unprojecting on the far plane

    fragView = view;
    fragProj = projection;

    near = 0.01;
    far = 4;

    gl_Position = vec4(p, 1.0); // using directly the clipped coordinates
}