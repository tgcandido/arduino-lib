/*
  Hrparser.cpp - Library for parsing Http headers.
  Created by tgcandido, December 15, 2016.
*/

#ifndef HRPARSER_H
#define HRPARSER_H

#include "Arduino.h"
#include <Ethernet.h>

enum HTTP_METHOD { GET, POST, DELETE, PUT };

struct Header_ {
  HTTP_METHOD method;
  String endpoint;
} typedef Header;

class HttpRequestParser{
    public:
    Header getHeader(EthernetClient client);
    private:
    String readRequestHeader(EthernetClient client);
    HTTP_METHOD getMethod(String headerStr);
    String getEndpoint(String headerStr);
};

#endif
