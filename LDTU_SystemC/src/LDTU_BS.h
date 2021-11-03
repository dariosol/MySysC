SC_MODULE(LDTU_BS) {
  //inputs:
  sc_in<bool> DCLK_1;
  sc_in<bool>  DCLK_10;
  sc_in<bool>  rst_b;
  sc_in< sc_uint<12> > DATA12_g01;
  sc_in< sc_uint<12> > DATA12_g10;
  sc_in< sc_uint<2> > shift_gain_10;
  sc_in< sc_uint<8> > BSL_VAL_g01;
  sc_in< sc_uint<8> >BSL_VAL_g10;
  //outputs:
  sc_out< sc_uint<12> > DATA_gain_01;
  sc_out< sc_uint<12> >  DATA_gain_10;


//signals
  sc_signal< sc_uint<12> > d_g10;
  sc_signal< sc_uint<12> > d_g01;
//variables
  sc_uint<12> d_g10_shifted;

  //function definition
  void Synch01();
  void Synch10();
  void Shift();
  void BS10();
  void BS01();



  //Process definition
  SC_CTOR(LDTU_BS){
    SC_METHOD(Synch01);
    sensitive_pos<<DCLK_1;
    sensitive_neg<<rst_b;

    SC_METHOD(Synch10);
    sensitive_pos<<DCLK_10;
    sensitive_neg<<rst_b;

    SC_METHOD(BS10);
    sensitive_pos<<DCLK_10;
    sensitive_neg<<rst_b;

    SC_METHOD(BS01);
    sensitive_pos<<DCLK_1;
    sensitive_neg<<rst_b;
  }

};
