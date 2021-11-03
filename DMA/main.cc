#include "systemc.h"
#include "test_bench.h"
#include "rtl_memory.h"
#include "dma_channel.h"

// Main program
int sc_main(int argc, char* argv[]) {

  sc_set_time_resolution(1, SC_NS);
   
  sc_signal_rv<16> address_s;
  sc_signal_rv<8> data_s;
  sc_signal_resolved rw_s;
   
  test_bench tb("tb");
  dma_channel transactor("transactor");
  rtl_memory uut("uut", 1000);
   
  tb.master_port(transactor);

  transactor.data_p(data_s);
  transactor.rw_p(rw_s);
  transactor.address_p(address_s);

  uut.address_p(address_s);
  uut.data_p(data_s);
  uut.rw_p(rw_s);
  
  sc_start();
  return 0;
}

