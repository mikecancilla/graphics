#version 430

in vec3 theColor;
in vec3 normalWorld;
in vec3 vertexPositionWorld;

uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;

out vec4 daColor;


// Light Attenuation: https://imdoingitwrong.wordpress.com/2011/01/31/light-attenuation/
//
// cutoff threshold of 0.005 to 0.001
vec3 AttenuationIllumination(vec3 P, vec3 N, vec3 lightCentre, float lightRadius, vec3 lightColour, float cutoff)
{
    // calculate normalized light vector and distance to sphere light surface
    float r = lightRadius;
    vec3 L = lightCentre - P;
    float distance = length(L);
    float d = max(distance - r, 0);
    L /= distance;
     
    // calculate basic attenuation
    float denom = d/r + 1;
    float attenuation = 1 / (denom*denom);
     
    // scale and bias attenuation such that:
    //   attenuation == 0 at extent of max influence
    //   attenuation == 1 when d == 0
    attenuation = (attenuation - cutoff) / (1 - cutoff);
    attenuation = max(attenuation, 0);
     
    float dot = max(dot(L, N), 0);
    return lightColour * dot * attenuation;
}

//
// d = distance between the light and the surface being shaded
// Kc = constant attenuation factor
// Kl = linear attenuation factor
// Kq = quadratic attenuation factor
//
// Attenuation =
//          1
// --------------------
// Kc + Kl(d) + Kq(d*d)
//

float Attenuate(float lightValue, vec3 vertexPosition, vec3 lightPosition)
{
    vec3 L = lightPosition - vertexPosition;
    float d = length(L);

    float Kc = .2f;
    float Kl = .01f;
    float Kq = .015f;

    float attenuation = Kc + (Kl * d) + (Kq * (d * d));
    attenuation = 1.0 / attenuation;

    return attenuation * lightValue;
}

void main()
{
    // Diffuse lighting
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float diffuseBrightness = dot(lightVectorWorld, normalize(normalWorld));
    diffuseBrightness = pow(diffuseBrightness, 15);
    diffuseBrightness = Attenuate(diffuseBrightness, vertexPositionWorld, lightPositionWorld);
    vec4 diffuseLight = vec4(diffuseBrightness, diffuseBrightness, diffuseBrightness, 1.0);  // varying data

    // Specular lighting
    vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
    vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
    float s = clamp(dot(reflectedLightVectorWorld, eyeVectorWorld), 0, 1);
    s = pow(s, 50);
    s = Attenuate(s, vertexPositionWorld, lightPositionWorld);
    vec4 specularLight = vec4(s, s, s, 1);

    //daColor = ambientLight + specularLight;
    //daColor = ambientLight + clamp(diffuseLight, 0, 1);
    //daColor = ambientLight + clamp(diffuseLight, 0, 1) + specularLight;
    daColor = vec4(theColor, 1.0) + ambientLight + clamp(diffuseLight, 0, 1) + specularLight;
    //daColor = ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
    //daColor = vec4(theColor, 1.0) + ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
    //daColor = clamp(specularLight, 0, 1);
}
