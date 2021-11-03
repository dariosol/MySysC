#include <systemc.h>
#include "LDTU_iFIFO.h"


void LDTU_iFIFO::Shift(){

  //reset
  if(rst_b.read()==0) SATval.write(0xfff);
  //process
  else {
    sc_uint<12> tmp = SATURATION_value.read();
    SATval.write(tmp << shift_gain_10.read());
  }
}


void LDTU_iFIFO::IncreaseFifoWRH(){
  //reset
  if(rst_b==0) wrH_ptr.write(0);
  //process
  else {
    wrH_ptr.write(wrH_ptr.read()+1);
  }
}

void LDTU_iFIFO::IncreaseFifoWRL(){
  //reset
  if(rst_b==0) wrL_ptr.write(0);
  //process
  else {
    wrL_ptr.write(wrL_ptr.read()+1);
  }
}

void LDTU_iFIFO::IncreaseFifoRD(){
  //reset
  if(rst_b==0) {
      rd_ptr.write(0x6); //4'b0110
      //ref_ptr.write( (GAIN_SEL_MODE.read() == 1) ? (rd_ptr.read() + RefSample2) : (rd_ptr.read() + RefSample) );
      ref_ptr.write( (GAIN_SEL_MODE.read() == 1) ? (0x6 + RefSample2) : (0x6 + RefSample) );
    }
  //process
  else {
    rd_ptr.write(rd_ptr.read() + 1 );
    ref_ptr.write(ref_ptr.read() + 1 );

  }
}


void LDTU_iFIFO::WriteFifoH(){
  //reset
  if(rst_b==0) {
  printf("RESETTING FIFOH\n");
  for(int i=0;i<15;++i) FIFO_H[i]=0;
  printf("END RESET FIFOH\n");
}
  //process
  else {
    FIFO_H[wrH_ptr.read()] = DATA_gain_10.read();
  }
}


void LDTU_iFIFO::WriteFifoL(){
  //reset
  if(rst_b==0) {
  printf("RESETTING FIFOL\n");
  for(int i=0;i<15;++i) FIFO_L[i]=0;
  printf("END RESET FIFOL\n");
  }
  //process
  else {
    FIFO_L[wrL_ptr.read()] = DATA_gain_01.read();
  }
}

/*
void LDTU_iFIFO::GainSelectionWin8(){
  //reset
  if(rst_b==0) gain_sel.write(0);
  //process
  else {
    if(GAIN_SEL_MODE.read()==0) gain_sel.write((gain_sel.read()<<1 | ref_sat.read()));
    else gain_sel = 0;
  }
}

void LDTU_iFIFO::GainSelectionWin16(){
  //reset
  if(rst_b==0) gain_sel2.write(0);
  //process
  else {
    if(GAIN_SEL_MODE.read()==1) gain_sel2.write((gain_sel2.read()<<1 | ref_sat.read()));
    else gain_sel2.write(0);
  }
}
*/
