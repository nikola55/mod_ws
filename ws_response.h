#ifndef _RESPONSE_INCLUDE_H
#define _RESPONSE_INCLUDE_H

#include <string>
#include <map>

namespace ws {

using std::string;
using std::map;

class response {
public:
  virtual void header(const string& key, const string& value) = 0;
  virtual void content_type(const string &type) = 0;
  virtual void status_code(int code) = 0;
  virtual int status_code() = 0;
  virtual void do_write(const char *message) = 0;

  virtual ~response() {

  }
};

}

#endif