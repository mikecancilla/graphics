#version 430

in layout(location=0) vec4 vertexPositionModel;    // in is for varying data
in layout(location=1) vec3 vertexColor;
in layout(location=2) vec3 normalModel; // Use this to send over data via instance data
//in layout(location=2) mat4 fullTransformMatrix; // Use this to send over data via instance data

//uniform vec3 dominatingColor; // the uniform keyword is for data that does not change, or is uniform
//uniform float yFlip;

uniform mat4 modelToProjectionMatrix; // MVP, Use this to send over data via a uniform
uniform mat4 modelToWorldMatrix;

out vec3 theColor;
out vec3 normalWorld;
out vec3 vertexPositionWorld;

void main()
{
    //gl_Position = vec4(position, 1.0);

    //vec4 v = vec4(vertexPositionModel, 1.0);
    //vec4 newPosition = modelTransformMatrix * v;
    //vec4 projectedPosition = projectionMatrix * newPosition;
    //gl_Position = projectedPosition;
    gl_Position = modelToProjectionMatrix * vertexPositionModel;

//    gl_Position.y = gl_Position.y * yFlip;

    // Diffuse lighting
//    vec3 lightVector = normalize(lightPosition - position);
//    float diffuseLight = dot(lightVector, normal);

    // Output Color
//    theColor = vec3(gl_Position);
//    theColor = position;
//    theColor = normal;
//    theColor = vec3(diffuseLight, diffuseLight, diffuseLight);  // varying data
//    theColor = vertexColor * ambientLight * diffuseLight;  // varying data
//    theColor = dominatingColor;  // uniform data
    theColor = vertexColor;  // varying data

//    theNormal = normal;
    // DO NOT TRANSLATE THE NORMAL, just rotate it.
    // Set the 4th parameter to 0 cancel out the translation value
    // If we were to scale our model, then we would have to re-normalize
    // If we did a non-uniform scale, well, there would be more to do

    normalWorld = vec3(modelToWorldMatrix * vec4(normalModel, 0));

    // Averaging the surface normals. Treat the normals as a vector from the center.
    //normalWorld = vec3(modelToWorldMatrix * normalize(vertexPositionModel));

//    thePosition = position;
    vertexPositionWorld = vec3(modelToWorldMatrix * vertexPositionModel);
}
