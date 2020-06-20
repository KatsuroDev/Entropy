#include "Renderer.h"

#include "../Core/Logger.h"

namespace Entropy {

    RenderingAPI* Renderer::s_RenderingAPI = nullptr;

    void Renderer::Init()
    {
        s_RenderingAPI = RenderingAPI::Create();
        // Calling these before Getting the Graphics API would result in a
        // segmentation fault!
        // We do NOT need to test if RenderingAPI::Get() returns nullptr.
        // It's done internally and asserts the program if necessary
        s_RenderingAPI->Init();

        Logger::Info("Initialized renderer successfully!");
    }

    void Renderer::Dispose()
    {
        // Clearing ressources
        delete s_RenderingAPI;

        Logger::Info("Disposed of renderer ressources");
    }

    void Renderer::SetClearColor(const Vector4f& rgba)
    {
        s_RenderingAPI->SetClearColor(rgba);
        std::stringstream ss;
        ss << "RENDERER: Changed clear color to (" << rgba.X << ", " << rgba.Y << ", " << rgba.Z << ", " << rgba.W << ")";
        Logger::Info(ss.str());
    }

    void Renderer::Clear()
    {
        s_RenderingAPI->Clear();
        Logger::Info("RENDERER: Cleared");
    }

    void Renderer::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        s_RenderingAPI->SetViewport(x, y, width, height);
    }

    void Renderer::Draw(const VertexArray& vertexArray, unsigned int count)
    {
        s_RenderingAPI->Draw(vertexArray, count);
        Logger::Info("RENDERER: Drawn");
    }

    void Renderer::AttachData(/* shader */ const VertexArray& vertexArray, const Matrix4f& transform)
    {
        // TODO: Attach shaders
        // set uniform the transformation matrix to the shader
        // set uniform the projection matrix to the shader

        vertexArray.Attach();
        // Draw the vertex array
        Logger::Info("RENDERER: Attached data");
    }

    void Renderer::OnWindowResize(unsigned int width, unsigned int height)
    {
        SetViewport(0, 0, width, height);
    }
}
