// a simple fla colour shader

#version 410

in vec4 vPosition;
in vec3 vNormal;

uniform vec3 CameraPosition;

uniform vec3 Ka; // Ambient mat color
uniform vec3 Kd; // Diffuse mat color
uniform vec3 Ks; // Specular mat color
float specularPower; // specular Power of mat

uniform vec3 AmbientColor; // Ambient light color

uniform vec3 LightColor; // Diffuse and specular color
uniform vec3 LightDirection;

out vec4 FragColor;

void main()
{
    // Make sure the normal and light direction are normilised 
    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

    // Then calculate the lambert term (negating light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    vec3 V = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(L, N);

    float specularTerm = pow(max(0, dot(R, V)), specularPower);

    // Calculate the diffuse, ambiet and specular color of the model
    vec3 ambient = AmbientColor * Ka;
    vec3 diffuse = LightColor * Kd * lambertTerm;
    vec3 specular = LightColor * Ks * specularTerm;

    FragColor = vec4(ambient + diffuse + specular, 1);
}