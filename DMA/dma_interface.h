#ifndef dma_interface_H
#define dma_interface_H
#include <systemc.h>
//I define the virtual interface from which the channel will inherit;


class dma_interface: virtual public sc_interface {
 public:
  virtual void burstWrite(int destAddress, int numBytes, sc_lv<8> *data ) = 0;
  virtual void burstRead(int sourceAddress, int numBytes, sc_lv<8>* data) = 0;
};
#endif
