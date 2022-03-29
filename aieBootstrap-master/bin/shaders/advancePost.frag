// a simple fla colour shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colorTarget;
uniform int postProcessTarget;
uniform sampler2D screenTexture;

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

vec4 EdgeDetection(vec2 texCoord){
    mat3 sx = mat3( 
    1.0, 2.0, 1.0, 
    0.0, 0.0, 0.0, 
   -1.0, -2.0, -1.0 
);
mat3 sy = mat3( 
    1.0, 0.0, -1.0, 
    2.0, 0.0, -2.0, 
    1.0, 0.0, -1.0 
);


vec3 diffuse = texture(colorTarget, texCoord).rgb;
    mat3 I;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            vec3 test = texelFetch(colorTarget, ivec2(gl_FragCoord) + ivec2(i-1,j-1), 0 ).rgb;
            I[i][j] = length(test); 
    }
}
float gx = dot(sx[0], I[0]) + dot(sx[1], I[1]) + dot(sx[2], I[2]); 
float gy = dot(sy[0], I[0]) + dot(sy[1], I[1]) + dot(sy[2], I[2]);

float g = sqrt(pow(gx, 2.0)+pow(gy, 2.0));
FragColor = vec4(diffuse - vec3(g), 1.0);
return FragColor;
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

vec4 GreyScale(vec2 texCoord){
    vec4 baseColor = texture(colorTarget, texCoord);
    vec4 grey = vec4(
        dot(baseColor.rgb, vec3(0.5f,0.5f,0.5f)),
        dot(baseColor.rgb, vec3(0.5f,0.5f,0.5f)),
        dot(baseColor.rgb, vec3(0.5f,0.5f,0.5f)),
        1.0f
    );
    return grey;
}

vec4 Invert(vec2 texCoord){
    vec4 baseColor = texture(colorTarget, texCoord);
    vec4 invert = vec4(
        1.0f - baseColor.r,
        1.0f - baseColor.g,
        1.0f - baseColor.b,
        1.0f
    );
    return invert;
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
    int temp = 0;
    switch(postProcessTarget)
    {
        case 0: // Default
        {
            FragColor = Default(texCoord);
            break;  
        }
        case 1: // BoxBlur
        {
            FragColor = BoxBlur(texCoord);
            break;  
        }
        case 2: // Distort
        {
            FragColor = Distort(texCoord);
            break;  
        }
        case 3: // Edge Detection
        {
            FragColor = EdgeDetection(texCoord);
            break;  
        }
        case 4: // Sepia
        {
            FragColor = Sepia(texCoord);
            break;  
        }
        case 5: // ScanLines
        {
            FragColor = Default(texCoord);
            break;  
        }
        case 6: // Grey Scale
        {
            FragColor = GreyScale(texCoord);
            break;  
        }
        case 7: // Invert
        {
            FragColor = Invert(texCoord);
            break;  
        }
        case 8: // Pixilizer
        {
            FragColor = Default(texCoord);
            break;  
        }
        case 9: // Posterization
        {
            FragColor = Default(texCoord);
            break;  
        }
        case 10: // Distance fog
        {
            FragColor = Default(texCoord);
            break;  
        }
        case 11: // Depth of Field
        {
            FragColor = Default(texCoord);
            break;  
        }

    }
}