#include "systemc.h"
#include <fstream>
#include "LDTU_BS.h"
#include "LDTU_iFIFO.h"
#include "LDTU_FSM.h"

const double CLOCK_PERIOD = 6.25; //160 MHz

int sc_main (int argc, char* argv[]) {
  sc_signal<bool>   DCLK_10;
  sc_signal<bool>   DCLK_1;
  sc_signal<bool>   CLK;
  sc_signal<bool>   rst_b;
  sc_signal< sc_uint<12> >  DATA12_g01;
  sc_signal< sc_uint<12> >  DATA12_g10;
  sc_signal< sc_uint<12> > DATA_gain_01;
  sc_signal< sc_uint<12> > DATA_gain_10;
  sc_signal< sc_uint<2> > shift_gain_10;
  sc_signal< sc_uint<8> > BSL_VAL_g01;
  sc_signal< sc_uint<8> > BSL_VAL_g10;
  std::unique_ptr<LDTU_BS> BaselineSubtractor(new LDTU_BS("LDTU_BS"));
  BaselineSubtractor -> DCLK_10(DCLK_10);
  BaselineSubtractor -> DCLK_1(DCLK_1);
  BaselineSubtractor -> rst_b(rst_b);
  BaselineSubtractor -> DATA12_g01(DATA12_g01);
  BaselineSubtractor -> DATA12_g10(DATA12_g10);
  BaselineSubtractor -> shift_gain_10(shift_gain_10);
  BaselineSubtractor -> BSL_VAL_g01(BSL_VAL_g01);
  BaselineSubtractor -> BSL_VAL_g10(BSL_VAL_g10);
  BaselineSubtractor -> DATA_gain_01(DATA_gain_01);
  BaselineSubtractor -> DATA_gain_10(DATA_gain_10);
  /////////////////////////////////////////////

  sc_signal < sc_uint<13> >   DATA_to_enc;
  sc_signal <bool>            baseline_flag;
  sc_signal < sc_uint<12> >   SATURATION_value;
  sc_signal < sc_uint<2> >    GAIN_SEL_MODE;

  std::unique_ptr<LDTU_iFIFO> iFIFO (new LDTU_iFIFO("iFIFO"));
  //inputs
  iFIFO -> DCLK_1(DCLK_1);
  iFIFO -> DCLK_10(DCLK_10);
  iFIFO -> CLK(CLK);
  iFIFO -> rst_b(rst_b);
  iFIFO -> GAIN_SEL_MODE(GAIN_SEL_MODE);
  iFIFO -> DATA_gain_01(DATA_gain_01);
  iFIFO -> DATA_gain_10(DATA_gain_10);
  iFIFO -> SATURATION_value(SATURATION_value);
  iFIFO -> shift_gain_10(shift_gain_10);
  //outputs
  iFIFO -> DATA_to_enc(DATA_to_enc);
  iFIFO -> baseline_flag(baseline_flag);

  std::unique_ptr<LDTU_FSM> FSM (new LDTU_FSM("FSM"));
  sc_signal < bool > Orbit;

  //inputs
  FSM -> CLK(CLK);
  FSM -> rst_b(rst_b);
  FSM -> Orbit(Orbit);
  FSM -> DATA_to_enc(DATA_to_enc);
  FSM -> baseline_flag(baseline_flag);
  //outputs

//////////////////////////////////////////
//Stimulus
  std::ifstream infile10("datain/d_ERan2000DistanceRan10_g10_new.dat");
  std::ifstream infile01("datain/d_ERan2000DistanceRan10_g01_new.dat");
  std::string line10;
  std::string line01;



  sc_core::sc_start(CLOCK_PERIOD/2,SC_NS);

  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("BS_wave");
  // Dump the desired signals
  sc_trace(wf, DCLK_10, "DCLK_10");
  sc_trace(wf, DCLK_1, "DCLK_1");
  sc_trace(wf, rst_b, "rst_b");
  sc_trace(wf, DATA12_g01, "DATA12_g01");
  sc_trace(wf, DATA12_g10, "DATA12_g10");
  sc_trace(wf,BaselineSubtractor->d_g01,"d_g01");

  sc_trace(wf, DATA_gain_01, "DATA_gain_01");
  sc_trace(wf, DATA_gain_10, "DATA_gain_10");

  sc_trace(wf,iFIFO->wrH_ptr,"iFIFO_wrH_ptr");
  sc_trace(wf,iFIFO->rd_ptr,"iFIFO_rd_ptr");
  sc_trace(wf,iFIFO->ref_ptr,"iFIFO_ref_ptr");
  sc_trace(wf,iFIFO->FIFO_g10_ref,"iFIFO_FIFO_g10_ref");
  sc_trace(wf,iFIFO->ref_sat,"iFIFO_ref_sat");
  sc_trace(wf,iFIFO->decision1,"iFIFO_decision1");
  sc_trace(wf,iFIFO->decision2,"iFIFO_decision2");
  sc_trace(wf,iFIFO->gain_sel,"iFIFO_gain_sel");
  sc_trace(wf,iFIFO->gain_sel2,"iFIFO_gain_sel2");
  sc_trace(wf,iFIFO->d2enc,"iFIFO_FIFO_d2enc");
  sc_trace(wf,iFIFO->baseline_flag,"iFIFO_baseline_flag");
  sc_trace(wf,FSM->baseline_flag,"FSM_baseline_flag");
  sc_trace(wf,FSM->rLoad,"FSM_Load");
  sc_trace(wf,FSM->rDATA_32,"FSM_rDATA_32");
  sc_trace(wf,iFIFO->FIFO_H[0],"iFIFO_FIFO_H(0)");
  sc_trace(wf,iFIFO->FIFO_H[1],"iFIFO_FIFO_H(1)");
  sc_trace(wf,iFIFO->FIFO_H[2],"iFIFO_FIFO_H(2)");
  sc_trace(wf,iFIFO->FIFO_H[3],"iFIFO_FIFO_H(3)");
  sc_trace(wf,iFIFO->FIFO_H[4],"iFIFO_FIFO_H(4)");
  sc_trace(wf,iFIFO->FIFO_H[5],"iFIFO_FIFO_H(5)");
  sc_trace(wf,iFIFO->FIFO_H[6],"iFIFO_FIFO_H(6)");
  sc_trace(wf,iFIFO->FIFO_H[7],"iFIFO_FIFO_H(7)");
  sc_trace(wf,iFIFO->FIFO_H[8],"iFIFO_FIFO_H(8)");
  sc_trace(wf,iFIFO->FIFO_H[9],"iFIFO_FIFO_H(9)");
  sc_trace(wf,iFIFO->FIFO_H[10],"iFIFO_FIFO_H(10)");
  sc_trace(wf,iFIFO->FIFO_H[11],"iFIFO_FIFO_H(11)");
  sc_trace(wf,iFIFO->FIFO_H[12],"iFIFO_FIFO_H(12)");
  sc_trace(wf,iFIFO->FIFO_H[13],"iFIFO_FIFO_H(13)");
  sc_trace(wf,iFIFO->FIFO_H[14],"iFIFO_FIFO_H(14)");
  sc_trace(wf,iFIFO->FIFO_H[15],"iFIFO_FIFO_H(15)");


  // Initialize all variables
  rst_b= 1;       // initial value of reset
  DATA12_g01       = 0;
  DATA12_g10       = 0;
  shift_gain_10    = 0;
  BSL_VAL_g01      = 0;
  BSL_VAL_g10      = 0;
  SATURATION_value = 0;
  Orbit            = 0;
  GAIN_SEL_MODE=0;
  for (int i=0;i<15;i++) {
    DCLK_10 = 0;
    DCLK_1  = 0;
    CLK     = 0;
    sc_core::sc_start(CLOCK_PERIOD/2,SC_NS);
    DCLK_1  = 1;
    DCLK_10 = 1;
    CLK     = 1;
    sc_core::sc_start(CLOCK_PERIOD/2,SC_NS);
  }
  rst_b= 0;    // Assert the reset
  DATA12_g01=0;
  DATA12_g10=0;
  ////////////////////////////////////////////////////////////////
  cout << "@" << sc_time_stamp() <<" Asserting reset\n" << endl;

  for (int i=0;i<6;i++) {
    DCLK_10 = 0;
    DCLK_1  = 0;
    CLK     = 0;
    sc_core::sc_start(CLOCK_PERIOD/2,SC_NS);
    DCLK_1   = 1;
    DCLK_10  = 1;
    CLK      = 1;
    sc_core::sc_start(CLOCK_PERIOD/2,SC_NS);

  }
  rst_b= 1;
  cout << "@" << sc_time_stamp() <<" De-Asserting reset\n" << endl;
  ////////////////////////////////////////////////////////////////
  DATA12_g01=10;
  DATA12_g10=10;

  GAIN_SEL_MODE=0;
  SATURATION_value=4095;
  while( getline(infile10, line10)) {
    DCLK_10 = 0;
    DCLK_1  = 0;
    CLK     = 0;
    sc_core::sc_start(CLOCK_PERIOD/2,SC_NS);
    DCLK_1  = 1;
    DCLK_10 = 1;
    CLK     = 1;
    getline(infile01, line01);
    DATA12_g10.write(stoi(line10,0,2));
    DATA12_g01.write(stoi(line01,0,2));
    sc_core::sc_start(CLOCK_PERIOD/2,SC_NS);
  }

  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  sc_close_vcd_trace_file(wf);
  return 0;// Terminate simulation
}
