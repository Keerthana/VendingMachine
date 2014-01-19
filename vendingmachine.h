#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include <uC++.h>
#include "printer.h"
#include "nameserver.h"
#include "watcard.h"
#include "config.h"

_Task VendingMachine {
  Printer *prt_;
  unsigned int id_, sodaCost_;
  unsigned int inventory_[N_FLAVOURS];
  bool isStocking_;

  void main();

public:
  enum Flavours {
    Blues,
    Classical,
    Rock,
    Jazz
  }; // flavours of soda (YOU DEFINE)
  enum Status {
    BUY,
    STOCK,
    FUNDS
  }; // purchase status: successful buy, out of stock, insufficient funds
  VendingMachine(Printer & prt, NameServer & nameServer, unsigned int id,
                 unsigned int sodaCost, unsigned int maxStockPerFlavour);

  // Direct communication (public member functions)
  Status buy(Flavours flavour, WATCard & card);
  unsigned int *inventory();
  void restocked();
  _Nomutex unsigned int cost();
  _Nomutex unsigned int getId();
}
;

#endif // __VENDINGMACHINE_H__
