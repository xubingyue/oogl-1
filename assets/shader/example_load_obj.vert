attribute vec3 position;
attribute vec2 inputTextureCoordinate;

varying vec2 textureCoordinate;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    textureCoordinate = inputTextureCoordinate;
    gl_Position = projection * view * model * vec4(position, 1.0);
}