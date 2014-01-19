#ifndef __TRUCK_H__
#define __TRUCK_H__

#include <uC++.h>
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "vendingmachine.h"
#include "config.h"

_Task BottlingPlant;

_Task Truck {
  Printer *prt_;
  NameServer *nameServer_;
  BottlingPlant *plant_;
  unsigned int numVendingMachines_, maxStockPerFlavour_;
  unsigned int cargo[N_FLAVOURS];
  VendingMachine **machines;

  void main();

public:
  Truck(Printer * prt, NameServer * nameServer, BottlingPlant * plant,
        unsigned int numVendingMachines, unsigned int maxStockPerFlavour);
}
;
#endif // __TRUCK_H__
