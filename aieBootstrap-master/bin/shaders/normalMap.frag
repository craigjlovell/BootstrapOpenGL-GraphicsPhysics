// a simple normal map colour shader

#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

uniform vec3 CameraPosition;

uniform vec3 Ka; // Ambient mat color
uniform vec3 Kd; // Diffuse mat color
uniform vec3 Ks; // Specular mat color
float specularPower; // specular Power of mat

uniform vec3 AmbientColor; // Ambient light color

uniform vec3 LightColor; // Diffuse and specular color
uniform vec3 LightDirection;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

out vec4 FragColor;

void main()
{
    // Make sure the normal and light direction are normilised 
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);
    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);

    mat3 TBN = mat3(T, B, N);

    vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
    vec3 texNormal = texture(normalTexture, vTexCoord).rgb;

    N = TBN * (texNormal * 2 - 1);

    // Then calculate the lambert term (negating light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    vec3 V = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(L, N);

    float specularTerm = pow(max(0, dot(R, V)), specularPower);

    // Calculate the diffuse, ambiet and specular color of the model
    vec3 ambient = AmbientColor * Ka * texDiffuse;
    vec3 diffuse = LightColor * Kd * texDiffuse * lambertTerm;
    vec3 specular = LightColor * Ks * texSpecular * specularTerm;

    FragColor = vec4(ambient + diffuse + specular, 1);
}