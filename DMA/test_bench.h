#include <systemc.h>
//#include "dma_interface.h"
#include "dma_channel.h"

class test_bench: public sc_module {
 public:

  //The port of this module is the DMA interface:
  sc_port<dma_channel> master_port;
  //It works also like (don't know why):
  //  sc_port<dma_interface> master_port;

  //This is a function to inject/read data from the DMA
  void stimuli() {
    sc_lv<8> data_sent[12] = {20, 21, 22, 23, 24, 25,26,27,28,29,30,31};
    sc_lv<8> data_rcv[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    cout<<"Writing data to the memory through DMA"<<endl;
    master_port->burstWrite(100, 12, data_sent);
    wait(100, SC_NS);
    cout<<"Reading data from the memory through DMA"<<endl;
    master_port->burstRead(100, 12, data_rcv);
    
    //consistency check:
    for (int i=0; i<10; i++) {
      if (data_sent[i] != data_rcv[i]) {
	cout << data_sent[i] << " "<< data_rcv[i] << endl;
	cout<<"data mismatch"<<endl;
      }
    }
  }

  SC_HAS_PROCESS(test_bench);
  
  //constructor: 
 test_bench(sc_module_name nm): sc_module(nm) {
    SC_THREAD(stimuli);
  }
};
