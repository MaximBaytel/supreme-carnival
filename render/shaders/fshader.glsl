#version 330

in highp vec3 vert;
in highp vec3 vertNormal;
in vec2 textCordinates;

uniform highp vec3 lightPos;
uniform vec3 baseColor;
uniform sampler2D texture;

out vec4 fragColor;


void main() {
    highp vec3 L = normalize(lightPos - vert);
    highp float NL = max(dot(normalize(vertNormal), L), 0.0);
    //highp vec3 color = vec3(0.39, 1.0, 0.0);
    //highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);
	highp vec4 coltext = texture2D(texture, textCordinates);
	//highp vec3 col = coltext * (NL*0.8 + 0.2);
    fragColor = coltext * (NL*0.8 + 0.2);
	};