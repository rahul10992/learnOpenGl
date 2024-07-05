#version 330 core
out vec4 FragColour;

in vec3 fragColour;
in vec2 fragTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main() {
    FragColour = mix(texture(texture1, fragTexCoord), texture(texture2, vec2(-fragTexCoord.x, fragTexCoord.y)), mixValue);//  * vec4(fragColour, 0.1)
}


