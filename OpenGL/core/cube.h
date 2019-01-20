#pragma once

#include "common.h"
#include "renderer.h"

class Cube : public IDrawable, public IGLResource
{
public:
	Cube(Shader* shader);

	virtual void drawWithShader(const Renderer& renderer, Shader* shader) override
	{
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_ElementCount);
		//glDrawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_INT, 0);
	}

	virtual void release() override;

private:
	unsigned int m_VBO;
	unsigned int m_VAO;
	//unsigned int m_IBO;
	unsigned int m_ElementCount;

};