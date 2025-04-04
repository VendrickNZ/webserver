#include "HttpRequest.h"

/**
    Reading the raw data until I find the header terminator (\r\n\r\n).

    Parsing the request line (e.g., GET /index.html HTTP/1.1).

    Splitting the header fields into key-value pairs.

    Optionally handling the message body if required.
 */

HttpRequest::HttpRequest()
    : method(), target(), httpVersion(), headers()
{

}

HttpRequest::~HttpRequest() 
{

}

std::string ParseData(std::string &buffer)
{
    ParseHeader(buffer);
}


std::string ParseHeader(std::string &buffer)
{
    std::string header = "";
    std::string header_terminator = "\r\n\r\n";
    size_t i = 0;
    while ((header.size() < header_terminator.size() ||
            header.substr(header.size() - header_terminator.size()) != header_terminator) &&
            i < buffer.size()) {
        header.push_back(buffer[i]);
    }
    return header;
}

std::string ParseBody()
{

}
