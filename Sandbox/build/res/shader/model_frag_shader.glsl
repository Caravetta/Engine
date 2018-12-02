#version 400

in vec3 colour;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 out_Color;

void main(void){
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitVectorToCamera = normalize(toCameraVector);

    float shineDamper = 1;
    float reflectivity = 0;

    vec3 attenuation = vec3(1, 0, 0);

    vec3 lightColour = vec3(1.5, 1.3, 1.2);
    
    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    float distance = length(toLightVector);
    float attFactor = attenuation.x + (attenuation.y * distance) + (attenuation.z * distance * distance);
    vec3 unitLightVector = normalize(toLightVector); 
    float nDotl = dot(unitNormal,unitLightVector);
    float brightness = max(nDotl,0.0);
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection,unitNormal);
    float specularFactor = dot(reflectedLightDirection , unitVectorToCamera);
    specularFactor = max(specularFactor,0.0);
    float dampedFactor = pow(specularFactor,shineDamper);
    totalDiffuse = totalDiffuse + (brightness * lightColour)/attFactor;
    totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColour)/attFactor;

    totalDiffuse = max(totalDiffuse, 0.1);

	out_Color = vec4(totalDiffuse,1.0) * vec4(colour, 1) + vec4(totalSpecular,1.0);
}
