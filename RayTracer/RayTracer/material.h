#pragma once

#include "shader.h"
#include "utility.h"

class Material
{
public:
	Material(Shader* shader) : m_Shader(shader) {}
	virtual ~Material() { SAFE_DELETE(m_Shader); }

	Color sample(const FragInput& input) { return m_Shader->fragment(input); }

protected:
	Shader* m_Shader;

};