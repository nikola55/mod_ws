#ifndef _REQUEST_INCLUDE_H_
#define _REQUEST_INCLUDE_H_

#include <stdexcept>
#include <string>
#include <map>
#include <streambuf>

namespace ws {

    using std::string;
    using std::map;

    class request {
	//virtual request & operator=(const request &other) = 0;
    public:
	virtual const string & method() = 0;
	virtual const string & header(const string &str) = 0;
	virtual const string & uri() = 0;
	virtual const map<string, string> & headers() = 0;
//	virtual const map<string, string> & query_string() = 0;
	virtual const char * body() = 0;
	virtual ~request() {
	}
    };

}

#endif