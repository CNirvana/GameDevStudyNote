#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "framebuffer.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "cubemap.h"
#include "cube.h"
#include "quad.h"
#include "model.h"
#include "renderer.h"
#include "transparent_object.h"

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

float deltaTime;
float lastFrame;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2;
float lastY = SCREEN_HEIGHT / 2;
bool firstMouse = true;

#pragma region Callbacks

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	camera.processMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.processMouseScroll(yOffset);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.processKeyboard(RIGHT, deltaTime);

	static bool enableMSAA = true;
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		enableMSAA = !enableMSAA;
		if (enableMSAA) glEnable(GL_MULTISAMPLE);
		else glDisable(GL_MULTISAMPLE);
	}
}

#pragma endregion

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 4); // Allow MSAA

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Renderer renderer;

	Shader* shader = Resources::loadShaderFromFile("default", "../resources/shaders/vert.vert", "../resources/shaders/frag.frag");
	Shader* lightShader = Resources::loadShaderFromFile("light", "../resources/shaders/light.vert", "../resources/shaders/light.frag");
	Shader* modelShader = Resources::loadShaderFromFile("model", "../resources/shaders/model.vert", "../resources/shaders/model.frag");
	Shader* reflectionShader = Resources::loadShaderFromFile("reflection", "../resources/shaders/reflection.vert", "../resources/shaders/reflection.frag");
	Shader* refractionShader = Resources::loadShaderFromFile("refraction", "../resources/shaders/refraction.vert", "../resources/shaders/refraction.frag");
	Shader* shownormalShader = Resources::loadShaderFromFile("shownormal",
		"../resources/shaders/geometry/shownormal.vert",
		"../resources/shaders/geometry/shownormal.frag",
		"../resources/shaders/geometry/shownormal.geom");

	TextureProperty textureProperty = { TextureType::Diffuse, TextureWrapMode::Clamp, TextureFilterMode::Bilinear, true };
	Texture* diffuseTex = Resources::loadTexture("../resources/textures/container2.png", textureProperty);
	textureProperty.type = TextureType::Specular;
	Texture* specularTex = Resources::loadTexture("../resources/textures/container2_specular.png", textureProperty);

	Cube reflectiveCube(Resources::getShader("reflection"));
	Cube refractiveCube(Resources::getShader("refraction"));
	TransparentObject trans1(Resources::getShader("default"),
		Resources::loadTexture("../resources/textures/grass.png", { TextureType::Diffuse, TextureWrapMode::Clamp, TextureFilterMode::Bilinear, true }));
	TransparentObject trans2(Resources::getShader("default"),
		Resources::loadTexture("../resources/textures/window.png", { TextureType::Diffuse, TextureWrapMode::Clamp, TextureFilterMode::Bilinear, true }));

	Model nanosuit("../resources/models/nanosuit/nanosuit.obj", Resources::getShader("model"));
	Model planet("../resources/models/planet/planet.obj", Resources::getShader("model"));

	Mesh plane(Resources::getShader("model"), std::vector<Vertex>
	{
		{ glm::vec3(-0.5, 0, 0.5), glm::vec3(0, 1, 0), glm::vec2(0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
		{ glm::vec3(0.5, 0, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
		{ glm::vec3(0.5, 0, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
		{ glm::vec3(-0.5, 0, -0.5), glm::vec3(0, 1, 0), glm::vec2(0, 1), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) }
	}, std::vector<unsigned int>{0, 1, 2, 0, 2, 3}, std::vector<Texture*>{ diffuseTex });

	Cubemap* skybox = new Cubemap(std::vector<std::string>{
		"../resources/skybox/right.jpg",
		"../resources/skybox/left.jpg",
		"../resources/skybox/top.jpg",
		"../resources/skybox/bottom.jpg",
		"../resources/skybox/front.jpg",
		"../resources/skybox/back.jpg"
	});
	renderer.setSkybox(skybox);

	FrameBuffer frameBuffer(SCREEN_WIDTH, SCREEN_HEIGHT);
	Shader* frameBufferShader = Resources::loadShaderFromFile("framebuffer", "../resources/shaders/posteffect/framebuffer.vert", "../resources/shaders/posteffect/gaussian_blur.frag");

	DirectionalLight dirLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(-1.0f, -1.0f, -1.0f));
	PointLight pointLights[] =
	{
		PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, glm::vec3(0.7f, 0.2f, 2.0f), 1.0f, 0.09f, 0.032f),
		PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, glm::vec3(2.3f, -3.3f, -4.0f), 1.0f, 0.09f, 0.032f),
		PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, glm::vec3(-4.0f, 2.0f, -12.0f), 1.0f, 0.09f, 0.032f),
		PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.8f, glm::vec3(0.0f, 0.0f, -3.0f), 1.0f, 0.09f, 0.032f)
	};
	SpotLight spotLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), 1.0f, 0.09f, 0.032f);

	renderer.enableDepthTest(true);

	renderer.enableBlend(true);
	renderer.setBlendFunc(BlendFunc::SrcAlpha, BlendFunc::OneMinusSrcAlpha);

	renderer.enableCulling(true);
	renderer.setClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		process_input(window);

		// bind framebuffer
		// renderer.bindFrameBuffer(frameBuffer);

		renderer.clear();

		glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		renderer.setProjectionMatrix(projection);
		renderer.setViewMatrix(view);
		renderer.setCameraPos(camera.getPosition());

		// 1.draw opaque objects
		/*lightShader->bind();
		lightShader->setInt("material.diffuse", 0);
		diffuseTex.bind(0);
		lightShader->setInt("material.specular", 1);
		specularTex.bind(1);
		lightShader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		lightShader->setFloat("material.shininess", 32);

		lightShader->setVec3("ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		dirLight.writeProperties(*lightShader);
		for (int i = 0; i < 4; i++)
		{
			pointLights[i].writeProperties(*lightShader, i);
		}
		spotLight.setLightPos(camera.getPosition());
		spotLight.setDirection(camera.getFront());
		spotLight.writeProperties(*lightShader);

		lightShader->setVec3("cameraPos", camera.getPosition());
		lightShader->setMat4("worldToObj", glm::transpose(glm::inverse(model)));
		lightShader->setMat4("mvp", projection * view * model);*/

		reflectiveCube.position = glm::vec3(5, 5, 0);
		renderer.draw(reflectiveCube);
		refractiveCube.position = glm::vec3(5, 7, 0);
		renderer.draw(refractiveCube);

		nanosuit.position = glm::vec3(1, 0, 0);
		nanosuit.scale = glm::vec3(0.1, 0.1, 0.1);
		renderer.draw(nanosuit);

		planet.position = glm::vec3(0, 0, -20);
		renderer.draw(planet);

		plane.position = glm::vec3(0, -1, 0);
		plane.scale = glm::vec3(100, 1, 100);
		renderer.draw(plane);

		// 2.draw skybox
		renderer.drawSkybox();

		// 3.draw transparent objects
		// need sorting
		trans1.position = glm::vec3(-3.0f, 0.0f, 0.0f);
		renderer.draw(trans1);
		trans2.position = glm::vec3(0.0f, 0.0f, 0.0f);
		renderer.draw(trans2);

		// draw framebuffer
		// renderer.drawFrameBuffer(frameBuffer, frameBufferShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}