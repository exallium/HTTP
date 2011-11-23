#ifndef _HTTP_H_
#define _HTTP_H_

struct HTTP_CONNECTION {
    int sd;                 // Socket descriptor
    char *hostname;         // Host Name
};

// Setup and Shutdown methods
int http_connect(struct HTTP_CONNECTION* conn, char* host);
int http_disconnect(struct HTTP_CONNECTION* conn, int flags);
int http_clean(struct HTTP_CONNECTION* conn);

// HTTP Methods
int http_request(struct HTTP_CONNECTION* conn, int type, char* resource, char* data);

// Flags
#define HTTP_FLAG_CLEAN 0x01

// Types
#define HTTP_HEAD   1
#define HTTP_GET    2
#define HTTP_POST   3
#define HTTP_PATCH  4

// Errors
// Request Erros
#define HTTP_REQERR_NO_RESOURCE     -1
#define HTTP_REQERR_NO_SLASH        -2
#define HTTP_REQERR_UNKNOWN_TYPE    -3
#endif
