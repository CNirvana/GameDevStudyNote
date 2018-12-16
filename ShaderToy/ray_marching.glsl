#define MAX_STEPS 64
#define EPS 0.0001
#define MIN_DIST 0.0
#define MAX_DIST 100.0

const vec3 ambientColor = vec3(1.0, 1.0, 1.0);

// Primitives
float sdSphere(vec3 p, float s)
{
    return length(p) - s;
}

float sdBox(vec3 p, vec3 b)
{
  vec3 d = abs(p) - b;
  return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0);
}

float sdTorus(vec3 p, vec2 t)
{
    vec2 q = vec2(length(p.xz) - t.x, p.y);
    return length(q) - t.y;
}

float sdCone(vec3 p, vec2 c)
{
    // c must be normalized
    float q = length(p.xy);
    return dot(c,vec2(q,p.z));
}

float sdEllipsoid( in vec3 p, in vec3 r )
{
    float k0 = length(p/r);
    float k1 = length(p/(r*r));
    return k0*(k0-1.0)/k1;
}

// Primitive alterations

// Primitive combinations
float opUnion(float d1, float d2)
{
    return min(d1, d2);
}

float opSmoothUnion(float d1, float d2, float k)
{
    float h = clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
    return mix(d2, d1, h) - k * h * (1.0 - h);
}

float opSubtraction(float d1, float d2)
{
    return max(-d1, d2);
}

float opSmoothSubtraction(float d1, float d2, float k)
{
    float h = clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0);
    return mix(d2, -d1, h) + k * h * (1.0 - h);
}

float opIntersection(float d1, float d2)
{
    return max(d1, d2);
}

float opSmoothIntersection(float d1, float d2, float k)
{
    float h = clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0);
    return mix(d2, d1, h) + k * h * (1.0 - h);
}

// Transformations
mat4 rotateX(float theta)
{
    float c = cos(theta);
    float s = sin(theta);

    return mat4(
        vec4(1, 0.0, 0.0, 0.0),
        vec4(0.0, c, -s, 0.0),
        vec4(0.0, s, c, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

mat4 rotateY(float theta)
{
    float c = cos(theta);
    float s = sin(theta);

    return mat4(
        vec4(c, 0.0, s, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(-s, 0.0, c, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

mat4 rotateZ(float theta)
{
    float c = cos(theta);
    float s = sin(theta);

    return mat4(
        vec4(c, -s, 0.0, 0.0),
        vec4(s, c, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );
}

// Scene
float map(vec3 p)
{
    //return sdBox(p, vec3(0.1));
    float sphereDist = sdSphere((p + vec3(0, sin(iGlobalTime), 0)) / 0.5, 1.0) * 0.5; // Uniform scale
    float ellipsoidDist = sdEllipsoid((p + vec3(0.0, 1.0, 0.0)) / vec3(2.0, 1.0, 1.0), vec3(1.0, 0.5, 1.0)) * min(2.0, min(1.0, 1.0)); // Nonuniform scale
    float torusDist = sdTorus((rotateZ(-iGlobalTime) * vec4(p + vec3(0.0, -1.0, 0.0), 1.0)).xyz, vec2(0.7, 0.5));

    float dist = opSmoothUnion(sphereDist, torusDist, 0.02);
    dist = opSmoothUnion(ellipsoidDist, dist, 0.02);
    return dist;
}

float rayMarching(vec3 ro, vec3 rd, float start, float end)
{
    float depth = start;
    for(int i = 0; i < MAX_STEPS; i++)
    {
        float dist = map(ro + rd * depth);
        if(dist < EPS)
        {
            return depth;
        }

        depth += dist;

        if(depth >= end)
        {
            return end;
        }
    }

    return end;
}

vec3 calcNormal(vec3 p)
{
    return normalize(vec3(
                map(vec3(p.x + EPS, p.y, p.z)) - map(vec3(p.x - EPS, p.y, p.z)),
                map(vec3(p.x, p.y + EPS, p.z)) - map(vec3(p.x, p.y - EPS, p.z)),
                map(vec3(p.x, p.y, p.z + EPS)) - map(vec3(p.x, p.y, p.z - EPS))
            ));
}

vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord)
{
    vec2 xy = fragCoord - size * 0.5;
    float z = size.y / tan(radians(fieldOfView) * 0.5);
    return normalize(vec3(xy, -z));
}

mat4 getViewMatrix(vec3 eye, vec3 center, vec3 up)
{
    vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);

    return mat4(vec4(s, 0.0), vec4(u, 0.0), vec4(-f, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
}

vec3 directionalLight(vec3 V, vec3 N, vec3 L, vec3 K_d, vec3 K_s, float shininess, vec3 intensity)
{
    float NdotL = max(0.0, dot(N, L));
    vec3 diff = K_d * NdotL;

    vec3 H = normalize(L + V);
    float NdotH = max(0.0, dot(N, H));
    vec3 spec = K_s * pow(NdotH, shininess);

    return intensity * (diff + spec);
}

vec3 phongIllumination(vec3 cameraPos, vec3 worldPos)
{
    vec3 N = calcNormal(worldPos);
    vec3 V = normalize(cameraPos - worldPos);

    const vec3 K_a = vec3(0.1, 0.1, 0.1);
    const vec3 I_a = vec3(1.0, 1.0, 1.0);
    vec3 ambient = K_a * I_a;

    vec3 L = normalize(vec3(1.0, 1.0, 1.0));
    vec3 color = ambient + directionalLight(V, N, L, vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), 100.0, vec3(0.4, 0.4, 0.4));

    return color;
}

void main()
{
    vec3 viewDir = rayDirection(45.0, iResolution.xy, gl_FragCoord.xy);
    vec3 ro = vec3(8.0, 5.0, 7.0);
    mat4 vm = getViewMatrix(ro, vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
    vec3 rd = (vm * vec4(viewDir, 0.0)).xyz;
    float dist = rayMarching(ro, rd, MIN_DIST, MAX_DIST);

    if (dist > MAX_DIST - EPS)
    {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    vec3 p = ro + dist * rd;
    vec3 color = phongIllumination(ro, p);

    gl_FragColor = vec4(color, 1.0);
}