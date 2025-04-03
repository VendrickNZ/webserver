#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>


class HttpRequest
{
public:
    HttpRequest();
    ~HttpRequest();
private:
    std::string ParseData(const std::string& buffer);
    std::string ParseHeader(const std::string& buffer);
    std::string ParseBody(const std::string& buffer);
    std::string method;
    std::string target;
    std::string httpVersion;
    std::unordered_map<std::string, std::string> headers;
};


#endif