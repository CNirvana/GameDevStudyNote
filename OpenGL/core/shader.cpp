#include "shader.h"

void Shader::loadFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// if geometry shader path is present, also load a geometry shader
		if (geometryPath != nullptr)
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = nullptr;
	if (geometryPath != nullptr)
	{
		gShaderCode = geometryCode.c_str();
	}

	loadFromSource(vShaderCode, fShaderCode, gShaderCode);
}

void Shader::loadFromSource(const char* vSource, const char* fSource, const char* gSource)
{
	unsigned int vertex, fragment;

	GL_CALL(vertex = glCreateShader(GL_VERTEX_SHADER));
	GL_CALL(glShaderSource(vertex, 1, &vSource, NULL));
	GL_CALL(glCompileShader(vertex));
	checkCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	GL_CALL(glShaderSource(fragment, 1, &fSource, NULL));
	GL_CALL(glCompileShader(fragment));
	checkCompileErrors(fragment, "FRAGMENT");

	unsigned int geometry;
	if (gSource != nullptr)
	{
		GL_CALL(geometry = glCreateShader(GL_GEOMETRY_SHADER));
		GL_CALL(glShaderSource(geometry, 1, &gSource, NULL));
		GL_CALL(glCompileShader(geometry));
		checkCompileErrors(geometry, "GEOMETRY");
	}

	GL_CALL(m_ID = glCreateProgram());
	GL_CALL(glAttachShader(m_ID, vertex));
	GL_CALL(glAttachShader(m_ID, fragment));
	if (gSource != nullptr)
	{
		GL_CALL(glAttachShader(m_ID, geometry));
	}
	GL_CALL(glLinkProgram(m_ID));
	checkCompileErrors(m_ID, "PROGRAM");

	GL_CALL(glDeleteShader(vertex));
	GL_CALL(glDeleteShader(fragment));
	if (gSource != nullptr)
	{
		GL_CALL(glDeleteShader(geometry));
	}
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}