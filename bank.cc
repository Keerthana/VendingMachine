#include "bank.h"

Bank::Bank(unsigned int numStudents)
    : balance(new unsigned int[numStudents]),
      transaction(new uCondition[numStudents]) {
  for (unsigned int i = 0; i < numStudents; ++i)
    balance[i] = 0;
}

Bank::~Bank() {
  delete[] balance;
  delete[] transaction;
}

// Called by _Task Parent to endow a topUp of 'amount' to a student with 'id'
void Bank::deposit(unsigned int id, unsigned int amount) {
  balance[id] += amount;
  transaction[id].signal();
}

// Called by _Task Courier on behalf of _Task Student to purchase soda
void Bank::withdraw(unsigned int id, unsigned int amount) {
  while (balance[id] < amount)
    transaction[id].wait();
  balance[id] -= amount;
}
