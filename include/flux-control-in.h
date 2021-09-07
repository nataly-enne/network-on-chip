#ifndef FLUX_CONTROL_IN_H
#define FLUX_CONTROL_IN_H

#include <stdio.h>

#include "systemc.h"

SC_MODULE(HandshakeIN) {

    sc_in<bool> request_to_receive; // Sinal que identifica a solicitação do envio de uma mensagem.
    sc_in<bool> buffer_is_full; // Sinal para saber se o buffer está cheio.
    sc_out<bool> can_receive; // Sinal que identifica se pode receber a mensagem ou não.

    void rules(){

        std::cout << "entra fc in" << std::endl;

        bool request = request_to_receive.read();
        bool full = buffer_is_full.read();

        if(request){
            if(full){
                can_receive.write(false);
            }
            else {
                can_receive.write(true);
            }
        } else{
            can_receive.write(false);
        }

        std::cout << "sai fc in" << std::endl;

    }

    SC_CTOR(HandshakeIN) {
        SC_METHOD(rules);
        sensitive << request_to_receive << buffer_is_full;
    }

};

#endif