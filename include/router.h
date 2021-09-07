#ifndef ROUTER_H
#define ROUTER_H

#include "systemc.h"

#include "buffer.h"
#include "routing.h"
#include "arbitration.h"
#include "flux-control-in.h"
#include "flux-control-out.h"

SC_MODULE(Router) {

    // Canal local.
    sc_in<sc_uint<2>> local_x_in, local_y_in; // Valores X e Y de entrada.
    sc_in<bool> local_x_sign_in, local_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> local_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> local_x_out, local_y_out; // Valores X e Y de saída.
    sc_out<bool> local_x_sign_out, local_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> local_message_out; // Mensagem de saída.
    sc_in<bool> local_read, local_write;  // Sinais para indicar que o canal local tem que ler da entrada ou escrever na saída.

    // Canal norte.
    sc_in<sc_uint<2>> north_x_in, north_y_in; // Valores X e Y de entrada.
    sc_in<bool> north_x_sign_in, north_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> north_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> north_x_out, north_y_out; // Valores X e Y de saída.
    sc_out<bool> north_x_sign_out, north_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> north_message_out; // Mensagem de saída.
    sc_in<bool> north_read, north_write;  // Sinais para indicar que o canal norte tem que ler da entrada ou escrever na saída.

    // Canal sul.
    sc_in<sc_uint<2>> south_x_in, south_y_in; // Valores X e Y de entrada.
    sc_in<bool> south_x_sign_in, south_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> south_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> south_x_out, south_y_out; // Valores X e Y de saída.
    sc_out<bool> south_x_sign_out, south_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> south_message_out; // Mensagem de saída.
    sc_in<bool> south_read, south_write;  // Sinais para indicar que o canal sul tem que ler da entrada ou escrever na saída.

    // Canal leste.
    sc_in<sc_uint<2>> east_x_in, east_y_in; // Valores X e Y de entrada.
    sc_in<bool> east_x_sign_in, east_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> east_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> east_x_out, east_y_out; // Valores X e Y de saída.
    sc_out<bool> east_x_sign_out, east_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> east_message_out; // Mensagem de saída.
    sc_in<bool> east_read, east_write;  // Sinais para indicar que o canal leste tem que ler da entrada ou escrever na saída.

    // Canal oeste.
    sc_in<sc_uint<2>> west_x_in, west_y_in; // Valores X e Y de entrada.
    sc_in<bool> west_x_sign_in, west_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_in<sc_uint<32>> west_message_in; // Mensagem de entrada.
    sc_out<sc_uint<2>> west_x_out, west_y_out; // Valores X e Y de saída.
    sc_out<bool> west_x_sign_out, west_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_out<sc_uint<32>> west_message_out; // Mensagem de saída.
    sc_in<bool> west_read, west_write;  // Sinais para indicar que o canal local tem que ler da entrada ou escrever na saída.

    // Sinais de controle para dizer se o buffer pode ler da entrada ou escrever na saída.
    sc_signal<bool> local_buffer_read, north_buffer_read, south_buffer_read, east_buffer_read, west_buffer_read;
    sc_signal<bool> local_buffer_write, north_buffer_write, south_buffer_write, east_buffer_write, west_buffer_write;

    // Sinais de controle para verificar se o buffer de cada canal está cheio.
    sc_signal<bool> local_buffer_full, north_buffer_full, south_buffer_full, east_buffer_full, west_buffer_full;

    // Sinais de controle para definição da rota.
    sc_signal<sc_uint<3>> local_direction, north_direction, south_direction, east_direction, west_direction;

    // Sinais de controle que indicam para onde cada canal quer enviar.
    sc_signal<bool> local_to_north, local_to_south, local_to_east, local_to_west;
    sc_signal<bool> north_to_local, north_to_south, north_to_east, north_to_west;
    sc_signal<bool> south_to_local, south_to_north, south_to_east, south_to_west;
    sc_signal<bool> east_to_local, east_to_north, east_to_south, east_to_west;
    sc_signal<bool> west_to_local, west_to_north, west_to_south, west_to_east;

    // Sinais de controle que indicam que cada árbitro escolheu um canal para enviar.
    sc_signal<bool> local_arbitration_ship, north_arbitration_ship, south_arbitration_ship, east_arbitration_ship, west_arbitration_ship;

    // Sinais de controle que indicam qual canal o árbitro escolheu.
    sc_signal<sc_uint<3>> local_arbitration_chosen, north_arbitration_chosen, south_arbitration_chosen, east_arbitration_chosen, west_arbitration_chosen;

    // sc_signal<bool> this_;
    sc_signal<bool> local_can_receive, north_can_receive, south_can_receive, east_can_receive, west_can_receive;

    // Request to receive
    sc_signal<bool> north_request_to_receive, local_request_to_receive, south_request_to_receive, east_request_to_receive, west_request_to_receive; 

    // As ligações com os próximos roteadores
    sc_signal<bool> local_shipping_request, north_shipping_request, south_shipping_request, west_shipping_request, east_shipping_request; 

    void initialize(){
        init_buffers();
        init_routers_xy();
        init_arbitrations();
        init_handshakes_in();
        init_handshakes_out();
    }

    void init_buffers(){

        Buffer local_buffer("local_buffer");
        local_buffer.x_in(local_x_in);
        local_buffer.y_in(local_y_in);
        local_buffer.x_sign_in(local_x_sign_in);
        local_buffer.y_sign_in(local_y_sign_in);
        local_buffer.message_in(local_message_in);
        
        local_buffer.read_(local_read);
        local_buffer.write_(local_write);
        
        local_buffer.is_full(local_buffer_full);

        local_buffer.x_out(local_x_out);
        local_buffer.y_out(local_y_out);
        local_buffer.x_sign_out(local_x_sign_out);
        local_buffer.y_sign_out(local_y_sign_out);
        local_buffer.message_out(local_message_out);

        Buffer north_buffer("north_buffer");

        north_buffer.x_in(north_x_in);
        north_buffer.y_in(north_y_in);
        north_buffer.x_sign_in(north_x_sign_in);
        north_buffer.y_sign_in(north_y_sign_in);
        north_buffer.message_in(north_message_in);
        
        north_buffer.read_(north_read);
        north_buffer.write_(north_write);
        
        north_buffer.is_full(north_buffer_full);
        
        north_buffer.x_out(north_x_out);
        north_buffer.y_out(north_y_out);
        north_buffer.x_sign_out(north_x_sign_out);
        north_buffer.y_sign_out(north_y_sign_out);
        north_buffer.message_out(north_message_out);
        
        Buffer south_buffer("south_buffer");

        south_buffer.x_in(south_x_in);
        south_buffer.y_in(south_y_in);
        south_buffer.x_sign_in(south_x_sign_in);
        south_buffer.y_sign_in(south_y_sign_in);
        south_buffer.message_in(south_message_in);
        
        south_buffer.read_(south_read);
        south_buffer.write_(south_write);
        
        south_buffer.is_full(south_buffer_full);
        
        south_buffer.x_out(south_x_out);
        south_buffer.y_out(south_y_out);
        south_buffer.x_sign_out(south_x_sign_out);
        south_buffer.y_sign_out(south_y_sign_out);
        south_buffer.message_out(south_message_out);
        
        Buffer east_buffer("east_buffer");
        
        east_buffer.x_in(east_x_in);
        east_buffer.y_in(east_y_in);
        east_buffer.x_sign_in(east_x_sign_in);
        east_buffer.y_sign_in(east_y_sign_in);
        east_buffer.message_in(east_message_in);
        
        east_buffer.read_(east_read);
        east_buffer.write_(east_write);
        
        east_buffer.is_full(east_buffer_full);
        
        east_buffer.x_out(east_x_out);
        east_buffer.y_out(east_y_out);
        east_buffer.x_sign_out(east_x_sign_out);
        east_buffer.y_sign_out(east_y_sign_out);
        east_buffer.message_out(east_message_out);
        
        Buffer west_buffer("west_buffer");
        
        west_buffer.x_in(west_x_in);
        west_buffer.y_in(west_y_in);
        west_buffer.x_sign_in(west_x_sign_in);
        west_buffer.y_sign_in(west_y_sign_in);
        west_buffer.message_in(west_message_in);
        
        west_buffer.read_(west_read);
        west_buffer.write_(west_write);
        
        west_buffer.is_full(west_buffer_full);
        
        west_buffer.x_out(west_x_out);
        west_buffer.y_out(west_y_out);
        west_buffer.x_sign_out(west_x_sign_out);
        west_buffer.y_sign_out(west_y_sign_out);
        west_buffer.message_out(west_message_out);
    }

    void init_routers_xy(){

        RoutingXY local_routing("local_routing");

        local_routing.x_in(local_x_in);
        local_routing.y_in(local_y_in);
        local_routing.x_sign_in(local_x_sign_in);
        local_routing.y_sign_in(local_y_sign_in);
        
        local_routing.direction(local_direction);
        
        local_routing.do_operation(local_buffer_full);
        
        RoutingXY north_routing("north_routing");
        
        north_routing.x_in(north_x_out);
        north_routing.y_in(north_y_out);
        north_routing.x_sign_in(north_x_sign_out);
        north_routing.y_sign_in(north_y_sign_out);
        
        north_routing.direction(north_direction);
        
        
        RoutingXY south_routing("south_routing");
        south_routing.x_in(south_x_out);
        south_routing.y_in(south_y_out);
        south_routing.x_sign_in(south_x_sign_out);
        south_routing.y_sign_in(south_y_sign_out);
        south_routing.direction(south_direction);
        
        RoutingXY east_routing("east_routing");
        east_routing.x_in(east_x_out);
        east_routing.y_in(east_y_out);
        east_routing.x_sign_in(east_x_sign_out);
        east_routing.y_sign_in(east_y_sign_out);
        east_routing.direction(east_direction);
        
        RoutingXY west_routing("west_routing");
        west_routing.x_in(west_x_out);
        west_routing.y_in(west_y_out);
        west_routing.x_sign_in(west_x_sign_out);
        west_routing.y_sign_in(west_y_sign_out);
        west_routing.direction(west_direction);
    }

    void init_arbitrations(){
        Arbitration local_arbitration("local_arbitration");
        local_arbitration.local_channel(north_to_local);
        local_arbitration.north_channel(north_to_local);
        local_arbitration.south_channel(south_to_local);
        local_arbitration.east_channel(east_to_local);
        local_arbitration.west_channel(west_to_local);
        local_arbitration.request_shipping(local_arbitration_ship);
        local_arbitration.chosen_channel(local_arbitration_chosen);
        
        Arbitration north_arbitration("north_arbitration");
        north_arbitration.north_channel(local_to_north);
        north_arbitration.local_channel(local_to_north);
        north_arbitration.south_channel(south_to_north);
        north_arbitration.east_channel(east_to_north);
        north_arbitration.west_channel(west_to_north);
        north_arbitration.request_shipping(north_arbitration_ship);
        north_arbitration.chosen_channel(north_arbitration_chosen);
        
        Arbitration south_arbitration("south_arbitration");
        south_arbitration.south_channel(local_to_south);
        south_arbitration.local_channel(local_to_south);
        south_arbitration.north_channel(north_to_south);
        south_arbitration.east_channel(east_to_south);
        south_arbitration.west_channel(west_to_south);
        south_arbitration.request_shipping(south_arbitration_ship);
        south_arbitration.chosen_channel(south_arbitration_chosen);
        
        Arbitration east_arbitration("east_arbitration");
        east_arbitration.east_channel(local_to_east);
        east_arbitration.local_channel(local_to_east);
        east_arbitration.north_channel(north_to_east);
        east_arbitration.south_channel(south_to_east);
        east_arbitration.west_channel(west_to_east);
        east_arbitration.request_shipping(east_arbitration_ship);
        east_arbitration.chosen_channel(east_arbitration_chosen);
        
        Arbitration west_arbitration("west_arbitration");
        west_arbitration.west_channel(local_to_west);
        west_arbitration.local_channel(local_to_west);
        west_arbitration.north_channel(north_to_west);
        west_arbitration.south_channel(south_to_west);
        west_arbitration.east_channel(east_to_west);
        west_arbitration.request_shipping(west_arbitration_ship);
        west_arbitration.chosen_channel(west_arbitration_chosen);
    }

    void init_handshakes_in(){
        HandshakeIN handshakein_local("local_handshakein");
        handshakein_local.request_to_receive(local_request_to_receive);
        handshakein_local.buffer_is_full(local_buffer_full);
        handshakein_local.can_receive(local_can_receive);
        
        HandshakeIN handshakein_north("north_handshakein");
        handshakein_north.request_to_receive(north_request_to_receive);
        handshakein_north.buffer_is_full(north_buffer_full);
        handshakein_north.can_receive(north_can_receive);
        
        HandshakeIN handshakein_south("south_handshakein");
        handshakein_south.request_to_receive(south_request_to_receive);
        handshakein_south.buffer_is_full(south_buffer_full);
        handshakein_south.can_receive(south_can_receive);
        
        HandshakeIN handshakein_west("west_handshakein");
        handshakein_west.request_to_receive(west_request_to_receive);
        handshakein_west.buffer_is_full(west_buffer_full);
        handshakein_west.can_receive(west_can_receive);
        
        HandshakeIN handshakein_east("east_handshakein");
        handshakein_east.request_to_receive(east_request_to_receive);
        handshakein_east.buffer_is_full(east_buffer_full);
        handshakein_east.can_receive(east_can_receive);
    }

    void init_handshakes_out(){
        HandshakeOUT north_out("north_out");
        north_out.request_to_shipping(north_arbitration_ship);
        north_out.can_ship(north_arbitration_ship);
        north_out.shipping_request(north_shipping_request);
        
        HandshakeOUT south_out("south_out");
        south_out.request_to_shipping(south_arbitration_ship);
        south_out.can_ship(south_arbitration_ship);
        south_out.shipping_request(south_shipping_request);
        
        HandshakeOUT west_out("west_out");
        west_out.request_to_shipping(west_arbitration_ship);
        west_out.can_ship(west_arbitration_ship);
        west_out.shipping_request(west_shipping_request);
        
        HandshakeOUT east_out("east_out");
        east_out.request_to_shipping(east_arbitration_ship);
        east_out.can_ship(east_arbitration_ship);
        east_out.shipping_request(east_shipping_request);
    }

    SC_CTOR(Router) {
        initialize();
    }

};

#endif