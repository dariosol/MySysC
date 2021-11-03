#ifndef __I2C_CONTROLLER_TB_H
#define __I2C_CONTROLLER_TB_H

#include <systemc.h>
#include <memory>
#include <i2c_controller.h>
#include <i2c_slave_controller.h>

SC_MODULE(i2c_controller_tb)
{

	std::unique_ptr<sc_clock> clk;
	sc_signal<bool> rst;
	sc_signal<sc_uint<7>> addr;
	sc_signal<sc_uint<8>> data_in;
	sc_signal<bool> enable;
	sc_signal<bool> rw;
	sc_signal<sc_lv<8>> data_out;
	sc_signal<bool> ready;
	sc_signal<sc_logic, SC_MANY_WRITERS> i2c_sda;
	sc_signal<sc_logic> i2c_scl;

	std::unique_ptr<i2c_controller> master;
	std::unique_ptr<i2c_slave_controller> slave;
	std::unique_ptr<i2c_slave_controller> slave2;

	SC_CTOR(i2c_controller_tb)
	{
		clk = std::make_unique<sc_clock>("clk",2,SC_NS);

		master = std::make_unique<i2c_controller>("i2c_controller");
			master->clk(*clk);
			master->rst(rst);
			master->addr(addr);
			master->data_in(data_in);
			master->enable(enable);
			master->rw(rw);
			master->data_out(data_out);
			master->ready(ready);
			master->i2c_sda(i2c_sda);
			master->i2c_scl(i2c_scl);

//Two slaves with different addresses in the constructor:
		slave = std::make_unique<i2c_slave_controller>("i2c_slave_controller","0101001");
			slave->sda(i2c_sda);
			slave->scl(i2c_scl);

		slave2 = std::make_unique<i2c_slave_controller>("i2c_slave_controller2","0101010");
			slave2->sda(i2c_sda);
			slave2->scl(i2c_scl);

		SC_THREAD(stimuli);
	 	sensitive << *clk << rst;

	}

	~i2c_controller_tb()
	{
		//Not needed anymore because of smart pointers
	//	delete master;
	//	delete slave;
	//	delete slave2;

	}

	void stimuli();

};
#endif
