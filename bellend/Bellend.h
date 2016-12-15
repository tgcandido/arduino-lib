/*
  Bellend.cpp - Library for developing REST services.
  Created by tgcandido, December 15, 2016.
*/

#ifndef BELLEND_H
#define BELLEND_H
#define MAX_HANDLERS 12

#include "Arduino.h"
#include "Hrparser.h"
#include <Ethernet.h>

struct RequestHandler_{
    Header header;
    void (*action) (EthernetClient);
} typedef RequestHandler;

class Bellend{
    public:
    Bellend() : _handlersCount(0) { };
    void process(EthernetClient client);
    void addHandler(HTTP_METHOD method, String endpoint, void (*action) (EthernetClient));
    void otherwise(void (*action) (EthernetClient));

    private:
    HttpRequestParser _parser;
    RequestHandler _handlers[MAX_HANDLERS];
    RequestHandler _otherwise;
    int _handlersCount;
};

#endif
