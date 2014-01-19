#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include <uC++.h>
#include "config.h"
#include "MPRNG.h"
#include "printer.h"
#include "nameserver.h"
#include "truck.h"

_Task Truck;

_Task BottlingPlant {
  Printer *prt_;
  NameServer *nameServer_;
  unsigned int maxShippedPerFlavour_, timeBetweenShipments_;
  unsigned int stock[N_FLAVOURS];
  bool closed;
  Truck *myTruck;

  void main();

public:
  BottlingPlant(
      Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
      unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
      unsigned int timeBetweenShipments);
  ~BottlingPlant();
  bool getShipment(unsigned int cargo[]);
}
;

#endif // __BOTTLINGPLANT_H__
