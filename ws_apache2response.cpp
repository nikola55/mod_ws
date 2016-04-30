#include "ws_apache2response.h"

#include "httpd.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"

#include <stdexcept>

ws::response * ws::apache2response::create(request_rec *r) {
  return new apache2response(r);
}

ws::apache2response::apache2response(request_rec *r) : __rr(r) {
  zero();
}

void ws::apache2response::header(const std::string& key, const std::string& value) {
  apr_table_add(__rr->headers_out, key.c_str(), value.c_str());
}

void ws::apache2response::content_type(const string& type) {
  int sz = type.size() + 1;
  char * ct = (char*) apr_pcalloc(__rr->pool, (apr_size_t) sz);
  memcpy(ct, type.c_str(), sz * sizeof(char));
  ap_set_content_type(__rr, ct);
}

void ws::apache2response::status_code(int code) {
  if(code < 100 || code > 599) {
    throw std::runtime_error("invalid status code");
  }
  __rr->status = code;
}

int ws::apache2response::status_code() {
  return __rr->status;
}

void ws::apache2response::do_write(const char * response) {
  ap_rputs(response, __rr);
}

void ws::apache2response::zero() {
  _ok = true;
  __rr->status = 200;
}

bool ws::apache2response::ok() const {
  return _ok;
}

ws::apache2response::apache2response(const apache2response &res) {
  throw std::runtime_error("unsupported opperation");
}

ws::apache2response & ws::apache2response::operator=(const apache2response &res) {
  throw std::runtime_error("unsupported opperation");
}

ws::apache2response::~apache2response() {

}