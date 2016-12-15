/*
  Hrparser.cpp - Library for parsing Http headers.
  Created by tgcandido, December 15, 2016.
*/

#ifndef HRPARSER_H
#define HRPARSER_H

#define METHOD_SIZE 16
#define ENDPOINT_SIZE 32
#define HEADER_SIZE 128

#include "Arduino.h"
#include <Ethernet.h>

enum HTTP_METHOD { GET, POST, DELETE, PUT };

struct Header_ {
  HTTP_METHOD method;
  const char* endpoint;
} typedef Header;

class HttpRequestParser{
    public:
    Header getHeader(EthernetClient client);
    private:
    char* readRequestHeader(EthernetClient client);
    HTTP_METHOD getMethod(const char* headerStr, int headerStrLen);
    char* getEndpoint(const char* headerStr, int headerStrLen);
};

#endif
