#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"http.h"

int main(int argc, char** argv) {
    int s;
    char buf[1024], c;
    struct HTTP_CONNECTION hc;

    http_connect(&hc, "www.google.ca");
    http_request(&hc, NULL, HTTP_HEAD, "/index.html", NULL);
    http_disconnect(&hc, HTTP_FLAG_CLEAN);
 
    return 0;
}
