#include <systemc.h>

SC_MODULE(Delay_enc) {
  //inputs:
  sc_in< bool > CLK;
  sc_in< bool > rst_b;
  sc_in< sc_uint<13> > D;
  sc_out <sc_uint<13> > Dd;

  void delay() {
    if(CLK.read()==1) {
      if(rst_b==0) Dd=0;
      else Dd=D;
    }
  }

  //Process definition
  SC_CTOR(Delay_enc) {
    SC_METHOD(delay);
    sensitive_pos<<CLK;
    sensitive_neg<<rst_b;

  }

};
