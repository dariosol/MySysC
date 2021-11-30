#ifndef INITIATOR_H
#define INITIATOR_H
#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include <memory>

SC_MODULE(Initiator) {
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_initiator_socket<Initiator> socket;

  // Internal data buffer used by initiator with generic payload
  int data;
  unique_ptr<tlm::tlm_generic_payload> trans;
  void thread_process();

  SC_CTOR(Initiator): socket("socket")  // Construct and name socket
  {
    SC_THREAD(thread_process);
  }

};
#endif
