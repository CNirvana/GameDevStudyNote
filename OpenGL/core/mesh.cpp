#include "mesh.h"

Mesh::Mesh(Shader* shader, const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<Texture*>& _textures)
	: IDrawable(shader), vertices(_vertices), indices(_indices), textures(_textures)
{
	setupMesh();
}

void Mesh::release()
{
	/*GL_CALL(glDeleteVertexArrays(1, &m_VAO));
	GL_CALL(glDeleteBuffers(1, &m_VBO));
	GL_CALL(glDeleteBuffers(1, &m_IBO));*/
}

void Mesh::setupMesh()
{
	GL_CALL(glGenVertexArrays(1, &m_VAO));
	GL_CALL(glGenBuffers(1, &m_VBO));
	GL_CALL(glGenBuffers(1, &m_IBO));
	GL_CALL(glBindVertexArray(m_VAO));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));

	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));

	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
	GL_CALL(glEnableVertexAttribArray(0));

	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
	GL_CALL(glEnableVertexAttribArray(1));

	GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord)));
	GL_CALL(glEnableVertexAttribArray(2));

	GL_CALL(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent)));
	GL_CALL(glEnableVertexAttribArray(3));

	GL_CALL(glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent)));
	GL_CALL(glEnableVertexAttribArray(4));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	GL_CALL(glBindVertexArray(0));
}

void Mesh::bindTextures(Shader* shader) const
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (size_t i = 0; i < textures.size(); i++)
	{
		std::string name;
		if (textures[i]->getTextureType() == TextureType::Diffuse)
			name = "u_texture_diffuse" + std::to_string(diffuseNr++);
		else if (textures[i]->getTextureType() == TextureType::Specular)
			name = "u_texture_specular" + std::to_string(specularNr++);
		else if (textures[i]->getTextureType() == TextureType::Normal)
			name = "u_texture_normal" + std::to_string(normalNr++);
		else if (textures[i]->getTextureType() == TextureType::Height)
			name = "u_texture_height" + std::to_string(heightNr++);

		shader->setInt(name, i);
		textures[i]->bind(i);
	}
}

void Mesh::draw(const Renderer& renderer)
{
	drawWithShader(renderer, m_Shader);
}

void Mesh::drawWithShader(const Renderer& renderer, Shader* shader)
{
	bindTextures(shader);
	GL_CALL(glBindVertexArray(m_VAO));
	GL_CALL(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	GL_CALL(glBindVertexArray(0));

	unbindTextures();
}

void Mesh::drawInstanced(const Shader& shader, int amount) const
{
	bindTextures(m_Shader);

	GL_CALL(glBindVertexArray(m_VAO));
	GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, amount));
	GL_CALL(glBindVertexArray(0));

	unbindTextures();
}