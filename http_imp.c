#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include"http.h"

#define DEBUG

// pulls information from the server, fills in necessary info
static int process_response(struct HTTP_CONNECTION *conn, 
        struct HTTP_RESPONSE* response) {
    char buffer[1024];
    int count, i, n;
    fd_set readfds;
    struct timeval tv;

    FD_ZERO(&readfds);
    FD_SET(conn->sd, &readfds);

    n = conn->sd + 1;
    tv.tv_sec = 0;
    tv.tv_usec = 500000;
    
    while(select(n, &readfds, NULL, NULL, &tv) != -1 && FD_ISSET(conn->sd, &readfds)) {
        count = read(conn->sd, buffer, 1024);
        for(i = 0; i < count; i++) {
#ifdef DEBUG
            putchar(buffer[i]);
#endif
        } 
    }

    return 0;
}

// http_get
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

    send(conn->sd, buffer, strlen(buffer), 0);

    process_response(conn, response);

    return 0;
}

