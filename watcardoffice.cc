#include "watcardoffice.h"

WATCardOffice::WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers)
    : prt_(&prt), bank_(&bank), job(NULL), closed(false) {
  for (unsigned int i = 0; i < numCouriers; ++i) {
    couriers.push_back(new Courier(i, prt_, this));
  }
}

WATCardOffice::~WATCardOffice() {
  closed = true;
  for (unsigned int i = 0; i < couriers.size(); ++i)
    delete couriers[i];
}

void WATCardOffice::main() {
  prt_->print(Printer::WATCardOffice, 'S');

  for (;;) {
    _Accept(~WATCardOffice) {
    // allow the courier to gracefully exit by completing the work requested
      for (unsigned int i = 0; i < couriers.size(); ++i)
        _Accept(requestWork);
      break;
    }
    or _When(job) _Accept(requestWork) job = NULL;
    or _When(!job) _Accept(create, transfer);
  }

  prt_->print(Printer::WATCardOffice, 'F');
}

// Called by _Task Student asynchronously to create a WATCard with
// an initial balance of 'amount'. Returns a Future fwatcard_ and 
// subsequently obtains the card balance from bank_ via a courier
FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
  prt_->print(Printer::WATCardOffice, 'C', sid, amount);
  return transfer(sid, amount, NULL);
}

// Called by _Task Student asynchronously to transfer some 'amount' of
// money into the WATCard, when there is insufficient funds to buy soda.
// Functions similar to WATCardOffice::create 
FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount,
                                 WATCard *card) {
  // Card already present, so do a transfer instead of creating a new card
  if (card)
    prt_->print(Printer::WATCardOffice, 'T', sid, amount);
  job = new Job(Args(bank_, sid, amount, card));
  return job->result;
}

// Called by sub _Task Courier, and blocks the courier until job is ready
WATCardOffice::Job *WATCardOffice::requestWork() {
  // WATCard Office is closed, so no more jobs are available
  if (closed)
    return NULL;
  return job;
}

void WATCardOffice::Courier::main() {
  prt_->print(Printer::Courier, id_, 'S');

  for (;;) {
    job = office_->requestWork();
    if (!job)
      break;
    Args *a = &job->args_;
    FWATCard *r = &job->result;

    if (mprng(LOSE_CARD) == 0) {
      // 1/6 chance of losing a WATCard raises exception
      r->exception(new Lost);
      if (a->watcard_) delete a->watcard_;
    } else {
      // Transfer money into a new or existing WATCard 
      // by withdrawing from bank
      prt_->print(Printer::Courier, id_, 't', a->sid_, a->amount_);
      a->bank_->withdraw(a->sid_, a->amount_);
      if (!a->watcard_)
        a->watcard_ = new WATCard();
      a->watcard_->deposit(a->amount_);
      prt_->print(Printer::Courier, id_, 'T', a->sid_, a->amount_);
      prt_->print(Printer::WATCardOffice, 'W');
      r->delivery(a->watcard_);
    }
    delete job;
  }
  prt_->print(Printer::Courier, id_, 'F');
}
