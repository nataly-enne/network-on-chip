#include "systemc.h"

SC_MODULE(Testbench) {

    sc_in<bool> clk;
    sc_out<sc_uint<2>> x, y;
    sc_out<bool> x_sign, y_sign;
    sc_out<sc_uint<32>> message;
    sc_out<bool> read_;

    void do_tb() {

        x.write(2);
        x_sign.write(1);
        y.write(0);
        y_sign.write(0);
        message.write (10);
        read_.write(1);

        wait();

    }

    SC_CTOR(Testbench) {
        SC_THREAD(do_tb);
        sensitive << clk.pos();
    }

};