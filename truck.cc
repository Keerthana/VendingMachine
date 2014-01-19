#include "truck.h"

Truck::Truck(Printer *prt, NameServer *nameServer, BottlingPlant *plant,
             unsigned int numVendingMachines, unsigned int maxStockPerFlavour)
    : prt_(prt), nameServer_(nameServer), plant_(plant),
      numVendingMachines_(numVendingMachines),
      maxStockPerFlavour_(maxStockPerFlavour) {
  for (unsigned int i = 0; i < N_FLAVOURS; ++i)
    cargo[i] = 0;
}

void Truck::main() {
  // Total shipment size, stock needed to replenish vending machines
  // and Unreplenished bottles
  unsigned int bottlesMissing = 0, totalCargo = 0, stockNeeded = 0;

  prt_->print(Printer::Truck, 'S');
  machines = nameServer_->getMachineList();

  for (;;) {
    yield(mprng(1, 10));

    // Exit if there is no shipment ready
    if (plant_->getShipment(cargo))
      break;

    // Pick up shipment that is available
    for (unsigned int i = 0; i < N_FLAVOURS; ++i)
      totalCargo += cargo[i];

    prt_->print(Printer::Truck, 'P', totalCargo);

    // Stock up and deliver to each vending machine
    for (unsigned int i = 0; i < numVendingMachines_; ++i) {

      prt_->print(Printer::Truck, 'd', i, totalCargo);

      unsigned int *inventory = machines[i]->inventory();

      // Stock upto maxStockPerFlavour_ for each machine and report
      // unreplenished bottles bottlesMissing per shipment
      for (unsigned int j = 0; j < N_FLAVOURS; ++j) {

        stockNeeded = maxStockPerFlavour_ - inventory[j];

        if (cargo[j] < stockNeeded) {
          inventory[j] += cargo[j];
          cargo[j] = 0;
          bottlesMissing += stockNeeded;
        } else {
          inventory[j] += stockNeeded;
          cargo[j] -= stockNeeded;
        }
      }
      if (bottlesMissing != 0)
        prt_->print(Printer::Truck, 'U', i, bottlesMissing);

      bottlesMissing = 0;
      totalCargo = 0;

      // Done restocking. Deliver shipment
      machines[i]->restocked();
      for (unsigned int j = 0; j < N_FLAVOURS; ++j)
        totalCargo += cargo[j];

      if (totalCargo != 0)
        prt_->print(Printer::Truck, 'D', i, totalCargo);
      else
        break;
    }
  }

  prt_->print(Printer::Truck, 'F');
}

