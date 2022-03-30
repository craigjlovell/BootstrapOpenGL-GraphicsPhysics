// a simple fla colour shader

#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec4 objPosition;

uniform sampler2D seamlessTexture;
uniform sampler2D hatchingTexture;
uniform sampler2D rampTexture;

uniform vec3 CameraPosition;

uniform vec3 Ka; // Ambient mat color
uniform vec3 Kd; // Diffuse mat color
uniform vec3 Ks; // Specular mat color
uniform float specularPower; // specular Power of mat

uniform vec3 AmbientColor; // Ambient light color

uniform vec3 LightColor; // Diffuse and specular color
uniform vec3 LightDirection; // Light direction

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

    vec4 sampleXY = texture(seamlessTexture, objPosition.xy * 0.1);
    vec4 sampleYZ = texture(seamlessTexture, objPosition.yz * 0.1);
    vec4 sampleXZ = texture(seamlessTexture, objPosition.xz * 0.1);
    vec4 sampleTP = N.x * N.x * sampleYZ + N.y * N.y * sampleXZ + N.z * N.z * sampleXY;
    sampleTP = vec4(ivec4(sampleTP * 4 + 0.5)) / 4;

    float intenstity = AmbientColor.r + lambertTerm + specularTerm;

    vec4 hatching = texture(hatchingTexture, gl_FragCoord.xy / 5);
    intenstity = step(hatching.x, intenstity);

    // Calculate the diffuse, ambiet and specular color of the model
    vec3 ambient = AmbientColor * Ka;
    vec3 diffuse = (AmbientColor + step(vec3(0.5,0.5,0.5), LightColor * lambertTerm)) * sampleTP.xyz;
    vec3 specular = LightColor * Ks * step(0.1, specularTerm);

    float rim = 1 - max(0, dot(N, V));
    rim = rim * rim * rim;
    float alpha = rim + specular.r;

    // if(alpha < 0.1f)
    //     discard; 

    //FragColor = vec4(ambient + diffuse + specular + rim, alpha);
    FragColor = vec4(diffuse + specular, 1);
    //FragColor = vec4(intenstity * vec3(1,1,1), 1);
    //FragColor = texture(rampTexture, vec2(lambertTerm, 0.03f));
}