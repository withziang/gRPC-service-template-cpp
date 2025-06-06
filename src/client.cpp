//src/client.cpp


#include "dispatcher.grpc.pb.h"

#include <grpcpp/grpcpp.h>
#include <iostream>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using dispatcher::Dispatcher;
using dispatcher::FunctionCallRequest;
using dispatcher::FunctionCallResponse;

class DispatcherClient {
public:
    DispatcherClient(std::shared_ptr<Channel> channel) : stub_(Dispatcher::NewStub(channel)) {}

    std::string CallFunction(const std::string& function_name, const std::string& args) {
        FunctionCallRequest request;
        request.set_function_name(function_name);
        request.set_arguments(args);

        FunctionCallResponse response;
        ClientContext context;

        Status status = stub_->CallFunction(&context, request, &response);

        if (status.ok() && response.success()) {
            return response.result();
        } else {
            return "RPC failed or function not found";
        }
    }

private:
    std::unique_ptr<Dispatcher::Stub> stub_;
};

int main() {
    DispatcherClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string reply = client.CallFunction("echo", "Hello world");
    std::cout << "Client received: " << reply << std::endl;

    return 0;
}
