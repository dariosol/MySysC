#include "systemc.h"

class rtl_memory: public sc_module {
 public:
  sc_in_rv<16> address_p;
  sc_inout_rv<8> data_p;
  sc_in_resolved rw_p;
  sc_lv<8> *mem_arr;

  void run() { // sensitive rw_p
  
    while(true) {
      // read cycle
      if (rw_p->read() == SC_LOGIC_1) {
	data_p->write( *( mem_arr + (sc_uint<16>(address_p->read())) ) );
      } 
	// write cycle
      else if (rw_p->read() == SC_LOGIC_0) {
	*(mem_arr + (sc_uint<16>(address_p->read()))) = data_p->read();
      }
      wait();
    }
  }

  SC_HAS_PROCESS(rtl_memory);

 rtl_memory(sc_module_name nm, int mem_size = 100): sc_module(nm) {

    mem_arr = new sc_lv<8>[mem_size];

    for (int i=0; i< mem_size; i++) {
      mem_arr[i] = sc_lv<8>(0);
    }

    SC_THREAD(run);
    sensitive << rw_p;
  }

  ~rtl_memory() { 
    delete []mem_arr; 
  } 

};
