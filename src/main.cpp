#include<stdio.h>

#include "systemc.h"

#include "../include/router.h"
#include "../include/testbench.h"

int sc_main(int argc, char* argv[]) {

    std::cout << "Criando sinais...";

    // Canal local.
    sc_signal<sc_uint<2>> local_x_in, local_y_in; // Valores X e Y de entrada.
    sc_signal<bool> local_x_sign_in, local_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> local_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> local_x_out, local_y_out; // Valores X e Y de saída.
    sc_signal<bool> local_x_sign_out, local_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> local_message_out; // Mensagem de saída.
    sc_signal<bool> local_read, local_write; // Sinais para indicar que o canal local tem que ler da entrada ou escrever na saída.

    // Canal norte.
    sc_signal<sc_uint<2>> north_x_in, north_y_in; // Valores X e Y de entrada.
    sc_signal<bool> north_x_sign_in, north_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> north_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> north_x_out, north_y_out; // Valores X e Y de saída.
    sc_signal<bool> north_x_sign_out, north_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> north_message_out; // Mensagem de saída.
    sc_signal<bool> north_read, north_write; // Sinais para indicar que o canal norte tem que ler da entrada ou escrever na saída.

    // Canal sul.
    sc_signal<sc_uint<2>> south_x_in, south_y_in; // Valores X e Y de entrada.
    sc_signal<bool> south_x_sign_in, south_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> south_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> south_x_out, south_y_out; // Valores X e Y de saída.
    sc_signal<bool> south_x_sign_out, south_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> south_message_out; // Mensagem de saída.
    sc_signal<bool> south_read, south_write; // Sinais para indicar que o canal sul tem que ler da entrada ou escrever na saída.

    // Canal leste.
    sc_signal<sc_uint<2>> east_x_in, east_y_in; // Valores X e Y de entrada.
    sc_signal<bool> east_x_sign_in, east_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> east_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> east_x_out, east_y_out; // Valores X e Y de saída.
    sc_signal<bool> east_x_sign_out, east_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> east_message_out; // Mensagem de saída.
    sc_signal<bool> east_read, east_write; // Sinais para indicar que o canal leste tem que ler da entrada ou escrever na saída.

    // Canal oeste.
    sc_signal<sc_uint<2>> west_x_in, west_y_in; // Valores X e Y de entrada.
    sc_signal<bool> west_x_sign_in, west_y_sign_in; // Sinais de X e Y de entrada. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> west_message_in; // Mensagem de entrada.
    sc_signal<sc_uint<2>> west_x_out, west_y_out; // Valores X e Y de saída.
    sc_signal<bool> west_x_sign_out, west_y_sign_out; // Sinais de X e Y de saída. 0 - negativo; 1 - positivo.
    sc_signal<sc_uint<32>> west_message_out; // Mensagem de saída.
    sc_signal<bool> west_read, west_write; // Sinais para indicar que o canal oeste tem que ler da entrada ou escrever na saída.

    std::cout << " Inicializando clock...";

    sc_clock clk("clk", 10, SC_NS, 0.5);

    std::cout << " Criando módulo do roteador...";

    Router router("router");

    router.local_x_in(local_x_in);
    router.local_y_in(local_y_in);
    router.local_x_sign_in(local_x_sign_in);
    router.local_y_sign_in(local_y_sign_in);
    router.local_message_in(local_message_in);

    router.local_x_out(local_x_out);
    router.local_y_out(local_y_out);
    router.local_x_sign_out(local_x_sign_out);
    router.local_y_sign_out(local_y_sign_out);
    router.local_message_out(local_message_out);

    router.local_read(local_read);
    router.local_write(local_write);

    router.north_x_in(south_x_out);
    router.north_y_in(south_y_out);
    router.north_x_sign_in(south_x_sign_out);
    router.north_y_sign_in(south_y_sign_out);
    router.north_message_in(south_message_out);

    router.north_x_out(south_x_in);
    router.north_y_out(south_y_in);
    router.north_x_sign_out(south_x_sign_in);
    router.north_y_sign_out(south_y_sign_in);
    router.north_message_out(south_message_in);

    router.north_read(north_read);
    router.north_write(north_write);

    router.south_x_in(north_x_out);
    router.south_y_in(north_y_out);
    router.south_x_sign_in(north_x_sign_out);
    router.south_y_sign_in(north_y_sign_out);
    router.south_message_in(north_message_out);

    router.south_x_out(north_x_in);
    router.south_y_out(north_y_in);
    router.south_x_sign_out(north_x_sign_in);
    router.south_y_sign_out(north_y_sign_in);
    router.south_message_out(north_message_in);

    router.south_read(south_read);
    router.south_write(south_write);

    router.east_x_in(west_x_out);
    router.east_y_in(west_y_out);
    router.east_x_sign_in(west_x_sign_out);
    router.east_y_sign_in(west_y_sign_out);
    router.east_message_in(west_message_out);

    router.east_x_out(west_x_in);
    router.east_y_out(west_y_in);
    router.east_x_sign_out(west_x_sign_in);
    router.east_y_sign_out(west_y_sign_in);
    router.east_message_out(west_message_in);

    router.east_read(east_read);
    router.east_write(east_write);

    router.west_x_in(east_x_out);
    router.west_y_in(east_y_out);
    router.west_x_sign_in(east_x_sign_out);
    router.west_y_sign_in(east_y_sign_out);
    router.west_message_in(east_message_out);

    router.west_x_out(east_x_in);
    router.west_y_out(east_y_in);
    router.west_x_sign_out(east_x_sign_in);
    router.west_y_sign_out(east_y_sign_in);
    router.west_message_out(east_message_in);

    router.west_read(west_read);
    router.west_write(west_write);

    std::cout << " Criando testbench...";

    Testbench testbench("testbench");
    testbench.clk(clk);
    testbench.x(local_x_in);
    testbench.y(local_y_in);
    testbench.x_sign(local_x_sign_in);
    testbench.y_sign(local_y_sign_in);
    testbench.message(local_message_in);
    testbench.read_(local_read);

    std::cout << " ---------- Início da simulação ---------- \n";

    sc_start();

    return 0;
}