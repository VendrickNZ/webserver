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
};


#endif