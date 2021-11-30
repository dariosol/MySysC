// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;
#include "Initiator.h"
#include <memory> //for smart pointers (make unique exists from C++14, but SystemC compiles with C++17)
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

// Target module representing a simple memory
class Memory : public sc_module {
public:
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Memory> socket;

  Memory(sc_module_name name);
  //method in socket, I have to implement for the specific application
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay );

private:
  enum { SIZE = 256 };
  int mem[SIZE];

};
