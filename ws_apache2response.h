#ifndef _APACHE2RESPONSE_INCLUDE_
#define _APACHE2RESPONSE_INCLUDE_
#include "ws_response.h"

struct request_rec;

namespace ws {
    class apache2response : public response {
	request_rec *__rr;
	bool _ok;
	int _status_code;
    public:
	virtual void header(const string& key, const string& value);
	virtual void content_type(const string &type);
	virtual void status_code(int code);
	virtual int status_code();
	virtual void do_write(const char * response);
	virtual bool ok() const;
	static response * create(request_rec *r);
    private:
	apache2response(request_rec *r);
	apache2response(const apache2response &res);
	apache2response & operator=(const apache2response &res);
	~apache2response();
	void zero();
    };
}

#endif