// a simple fla colour shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colorTarget;
uniform vec2 screensize;
uniform int postProcessTarget;
uniform float deltaTime;

uniform sampler2D outOfFocusTexture;
uniform sampler2D positionTexture;
uniform vec2 mouseFocusPoint;

uniform vec4 color;
uniform vec2 nearFar;
uniform sampler2D fogTexture;

out vec4 FragColor;
out vec4 FragColor1;

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

vec4 ScanLines(vec2 texCoord){
    float density = 1.3f;
    float opacityScanline = 0.3;
    float opacityNoise = 0.2;
    float flickering = 0.03;

    vec2 uv = texCoord / screensize.xy;
    vec3 baseColor = texture(colorTarget, uv).rgb;

    float count = screensize.y * density;
    vec2 sl = vec2(sin(uv.y * count), cos(uv.y * count));
    vec3 scanlines = vec3(sl.x, sl.y, sl.x);

    float random = fract(sin(dot(uv * deltaTime, vec2(12.9898,78.233)))*43758.5453123);

    baseColor += baseColor * scanlines * opacityScanline;
    baseColor += baseColor * random * opacityNoise;
    baseColor += baseColor * sin(110.0 * deltaTime) * flickering;
    baseColor += texture(colorTarget, texCoord).rgb;
    
    return vec4(baseColor, 1.0f);
}

vec4 GreyScale(vec2 texCoord){
    vec4 baseColor = texture(colorTarget, texCoord);
    float greyData = dot(baseColor.rgb, vec3(0.5f,0.5f,0.5f));
    vec4 grey = vec4(
        greyData, greyData, greyData, 1.0f        
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

vec4 Pixilizer (vec2 texCoord){
    float pixels = 512;
    float dx = 15 * (1.0 / pixels);
    float dy = 10 * (1.0 / pixels);
    vec2 coord = vec2(dx * floor(texCoord.x / dx),
                      dy * floor(texCoord.y / dy));
    return texture(colorTarget, coord);
}

vec4 Posterization(vec2 texCoord){
    float levels = 10;
    vec4 baseColor = texture(colorTarget, texCoord);
    float greyscale = max(baseColor.r, max(baseColor.g, baseColor.b));
    float lower = floor(greyscale * levels) / levels;
    float lowerDiff = abs(greyscale - lower);
    float upper = ceil(greyscale * levels) / levels;
    float upperDiff = abs(upper - greyscale);
    float level = lowerDiff <= upperDiff ? lower : upper;
    float adjustment = level / greyscale;
    return vec4(baseColor.rgb * adjustment, 1.0f);
}

//vec4 Fog(vec2 texCoord){
//    float fogMin = 0.00;
//    float fogMax = 0.97;//

//    vec4 baseColor = texture(colorTarget, texCoord);
//    vec4 fogColor  = texture(fogTexture,  texCoord);
//    vec4 position = texture(positionTexture, texCoord);//

//    float near = nearFar.x;
//    float far  = nearFar.y;//

//    float intensity = clamp((position.y - near) / (far - near), fogMin, fogMax);//

//    return FragColor = vec4(baseColor.rgb, intensity);
//    //FragColor = baseColor;
//    //FragColor = mix(FragColor, fogColor, min(fogColor.a, 1));
//}

vec4 DepthOfField(vec2 texCoord){
    float minDistance = 1.0;
    float maxDistance = 3.0;

    vec4 focusColor      = texture(colorTarget, texCoord);
    vec4 outOfFocusColor = texture(outOfFocusTexture, texCoord);
    vec4 position = texture(positionTexture, texCoord);
    vec4 focusPoint = texture(positionTexture, mouseFocusPoint);

    float blur =
    smoothstep
      ( minDistance
      , maxDistance
      , abs(position.y - focusPoint.y)
      );

    FragColor = mix(focusColor, outOfFocusColor, blur);
    return FragColor;
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
            FragColor = ScanLines(texCoord);
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
        case 8: // Pixilizer easy
        {
            FragColor = Pixilizer(texCoord);
            break;  
        }
        case 9: // Posterization easy
        {
            FragColor = Posterization(texCoord);
            break;  
        }
        case 10: // Distance fog
        {
            FragColor = Default(texCoord);
            break;  
        }
        case 11: // Depth of Field
        {
            FragColor = DepthOfField(texCoord);
            break;  
        }

    }
}