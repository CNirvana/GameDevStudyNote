#pragma once

class Renderer;
class IDrawable
{
public:
	IDrawable(Shader* shader) : m_Shader(shader) {}

	virtual void draw(const Renderer& renderer) { drawWithShader(renderer, m_Shader); }
	virtual void drawWithShader(const Renderer& renderer, Shader* shader) = 0;
	const Shader* getShader() const { return m_Shader; }
	glm::mat4 getModelMatrix()
	{
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::rotate(modelMatrix, angle, axis);
		modelMatrix = glm::scale(modelMatrix, scale);
		return modelMatrix;
	}

	glm::vec3 position = glm::vec3(0.0f);
	float angle = 0.0f;
	glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

protected:
	Shader* m_Shader;

private:
	IDrawable();

};