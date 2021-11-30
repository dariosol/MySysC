// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;
#include "Initiator.h"
#include "Memory.h"

#include <memory> //for smart pointers (make unique exists from C++14, but SystemC compiles with C++17)
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
// Target module representing a simple memory

SC_MODULE(Top)
{
  unique_ptr<Initiator> initiator;
  unique_ptr<Memory>    memory;

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = make_unique<Initiator>("initiator");
    memory    = make_unique<Memory>   ("memory");
    // One initiator is bound directly to one target with no intervening bus
    // Bind initiator socket to target socket
    initiator->socket.bind( memory->socket );
  }
};


int sc_main(int argc, char* argv[])
{
  Top top("top");
  sc_start();
  return 0;
}
