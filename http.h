#ifndef _HTTP_H_
#define _HTTP_H_

struct HTTP_CONNECTION {
    int sd;                 // Socket descriptor
    char *hostname;         // Host Name
};

struct HTTP_RESPONSE {
    int status;
};

// Setup and Shutdown methods
int http_connect(struct HTTP_CONNECTION* conn, char* host);
int http_disconnect(struct HTTP_CONNECTION* conn, int flags);
int http_clean(struct HTTP_CONNECTION* conn);

// HTTP Methods
int http_request(struct HTTP_CONNECTION* conn, 
        struct HTTP_RESPONSE* response, 
        char* type, char* resource, char* data);

// Flags
#define HTTP_FLAG_CLEAN 0x01

// Types
#define HTTP_HEAD   "HEAD"
#define HTTP_GET    "GET"
#define HTTP_POST   "POST"
#define HTTP_PATCH  "PATCH"

// Errors
// Request Erros
#define HTTP_REQERR_NO_RESOURCE     -1
#define HTTP_REQERR_NO_SLASH        -2
#define HTTP_REQERR_UNKNOWN_TYPE    -3
#endif
