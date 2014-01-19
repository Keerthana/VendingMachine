#include "bottlingplant.h"

BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer,
                             unsigned int numVendingMachines,
                             unsigned int maxShippedPerFlavour,
                             unsigned int maxStockPerFlavour,
                             unsigned int timeBetweenShipments)
    : prt_(&prt), nameServer_(&nameServer),
      maxShippedPerFlavour_(maxShippedPerFlavour),
      timeBetweenShipments_(timeBetweenShipments), closed(false) {
  for (int i = 0; i < N_FLAVOURS; ++i) {
    stock[i] = 0;
  }
  myTruck = new Truck(prt_, nameServer_, this, numVendingMachines,
                      maxStockPerFlavour);
}

BottlingPlant::~BottlingPlant() { delete myTruck; }

void BottlingPlant::main() {

  int maxStock = 0;
  prt_->print(Printer::BottlingPlant, 'S');
  for (;;) {
    _Accept(~BottlingPlant) {
      closed = true;
      _Accept(getShipment);
      break;
    }
    _Else {
      // Yield for a fixed amount of time between shipment pickup by the truck
      yield(timeBetweenShipments_);

      // Produce a random number of bottles of each type, within a range
      // during a production run and allow _Task Truck to pick it up
      for (unsigned int i = 0; i < N_FLAVOURS; ++i)
        maxStock = stock[i] += mprng(maxShippedPerFlavour_);

      prt_->print(Printer::BottlingPlant, 'G', maxStock);
      _Accept(getShipment);
      prt_->print(Printer::BottlingPlant, 'P');
    }
  }
  prt_->print(Printer::BottlingPlant, 'F');
}

// Called by _Task Truck to get the shipment from the BottlingPlant
bool BottlingPlant::getShipment(unsigned int cargo[]) {
  if (closed)
    return true;
  for (unsigned int i = 0; i < N_FLAVOURS; ++i) {
    cargo[i] = stock[i];
    stock[i] = 0;
  }
  return false;
}
