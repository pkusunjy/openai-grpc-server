# openai-grpc-server

## 1. Install dependencies required by grpc-gateway.

## 2. Generate gRPC stubs

```
protoc -I . \
    --go_out ./ --go_opt paths=source_relative \
    --go-grpc_out ./ --go-grpc_opt paths=source_relative \
    proto/chat_completion/chat_completion.proto
```

## 3. Generate reverse-proxy using protoc-gen-grpc-gateway

```
protoc -I . --grpc-gateway_out ./ \
    --grpc-gateway_opt paths=source_relative \
    --grpc-gateway_opt generate_unbound_methods=true \
    proto/chat_completion/chat_completion.proto
```
