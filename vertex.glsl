#version 120

uniform sampler2D texture;

attribute vec4 vertex;
attribute vec4 texCoord;
attribute vec4 normal;

//attribute float indexVertex;
//attribute float indexTexCoord;
//attribute float indexNormal;

attribute vec4 direction;
attribute vec2 chest;
attribute vec2 waist;
attribute vec2 arms;
attribute vec2 legs;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;
uniform mat4 initTranslation;
uniform mat4 initRotation;

uniform vec3 lightPos;
uniform vec3 eyePos;

uniform int width;
uniform int height;

uniform float pixelWidth;
uniform float pixelHeight;

varying vec2 vert_tc;
varying vec3 vert_L;
varying vec3 vert_V;
varying vec3 vert_N;
varying vec4 vert_vertex;
varying vec4 vert_color;

uniform float tourPoitrine;
uniform float tourHanches;
uniform float tourVentre;
uniform float tourCou;
uniform float tourBras;
uniform float tourJambes;
uniform float longBras;
uniform float longJambes;

uniform int nbrTextureParts;


vec4 color(int _texPosition, vec2 _texCoord);

vec3 projection(vec3 P, vec3 A, vec3 U);
vec4 computeDirection();

float coefficient(vec4 _vec);

bool isInFront(vec3 P, vec3 A, vec3 B, vec3 C);
bool compare(float _color, float _val, float _tolerance);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3 epauleG = vec3(14, 137, 28);
vec3 coudeG0 = vec3(18, 111, 26);
vec3 coudeG1 = vec3(27, 115, 30);
vec3 coudeG = (coudeG0 + coudeG1) / 2.0;
vec3 mainG = vec3(40, 50, 41);

vec3 epauleD = vec3(-12, 136, 23);
vec3 coudeD0 = vec3(-16.5, 109, 25);
vec3 coudeD1 = vec3(-24.5, 114, 27);
vec3 coudeD = (coudeD0 + coudeD1) / 2.0;
vec3 mainD = vec3(-45, 50, 49);

vec3 hancheD = vec3(-7, 90, 29);
vec3 genouD0 = vec3(-12, 52, 30);
vec3 genouD1 = vec3(-24, 55, 26);
vec3 genouD = (genouD0 + genouD1) / 2.0;
vec3 piedD = vec3(-42, -50, 16);

vec3 hancheG = vec3(11, 90, 33);
vec3 genouG0 = vec3(2, 54, 38);
vec3 genouG1 = vec3(16, 54, 38);
vec3 genouG = (genouG0 + genouG1) / 2.0;
vec3 piedG = vec3(8, -50, 20);

vec3 oreilleD = vec3(-11, 170, 33);
vec3 oreilleG = vec3(12, 170, 33);
vec3 tete = (oreilleD + oreilleG) / 2.0;
vec3 gorge = (epauleD + epauleG) / 2.0;
vec3 entrejambe = (hancheG + hancheD) / 2.0;

vec3 A = vec3(1, 130.5, 34.5);
vec3 B = vec3(0, 90, 40);

const int torse         = 1001;

const int molletG       = 7;
const int basVentre     = 13;
const int cuisseG       = 19;
const int molletD       = 27;
const int cuisseD       = 36;
const int ventreC       = 45;
const int ventreD       = 56;
const int poitrineC     = 67;
const int ventreG       = 80;
const int poitrineD     = 93;
const int cou           = 105;
const int epaules       = 119;
const int poitrineG     = 135;
const int brasD         = 150;
const int brasG         = 166;
const int avantBrasG    = 183;
const int avantBrasD    = 200;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main(void)
{
    vec4 vertex = vertex + normalize(direction) * (chest.x * tourCou +
                                                   chest.y * tourPoitrine +
                                                   waist.x * tourVentre +
                                                   waist.y * tourHanches +
                                                   arms.x * tourBras +
                                                   legs.x * tourJambes) / 255.0;

    vertex = vertex + vec4(0, -1, 0, 1) * (arms.y * longBras +
                                           legs.y * longJambes) / 255.0;

    vertex.w = 1;


    vec4 normal = initRotation * normal;

    vertex = initRotation * initTranslation * vertex;

    // if(normal.z > 0 || vertex.z > -7)

    //    if(color(0) == vec3(1, 0, 0))
    //    {

    //        // normal = normalize(normal + vec4(0, 0, 5, 1));

    //        normal = normalize(vertex - vec4(0, 60, -20, 1));

    //        float plan_z = 20;
    //        float coef = (plan_z - vertex.z) / normal.z;
    //        vertex.x += normal.x * coef;
    //        vertex.y += normal.y * coef;
    //        vertex.z = plan_z;
    //        vertex.w = 1;

    //        normal = vec4(0, 0, 1, 1);
    //    }

    //    else
    //    {
    //        normal = normalize(vertex - vec4(0, 60, 20, 1));

    //        float plan_z = -60;
    //        float coef = (plan_z - vertex.z) / normal.z;
    //        vertex.x += normal.x * coef;
    //        vertex.y += normal.y * coef;
    //        vertex.z = plan_z;
    //        vertex.w = 1;

    //        normal = vec4(0, 0, 1, 1);
    //    }

    normal = model * normal;

    vertex = model * vertex;

    gl_Position = perspective * view * vertex;

    // gl_Position = vec4(pixelWidth, pixelHeight, 0, 0);
    // gl_Position = vec4(-1 + indexTexCoord * 2.0 / width, -pixelHeight * 400, 0, 1);
    // gl_Position = vec4(- 1 + indexTexCoord * 2.0 / height, -1, 0, 1);
    // vec2 position = vec2(mod(indexTexCoord, float(width)), int(indexTexCoord) / (width));
    // gl_Position = vec4(position.x * pixelWidth - 1, position.y * pixelHeight - 1, 0, 1);

    vert_L = lightPos - vertex.xyz;
    vert_V = eyePos - vertex.xyz;
    vert_N = normal.xyz;

    vert_tc = texCoord.xy;

}


