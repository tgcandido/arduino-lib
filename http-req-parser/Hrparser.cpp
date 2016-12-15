/*
  Hrparser.cpp - Library for parsing Http headers.
  Created by tgcandido, December 15, 2016.
*/

#include "Arduino.h"
#include "Hrparser.h"

Header HttpRequestParser::getHeader(EthernetClient client){
    Header header;
    String headerStr = this->readRequestHeader(client);
    header.method = this->getMethod(headerStr);
    header.endpoint = this->getEndpoint(headerStr);
    return header;
}

String HttpRequestParser::getEndpoint(String headerStr){
    String endpoint = "";
    int startOfEndpoint = headerStr.indexOf("/");
    int offset = 1;
    while (headerStr[startOfEndpoint + offset] != ' ')
    {
        endpoint += headerStr[startOfEndpoint + offset];
        offset++;
    }
    return endpoint;
}

HTTP_METHOD HttpRequestParser::getMethod(String headerStr){
    HTTP_METHOD method;
    int endOfMethod = headerStr.indexOf(" ");
    String methodStr = headerStr.substring(0, endOfMethod);
    if (methodStr.equals("GET"))
    {
        method = GET;
    }

    return method;
}

String HttpRequestParser::readRequestHeader(EthernetClient client){
    char c = client.read();
    String headerStr = "";
    while (c != -1)
    {
        headerStr += c;
        c = client.read();
    }
    return headerStr;
}
