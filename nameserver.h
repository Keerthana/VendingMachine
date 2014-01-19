#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include <uC++.h>
#include "printer.h"

_Task VendingMachine;

_Task NameServer {
  Printer *prt_;
  unsigned int numVendingMachines_;

  unsigned int *nextMachine_;
  VendingMachine **machineList_;
  void main();

public:
  NameServer(Printer & prt, unsigned int numVendingMachines,
             unsigned int numStudents);
  ~NameServer();
  void VMregister(VendingMachine * vendingmachine);
  VendingMachine *getMachine(unsigned int id);
  VendingMachine **getMachineList();
}
;

#endif // __NAMESERVER_H__
