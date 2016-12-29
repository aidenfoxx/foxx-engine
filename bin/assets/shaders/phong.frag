#version 330 core

const vec3 lightPosition = vec3(4.0, 4.0, 4.0);
const vec3 diffuseColor = vec3(0.9, 0.5, 1.0);
const vec3 ambientColor = vec3(0.1, 0.1, 0.1);
const vec3 specularColor = vec3(0.2, 0.2, 0.2);

uniform sampler2D diffuseTexture;

in vec2 uv;
in vec3 vertexPosition;
in vec3 normalInterp;

out vec4 gl_FragColor;

void main()
{
    vec3 diffuse = diffuseColor;
    vec3 normal = normalize(normalInterp);
    vec3 lightDirection = normalize(lightPosition - vertexPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    vec3 viewDirection = normalize(-vertexPosition);

    float lambertian = max(dot(lightDirection, normal), 0.0);
    float specular = 0.0;

    if (lambertian > 0.0)
    {
       float specularAngle = max(dot(reflectDirection, viewDirection), 0.0);
       specular = pow(specularAngle, 4.0);
    }

    if (textureSize(diffuseTexture, 1).x > 0)
    {
        diffuse = texture(diffuseTexture, uv).rgb;
    }

    gl_FragColor = vec4(ambientColor + lambertian * diffuse + specular * specularColor, 1.0);
}