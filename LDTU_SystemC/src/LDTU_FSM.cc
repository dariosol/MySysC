#include "LDTU_FSM.h"



void LDTU_FSM::update_state() {

  if(rst_b.read()==0) {
    cout<<"RESET FSM"<<endl;
    Current_state.write(Idle);
  }
  else if(CLK.read()==1) Current_state.write(Next_state);
  else Current_state.write(Current_state);
}

void LDTU_FSM::fsm() {
  switch(Current_state) {
  case Idle:
    if (baseline_flag.read()==1 && Orbit.read()==0) Next_state.write(bas_0);
    else if (Orbit.read() == 1) Next_state.write(header);
    else Next_state.write(sign_0);
    break;

  case bas_0_bis:
    if (baseline_flag.read()==1 && Orbit.read()==0) Next_state.write(sign_0_bis);
    else if(Orbit.read()==1) Next_state.write(bc0_s0_bis);
    else Next_state.write(sign_0);
    break;

  case bas_0:
    if (baseline_flag.read()==1 && Orbit.read()==0) Next_state.write(bas_1);
    else if(Orbit.read()==1) Next_state.write(bc0_1);
    else Next_state.write(bas_1_bis);
    break;

  case bas_1_bis:
    if (baseline_flag.read()==1 && Orbit.read() == 0) Next_state.write(sign_0_bis);
    else if(Orbit.read() == 1) Next_state.write(bc0_s0_bis);
    else Next_state.write(sign_0);
    break;

  case bas_1:
    if (baseline_flag.read()==1 && Orbit.read() == 0) Next_state.write(bas_2);
    else if(Orbit.read() == 1)  Next_state.write(bc0_2);
    else Next_state.write(bas_2_bis);
    break;

  case bas_2_bis : //**********************
    if (baseline_flag.read()==1  && Orbit.read() == 0) Next_state.write(sign_0_bis);
    else if(Orbit.read() == 1) Next_state.write(bc0_s0_bis);
    else  Next_state.write(sign_0);
    break;

  case bas_2 : ///////////////////////////
    if (baseline_flag.read()==1  && Orbit.read() == 0) Next_state.write(bas_3);
    else if(Orbit.read() == 1) Next_state.write(bc0_3);
    else Next_state.write(bas_3_bis);
    break;

  case bas_3_bis : //**********************
    if (baseline_flag.read()==1 && Orbit.read() == 0)  Next_state.write(sign_0_bis);
    else if(Orbit.read() == 1) Next_state.write(bc0_s0_bis);
    else Next_state.write(sign_0);
    break;

  case bas_3 : ////////////////////////////
    if (baseline_flag.read()==1  && Orbit.read() == 0) Next_state.write(bas_4);
    else if(Orbit.read() == 1) Next_state.write(bc0_4);
    else  Next_state.write(bas_4_bis);
    break;

  case bas_4_bis : //**********************
    if (baseline_flag.read()==1  && Orbit.read() == 0) Next_state.write(sign_0_bis);
    else if(Orbit.read() == 1)  Next_state.write(bc0_s0_bis);
    else Next_state.write(sign_0);
    break;

  case bas_4 : /////////////////////////////////
    if (baseline_flag.read()==1  && Orbit.read() == 0) Next_state.write(bas_0);
    else if(Orbit.read() == 1) Next_state.write(bc0_0);
    else Next_state.write(bas_0_bis);
    break;

  case  sign_0_bis: //sssssssssssssssssssssssssssss
    if (baseline_flag.read()==0 && Orbit.read() == 0) Next_state.write(bas_0_bis);
    else if( Orbit == 1) Next_state.write(bc0_0);
    else Next_state.write(bas_0);
    break;

  case sign_0 : //s22222222222222222222222222222222222
    if (baseline_flag.read()==0  && Orbit.read() == 0) Next_state.write(sign_1);
    else if(Orbit.read() == 1) Next_state.write(bc0_s0);
    else  Next_state.write(sign_1_bis);
    break;

  case sign_1_bis : //sssssssssssssssssssssssssssss
    if (baseline_flag.read()==0 && Orbit.read() == 0)  Next_state.write(bas_0_bis);
    else if( Orbit.read() == 1) Next_state.write(bc0_0);
    else  Next_state.write(bas_0);
    break;

  case sign_1: //s11111111111111111111111111111111
    if (baseline_flag.read()==0 && Orbit.read() == 0) Next_state.write(sign_0);
    else if( Orbit.read() == 1) Next_state.write(bc0_s0_bis);
    else Next_state.write(sign_0_bis);
    break;

  case bc0_0:
    if (baseline_flag.read()==0) Next_state.write(header_s0);
    else Next_state.write(header_b0);
    break;

  case bc0_1:
    if (baseline_flag.read()==0) Next_state.write(header_s0);
    else Next_state.write(header_b0);
    break;

  case bc0_2:
    if (baseline_flag.read()==0) Next_state.write(header_s0);
    else Next_state.write(header_b0);
    break;

  case bc0_3:
    if (baseline_flag.read()==0) Next_state.write(header_s0);
    else Next_state.write(header_b0);
    break;

  case bc0_4:
    if (baseline_flag.read()==0) Next_state.write(header_s0);
    else Next_state.write(header_b0);
    break;

  case bc0_s0:
    Next_state.write(header);
    break;

  case bc0_s0_bis:
    if (baseline_flag.read()==0) Next_state.write(header_s0);
    else Next_state.write(header_b0);
    break;

  case header:
    if (baseline_flag.read()==0)  Next_state.write(sign_0);
    else Next_state.write(bas_0);
    break;


  case header_s0:
    if (baseline_flag.read()==0)  Next_state.write(sign_0);
    else  Next_state.write(sign_0_bis);
    break;


  case header_b0:
    if (baseline_flag.read()==0) Next_state.write(bas_0_bis);
    else Next_state.write(bas_0);
    break;

  default : Next_state.write(Idle);
    break;
  }
}

