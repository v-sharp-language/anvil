#pragma once

#include <string>

inline std::string global(const std::string &name)
{
    return "@" + name;
}

inline std::string local(unsigned id)
{
    return "%" + std::to_string(id);
}