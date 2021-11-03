#include <systemc.h>
using namespace sc_core;
//1 less wrt to verilog: the RTL design in verilog has assign statement a bit different from what we have here.
#define RefSample 2
#define RefSample2  8

SC_MODULE(LDTU_iFIFO) {
  ///////////////////////////////////
  //inputs:
  ///////////////////////////////////
  sc_in<bool>  DCLK_1;
  sc_in<bool>  DCLK_10;
  sc_in<bool>  CLK;
  sc_in<bool>  rst_b;
  sc_in< sc_uint<2> > GAIN_SEL_MODE;
  sc_in< sc_uint<12> > DATA_gain_01;
  sc_in< sc_uint<12> > DATA_gain_10;
  sc_in< sc_uint<12> > SATURATION_value;
  sc_in< sc_uint<2> > shift_gain_10;
  ///////////////////////////////////
  //outputs:
  ///////////////////////////////////
  sc_out< sc_uint<13> > DATA_to_enc;
  sc_out< bool > baseline_flag;

  sc_uint<12>  FIFO_H[16];
  sc_uint<12>  FIFO_L[16];
  void Shift();
  void IncreaseFifoWRH();
  void IncreaseFifoWRL();
  void IncreaseFifoRD();
  void WriteFifoH();
  void WriteFifoL();
  void GainSelectionWin8();
  void GainSelectionWin16();

//Data members to "speak" between two different processes must be signals,
//otherwise possible orter problem
  sc_signal< sc_uint< 4 > >  wrH_ptr;
  sc_signal< sc_uint< 4 > >  wrL_ptr;
  sc_signal< sc_uint< 4 > >  rd_ptr;
  sc_signal< sc_uint< 4 > >  ref_ptr;
  sc_signal< sc_uint< 12 > > SATval;

  sc_uint<8>     gain_sel;
  sc_uint<16>    gain_sel2;
  sc_uint<1>     ref_sat;
  sc_uint<12>    dout_g1;
  sc_uint<12>    dout_g10;
  sc_uint<13>    d2enc;
  sc_uint<12>    FIFO_g10_ref;

  bool decision1;
  bool decision2;

  void SetRef() { // inline definition

     ////FIFO OUTPUTS:
     FIFO_g10_ref = FIFO_H[ref_ptr.read()];
     dout_g1      = FIFO_L[rd_ptr.read()];
     dout_g10     = FIFO_H[rd_ptr.read()];
     //works as assign
     ref_sat = (  (FIFO_g10_ref >= SATval) ? 1 : 0 );
     if(GAIN_SEL_MODE.read()==0) gain_sel = (gain_sel <<1 | ref_sat);
     else  gain_sel = 0;
     if(GAIN_SEL_MODE.read()==1) gain_sel2 = (gain_sel2 <<1 | ref_sat);
     else gain_sel2 = 0;

     if(gain_sel == 0) decision1 = 1;
     else decision1 = 0;

     if(gain_sel2 == 0) decision2 = 1;
     else decision2 = 0;

     d2enc = (decision1 && decision2) ? (0,dout_g10) : (1,dout_g1);
     if(d2enc.range(12,6)==0) baseline_flag.write(1);
     else baseline_flag.write(0);
     DATA_to_enc.write(d2enc);
  }

  //Process definition
  SC_CTOR(LDTU_iFIFO){

    SC_METHOD(Shift);
    sensitive_pos<<DCLK_10;
    sensitive_neg<<rst_b;

    SC_METHOD(IncreaseFifoWRL);
    sensitive_pos<<DCLK_1;
    sensitive_neg<<rst_b;

    SC_METHOD(IncreaseFifoWRH);
    sensitive_pos<<DCLK_10;
    sensitive_neg<<rst_b;

    SC_METHOD(IncreaseFifoRD);
    sensitive_pos<<CLK;
    sensitive_neg<<rst_b;

    SC_METHOD(WriteFifoH);
    sensitive_pos<<DCLK_10;
    sensitive_neg<<rst_b;

    SC_METHOD(WriteFifoL);
    sensitive_pos<<DCLK_1;
    sensitive_neg<<rst_b;
/*
    SC_METHOD(GainSelectionWin8);
    sensitive_pos<<CLK;
    sensitive_neg<<rst_b;

    SC_METHOD(GainSelectionWin16);
    sensitive_pos<<CLK;
    sensitive_neg<<rst_b;
*/
    SC_METHOD(SetRef);
    sensitive_pos<<CLK;
    sensitive_neg<<rst_b;

  }

};
