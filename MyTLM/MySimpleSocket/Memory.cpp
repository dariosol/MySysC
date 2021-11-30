
#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;
#include "Memory.h"
#include <memory>
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

//constructor:
Memory::Memory(sc_module_name name="socket") : socket(name)
{
  // Register callback for incoming b_transport interface method call
  socket.register_b_transport(this, &Memory::b_transport);

  // Initialize memory with random data
  for (int i = 0; i < SIZE; i++) mem[i] = 0xAAF1CA00 | (rand() % 256);

}

// TLM-2 blocking transport method
void Memory::b_transport( tlm::tlm_generic_payload& trans, sc_time& delay ) {
  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address() / 4;
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  // Obliged to check address range and check for unsupported features,
  //   i.e. byte enables, streaming, and bursts
  // Can ignore DMI hint and extensions
  // Using the SystemC report handler is an acceptable way of signalling an error

  if (adr >= sc_dt::uint64(SIZE) || byt != 0 || len > 4 || wid < len)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

  // Obliged to implement read and write commands
  if ( cmd == tlm::TLM_READ_COMMAND )
    memcpy(ptr, &mem[adr], len);
  else if ( cmd == tlm::TLM_WRITE_COMMAND )
    memcpy(&mem[adr], ptr, len);

  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}
