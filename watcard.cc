#include "watcard.h"

// Initialized when card is created
WATCard::WATCard() { balance = 0; }

// Called by _Task Courier deposit after a successful fund transfer
void WATCard::deposit(unsigned int amount) { balance += amount; }

// Called by _Task VendingMachine when a soda is successfully purchased
void WATCard::withdraw(unsigned int amount) { balance -= amount; }

// Callers:_Task Student or _Task VendingMachine to know the WATCard balance
unsigned int WATCard::getBalance() { return balance; }
