#pragma once

#include <memory>

namespace Snowflake
{
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    Ref<T> CreateRef(Args&& ... Arguments)
    {
        return std::make_shared<T>(std::forward<Args>(Arguments)...);
    }

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    Scope<T> CreateScope(Args&& ... Arguments)
    {
        return std::make_unique<T>(std::forward<Args>(Arguments)...);
    }
}