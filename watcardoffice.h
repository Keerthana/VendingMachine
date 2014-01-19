#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include <uC++.h>
#include <vector>
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "watcard.h"
#include "MPRNG.h"
using namespace std;

_Task WATCardOffice {
  struct Args {
    Bank *bank_;          // monitor Bank
    unsigned int sid_;    // student id
    unsigned int amount_; // balance
    WATCard *watcard_;    // class WATcard

    Args(Bank *bank, unsigned int sid, unsigned int amount, WATCard *watcard)
        : bank_(bank), sid_(sid), amount_(amount), watcard_(watcard) {}
  };

  typedef struct Job { // marshalled arguments and return future
    Args args_;        // call arguments (YOU DEFINE "Args")
    FWATCard result;   // return future
    Job(Args args) : args_(args) {}
  } Job;

  // Subtask Courier to communicate between Bank and WATCard office
  _Task Courier {
    unsigned int id_;
    Printer *prt_;
    WATCardOffice *office_;
    Job *job;

    void main();

  public:
    Courier(unsigned int id, Printer * prt, WATCardOffice * office)
        : id_(id), prt_(prt), office_(office) {}
    ~Courier() {}
  };

  Printer *prt_;
  Bank *bank_;
  vector<Courier *> couriers;
  Job *job;
  bool closed;

  void main();

public:
  _Event Lost{}; // uC++ exception type, like "struct"
  WATCardOffice(Printer & prt, Bank & bank, unsigned int numCouriers);
  ~WATCardOffice();
  FWATCard create(unsigned int sid, unsigned int amount);
  FWATCard transfer(unsigned int sid, unsigned int amount, WATCard * card);
  Job *requestWork();
};

#endif // __WATCARDOFFICE_H__
