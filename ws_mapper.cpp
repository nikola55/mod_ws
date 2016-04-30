#include <string>
#include <iostream>
#include "ws_mapper.h"
#include "ws_apache2request.h"
#include "ws_apache2response.h"

using namespace std;

typedef void(*ws_handler)(ws::request &req, ws::response &resp);

ws_handler create_request_mapping(ws::request &req, ws::response &res);

int map_request(request_rec *r)
{
	ws::request * request = ws::apache2request::create(r);
	ws::response * response = ws::apache2response::create(r);
	create_request_mapping(*request, *response);
	int status = response->status_code();
	delete request;
	delete response;
	return status;
}

ws_handler create_request_mapping(ws::request &req, ws::response &res)
{
	cout << req.body() << endl;
	res.content_type("text/html");
	res.status_code(500);
	res.do_write(
	"<!DOCTYPE html>"
	"	<html>"
	"		<head>"
	"			<title>example</title>"
	"		</head>"
	"		<body>"
	"			<b>Hello</b><code>World</code>"
	"		</body>"
	"	</html>");
}

