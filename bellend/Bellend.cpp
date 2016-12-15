/*
  Bellend.cpp - Library for developing REST services.
  Created by tgcandido, December 15, 2016.
*/

#include "Arduino.h"
#include "Hrparser.h"
#include "Bellend.h"
#include <Ethernet.h>


void Bellend::process(EthernetClient client){
    Header header = this->_parser.getHeader(client);
    boolean found = false;
    for (int i = 0; i < this->_handlersCount; i++){
        RequestHandler handler = this->_handlers[i];
        if (handler.header.endpoint.equals(header.endpoint) && 
            handler.header.method == header.method){
                found = true;
                handler.action(client);
            }
    }

    if (!found && this->_otherwise.action){
        this->_otherwise.action(client);
    }
}

void Bellend::addHandler(HTTP_METHOD method, String endpoint, void (*action) (EthernetClient)){
    if (this->_handlersCount >= MAX_HANDLERS){
        Serial.print("BELLEND - ERR - MAX HANDLERS REACHED");
        return;
    }
    
    RequestHandler handler;
    handler.header.method = method;
    handler.header.endpoint = endpoint;
    handler.action = action;

    this->_handlers[this->_handlersCount] = handler;
    this->_handlersCount++;
}

void Bellend::otherwise(void (*action) (EthernetClient)){
    this->_otherwise.action = action;
}