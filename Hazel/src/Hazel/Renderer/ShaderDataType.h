#pragma once
#include "Hazel/Core/Core.h"

namespace Hazel
{
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    struct ShaderDataTypeData
    {
        uint Size = 0;
        uint Count = 0;

        ShaderDataTypeData() {}

        ShaderDataTypeData(uint size, uint count)
            : Size(size), Count(count) {}
    };

    extern std::unordered_map<ShaderDataType, ShaderDataTypeData> g_ShaderDataTypeMap;
#define ShaderDataTypeSize(type) g_ShaderDataTypeMap[type].Size
#define ShaderDataTypeCount(type) g_ShaderDataTypeMap[type].Count
}