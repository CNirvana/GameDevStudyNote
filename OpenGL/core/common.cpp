#include "common.h"

float getTime()
{
    return glfwGetTime();
}

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

GLenum toGLTextureWrapMode(TextureWrapMode wrapMode)
{
    switch (wrapMode)
    {
    case TextureWrapMode::Repeat:
        return GL_REPEAT;
    case TextureWrapMode::Clamp:
    default:
        return GL_CLAMP_TO_EDGE;
    }
}

GLenum toGLTextureFilterMode(TextureFilterMode filterMode)
{
    switch (filterMode)
    {
    case TextureFilterMode::Nearest:
        return GL_NEAREST;
    case TextureFilterMode::Trilinear:
        return GL_LINEAR_MIPMAP_LINEAR;
    case TextureFilterMode::Bilinear:
    default:
        return GL_LINEAR;
    }
}

GLenum toGLDepthFunc(DepthTestFunc func)
{
    switch (func)
    {
    case DepthTestFunc::Never:
        return GL_NEVER;
    case DepthTestFunc::Less:
        return GL_LESS;
    case DepthTestFunc::Equal:
        return GL_EQUAL;
    case DepthTestFunc::LessEqual:
        return GL_LEQUAL;
    case DepthTestFunc::Greater:
        return GL_GREATER;
    case DepthTestFunc::NotEqual:
        return GL_NOTEQUAL;
    case DepthTestFunc::GreaterEqual:
        return GL_GEQUAL;
    case DepthTestFunc::Always:
        return GL_ALWAYS;
    default:
        return GL_LESS;
    }
}

GLenum toGLStencilFunc(StencilFunc func)
{
    switch (func)
    {
    case StencilFunc::Never:
        return GL_NEVER;
    case StencilFunc::Less:
        return GL_LESS;
    case StencilFunc::Equal:
        return GL_EQUAL;
    case StencilFunc::LessEqual:
        return GL_LEQUAL;
    case StencilFunc::Greater:
        return GL_GREATER;
    case StencilFunc::NotEqual:
        return GL_NOTEQUAL;
    case StencilFunc::GreaterEqual:
        return GL_GEQUAL;
    case StencilFunc::Always:
        return GL_ALWAYS;
    default:
        return GL_LESS;
    }
}

GLenum toGLStencilOp(StencilOp op)
{
    switch (op)
    {
    case StencilOp::Keep:
        return GL_KEEP;
    case StencilOp::Zero:
        return GL_ZERO;
    case StencilOp::Replace:
        return GL_REPLACE;
    case StencilOp::Increament:
        return GL_INCR;
    case StencilOp::IncreamentWrap:
        return GL_INCR_WRAP;
    case StencilOp::Decrement:
        return GL_DECR;
    case StencilOp::DecrementWrap:
        return GL_DECR_WRAP;
    case StencilOp::Invert:
        return GL_INVERT;
    default:
        return GL_KEEP;
    }
}

GLenum toGLBlendFunc(BlendFunc func)
{
    switch (func)
    {
    case BlendFunc::Zero:
        return GL_ZERO;
    case BlendFunc::One:
        return GL_ONE;
    case BlendFunc::SrcColor:
        return GL_SRC_COLOR;
    case BlendFunc::OneMinusSrcColor:
        return GL_ONE_MINUS_SRC_COLOR;
    case BlendFunc::DstColor:
        return GL_DST_COLOR;
    case BlendFunc::OneMinusDstColor:
        return GL_ONE_MINUS_DST_COLOR;
    case BlendFunc::SrcAlpha:
        return GL_SRC_ALPHA;
    case BlendFunc::OneMinusSrcAlpha:
        return GL_ONE_MINUS_SRC_ALPHA;
    case BlendFunc::DstAlpha:
        return GL_DST_ALPHA;
    case BlendFunc::OneMinusDstAlpha:
        return GL_ONE_MINUS_DST_ALPHA;
    case BlendFunc::ConstantColor:
        return GL_CONSTANT_COLOR;
    case BlendFunc::OneMinusConstantColor:
        return GL_ONE_MINUS_CONSTANT_COLOR;
    case BlendFunc::ConstantAlpha:
        return GL_CONSTANT_ALPHA;
    case BlendFunc::OneMinusConstantAlpha:
        return GL_ONE_MINUS_CONSTANT_ALPHA;
    default:
        return GL_SRC_ALPHA;
    }
}

GLenum toGLBlendEquation(BlendEquation mode)
{
    switch (mode)
    {
    case BlendEquation::Add:
        return GL_FUNC_ADD;
    case BlendEquation::Subtract:
        return GL_FUNC_SUBTRACT;
    case BlendEquation::ReverseSubtract:
        return GL_FUNC_REVERSE_SUBTRACT;
    default:
        return GL_FUNC_ADD;
    }
}

GLenum toGLCullFace(CullFace mode)
{
    switch (mode)
    {
    case CullFace::Front:
        return GL_FRONT;
    case CullFace::Back:
        return GL_BACK;
    case CullFace::FrontAndBack:
        return GL_FRONT_AND_BACK;
    default:
        return GL_BACK;
    }
}

GLenum toGLFrontFace(FrontFace mode)
{
    switch (mode)
    {
    case FrontFace::CW:
        return GL_CW;
    case FrontFace::CCW:
        return GL_CCW;
    default:
        return GL_CCW;
    }
}