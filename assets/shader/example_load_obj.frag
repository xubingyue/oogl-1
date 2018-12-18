uniform sampler2D diffuseTexture;

varying vec2 textureCoordinate;

void main()
{
    gl_FragColor = texture2D(diffuseTexture, textureCoordinate);
}