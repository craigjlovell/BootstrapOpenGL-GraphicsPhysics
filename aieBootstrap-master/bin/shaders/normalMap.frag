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
uniform float specularPower; // specular Power of mat

uniform vec3 AmbientColor; // Ambient light color
uniform vec3 LightColor; // Diffuse and specular color
uniform vec3 LightDirection;

const int MAX_LIGHTS = 4;
uniform int numLights;
uniform vec3 PointLightColors[MAX_LIGHTS];
uniform vec3 PointLightPositions[MAX_LIGHTS];

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

out vec4 FragColor;

vec3 Diffuse(vec3 direction, vec3 color, vec3 normal)
{
    return color * max(0, dot(normal, -direction));
}

vec3 Specular(vec3 direction, vec3 color, vec3 normal, vec3 view)
{
    vec3 R = reflect(direction, normal);

    float specularTerm = pow(max(0, dot(R, view)), specularPower);
    return specularTerm * color;
}


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

    // Calculate the diffuse lighting from the global source
    vec3 diffuseTotal = Diffuse(L, LightColor, N);

    vec3 V = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(L, N);

    // Calculate the specular light from the global source
    vec3 specularTotal = Specular(L, LightColor, N , V);

    for(int i = 0; i < numLights; i++)
    {
        vec3 direction = vPosition.xyz - PointLightPositions[i];
        float distance = length(direction);
        direction = direction/distance;

        vec3 color = PointLightColors[i] / (distance * distance);

        diffuseTotal += Diffuse(direction, color, N);
        specularTotal += Specular(direction, color, N, V);
    }

    // calculate specular term 
 //float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );

    // Calculate the diffuse, ambiet and specular color of the model
    vec3 ambient  = AmbientColor * Ka * texDiffuse;
    vec3 diffuse  = Kd * texDiffuse * diffuseTotal;
    vec3 specular = Ks * texSpecular * specularTotal;

    FragColor = vec4(ambient + diffuse + specular, 1);
}