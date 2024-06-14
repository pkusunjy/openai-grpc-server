#include "wx_payment.h"

namespace wx_payment {
int32_t WxPaymentImpl::generate_nonce_str(std::string& res) {
  std::ifstream ifs("/dev/random", std::ios::in | std::ios::binary);
  BOOST_SCOPE_EXIT(&ifs) {
    ifs.close();
  }
  BOOST_SCOPE_EXIT_END
  uint8_t buffer[16];
  ifs.read(reinterpret_cast<char*>(buffer), sizeof(buffer));
  if (!ifs) {
    LOG(WARNING) << "read 16 bytes failed";
    return 1;
  }
  std::stringstream ss;
  for (int32_t i = 0; i < 16; i += 4) {
    uint32_t value = (buffer[i] << 24) | (buffer[i+1] << 16) | (buffer[i+2] << 8) | buffer[i+3];
    ss << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << value;
  }
  res.assign(ss.str());
  LOG(INFO) << "generate nonce_str success: " << res;
  return 0;
}
}