// Function : This is a 4 bit up-counter with
 // Synchronous active high reset and
 // with active high enable signal

#include "systemc.h"

SC_MODULE(counter) {
  //PORTS
  sc_in_clk clk;
  sc_in<bool> reset;
  sc_in<bool> enable;
  sc_out< sc_uint<4> > counter_out;

  //LOCAL VAR
  sc_uint<4> count;

  //BEGIN
  // At every rising edge of clock we check if reset is active
  // If active, we load the counter output with 4'b0000
  void incr_count () {
    if(reset.read()==1) {
      count =0;
      counter_out.write(count);
    }
    else if (enable.read() == 1) {
      count = count +1;
      counter_out.write(count);
      cout<<"@" << sc_time_stamp() <<" :: Incremented Counter "<<counter_out.read()<<endl;
    }
    else {
      count = count;
    }
  }

  SC_CTOR(counter) {
    cout<<"Executing new"<<endl;
    SC_METHOD(incr_count);
    sensitive << reset;
    sensitive << clk.pos();
  } // End of Constructor

};

  
