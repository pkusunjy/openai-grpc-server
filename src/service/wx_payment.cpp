#include "wx_payment.h"

namespace wx_payment {

int32_t WxPaymentImpl::initialize() {
  OpenSSL_add_all_algorithms();
  ERR_load_crypto_strings();
  return 0;
}

grpc::Status WxPaymentImpl::notify_url(grpc::ServerContext* ctx, const NotifyUrlRequest* req, NotifyUrlResponse* resp) {
  return grpc::Status::OK;
}

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

int32_t WxPaymentImpl::generate_http_authorization(const AuthorizationInput& input, std::string& res) {
  auto input_vec = input.get_vec();
  std::string data = absl::StrJoin(input_vec, "\n");
  data.append("\n");

  FILE* fp = fopen("/Users/sunjiayu01/projects/openai-grpc-server/apiclient_key.pem", "r");
  if (fp == nullptr) {
    LOG(WARNING) << "fopen apiclient_key.pem failed";
    return -1;
  }
  BOOST_SCOPE_EXIT(&fp) {
    fclose(fp);
  }
  BOOST_SCOPE_EXIT_END

  EVP_PKEY* pkey = PEM_read_PrivateKey(fp, nullptr, nullptr, nullptr);
  if (pkey == nullptr) {
    LOG(WARNING) << "Failed to load private key";
    return -1;
  }
  BOOST_SCOPE_EXIT(&pkey) {
    EVP_PKEY_free(pkey);
  }
  BOOST_SCOPE_EXIT_END

  EVP_MD_CTX* ctx = EVP_MD_CTX_new();
  if (ctx == nullptr) {
    LOG(WARNING) << "Failed to create EVP_MD_CTX";
    return -1;
  }
  BOOST_SCOPE_EXIT(&ctx) {
    EVP_MD_CTX_free(ctx);
  }
  BOOST_SCOPE_EXIT_END

  if (EVP_DigestSignInit(ctx, nullptr, EVP_sha256(), nullptr, pkey) != 1) {
    LOG(WARNING) << "EVP_DigestSignInit failed";
    return -1;
  }

  if (EVP_DigestSignUpdate(ctx, data.c_str(), data.size()) != 1) {
    LOG(WARNING) << "EVP_DigestSignUpdate failed";
    return -1;
  }

  size_t siglen;
  if (EVP_DigestSignFinal(ctx, nullptr, &siglen) != 1) {
    LOG(WARNING) << "EVP_DigestSignFinal (size) failed";
    return -1;
  }
  LOG(INFO) << "dgst final siglen:" << siglen;

  std::vector<unsigned char> sig(siglen);
  if (EVP_DigestSignFinal(ctx, sig.data(), &siglen) != 1) {
    LOG(WARNING) << "EVP_DigestSignFinal failed";
    return -1;
  }

  LOG(INFO) << "sig: " << std::string(sig.begin(), sig.end());

  // base64 encode
  res.assign(base64_encode(sig.data(), sig.size()));
  return 0;
}

}