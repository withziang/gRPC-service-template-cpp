# Overview

## RPC Dispatcher Pattern

- Callers send a request message: function name + serialized arguments

- The server deserializes the arguments, looks up the function, and calls it

- The server sends back a serialized result