//src/function_registry.h

#pragma once
#include <functional>
#include <string>
#include <map>

class FunctionRegistry {
private:
    std::unordered_map<std::string, FunctionType> registry_;
public:
    using FunctionType = std::function<std::string(const std::string&)>;

    void register_function(const std::string& name, FunctionType func);
    std::string call_function(const std::string& name, const std::string& args, bool& success);

};