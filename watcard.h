#ifndef __WATCARD_H__
#define __WATCARD_H__

#include <uC++.h>
#include <uFuture.h>

class WATCard {
  unsigned int balance;
  WATCard(const WATCard &) {} // prevent copying
  WATCard &operator=(const WATCard &);

public:
  WATCard();
  void deposit(unsigned int amount);
  void withdraw(unsigned int amount);
  unsigned int getBalance();
};

typedef Future_ISM<WATCard *> FWATCard; // future WATCard pointer

#endif // __WATCARD_H__