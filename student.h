#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <uC++.h>
#include "printer.h"
#include "nameserver.h"
#include "vendingmachine.h"
#include "watcardoffice.h"
#include "watcard.h"
#include "config.h"
#include "MPRNG.h"

_Task Student {
  Printer *prt_;
  NameServer *nameServer_;
  WATCardOffice *cardOffice_;
  unsigned int id_, nBtlToPurchase_;
  VendingMachine::Flavours faveFlavour_;
  VendingMachine *machine_;
  FWATCard fwatcard_;

  void main();

public:
  Student(Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice,
          unsigned int id, unsigned int maxPurchases);
  ~Student();
}
;

#endif // __STUDENT_H__
