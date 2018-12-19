#pragma once

#include "utility.h"
#include "iglresource.h"

class Quad : IGLResource
{
public:
	Quad();

	void draw() const
	{
		GL_CALL(glBindVertexArray(m_VAO));
		GL_CALL(glDrawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_INT, 0));
	}

	virtual void release() override
	{
		GL_CALL(glDeleteVertexArrays(1, &m_VAO));
		GL_CALL(glDeleteBuffers(1, &m_VBO));
		GL_CALL(glDeleteBuffers(1, &m_IBO));
	}

private:
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_IBO;
	unsigned int m_ElementCount;

};