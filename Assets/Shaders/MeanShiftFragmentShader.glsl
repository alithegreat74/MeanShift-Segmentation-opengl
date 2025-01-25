#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uTexture;
uniform vec2 uTexelSize;
uniform float uRadius;
uniform float uColorWeight;

void main()
{
    vec4 centerColor = texture(uTexture, TexCoords);
    
    vec4 sum = vec4(0.0);
    float totalWeight = 0.0;
    
    for(float x = -uRadius; x <= uRadius; x += 1.0) {
        for(float y = -uRadius; y <= uRadius; y += 1.0) {
            vec2 offset = vec2(x, y) * uTexelSize;
            vec4 sampleColor = texture(uTexture, TexCoords + offset);
            
            float colorDist = length(sampleColor.rgb - centerColor.rgb);
            float weight = exp(-colorDist * uColorWeight);
            
            sum += sampleColor * weight;
            totalWeight += weight;
        }
    }
    
    FragColor = totalWeight > 0.0 ? sum / totalWeight : centerColor;
}