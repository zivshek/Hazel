#include "pch.h"
#include "ShaderDataType.h"

namespace Hazel
{
    std::unordered_map<ShaderDataType, ShaderDataTypeData> g_ShaderDataTypeMap
    {
        { ShaderDataType::Bool,   {1        , 1    } },
        { ShaderDataType::Float,  {4        , 1    } },
        { ShaderDataType::Float2, {4 * 2    , 2    } },
        { ShaderDataType::Float3, {4 * 3    , 3    } },
        { ShaderDataType::Float4, {4 * 4    , 4    } },
        { ShaderDataType::Int,    {4        , 1    } },
        { ShaderDataType::Int2,   {4 * 2    , 2    } },
        { ShaderDataType::Int3,   {4 * 3    , 3    } },
        { ShaderDataType::Int4,   {4 * 4    , 4    } },
        { ShaderDataType::Mat3,   {4 * 3 * 3, 3 * 3} },
        { ShaderDataType::Mat4,   {4 * 4 * 4, 4 * 4} }
    };
}