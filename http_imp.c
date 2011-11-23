#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include"http.h"

#define DEBUG

// http_head
// sends <type> request to a server
// Simple enough.
int http_request(struct HTTP_CONNECTION* conn, 
        struct HTTP_RESPONSE* response,
        char* type, char* resource, char* data) {
    char *buffer;
    int len = 32 + strlen(conn->hostname) + strlen(resource);
    buffer = (char *)malloc(sizeof(char) * len);

    if(strlen(resource) == 0) {
        return HTTP_REQERR_NO_RESOURCE;
    }

    if(resource[0] != '/') {
        return HTTP_REQERR_NO_SLASH;
    }

    sprintf(buffer, "%s %s HTTP/1.1\r\nHost: %s\r\n\r\n", 
            type, resource, conn->hostname);

#ifdef DEBUG
    printf("d:http_request:generated\n%s", buffer);
#endif

    return 0;
}
