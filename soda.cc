#include <uC++.h>
#include <string>

#include "config.h"
#include "printer.h"
#include "bank.h"
#include "watcardoffice.h"
#include "parent.h"
#include "bottlingplant.h"
#include "vendingmachine.h"
#include "student.h"
#include "nameserver.h"
#include "MPRNG.h"
using namespace std;

MPRNG mprng;
extern void usage(char *argv[]);

void uMain::main() {

  // Config file
  string conf = "soda.config";

  // Seed for Random number generator
  unsigned int seed = time(NULL) ^ getpid();

  switch (argc) {
  case 3:
    if (atoi(argv[2]) < 1)
      usage(argv);
    seed = atoi(argv[2]);
    mprng.seed(seed);
  case 2:
    conf = string(argv[1]);
  case 1:
    break;
  default:
    usage(argv);
  }

  // Setting up Vending machines
  ConfigParms in;
  processConfigFile(conf.c_str(), in);

  Printer myPrinter(in.numStudents, in.numVendingMachines, in.numCouriers);

  Bank myBank(in.numStudents);
  Parent *myParent =
      new Parent(myPrinter, myBank, in.numStudents, in.parentalDelay);
  WATCardOffice *myWATCardOffice =
      new WATCardOffice(myPrinter, myBank, in.numCouriers);
  NameServer *myNameServer =
      new NameServer(myPrinter, in.numVendingMachines, in.numStudents);

  VendingMachine *myVendingMachine[in.numVendingMachines];
  for (unsigned int i = 0; i < in.numVendingMachines; ++i)
    myVendingMachine[i] = new VendingMachine(
        myPrinter, *myNameServer, i, in.sodaCost, in.maxStockPerFlavour);

  BottlingPlant *myBottlingPlant = new BottlingPlant(
      myPrinter, *myNameServer, in.numVendingMachines, in.maxShippedPerFlavour,
      in.maxStockPerFlavour, in.timeBetweenShipments);

  Student *myStudent[in.numStudents];
  for (unsigned int i = 0; i < in.numStudents; ++i)
    myStudent[i] = new Student(myPrinter, *myNameServer, *myWATCardOffice, i,
                               in.maxPurchases);

  for (unsigned int i = 0; i < in.numStudents; ++i)
    delete myStudent[i];

  delete myBottlingPlant;
  for (unsigned int i = 0; i < in.numVendingMachines; ++i)
    delete myVendingMachine[i];

  delete myNameServer;
  delete myWATCardOffice;
  delete myParent;
}
