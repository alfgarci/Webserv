# include <string>

# pragma once

template <typename T>
int to_int(const T& value)
{
    std::istringstream iss(value);
    int result;

    iss >> result;
    return (result);
}
