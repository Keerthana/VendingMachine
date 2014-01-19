#include "parent.h"

void Parent::main() {
  unsigned int sid, topUp;
  prt_->print(Printer::Parent, 'S');
  for (;;) {
    _Accept(~Parent) break;
    _Else {
      // Yield for a constant time and topUp the WATCard of a student sid
      // Allowed range for topUp : $1 - $3
      yield(parentalDelay_);
      sid = mprng(numStudents_ - 1);
      topUp = mprng(1, 3);
      prt_->print(Printer::Parent, 'D', sid, topUp);
      bank_->deposit(sid, topUp);
    }
  }
  prt_->print(Printer::Parent, 'F');
}
