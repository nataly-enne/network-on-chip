#ifndef ARBITRATION_H
#define ARBITRATION_H

#include <stdio.h>

#include "systemc.h"

SC_MODULE(Arbitration) {

    // Sinais de identificação. verifica quais canais de entradas solicitam sair pelo canal do árbitro
    sc_in<bool> local_channel, north_channel, south_channel, east_channel, west_channel;
    // Sinal que identifica se o árbitro escolheu algum canal e deseja enviar a mensagem.
    sc_out<bool> request_shipping;

    /**
     * Indica qual canal o árbitro escolheu.
     * 000 (0) - Canal local.
     * 001 (1) - Canal norte.
     * 010 (2) - Canal sul.
     * 011 (3) - Canal leste.
     * 100 (4) - Canal oeste.  
     */

    sc_out<sc_uint<3>> chosen_channel;
    

    void rules(){

         std::cout << "entra arbitro" << std::endl;

        if(local_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(0);

        }
        else if(north_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(1);

        }
        else if(south_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(2);

        }
        else if(east_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(3);

        }
        else if(west_channel.read()){

            request_shipping.write(true);
            chosen_channel.write(4);

        }

        request_shipping.write(false);

         std::cout << "sai arbitro" << std::endl;

    }

    SC_CTOR(Arbitration) {
        SC_METHOD(rules);
        sensitive << local_channel << north_channel << south_channel << east_channel << west_channel;
    }

};

#endif