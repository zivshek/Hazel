#include "pch.h"
#include "Application.h"

#include "Hazel/Log.h"
#include "Hazel/Events/MouseEvents.h"

namespace Hazel
{
    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        auto e = MousePressedEvent(1);
        EventDispatcher dispatcher{ e };
        dispatcher.Dispatch([](Event& e)->bool {
            HZ_CORE_TRACE(e);
            return true;
        });

        HZ_CORE_TRACE(e.GetCategory());
        HZ_CORE_TRACE(e.GetEventType());
        HZ_CORE_TRACE(e.GetName());

        while (true);
    }

}