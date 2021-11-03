#include <systemc.h>
#include "LDTU_BS.h"

void LDTU_BS::Synch01(){

  //reset
  if(rst_b.read()==0) d_g01.write(0);
  //process
  else d_g01.write(DATA12_g01.read());


}


void LDTU_BS::Synch10(){

  //reset
  if(rst_b.read()==0) d_g10.write(0);
  //process
   else d_g10.write(DATA12_g10.read() >> shift_gain_10.read());

}



void LDTU_BS::BS10(){

  //reset
  if (rst_b.read()==0) DATA_gain_10.write(0);
  //process
  else
    DATA_gain_10.write(( sc_int<13> )d_g10.read() - ( sc_int<13> )BSL_VAL_g10.read());
}


void LDTU_BS::BS01(){
  //reset
  if (rst_b.read()==0) DATA_gain_01.write(0);
  else DATA_gain_01.write(d_g01.read() - BSL_VAL_g01.read());

}
