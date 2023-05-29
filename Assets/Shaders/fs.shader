#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D tSampler;
uniform bool flipHorizontal;


void main() {
    vec2 uv = fragmentUV;    
    if (flipHorizontal)    {        
        uv.x = 1.0 - uv.x;    
    }   
        
    vec4 imageTexture = texture(tSampler, uv);    
    color = imageTexture * fragmentColor;
}