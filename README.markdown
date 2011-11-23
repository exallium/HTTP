# HTTP API for C
There are several things that this project is and isnt.
1. This project should not be considered a replacement for traditional libraires
   (at this time).
2. This project has no completion date or set course.  It is purely for my own
   enjoyment.
3. This project is licensed as GPL.  Feel free to take from it what you will.
4. This project is a personal learning environment.  Github just so happens to
   be a place where I can host my code and other people can look at it if they
   so choose to do so.

## Basic Methodology
The underlying workings for this is of course the BSD Sockets API.  This is a
client library.  Thus the way it works is that it establishes a connection with
a server on port 80 (specified by the programmer) and hands back a populated
HTTP\_CONNECTION object.  This object contains information vital to the success
of the API and thus should not be tampered with by the programmer. (Go to,
though.  Your loss.)  This object then represents this connection.  A connection
is made like so:

```
struct HTTP_CONNECTION hc;
http_connect(&hc, "www.google.com"); // Will return a zero value on success
```

The programmer then interacts with the server, using the HTTP request method.
Ideally, this will hand the programmer back an HTTP response object, though the
parsing implementation for this is not written as of yet.

```
// Assuming we have connected as in the above example
struct HTTP_RESPONSE hr;
http_request(&hc, &hr, HTTP_GET, "/index.html", NULL);
// At this point, hr can be processed for results.
```

Notice the NULL at the end.  Eventually, this will be used for passing data to
the server.
