#include "renderer.h"

const char* skyboxVertSource =
"#version 450 core\n"
"layout(location = 0) in vec3 n_Position;\n"
"out vec3 v_texCoord;\n"
"uniform mat4 u_mvp;\n"
"void main()\n"
"{\n"
"	vec4 pos = u_mvp * vec4(n_Position, 1.0);\n"
"	gl_Position = pos.xyww;\n"
"	v_texCoord = n_Position;\n"
"}";

const char* skyboxFragSource =
"#version 450 core\n"
"in vec3 v_texCoord;\n"
"uniform samplerCube u_skybox;\n"
"void main()\n"
"{\n"
"	gl_FragColor = texture(u_skybox, v_texCoord);\n"
"}";

const char* depthMapVertSource =
"#version 450 core\n"
"layout (location = 0) in vec3 n_Position;\n"
"uniform mat4 u_lightSpaceMatrix;\n"
"uniform mat4 u_model;\n"
"void main()\n"
"{\n"
"	gl_Position = u_lightSpaceMatrix * u_model * vec4(n_Position, 1.0);"
"}\n";

const char* depthMapFragSource =
"#version 450 core\n"
"void main()"
"{\n"
"	// gl_FragColor = gl_FragCoord.z;\n"
"}\n";

Renderer::Renderer() : m_Skybox(nullptr), m_OffscreenQuad(nullptr)
{
}

Renderer::~Renderer()
{
	m_DepthMap->release();
	SAFE_DELETE(m_DepthMap);
    SAFE_RELEASE(m_OffscreenQuad);
	SAFE_RELEASE(m_Skybox);
}

void Renderer::setup()
{
    m_SkyboxShader = Resources::loadShaderFromSource("skybox", skyboxVertSource, skyboxFragSource);
    m_SkyboxShader->bind();
    m_SkyboxShader->setInt("u_skybox", 0);
    m_SkyboxShader->unbind();

    m_DepthMap = new DepthMap();

    m_OffscreenQuad = new Quad();
}

void Renderer::draw(IDrawable& drawable) const
{
	auto shader = drawable.getShader();
	drawWithShader(drawable, const_cast<Shader*>(shader));
}

void Renderer::drawWithShader(IDrawable& drawable, Shader* shader) const
{
	shader->bind();
	glm::mat4 modelMatrix = drawable.getModelMatrix();
	shader->setMat4("u_projection", m_ProjectionMatrix);
	shader->setMat4("u_view", m_ViewMatrix);
	shader->setMat4("u_model", modelMatrix);
	shader->setMat4("u_mvp", m_ProjectionMatrix * m_ViewMatrix * modelMatrix);
	shader->setMat4("u_worldToObj", glm::transpose(glm::inverse(modelMatrix)));
	shader->setVec3("u_cameraPos", m_CameraPos);
	if (m_Skybox != nullptr)
	{
		shader->setInt("u_skybox", 16);
		m_Skybox->bind(16);
	}
	drawable.draw(*this);
	shader->unbind();
}

void Renderer::drawSkybox() const
{
	if (m_Skybox != nullptr)
	{
		glDepthFunc(GL_LEQUAL);
		m_SkyboxShader->bind();
		glm::mat4 view = glm::mat4(glm::mat3(m_ViewMatrix));
		m_SkyboxShader->setMat4("u_mvp", m_ProjectionMatrix * view);
		m_Skybox->bind(0);
		m_Skybox->draw();
		glDepthFunc(GL_LESS);
	}
}

void Renderer::bindFrameBuffer(const FrameBuffer& frameBuffer) const
{
	frameBuffer.bind();
	enableDepthTest(true);
}

void Renderer::drawFrameBuffer(const FrameBuffer& frameBuffer, Shader* shader) const
{
	frameBuffer.unbind();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	shader->bind();
	shader->setInt("u_screenTex", 0);
	shader->setVec4("u_screenTex_texelSize", glm::vec4(1.0f / frameBuffer.getWidth(), 1.0f / frameBuffer.getHeight(), frameBuffer.getWidth(), frameBuffer.getHeight()));
	shader->setFloat("u_time", getTime());
	frameBuffer.bindColorBuffer();
	m_OffscreenQuad->draw();
}

void Renderer::clear(bool color, bool depth, bool stencil) const
{
	GLbitfield mask = 0;
	if (color) mask |= GL_COLOR_BUFFER_BIT;
	if (depth) mask |= GL_DEPTH_BUFFER_BIT;
	if (stencil) mask |= GL_STENCIL_BUFFER_BIT;
	glClear(mask);
}

void Renderer::enableDepthTest(bool enable) const
{
	if (enable)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

void Renderer::setDepthWrite(bool write) const
{
	glDepthMask(write ? GL_TRUE : GL_FALSE);
}

void Renderer::setDepthFunc(DepthTestFunc func) const
{

}

void Renderer::enableStencilTest(bool enable) const
{
	if (enable)
	{
		glEnable(GL_STENCIL_TEST);
	}
	else
	{
		glDisable(GL_STENCIL_TEST);
	}
}

void Renderer::setStencilMask(unsigned int mask) const
{
	glStencilMask(mask);
}

void Renderer::setStencilFunc(StencilFunc func, int ref, unsigned int mask) const
{
	glStencilFunc(toGLStencilFunc(func), ref, mask);
}

void Renderer::setStencilOp(StencilOp stencilFail, StencilOp depthFail, StencilOp depthPass) const
{
	glStencilOp(toGLStencilOp(stencilFail), toGLStencilOp(depthFail), toGLStencilOp(depthPass));
}

void Renderer::enableBlend(bool enable) const
{
	if (enable)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void Renderer::setBlendFunc(BlendFunc srcFactor, BlendFunc dstFactor) const
{
	glBlendFunc(toGLBlendFunc(srcFactor), toGLBlendFunc(dstFactor));
}

void Renderer::setBlendEquation(BlendEquation mode) const
{
	glBlendEquation(toGLBlendEquation(mode));
}

void Renderer::enableCulling(bool enable) const
{
	if (enable)
	{
		glEnable(GL_CULL_FACE);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
}

void Renderer::setCullFace(CullFace mode) const
{
	glCullFace(toGLCullFace(mode));
}

void Renderer::setFontFace(FrontFace mode) const
{
	glFrontFace(toGLFrontFace(mode));
}

void Renderer::enablePolygonMode(bool enable) const
{
	glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
}

void Renderer::enableMSAA(bool enable) const
{
	if (enable)
	{
		glEnable(GL_MULTISAMPLE);
	}
	else
	{
		glDisable(GL_MULTISAMPLE);
	}
}