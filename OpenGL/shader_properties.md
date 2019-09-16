```glsl
#version 450 core
layout (location = 0) in vec3 n_Position;
layout (location = 1) in vec3 n_Normal;
layout (location = 2) in vec2 n_Texcoord;
```

# Uniform
- u_viewProjectionMatrix
- u_projectionMatrix
- u_viewMatrix
- u_modelMatrix
- u_worldToObj
- u_cameraPos

- u_screenTex
- u_screenTex_texelSize
- u_time
- u_skybox
- u_ambient

# Lighting

## Directional Light
```glsl
struct DirectionalLight
{
    vec3 lightColor;
    vec3 lightDir;
};
```
- u_dirLight
- u_dirLights[index]

## Point Light
```glsl
struct PointLight
{
    vec3 lightColor;
    vec3 lightPos;

    float constant;
    float linear;
    float quadratic;
};
```
- u_pointLight
- u_pointLights[index]

## Spot Light
```glsl
struct SpotLight
{
    vec3 lightColor;
    vec3 lightPos;
    vec3 direction;
    float cutOff;
    float outerCutoff;

    float constant;
    float linear;
    float quadratic;
};
```
- u_spotLight
- u_spotLights[index]