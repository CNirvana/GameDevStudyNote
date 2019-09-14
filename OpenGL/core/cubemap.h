#pragma once

#include "common.h"
#include "iglresource.h"

class Cubemap : public IGLResource
{
public:
    Cubemap(const std::vector<std::string>& rltbfb);

    void bind(unsigned int slot) const
    {
        GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
        GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID));
    }

    void draw() const
    {
        GL_CALL(glBindVertexArray(m_VAO));
        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
        GL_CALL(glBindVertexArray(0));
    }

    virtual void release() override;

protected:
    unsigned int loadCubemap(const std::vector<std::string>& rltbfb);

private:
    unsigned int m_TextureID;
    unsigned int m_VAO;
    unsigned int m_VBO;
};