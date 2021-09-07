#!/bin/bash
echo Compilando...

export SYSTEMC_HOME=/usr/local/systemc-2.3.3

g++ -I. -std=c++11 src/main.cpp -o networkonchip -I include/ -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -lsystemc -lm
# g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux -Wl,-rpath=$SYSTEMC_HOME/lib-linux -o hello main.cpp -lsystemc -lm

echo Compilado!