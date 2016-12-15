/*
  Hrparser.cpp - Library for parsing Http headers.
  Created by tgcandido, December 15, 2016.
*/

#include "Arduino.h"
#include "Hrparser.h"

Header HttpRequestParser::getHeader(EthernetClient client){
    char* headerStr = this->readRequestHeader(client);
    int headerStrLen = strlen(headerStr);
    Header header;
    
    header.method = this->getMethod(headerStr, headerStrLen);
    header.endpoint = this->getEndpoint(headerStr, headerStrLen);
    
    free(headerStr);
    return header;
}

void HttpRequestParser::freeHeader(Header header){
    free((char*)header.endpoint);
}

char* HttpRequestParser::getEndpoint(const char* headerStr, int headerStrLen){
    char* endpoint = (char*)malloc(ENDPOINT_SIZE);
    int endpointOffset = 0;

    char* startOfEndpoint = (char*)memchr(headerStr, '/', headerStrLen);
    ++startOfEndpoint;

    while (*startOfEndpoint != ' '){
        endpoint[endpointOffset++] = *startOfEndpoint;
        ++startOfEndpoint;
    }
    
    endpoint[endpointOffset] = '\0';
    return endpoint;
}

HTTP_METHOD HttpRequestParser::getMethod(const char* headerStr, int headerStrLen){
    HTTP_METHOD method;
    char methodStr[METHOD_SIZE];
    int methodOffset = 0;

    while (headerStr[methodOffset] != ' '){
        methodStr[methodOffset] = headerStr[methodOffset];
        methodOffset++;
    }
    methodStr[methodOffset] = '\0';    
    if (strcmp(methodStr, "GET") == 0)
    {
        method = GET;
    }

    return method;
}

char* HttpRequestParser::readRequestHeader(EthernetClient client){
    char c = client.read();
    char* headerStr = (char*)malloc(HEADER_SIZE);
    int index = 0;
    while (c != -1)
    {
        headerStr[index++] = c;
        c = client.read();
    }
    headerStr[index] = '\0';

    return headerStr;
}
