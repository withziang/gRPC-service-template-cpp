//src/server.cpp


#include "dispatcher.grpc.pb.h"
#include "function_registry.h"

#include <grpcpp/grpcpp.h>
#include <memory>
#include <string>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using dispatcher::Dispatcher;
using dispatcher::FunctionCallRequest;
using dispatcher::FunctionCallResponse;

class DispatcherServiceImpl final : public Dispatcher::Service {
public:
    DispatcherServiceImpl(FunctionRegistry& registry) : registry_(registry) {}

    Status CallFunction(ServerContext* context, const FunctionCallRequest* request,
                        FunctionCallResponse* response) override {
        bool success;
        std::string result = registry_.call_function(request->function_name(), request->arguments(), success);

        response->set_success(success);
        response->set_result(result);
        if (!success) {
            response->set_error_message("Function not found");
        }

        return Status::OK;
    }

private:
    FunctionRegistry& registry_;
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    FunctionRegistry registry;

    // Example function: echo
    registry.register_function("echo", [](const std::string& args) {
        return "Echo: " + args;
    });

    DispatcherServiceImpl service(registry);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main() {
    RunServer();
    return 0;
}
