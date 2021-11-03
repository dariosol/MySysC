SC_MODULE(LDTU_BS) {
  //inputs:
  sc_in<bool> DCLK_1;
  sc_in<bool>  DCLK_10;
  sc_in<bool>  rst_b;
  sc_in<sc_uint<12>>  DATA12_g01;
  sc_in<sc_uint<12>>  DATA12_g10;
  sc_in<sc_uint<2>>  shift_gain_10;
  sc_in<sc_uint<8>> BSL_VAL_g01;
  sc_in<sc_uint<8>>BSL_VAL_g10;
  //outputs:
  sc_out<sc_uint<12>> DATA_gain_01;
  sc_out<sc_uint<12>>  DATA_gain_10;
  sc_out<bool>  SeuError;

    //variables
  sc_unit<12> d_g10;
  sc_unit<12> d_g10_shifted;
  sc_unit<12> d_g01;
  
  //function definition
  void Synch01();
  void Synch10();
  void Shift();
  void BS10();
  void BS01();


  
  //Process definition
  SC_CTOR(LDTU_BS){
    SC_CTHREAD(Synch01, DCLK_1.pos());
    reset_signal_is(rst_b,false);
    SC_CTHREAD(Synch10, DCLK_10.pos());
    reset_signal_is(rst_b,false);
    SC_CTHREAD(Shift(), DCLK_10.pos());
    reset_signal_is(rst_b,false);
    SC_CTHREAD(BS10(), DCLK_10.pos());
    reset_signal_is(rst_b,false);
    SC_CTHREAD(BS01(), DCLK_1.pos());
    reset_signal_is(rst_b,false);
  }

};
