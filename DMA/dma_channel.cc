#include <systemc.h>
#include "dma_channel.h"

void dma_channel::burstWrite( int destAddress, int numBytes, sc_lv<8> *data ) {

  sc_lv<8> *ite = data;
  for (int i=0; i<numBytes; i++) {
    address_p->write(destAddress++);
    data_p->write( *(ite++) );
    wait(10, SC_NS);
    cout<<"Write out " << data_p->read()<<endl;
    rw_p->write(SC_LOGIC_0); // Write pulse
    wait(50, SC_NS);
    rw_p->write(SC_LOGIC_Z);
    address_p->write("ZZZZZZZZZZZZZZZZ");
    data_p->write("ZZZZZZZZ");
    wait(10, SC_NS);
  }
}


void dma_channel::burstRead(int sourceAddress, int numBytes, sc_lv<8>* data) {
 
 for (int i=0; i<numBytes; i++) {
    address_p->write(sourceAddress++);
    wait(10, SC_NS);
    rw_p->write(SC_LOGIC_1); // Read pulse
    wait(10, SC_NS);
    *(data++) = data_p->read();
    cout<<"Data read " << data_p->read() << endl;
    wait(40, SC_NS);
    rw_p->write(SC_LOGIC_Z);
    address_p->write("ZZZZZZZZZZZZZZZZ");
    data_p->write("ZZZZZZZZ");
    wait(10, SC_NS);
  }
}

