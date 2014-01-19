#ifndef __CONFIG_H__
#define __CONFIG_H__

// Blues Black-Cherry, Classical Cream-Soda, Rock Root-Beer, and Jazz Lime.
#define N_FLAVOURS (4)

// Starting Balance for WATCard
#define WATCARD_BALANCE (5)

// Random Chance of losing WATCard
#define LOSE_CARD (5)

struct ConfigParms {
  unsigned int sodaCost;     // MSRP per bottle
  unsigned int numStudents;  // number of students to create
  unsigned int maxPurchases; // maximum number of bottles a student purchases
  unsigned int numVendingMachines; // number of vending machines
  unsigned int maxStockPerFlavour; // maximum number of bottles of each flavour
                                   // stocked
  unsigned int maxShippedPerFlavour; // number of bottles of each flavour in a
                                     // shipment
  unsigned int timeBetweenShipments; // length of time between shipment pickup
  unsigned int parentalDelay;        // length of time between cash deposits
  unsigned int numCouriers;          // number of couriers in the pool
};

void processConfigFile(const char *configFile, ConfigParms &cparms);

#endif // __CONFIG_H__
