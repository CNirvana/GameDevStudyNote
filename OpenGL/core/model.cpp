#include "model.h"

Model::Model(const std::string& path, Shader* shader) : IDrawable(shader)
{
    loadModel(path);
}

Model::~Model()
{
    for (size_t i = 0; i < m_Meshes.size(); i++)
    {
        SAFE_DELETE(m_Meshes[i]);
    }
}

void Model::drawWithShader(const Renderer& renderer, Shader* shader)
{
    for (size_t i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes[i]->drawWithShader(renderer, shader);
    }
}

void Model::drawInstanced(const Shader& shader, int amount) const
{
    for (size_t i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes[i]->drawInstanced(shader, amount);
    }
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    m_ModelDirectory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

    // Vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        // Position
        glm::vec3 v;
        v.x = mesh->mVertices[i].x;
        v.y = mesh->mVertices[i].y;
        v.z = mesh->mVertices[i].z;
        vertex.position = v;

        // Normal
        v.x = mesh->mNormals[i].x;
        v.y = mesh->mNormals[i].y;
        v.z = mesh->mNormals[i].z;
        vertex.normal = v;

        // TexCoord
        if (mesh->mTextureCoords[0] != nullptr)
        {
            vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        else
        {
            vertex.texCoord = glm::vec2(0.0f, 0.0f);
        }

        // Tangent
        v.x = mesh->mTangents[i].x;
        v.y = mesh->mTangents[i].y;
        v.z = mesh->mTangents[i].z;
        vertex.tangent = v;

        // Bitangent
        v.x = mesh->mBitangents[i].x;
        v.y = mesh->mBitangents[i].y;
        v.z = mesh->mBitangents[i].z;
        vertex.bitangent = v;

        vertices.push_back(vertex);
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Materials
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Diffuse
        std::vector<Texture*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Specular
        std::vector<Texture*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // Normal
        std::vector<Texture*> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        // Height
        std::vector<Texture*> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }

    return new Mesh(m_Shader, vertices, indices, textures);
}

std::vector<Texture*> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
    std::vector<Texture*> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        std::string texturePath = m_ModelDirectory + '/' + str.C_Str();
        for (size_t j = 0; j < m_Textures.size(); j++)
        {
            if (texturePath == m_Textures[i]->getPath())
            {
                textures.push_back(m_Textures[i]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            textures.push_back(new Texture(texturePath, {convertAssimpTextureType(type), TextureWrapMode::Clamp, TextureFilterMode::Bilinear, true }));
        }
    }

    return textures;
}

TextureType Model::convertAssimpTextureType(aiTextureType type)
{
    TextureType textureType = TextureType::None;
    switch (type)
    {
    case aiTextureType_NONE:
        break;
    case aiTextureType_DIFFUSE:
        textureType = TextureType::Diffuse;
        break;
    case aiTextureType_SPECULAR:
        textureType = TextureType::Specular;
        break;
    case aiTextureType_AMBIENT:
        break;
    case aiTextureType_EMISSIVE:
        break;
    case aiTextureType_HEIGHT:
        textureType = TextureType::Height;
        break;
    case aiTextureType_NORMALS:
        textureType = TextureType::Normal;
        break;
    case aiTextureType_SHININESS:
        break;
    case aiTextureType_OPACITY:
        break;
    case aiTextureType_DISPLACEMENT:
        break;
    case aiTextureType_LIGHTMAP:
        break;
    case aiTextureType_REFLECTION:
        break;
    case aiTextureType_UNKNOWN:
        break;
    case _aiTextureType_Force32Bit:
        break;
    default:
        break;
    }

    return textureType;
}