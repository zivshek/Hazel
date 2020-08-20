#pragma once

#include "pch.h"

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"
#include "Hazel/PlatformTypes.h"

namespace Hazel
{
    struct WindowProps
    {
        std::string Title;
        uint Width;
        uint Height;

        WindowProps(const std::string& title = "Hazel Engine", uint width = 1280, uint height = 720)
            : Title{ title }, Width{ width }, Height{ height }
        {
        }
    };

    class HAZEL_API Window
    {
    public:
        typedef std::function<void(Event&)> EventCallback;
        virtual ~Window() {}

        virtual void OnUpdate() = 0;
        virtual uint GetWidth() const = 0;
        virtual uint GetHeight() const = 0;
        virtual void SetEventCallback(const EventCallback&) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        virtual PlatformWindow* GetPlatformWindow() const = 0;

        static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
    };
}
