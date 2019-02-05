#include "light.h"

void DirectionalLight::writeProperties(const Shader& shader)
{
	shader.setVec3("dirLight.lightColor", m_Color * m_Intensity);
	shader.setVec3("dirLight.lightDir", m_LightDir);
}

void DirectionalLight::writeProperties(const Shader& shader, int lightIndex)
{
	shader.setVec3("dirLights[" + std::to_string(lightIndex) + "].lightColor", m_Color * m_Intensity);
	shader.setVec3("dirLights[" + std::to_string(lightIndex) + "].lightDir", m_LightDir);
}

void PointLight::writeProperties(const Shader& shader)
{
	shader.setVec3("pointLight.lightColor", m_Color * m_Intensity);
	shader.setVec3("pointLight.lightPos", m_LightPos);
	shader.setFloat("pointLight.constant", m_Constant);
	shader.setFloat("pointLight.linear", m_Linear);
	shader.setFloat("pointLight.quadratic", m_Quadratic);
}

void PointLight::writeProperties(const Shader& shader, int lightIndex)
{
	std::string index = std::to_string(lightIndex);
	shader.setVec3("pointLights[" + index + "].lightColor", m_Color * m_Intensity);
	shader.setVec3("pointLights[" + index + "].lightPos", m_LightPos);
	shader.setFloat("pointLights[" + index + "].constant", m_Constant);
	shader.setFloat("pointLights[" + index + "].linear", m_Linear);
	shader.setFloat("pointLights[" + index + "].quadratic", m_Quadratic);
}

void SpotLight::writeProperties(const Shader& shader)
{
	shader.setVec3("spotLight.lightColor", m_Color * m_Intensity);
	shader.setVec3("spotLight.lightPos", m_LightPos);
	shader.setVec3("spotLight.direction", m_Direction);
	shader.setFloat("spotLight.cutOff", m_CutOff);
	shader.setFloat("spotLight.outerCutOff", m_OuterCutOff);
	shader.setFloat("spotLight.constant", m_Constant);
	shader.setFloat("spotLight.linear", m_Linear);
	shader.setFloat("spotLight.quadratic", m_Quadratic);
}

void SpotLight::writeProperties(const Shader& shader, int lightIndex)
{
	std::string index = std::to_string(lightIndex);
	shader.setVec3("spotLights[" + index + "].lightColor", m_Color * m_Intensity);
	shader.setVec3("spotLights[" + index + "].lightPos", m_LightPos);
	shader.setVec3("spotLights[" + index + "].direction", m_Direction);
	shader.setFloat("spotLights[" + index + "].cutOff", m_CutOff);
	shader.setFloat("spotLights[" + index + "].outerCutOff", m_OuterCutOff);
	shader.setFloat("spotLights[" + index + "].constant", m_Constant);
	shader.setFloat("spotLights[" + index + "].linear", m_Linear);
	shader.setFloat("spotLights[" + index + "].quadratic", m_Quadratic);
}