float coefficient(vec4 _vec)
{
    vec4 c = color(int(_vec.a), texCoord.xy);

    return c.r * _vec.r +
            c.g * _vec.g +
            c.b * _vec.b;
}


vec4 color(int _texPosition, vec2 _texCoord)
{
    int nbrCols = int(min(float(nbrTextureParts), 3.0f));
    int nbrRows = 1 + (nbrTextureParts - 1) / 3;

    int col = int(mod(_texPosition, 3));
    int row = nbrRows - 1 - _texPosition / 3;

    return texture2D(texture, vec2((col + _texCoord.x) / nbrCols, (row + _texCoord.y) / nbrRows));
}


vec3 projection(vec3 P, vec3 A, vec3 B) // projection du point P sur la droite definie par les deux points A et B
{
    vec3 U = A - B;
    return A + U * ((P.x - A.x) * U.x + (P.y - A.y) * U.y + (P.z - A.z) * U.z) / (U.x * U.x + U.y * U.y + U.z * U.z);
}


bool isInFront(vec3 P, vec3 A, vec3 B, vec3 C) // verefie si le point P est devant le plan defini par les trois points A, B et C
{
    return dot(cross(B - A, C - A), P - A) > 0;
}


vec4 computeDirection()
{
    vert_vertex = initRotation * initTranslation * vertex;

    vec2 coord = (vert_vertex.xy + 100.0) / 200.0;
    coord -= (mod(coord, 1.0 / 1024) - vec2(1.0 / 2048));
    vert_color = color(2, coord);

    float tolerance = 2;

    vec3 direction = vec3(0, 0, 1);

    vec3 p = vertex.xyz;

    if(compare(vert_color.b, brasG, tolerance))

        direction = p - projection(p, epauleG, coudeG);

    else if(compare(vert_color.b, avantBrasG, tolerance))

        direction = p - projection(p, mainG, coudeG);

    else if(compare(vert_color.b, brasD, tolerance))

        direction = p - projection(p, epauleD, coudeD);

    else if(compare(vert_color.b, avantBrasD, tolerance))

        direction = p - projection(p, mainD, coudeD);

    else if(compare(vert_color.b, cuisseD, tolerance))

        direction = p - projection(p, hancheD, genouD);

    else if(compare(vert_color.b, molletD, tolerance))

        direction = p - projection(p, piedD, genouD);

    else if(compare(vert_color.b, cuisseG, tolerance))

        direction = p - projection(p, hancheG, genouG);

    else if(compare(vert_color.b, molletG, tolerance))

        direction = p - projection(p, piedG, genouG);

    else if(compare(vert_color.b, poitrineC, tolerance))
    {
        direction = cross(gorge - hancheD, gorge - hancheG);

        if(isInFront(p, B, epauleD, epauleG))

            direction = -direction;
    }

    else if(compare(vert_color.b, ventreC, tolerance))
    {
        direction = cross(gorge - hancheD, gorge - hancheG);

        if(isInFront(p, A, hancheG, hancheD))

            direction = -direction;
    }

    else if(compare(vert_color.b, poitrineG, tolerance))

        direction = p - projection(p, gorge, hancheG);

    else if(compare(vert_color.b, ventreG, tolerance))

        direction = p - projection(p, gorge, hancheG);

    else if(compare(vert_color.b, poitrineD, tolerance))

        direction = p - projection(p, gorge, hancheD);

    else if(compare(vert_color.b, ventreD, tolerance))

        direction = p - projection(p, gorge, hancheD);

    else if(compare(vert_color.b, basVentre, tolerance))

        direction = p - projection(p, hancheG, hancheD);

    return vec4(normalize(direction), 1);

}


bool compare(float _color, float _val, float _tolerance)
{
    return (_color >= (_val - _tolerance) / 255.0 && _color <= (_val + _tolerance) / 255.0);
}




