#pragma once

namespace Entropy {

    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        void GetDimensions(int& width, int& height);

        void SetDimensions(int width, int height);

        void SetTitle(const char* title);

        bool ShouldClose();

        void SwapBuffers();

        void PollEvents();


        // New code implementation
        void* GetNativeWindow() const;
    };
}
