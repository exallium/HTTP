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
int http_request(struct HTTP_CONNECTION* conn, int type, char* resource, char* data) {
    char rtype[12];
    char *buffer;
    int len = 32 + strlen(conn->hostname) + strlen(resource);
    buffer = (char *)malloc(sizeof(char) * len);

    if(strlen(resource) == 0) {
        return HTTP_REQERR_NO_RESOURCE;
    }

    if(resource[0] != '/') {
        return HTTP_REQERR_NO_SLASH;
    }

    switch(type) {
        case HTTP_HEAD:
            memcpy(rtype, "HEAD", 5);
            break;
        case HTTP_GET:
            memcpy(rtype, "GET", 4);
            break;
        default:
            return HTTP_REQERR_UNKNOWN_TYPE;
    }

    sprintf(buffer, "%s %s HTTP/1.1\r\nHost: %s\r\n\r\n", 
            rtype, resource, conn->hostname);

#ifdef DEBUG
    printf("d:http_request:generated\n%s", buffer);
#endif

    return 0;
}
