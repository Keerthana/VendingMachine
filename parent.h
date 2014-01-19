#ifndef __PARENT_H__
#define __PARENT_H__

#include <uC++.h>
#include "printer.h"
#include "bank.h"
#include "MPRNG.h"
_Task Parent {
  Printer *prt_;
  Bank *bank_;
  unsigned int numStudents_, parentalDelay_;

  void main();

public:
  Parent(Printer & prt, Bank & bank, unsigned int numStudents,
         unsigned int parentalDelay)
      : prt_(&prt), bank_(&bank), numStudents_(numStudents),
        parentalDelay_(parentalDelay) {}
}
;

#endif // __PARENT_H__
