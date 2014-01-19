#include "vendingmachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer,
                               unsigned int id, unsigned int sodaCost,
                               unsigned int maxStockPerFlavour)
    : prt_(&prt), id_(id), sodaCost_(sodaCost), isStocking_(false) {
  // Create an empty VendingMachine with no bottles of soda, and 
  // register it with the NameServer
  for (int i = 0; i < N_FLAVOURS; ++i)
    inventory_[i] = 0;
  nameServer.VMregister(this);
}

void VendingMachine::main() {
  prt_->print(Printer::Vending, id_, 'S', sodaCost_);

  for (;;) {
    _Accept(~VendingMachine) break;
    or _When(isStocking_) _Accept(restocked);
    or _When(!isStocking_) _Accept(buy, inventory);
  }

  prt_->print(Printer::Vending, id_, 'F');
}

// Called by _Task Student to obtain a particular bottle of soda 
VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
  // Obtain soda elsewhere since the desired flavor is not available
  if (inventory_[flavour] == 0)
    return STOCK;

  // Student doesn't have enough balance in the WATCard. TopUp needed
  if (card.getBalance() < sodaCost_)
    return FUNDS;

  // Transaction is successful when the student buys a bottle of soda 
  card.withdraw(sodaCost_);
  inventory_[flavour]--;
  prt_->print(Printer::Vending, id_, 'B', flavour, inventory_[flavour]);
  return BUY;
}

// Called by _Task Truck to obtain the number of bottles of soda of each kind
// available in the vending machine for restocking. This call blocks the
// Vending Machine from being accessed via buy
unsigned int *VendingMachine::inventory() {
  prt_->print(Printer::Vending, id_, 'r');
  isStocking_ = true;
  return inventory_;
}

// Called by _Task Truck to indicate that the restocking process is complete
// This call unblocks the Vending Machine for access via buy
void VendingMachine::restocked() {
  prt_->print(Printer::Vending, id_, 'R');
  isStocking_ = false;
}

// Returns the cost of purchasing soda for this machine
_Nomutex unsigned int VendingMachine::cost() { return sodaCost_; }

// Returns the id of a vending machine
_Nomutex unsigned int VendingMachine::getId() { return id_; }
