#include <systemc.h>
#include "StateDefinition.h"
#include "Delay_enc.h"

SC_MODULE(LDTU_FSM) {
  //inputs:
  sc_in< bool > CLK;
  sc_in< bool > rst_b;
  sc_in< bool > Orbit;
  sc_in< bool > baseline_flag;
  sc_in< sc_uint<13> > DATA_to_enc;
  //outputs:
  sc_signal< State > Current_state;
  sc_signal< State > Next_state;

  sc_signal<sc_uint<6> > 	 Ld_bas_1;
  sc_signal<sc_uint<6> > 	 Ld_bas_2;
  sc_signal<sc_uint<6> > 	 Ld_bas_3;
  sc_signal<sc_uint<6> > 	 Ld_bas_4;
  sc_signal<sc_uint<6> > 	 Ld_bas_5;
  sc_signal<sc_uint<13> >  Ld_sign_1;
  sc_signal<sc_uint<13> >  Ld_sign_2;
  sc_signal<sc_uint<32> >  rDATA_32;
  sc_signal<bool>	 rLoad;
  sc_signal<sc_uint<13> >  dDATA_to_enc;

  void update_state();
  void fsm();
  void encoder();
  Delay_enc * Delay;


  //Process definition
  SC_CTOR(LDTU_FSM) {
    Delay = new Delay_enc("Delay");
    Delay->CLK(CLK);
    Delay->rst_b(rst_b);
    Delay->D(DATA_to_enc);
    Delay->Dd(dDATA_to_enc);

    SC_METHOD(update_state);
    sensitive_pos<<CLK;
    sensitive_neg<<rst_b;
    SC_METHOD(fsm);
    sensitive<<Current_state<<Orbit<<baseline_flag;
    SC_METHOD(encoder);
    sensitive<<CLK;
    sensitive_neg<<rst_b;

  }

};