void LDTU_FSM::encoder() {
  sc_uint<32> Initial=0xF0000000;
  sc_uint<6> code_sel_sign1=0xA;
  sc_uint<6> code_sel_sign2=0xB;
  sc_uint<2> code_sel_bas1= 0x1;
  sc_uint<2> code_sel_bas2= 0x2;
  sc_uint<13> sync=0xAAA;
  sc_uint<24> one=0x40000;
  sc_uint<18> two=0x2000;
  sc_uint<12> three=0xc0;
  sc_uint<6> four=0x4;
  sc_uint<32> tmp=0;
  sc_uint<13> dDATA_to_enc_tmp=0;

  if (rst_b.read()==0) {
    Ld_bas_1.write(0);
    Ld_bas_2.write(0);
    Ld_bas_3.write(0);
    Ld_bas_4.write(0);
    Ld_bas_5.write(0);
    Ld_sign_1.write(0);
    Ld_sign_2.write(0);
    rLoad.write(0);
    rDATA_32.write(Initial);
  }
  else if(CLK.read()==1) {
    dDATA_to_enc_tmp=dDATA_to_enc.read();

    switch(Current_state) {

    case Idle:
      rLoad.write(0);
      rDATA_32.write(Initial);
      break;

    case bas_0:
      rLoad.write(0);
      Ld_bas_2.write(dDATA_to_enc_tmp.range(5,0));
      break;

    case bas_0_bis:
      rLoad.write(1);
      tmp = (code_sel_bas2,one,Ld_bas_1.read());
      rDATA_32.write(tmp);
      Ld_sign_1.write(dDATA_to_enc_tmp);
      break;

    case bas_1:
      rLoad.write(0);
      Ld_bas_3.write(dDATA_to_enc_tmp.range(5,0));
      break;

    case bas_1_bis :
      rLoad.write(1);
      tmp=(code_sel_bas2,two,Ld_bas_2,Ld_bas_1);
      rDATA_32.write(tmp);
      Ld_sign_1.write(dDATA_to_enc_tmp);
      break;

    case bas_2 :
      rLoad.write(0);
      Ld_bas_4.write(dDATA_to_enc_tmp.range(5,0));
      break;

    case bas_2_bis :
      rLoad.write(1);
      tmp = (code_sel_bas2,three,Ld_bas_3,Ld_bas_2,Ld_bas_1);
      rDATA_32.write(tmp);
      Ld_sign_1.write(dDATA_to_enc_tmp);
      break;

    case bas_3 :
      rLoad.write(0);
      Ld_bas_5.write(dDATA_to_enc_tmp.range(5,0));
      break;

    case bas_3_bis :
      rLoad.write(1);
      tmp = (code_sel_bas2,four,Ld_bas_4,Ld_bas_3,Ld_bas_2,Ld_bas_1);
      rDATA_32.write(tmp);
      Ld_sign_1.write(dDATA_to_enc_tmp);
      break;
    case bas_4:
      rLoad.write(1);
      tmp = (code_sel_bas1,Ld_bas_5,Ld_bas_4,Ld_bas_3,Ld_bas_2,Ld_bas_1);
      rDATA_32.write(tmp);
      Ld_bas_1.write(dDATA_to_enc_tmp.range(5,0));
      break;

    case bas_4_bis:
      rLoad.write(1);
      tmp = (code_sel_bas1,Ld_bas_5,Ld_bas_4,Ld_bas_3,Ld_bas_2,Ld_bas_1);
      rDATA_32.write(tmp);
      Ld_sign_1.write(dDATA_to_enc_tmp);
      break;

    case  sign_0 :
      rLoad.write(0);
      Ld_sign_2.write(dDATA_to_enc_tmp);
      break;

    case sign_0_bis :
      rLoad.write(1);
      tmp = (code_sel_sign2,sync,Ld_sign_1);
      rDATA_32.write(tmp);
      Ld_bas_1.write(dDATA_to_enc_tmp.range(5,0));
      break;

    case sign_1 :
      rLoad.write(1);
      tmp = (code_sel_sign1,Ld_sign_2,Ld_sign_1);
      rDATA_32.write(tmp);
      Ld_sign_1.write(dDATA_to_enc_tmp);
      break;

    case sign_1_bis :
      rLoad.write(1);
      tmp = (code_sel_sign1,Ld_sign_2,Ld_sign_1);
      rDATA_32.write(tmp);
      Ld_bas_1.write(dDATA_to_enc_tmp.range(5,0));
      break;
    }//case
  }//clock
}//encoder
