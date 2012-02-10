#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include"http.h"

// Define this to include debugging code.
#define DEBUG

#ifdef DEBUG
#include<stdio.h>
#endif

// Creates an http connection to specified host name.
// Returns an error based off several different situations.
// Returns zero if successful.
//
// PARAMETERS
// conn -- a pointer to the HTTP_CONNECTION structure representing this
//      connection
// host -- The DNS hostname or IP address.
int http_connect(struct HTTP_CONNECTION* conn, char* host) {
    int s;
    struct sockaddr_in server;
    struct hostent *hp;

    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    hp = gethostbyname(host);
    bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
    server.sin_port = htons(80);

    connect(s, &server, sizeof(server));

    conn->sd = s;
    conn->hostname = (char *)malloc(sizeof(char) * strlen(host));
    memset(conn->hostname, 0, strlen(host));
    memcpy(conn->hostname, host, strlen(host));

    return 0;
}

// Closes the socket
int http_disconnect(struct HTTP_CONNECTION* conn, int flags) {

    close(conn->sd);

    if(flags & HTTP_FLAG_CLEAN) {

#ifdef DEBUG
        printf("\nd:http_disconnect: Cleaning allocated memory\n");
#endif
        http_clean(conn);
    }
    
    return 0;
}

// Deallocates any dynamic memory associated with conn
int http_clean(struct HTTP_CONNECTION* conn) {
    if(conn->hostname != NULL) {
        free(conn->hostname);
        conn->hostname = NULL;
        return 0;
    } else {
        return -1;
    }
}

