#ifndef _APACHE2REQUEST_INCLUDE_
#define _APACHE2REQUEST_INCLUDE_

#include "ws_request.h"

struct request_rec;
struct apr_table_t ;

namespace ws {

    class apache2request : public request {
	request_rec * __rr;
	string * _method;
	string * _uri;
	map<string, string> * _headers;
//	map<string, string> * _query_string;
	char * _body;
	static string no_value;
    public:
	virtual const string & method();
	virtual const string & header(const string &str);
	virtual const string & uri();
	virtual const map<string, string> & headers();
//	virtual const map<string, string>& query_string();
	virtual const char * body();
	static request * create(request_rec *r);
    private:
	apache2request(request_rec *r);
	apache2request(const apache2request &other);
	virtual apache2request & operator=(const apache2request &other);
	~apache2request();
	void zero();
	void load_headers();
	void load_table_to_map(apr_table_t * table, map<string, string> *map);
    };
}
#endif
