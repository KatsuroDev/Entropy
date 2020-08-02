#pragma once

#include "../../Entropy/Renderer/Texture.h"

#include <GL/glew.h>

namespace Entropy {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(unsigned int width, unsigned int height);
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }
		virtual unsigned int GetRendererID() const override { return m_RendererID; }

		virtual void SetData(void* data, unsigned int size) override;

		virtual void Attach(unsigned int textureSlot = 0) const override;
		// Detaches automatically after render

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		std::string m_Filepath;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}
