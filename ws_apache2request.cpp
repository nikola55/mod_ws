#include "ws_apache2request.h"

#include "httpd.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"

#include <cstring>

ws::request * ws::apache2request::create(request_rec *r)
{
	return new apache2request(r);
}

ws::apache2request::apache2request(request_rec *r) : __rr(r)
{	
	zero();
}

void ws::apache2request::zero()
{
	_method = 0;
	_uri = 0;
	_headers = 0;
//	_query_string = 0;
	_body = 0;
}

const std::string & ws::apache2request::uri() {
	if(_uri == 0) {
		_uri = new string(__rr->uri);
	}
	return *_uri;
}

const std::string& ws::apache2request::method()
{
	if(_method == 0) {
		_method = new string(__rr->method);
	}
	return *_method;
}

const std::string& ws::apache2request::header(const string& str) {
	std::map<std::string, std::string> &all = const_cast<std::map<std::string, std::string>& >(headers());
	if(all.find(str) == headers().end()) {
		return no_value;
	}
	return all[str];
}

const std::map<std::string, std::string> & ws::apache2request::headers() {
	if(_headers == 0) {
		_headers = new std::map<std::string, std::string>;
		load_table_to_map(__rr->headers_in, _headers);
	}
	return *_headers;
}

const char * ws::apache2request::body() {
	if(_body != 0) {
		return _body;
	}
	if(ap_setup_client_block(__rr, REQUEST_CHUNKED_ERROR)) {
		return _body;
	}
	if(!ap_should_client_block(__rr)) {
		return _body;
	}
	apr_off_t length = __rr->remaining;
	
	apr_off_t len_read, rsize, rpos = 0;
	char argsbuffer[HUGE_STRING_LEN];
	_body = (char*)apr_pcalloc(__rr->pool, (apr_size_t) (length + 1));
	while((len_read = ap_get_client_block(__rr, argsbuffer, sizeof(argsbuffer))) > 0) {
		if((rpos + len_read) > length) {
			rsize = length - rpos;
		} else {
			rsize = len_read;
		}
		memcpy(_body + rpos, argsbuffer, (size_t) rsize);
		rpos += rsize;
	}
	return _body;
}

ws::apache2request::apache2request(const apache2request &other)
{
	throw std::runtime_error("unsupported opperation");
}

ws::apache2request & ws::apache2request::operator=(const apache2request &other)
{
	throw std::runtime_error("unsupported opperation");
}

ws::apache2request::~apache2request() {
	if(_method != 0) {
		delete _method;
	}
	if(_uri != 0) {
		delete _uri;
	}
	if(_headers != 0) {
		delete _headers;
	}
//	if(_query_string != 0) {
//		delete _query_string;
//	}
}

void ws::apache2request::load_table_to_map(apr_table_t * table, std::map<std::string, std::string> *map) {
	std::map<std::string, std::string> &mapRef = *map;
	const apr_array_header_t *fields = apr_table_elts(table);
	apr_table_entry_t *e = (apr_table_entry_t *) fields->elts;
	for(int i = 0 ; i < fields->nelts ; i++) {
		mapRef[string(e[i].key)] = string(e[i].val);
	}
}

std::string ws::apache2request::no_value = "";