#include <uC++.h>
#include "vendingmachine.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines,
                       unsigned int numStudents)
    : prt_(&prt), numVendingMachines_(numVendingMachines) {

  nextMachine_ = new unsigned int[numStudents];
  machineList_ = new VendingMachine *[numVendingMachines];
  // Assigns students to a vending machine in round-robin fashion
  for (unsigned int i = 0; i < numStudents; ++i)
    nextMachine_[i] = i % numVendingMachines;
}

NameServer::~NameServer() {
  delete[] nextMachine_;
  delete[] machineList_;
}

void NameServer::main() {
  prt_->print(Printer::NameServer, 'S');

  for (;;) {
    _Accept(~NameServer) break;
    or _Accept(VMregister, getMachine, getMachineList);
  }

  prt_->print(Printer::NameServer, 'F');
}

// Called by _Task VendingMachine to register itself, for students
// to be able to find its location
void NameServer::VMregister(VendingMachine *vendingmachine) {
  int id = vendingmachine->getId();
  prt_->print(Printer::NameServer, 'R', id);
  machineList_[id] = vendingmachine;
}

// Called by _Task Student to get access to a VendingMachine
VendingMachine *NameServer::getMachine(unsigned int id) {
  // Get the id of the next VendingMachine
  unsigned int machineId = nextMachine_[id];
  VendingMachine *machine = machineList_[machineId];
  prt_->print(Printer::NameServer, 'N', id, machine->getId());

  // Update the id of the next VendingMachine for a Student
  nextMachine_[id] = (nextMachine_[id] + 1) % numVendingMachines_;

  return machine;
}

// Called by _Task Truck to get the list of all VendingMachines for delivery
VendingMachine **NameServer::getMachineList() { return machineList_; }
