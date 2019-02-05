#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#define GL_CALL(x)\
	{\
		x;\
		glCheckError();\
	}

#define DECLARE_APPLICATION(name) \
	Application* CreateApplication()\
	{\
		return new name();\
	}

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
#define SAFE_RELEASE(p) { if(p) { p->release(); SAFE_DELETE(p); } }

float getTime();

enum TextureType
{
	None,
	Diffuse,
	Specular,
	Normal,
	Height
};

enum TextureWrapMode
{
	Clamp,
	Repeat
};
GLenum toGLTextureWrapMode(TextureWrapMode wrapMode);

enum TextureFilterMode
{
	Nearest,
	Bilinear,
	Trilinear,
};
GLenum toGLTextureFilterMode(TextureFilterMode filterMode);

enum class DepthTestFunc
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always
};
GLenum toGLDepthFunc(DepthTestFunc func);

enum class StencilFunc
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always
};
GLenum toGLStencilFunc(StencilFunc func);

enum class StencilOp
{
	Keep,
	Zero,
	Replace,
	Increament,
	IncreamentWrap,
	Decrement,
	DecrementWrap,
	Invert
};
GLenum toGLStencilOp(StencilOp op);

enum class BlendFunc
{
	Zero,
	One,
	SrcColor,
	OneMinusSrcColor,
	DstColor,
	OneMinusDstColor,
	SrcAlpha,
	OneMinusSrcAlpha,
	DstAlpha,
	OneMinusDstAlpha,
	ConstantColor,
	OneMinusConstantColor,
	ConstantAlpha,
	OneMinusConstantAlpha
};
GLenum toGLBlendFunc(BlendFunc func);

enum class BlendEquation
{
	Add,
	Subtract,
	ReverseSubtract
};
GLenum toGLBlendEquation(BlendEquation mode);

enum class CullFace
{
	Front,
	Back,
	FrontAndBack
};
GLenum toGLCullFace(CullFace mode);

enum class FrontFace
{
	CW,
	CCW
};
GLenum toGLFrontFace(FrontFace mode);