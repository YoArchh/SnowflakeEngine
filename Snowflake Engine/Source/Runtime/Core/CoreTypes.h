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
}