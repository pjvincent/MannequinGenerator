#version 120

uniform sampler2D texture;

uniform float map_KaMargin;
uniform float map_KdMargin;
uniform float map_dMargin;
uniform float map_BumpMargin;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ns;
uniform float d;

uniform int texturePosition;
uniform int nbrTextureParts;

uniform vec4 hairColor;
uniform int objectType;

uniform mat4 mvpt;

varying vec2 vert_tc;
varying vec3 vert_L;
varying vec3 vert_V;
varying vec3 vert_N;
varying vec4 vert_vertex;
varying vec4 vert_color;

vec4 color(int _texPosition, vec2 _texCoord);

vec3 ambientDiffuseSpecularIntensity(vec3 _L, float _Ns);

const int HAIR = 0;
const int SKIN = 1;
const int EYES = 2;
const int OTHER = 3;

vec3 V;
vec3 N;
vec3 L;

void main(void)
{
    vec4 texColor = color(texturePosition, vert_tc);
    vec4 map_dColor  = vec4(d);


    N = normalize(vert_N);
    L = normalize(vert_L);
    V = normalize(vert_V);



    vec3 intensity;


    if(objectType == HAIR)
    {
        texColor.rgb *= hairColor.rgb;
        intensity =
                ambientDiffuseSpecularIntensity(vec3(1, 0, 0), 0.4) * vec3(0.3, 0.4, 0.2) +
                ambientDiffuseSpecularIntensity(vec3(0, 0, 1), 0.4) * vec3(0.3, 0.4, 0.2);
        // ambientDiffuseSpecularIntensity(vec3(1, 0, 0), 50) * vec3(0.3, 0.4, 0.5) +
        // ambientDiffuseSpecularIntensity(vec3(0, 0, 1), 50) * vec3(0.3, 0.4, 0.5);
    }
    else
        intensity =
                ambientDiffuseSpecularIntensity(vec3(1, 0, 0), 5) * vec3(0.3, 0.4, 0.02) +
                ambientDiffuseSpecularIntensity(vec3(0, 0, 1), 5) * vec3(0.3, 0.4, 0.02) +
                ambientDiffuseSpecularIntensity(vec3(-1, 1, 0), 5) * vec3(0.3, 0.4, 0.02);








    gl_FragColor = texColor * (intensity.x + intensity.y) + vec4(1) * intensity.z;
    gl_FragColor.a = texColor.a;




    // if(objectType == HAIR)
    // {
    // Ns = 20.21928024;
    // Ks = vec3(0.5);
    // texColor *= hairColor;
    // }// vec4 specularColor;
    // if(objectType == SKIN)
    // specularColor = vec4(texColor.rgb * specularIntensity, 1);
    // else
    // specularColor = vec4(0);
    // vec4 diffuseColor = vec4(map_KdColor.rgb * diffuseIntensity, 1);
    // if(map_KaMargin >= 0)
    // texColor = texture2D(texture, vec2(map_KaMargin + vert_tc.x / nbrMaxTextures, vert_tc.y)).rgb;
    // else
    // texColor = Ka;
    // if(map_KdMargin >= 0)
    // map_KdColor = texture2D(texture, vec2(map_KdMargin + vert_tc.x / nbrMaxTextures, vert_tc.y)).rgb;
    // else
    // map_KdColor = Kd;
    // texColor = color(texturePosition);
    // texColor = color(2, (vert_vertex.xy + 100.0) / 200.0);
    // if(texColor.rgb == vec3(0, 255, 255) / 255.0)
    // texColor = vec4(0, 0, 0, 1);
    // texColor = vert_color;
    // texColor = vec3(75, 50, 38) / 255.0;
    // texColor = vec3(0.5, 0, 0);
    // map_KdColor = vec3(0.5, 0, 0);
    // texColor = N;
    // map_KdColor = N;
    // if(map_dMargin >= 0)
    // map_dColor = texture2D(texture, vec2(map_dMargin + vert_tc.x / nbrMaxTextures, vert_tc.y)).rgb;
    // else
    // map_dColor = vec3(d);
    // texColor = map_dColor;
    // map_KdColor = map_dColor;
    // N.x = N.x + (texture2D(texture, vec2(map_dMargin + (vert_tc.x + pow(distance, 2) / 500) / nbrMaxTextures, vert_tc.y)).r
    // - texture2D(texture, vec2(map_dMargin + vert_tc.x / nbrMaxTextures, vert_tc.y)).r) * 2 ;
    // N.y = N.y + (texture2D(texture, vec2(map_dMargin + vert_tc.x / nbrMaxTextures, vert_tc.y +  pow(distance, 2) / 250)).r
    // - texture2D(texture, vec2(map_dMargin + vert_tc.x / nbrMaxTextures, vert_tc.y)).r) * 2 ;
    // Ns = 0.3;
    // float specularIntensity = pow(max(dot(R, V), 0.0), Ns);
    // float specularIntensity =
    // pow(max(dot(R, V), 0.0), 0.3) +
    // pow(max(dot(R, V), 0.0), -0.4) * 0;
    // float specularIntensity =
    // pow(max(dot(R, V), 0.0), 0.3) +
    // pow(max(dot(R, V), 0.0), -0.4) * 0;
    // float specularIntensity = pow(max(dot(R, V), 0.0), Ns);
    // color = vec4
    // (Ka * texColor +
    // Kd * map_KdColor * diffuseIntensity +
    // Ks * specularIntensity, map_dColor.r);
    // specularColor = vec4(Ks * specularIntensity, texColor.a);
    // if(Ks == vec3(0, 0, 0) || dot(V, N) < 0)
    // specularColor = vec4(0);
    // gl_FragColor = texColor +
    // map_KdColor * 0.4 * diffuseIntensity;
    // gl_FragColor = texColor +
    // map_KdColor * diffuseIntensity +
    // specularColor;
    // if(objectType == 0)
    // gl_FragColor = texColor;
    // gl_FragColor = vert_color;
    // gl_FragColor = vec4(texColor, 1.0);
    // color.a = 1;
}


vec3 ambientDiffuseSpecularIntensity(vec3 _L, float _Ns)
{
    vec3 R = 2.0 * dot(N, _L) * N - _L;
    return vec3(1,
                max(dot(N, _L), 0.0),
                max(pow(max(dot(R, V), 0.0), _Ns), 0));
}


vec4 color(int _texPosition, vec2 _texCoord)
{
    int nbrCols = int(min(float(nbrTextureParts), 3.0f));
    int nbrRows = 1 + (nbrTextureParts - 1) / 3;

    int col = int(mod(_texPosition, 3));
    int row = nbrRows - 1 - _texPosition / 3;

    return texture2D(texture, vec2((col + _texCoord.x) / nbrCols, (row + _texCoord.y) / nbrRows));
}
