//
// Created by xiaozhuai on 2018/12/14.
//
#ifndef OOGL_OBJ_LOADER_WITH_OBJL_H
#define OOGL_OBJ_LOADER_WITH_OBJL_H

#include <map>
#include <string>
#include <oogl/oogl.h>
#include "OBJ_Loader.h"

class Mesh {
    public:
        Mesh(const std::string &modelDir, const objl::Mesh &m) : verticesCount(0), diffuseColor{0, 0, 0} {
            verticesCount = static_cast<int>(m.Vertices.size());

            GLfloat *vertexCoord = new GLfloat[verticesCount * 3];
            GLfloat *normalCoord = new GLfloat[verticesCount * 3];
            GLfloat *textureCoord = new GLfloat[verticesCount * 2];

            for (int i = 0; i < verticesCount; ++i) {
                vertexCoord[i * 3 + 0] = m.Vertices[i].Position.X;
                vertexCoord[i * 3 + 1] = m.Vertices[i].Position.Y;
                vertexCoord[i * 3 + 2] = m.Vertices[i].Position.Z;

                normalCoord[i * 3 + 0] = m.Vertices[i].Normal.X;
                normalCoord[i * 3 + 1] = m.Vertices[i].Normal.Y;
                normalCoord[i * 3 + 2] = m.Vertices[i].Normal.Z;

                textureCoord[i * 2 + 0] = m.Vertices[i].TextureCoordinate.X;
                textureCoord[i * 2 + 1] = m.Vertices[i].TextureCoordinate.Y;
            }

            positionVBO.create();
            positionVBO.setData(verticesCount * 3, vertexCoord, GL_STATIC_DRAW);

            normalVBO.create();
            normalVBO.setData(verticesCount * 3, normalCoord, GL_STATIC_DRAW);

            textureCoordinateVBO.create();
            textureCoordinateVBO.setData(verticesCount * 2, textureCoord, GL_STATIC_DRAW);

            delete[] vertexCoord;
            delete[] textureCoord;
            delete[] normalCoord;

            if (!m.MeshMaterial.map_Kd.empty())
                diffuseTexture = loadTexture(modelDir + m.MeshMaterial.map_Kd);

            diffuseColor[0] = m.MeshMaterial.Kd.X;
            diffuseColor[1] = m.MeshMaterial.Kd.Y;
            diffuseColor[2] = m.MeshMaterial.Kd.Z;
        }

    public:
        int verticesCount;
        oogl::Texture2D diffuseTexture;
        float diffuseColor[3];
        oogl::VBO positionVBO;
        oogl::VBO normalVBO;
        oogl::VBO textureCoordinateVBO;

    protected:
        static oogl::Texture2D loadTexture(const std::string &file, bool flip = true) {
            if (textureMap.find(file) == textureMap.end()) {
                oogl::Texture2D texture;
                texture.create();
                texture.bind();
                texture.loadFromFile(file, flip);
                texture.genMipmap();
                texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                texture.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
                texture.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
                texture.unbind();
                textureMap[file] = texture;
            }
            return textureMap[file];
        }

        static std::map<std::string, oogl::Texture2D> textureMap;

};

std::map<std::string, oogl::Texture2D> Mesh::textureMap;

class Model {
    public:
        Model() : meshCount(0) {}

        bool load(const std::string &path) {
            objl::Loader loader;
            loader.LoadFile(path);

            std::string modelDir = path.substr(0, path.find_last_of('/')) + "/";

            for (auto &m : loader.LoadedMeshes) {
                meshes.emplace_back(modelDir, m);
            }

            meshCount = static_cast<int>(loader.LoadedMeshes.size());
            return true;
        }

    public:
        int meshCount;
        std::vector<Mesh> meshes;
};

#endif //OOGL_OBJ_LOADER_WITH_OBJL_H
