#ifndef dma_channel_H
#define dma_channel_H
#include "tlm.h"
#include <systemc.h>
#include "dma_interface.h"

class dma_channel: public dma_interface, public sc_channel {
 public:
  sc_out_rv<16> address_p;
  sc_inout_rv<8> data_p;
  sc_out_resolved rw_p;
 
 //constructor:
 dma_channel(sc_module_name nm): sc_channel(nm)
    ,address_p("address_p")
    ,data_p("data_p")
    ,rw_p("rw_p")
    { }

virtual void burstWrite( int destAddress, int numBytes, sc_lv<8> *data );
virtual void burstRead(int sourceAddress, int numBytes, sc_lv<8>* data);
};
#endif
