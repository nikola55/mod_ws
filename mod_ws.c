#include "httpd.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_config.h"
#include "ws_mapper.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    static void register_hooks(apr_pool_t *pool);
    static int ws_handler(request_rec *r);
    
#ifdef __cplusplus
}
#endif

module AP_MODULE_DECLARE_DATA ws_module ={
    STANDARD20_MODULE_STUFF,
    NULL, // Per-directory configuration handler
    NULL, // Merge handler for per-directory configurations
    NULL, // Per-server configuration handler
    NULL, // Merge handler for per-server configurations
    NULL, // Any directives we may have for httpd
    register_hooks // Our hook registering function
};

static void initialize() {
    // do initialize here if needed.
}

static void register_hooks(apr_pool_t *pool) {
    initialize();
    ap_hook_handler(ws_handler, NULL, NULL, APR_HOOK_LAST);
}

static int ws_handler(request_rec *r) {
    if (!r->handler || strcmp(r->handler, "ws-handler")) return (DECLINED);

    int status = map_request(r);
    // return 
    // OK in case the request went well 
    // DECLINED if you are not interested in this request
    // DONE when you don't want other handlers to handle the request
    // ************** find better way to return the http code than:
    //HTTP_OK (200): Request was okay
    //HTTP_MOVED_PERMANENTLY (301): The resource has moved to a new URL
    //HTTP_UNAUTHORIZED (401): Client is not authorized to visit this page
    //HTTP_FORBIDDEN (403): Permission denied
    //HTTP_NOT_FOUND (404): File not found
    //HTTP_INTERNAL_SERVER_ERROR (500): Internal server error (self explanatory)
    return OK;
}
