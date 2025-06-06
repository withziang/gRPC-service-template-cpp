//src/function_registry.cpp

#include "function_registry.h"

void FunctionRegistry::register_function(const std::string& name, FunctionType func) {
    registry_[name] = func;
}

std::string FunctionRegistry::call_function(const std::string& name, const std::string& args, bool& success) {
    auto it = registry_.find(name);
    if (it != registry_.end()) {
        success = true;
        return it->second(args);
    } else {
        success = false;
        return "Function not found";
    }
}
