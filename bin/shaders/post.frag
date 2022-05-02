// a simple fla colour shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colorTarget;

out vec4 FragColor;

//Return the out of the colors as the data was originally provided
vec4 Default(vec2 texCoord){
    return texture(colorTarget, texCoord);
}

vec4 BoxBlur(vec2 texCoord){
    vec2 texel = 1.0f / textureSize(colorTarget, 0);
    
    vec4 color = texture(colorTarget, texCoord);
    color += texture(colorTarget, texCoord + texel * vec2(-1, 1));
    color += texture(colorTarget, texCoord + texel * vec2(-1, 0));
    color += texture(colorTarget, texCoord + texel * vec2(-1,-1));
    
    color += texture(colorTarget, texCoord + texel * vec2( 0, 1));
    color += texture(colorTarget, texCoord + texel * vec2( 0,-1));

    color += texture(colorTarget, texCoord + texel * vec2(1, 1));
    color += texture(colorTarget, texCoord + texel * vec2(1, 0));
    color += texture(colorTarget, texCoord + texel * vec2(1,-1));

    return color / 9;
}

vec4 Distort(vec2 texCoord){
    vec2 mid = vec2(0.5f);

    float distanceFromCentre = distance(texCoord, mid);
    vec2 normalizedCoord = normalize(texCoord - mid);
    float bias = distanceFromCentre + sin(distanceFromCentre * 15) * 0.05f;
    vec2 newCoord = mid + bias * normalizedCoord;
    return texture(colorTarget, newCoord);
}

vec4 Sepia(vec2 texCoord){
    vec4 baseColor = texture(colorTarget, texCoord);
    vec4 sepia = vec4(
        dot(baseColor.rgb, vec3(0.393f, 0.769f, 0.189f)),
        dot(baseColor.rgb, vec3(0.349f, 0.686f, 0.168f)),
        dot(baseColor.rgb, vec3(0.272f, 0.534f, 0.131f)),
        1.0f
    );
    return sepia;
}

void main()
{
    // First calculate the texel's size
    vec2 texSize = textureSize(colorTarget, 0);
    vec2 texelSize = 1.0f / texSize;

    // Adjust the scale and coordinates
    vec2 scale = (texSize - texelSize) / texSize;
    vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;

    // This will output the desired post processing effect
    FragColor = Sepia(texCoord);
}