#ifndef __I2C_SLAVE_CONTROLLER_H
#define __I2C_SLAVE_CONTROLLER_H

#include <systemc.h>

SC_MODULE(i2c_slave_controller)
{
	sc_inout<sc_logic> sda;
	sc_inout<sc_logic> scl;

	enum states {READ_ADDR, SEND_ACK, READ_DATA, WRITE_DATA, SEND_ACK2};
	sc_signal<states> state;

	const sc_lv<7> ADDRESS;
	sc_signal<sc_logic> sda_out;
	sc_signal<bool> start;
	sc_signal<bool> write_enable;
	sc_lv<8> addr;
	sc_uint<8> counter;
	sc_lv<8> data_in;
	sc_uint<8> data_out = 170;

	//Personal constructor, to have the address in the constructor. It must use "SC_HAS_PROCESS" to work
	i2c_slave_controller(sc_module_name name, sc_lv<7> ADDRESS_): sc_module(name), ADDRESS(ADDRESS_) {
		SC_METHOD(start_condition);
		sensitive << sda.neg();

		SC_METHOD(stop_condition);
		sensitive << sda;

		SC_METHOD(logic_fsm);
		sensitive << scl.pos();

		SC_METHOD(data_fsm);
		sensitive << scl.neg();
		}

	void start_condition();
	void stop_condition();
	void logic_fsm();
	void data_fsm();

	SC_HAS_PROCESS(i2c_slave_controller);

};
#endif
