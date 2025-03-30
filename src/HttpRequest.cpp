#include "HttpRequest.h"

/**
    Reading the raw data until I find the header terminator (\r\n\r\n).

    Parsing the request line (e.g., GET /index.html HTTP/1.1).

    Splitting the header fields into key-value pairs.

    Optionally handling the message body if required.
 */

HttpRequest::HttpRequest()
{

}

HttpRequest::~HttpRequest() 
{

}

std::string ParseData(std::string &buffer)
{

}