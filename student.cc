#include "student.h"

Student::Student(Printer &prt, NameServer &nameServer,
                 WATCardOffice &cardOffice, unsigned int id,
                 unsigned int maxPurchases)
    : prt_(&prt), nameServer_(&nameServer), cardOffice_(&cardOffice), id_(id) {

  // Select a random number of bottles to purchase and type of soda
  nBtlToPurchase_ = mprng(1, maxPurchases);
  faveFlavour_ = static_cast<VendingMachine::Flavours>(mprng(0, 3));

  prt_->print(Printer::Student, id_, 'S', static_cast<int>(faveFlavour_),
              nBtlToPurchase_);

  // Create a WATCard with initial balance of $5
  fwatcard_ = cardOffice_->create(id_, WATCARD_BALANCE);

  // Select a Vending machine from the nameserver
  machine_ = nameServer_->getMachine(id_);
  prt_->print(Printer::Student, id_, 'V', machine_->getId());
}

Student::~Student() {
  delete fwatcard_();
  prt_->print(Printer::Student, id_, 'F');
}

void Student::main() {
  for (;;) {
    // Exit condition for the _Task Student
    _When(nBtlToPurchase_ == 0) _Accept(~Student) break; // for

    // Yield randomly before attempting to buy soda
    yield(mprng(1, 10));

    while (true) {
      try {
        VendingMachine::Status status;
        status = machine_->buy(faveFlavour_, *fwatcard_());

        if (status == VendingMachine::BUY) {
          // Success! Bought soda
          prt_->print(Printer::Student, id_, 'B', machine_->getId());
          nBtlToPurchase_--;
        } else if (status == VendingMachine::STOCK) {
          // No stock -> Go to a new Vending machine
          machine_ = nameServer_->getMachine(id_);
          prt_->print(Printer::Student, id_, 'V', machine_->getId());
        } else if (status == VendingMachine::FUNDS) {
          // Insufficient funds -> Transfer cost of soda + $5 into WATCard
          fwatcard_ =
              cardOffice_->transfer(id_, WATCARD_BALANCE + machine_->cost(), 
                                   fwatcard_());
        }
        break; // while
      }
      catch (WATCardOffice::Lost &) {
        // Create a new card when the WATCard is lost by the courier
        //  during transfer in cardOffice_->transfer
        fwatcard_ = cardOffice_->create(id_, WATCARD_BALANCE);
        prt_->print(Printer::Student, 'L');
      }
    }
  }
}
