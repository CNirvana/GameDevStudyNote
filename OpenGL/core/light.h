#pragma once

#include "shader.h"

class Light
{
public:
	Light(const glm::vec3& lightColor, float intensity) : m_Color(lightColor), m_Intensity(intensity) {}
	virtual void writeProperties(const Shader& shader) = 0;
	virtual void writeProperties(const Shader& shader, int lightIndex) = 0;

	glm::vec3 getLightColor() const { return m_Color; }
	void setLightColor(const glm::vec3& lightColor) { m_Color = lightColor; }

	float getIntensity() const { return m_Intensity; }
	void setIntensity(float intensity) { m_Intensity = intensity; }

protected:
	glm::vec3 m_Color;
	float m_Intensity;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight(const glm::vec3& lightColor, float intensity, const glm::vec3& lightDir)
		: Light(lightColor, intensity), m_LightDir(lightDir) {}

	virtual void writeProperties(const Shader& shader) override;
	virtual void writeProperties(const Shader& shader, int lightIndex) override;

	glm::vec3 getLightDir() const { return m_LightDir; }
	void setLightDir(const glm::vec3& lightDir) { m_LightDir = lightDir; }

private:
	glm::vec3 m_LightDir;
};

class PointLight : public Light
{
public:
	PointLight(const glm::vec3& lightColor, float intensity, const glm::vec3& lightPos, float constant, float linear, float quadratic)
		: Light(lightColor, intensity), m_LightPos(lightPos), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic) {}

	virtual void writeProperties(const Shader& shader) override;
	virtual void writeProperties(const Shader& shader, int lightIndex) override;

	glm::vec3 getLightPos() const { return m_LightPos; }
	void setLightPos(const glm::vec3& lightPos) { m_LightPos = lightPos; }
	float getConstant() const { return m_Constant; }
	void setConstant(float constant) { m_Constant = constant; }
	float getLinear() const { return m_Linear; }
	void setLinear(float linear) { m_Linear = linear; }
	float getQuadratic() const { return m_Quadratic; }
	void setQuadratic(float quadratic) { m_Quadratic= quadratic; }

private:
	glm::vec3 m_LightPos;
	float m_Constant;
	float m_Linear;
	float m_Quadratic;

};

class SpotLight : public Light
{
public:
	SpotLight(const glm::vec3& lightColor, float intensity, const glm::vec3& lightPos, const glm::vec3& direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic)
		: Light(lightColor, intensity), m_LightPos(lightPos), m_Direction(direction), m_CutOff(cutOff), m_OuterCutOff(outerCutOff), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic) {}

	virtual void writeProperties(const Shader& shader) override;
	virtual void writeProperties(const Shader& shader, int lightIndex) override;

	glm::vec3 getLightPos() const { return m_LightPos; }
	void setLightPos(const glm::vec3& lightPos) { m_LightPos = lightPos; }
	glm::vec3 getDirection() const { return m_Direction; }
	void setDirection(const glm::vec3& direction) { m_Direction = direction; }

private:
	glm::vec3 m_LightPos;
	glm::vec3 m_Direction;
	float m_CutOff;
	float m_OuterCutOff;
	float m_Constant;
	float m_Linear;
	float m_Quadratic;

};