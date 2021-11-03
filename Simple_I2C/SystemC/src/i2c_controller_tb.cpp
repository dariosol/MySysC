#include <systemc.h>

#include <i2c_controller_tb.h>

void i2c_controller_tb::stimuli()
{
    rst = 1;
    
    wait(100, SC_NS);
    rst = 0;

    addr = 41;
    data_in = 10;
    rw = 0;
    enable = 1;    

    wait(10, SC_NS);
    enable = 0;

    wait(300, SC_NS);
    
    addr = 42;
    data_in = 170;
    rw = 0;
    enable = 1;

    wait(10, SC_NS);
    enable = 0;
    
    ////READ:
    /*
    wait(500, SC_NS);
    addr = 43;
    rw = 1;
    enable = 1;
    
    wait(10, SC_NS);
    enable = 0;
    */
}
