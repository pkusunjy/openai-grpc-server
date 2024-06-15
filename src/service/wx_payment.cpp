#include "wx_payment.h"

namespace wx_payment {

grpc::Status NotifyServiceImpl::jsapi_notify_url(grpc::ServerContext* ctx, const NotifyUrlRequest* req,
                                                 NotifyUrlResponse* resp) {
  std::string debug_str;
  if (::google::protobuf::util::MessageToJsonString(*req, &debug_str).ok()) {
    LOG(INFO) << "received request: " << debug_str;
  } else {
    LOG(INFO) << "error happens";
  }
  return grpc::Status::OK;
}

} // namespace wx_payment