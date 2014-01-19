#ifndef __BANK_H__
#define __BANK_H__

#include <uC++.h>

_Monitor Bank {
  unsigned int *balance;
  uCondition *transaction;

public:
  Bank(unsigned int numStudents);
  ~Bank();
  void deposit(unsigned int id, unsigned int amount);
  void withdraw(unsigned int id, unsigned int amount);
}
;

#endif // __BANK_H__