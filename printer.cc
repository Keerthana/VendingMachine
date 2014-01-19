#include "printer.h"
#include <iostream>

using namespace std;

void usage(char **argv) {
  cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]"
       << endl;
  exit(EXIT_FAILURE);
}

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines,
                 unsigned int numCouriers)
    : numStudents_(numStudents), numVendingMachines_(numVendingMachines),
      numCouriers_(numCouriers),
      numItems(numStudents_ + numVendingMachines_ + numCouriers_ + 5),
      flushData(new FlushData[numItems]) {

  cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
  for (unsigned int i = 0; i < numStudents_; ++i)
    cout << "Stud" << i << "\t";
  for (unsigned int i = 0; i < numVendingMachines_; ++i)
    cout << "Mach" << i << "\t";
  for (unsigned int i = 0; i < numCouriers_; ++i)
    cout << "Cour" << i << "\t";
  cout << endl;
  for (unsigned int i = 0; i < numItems; ++i) {
    cout << "*******\t";
    flushData[i].hasData = false;
  }
  cout << endl;
}

Printer::~Printer() {
  delete[] flushData;
  cout << "***********************\n";
}

void Printer::print(Kind kind, char state) { print(kind, state, -1, -1); }

void Printer::print(Kind kind, char state, int value1) {
  print(kind, state, value1, -1);
}

void Printer::print(Kind kind, char state, int value1, int value2) {
  print(kind, 0, state, value1, value2);
}

void Printer::print(Kind kind, unsigned int lid, char state) {
  print(kind, lid, state, -1, -1);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1) {
  print(kind, lid, state, value1, -1);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1,
                    int value2) {
  int id = 0;
  switch (kind) {
  case Student:
    id = lid + 5;
    break;
  case Vending:
    id = lid + numStudents_ + 5;
    break;
  case Courier:
    id = lid + numStudents_ + numVendingMachines_ + 5;
    break;
  default:
    id = lid + (unsigned int)kind;
    break;
  }

  if (flushData[id].hasData)
    resume();
  if (state == 'F') {
    printFinished(id, state);
    return;
  } else {
    flushData[id].hasData = true;
    flushData[id].state = state;
    flushData[id].value1 = value1;
    flushData[id].value2 = value2;
  }
}

void Printer::printFinished(unsigned int id, char state) {
  for (unsigned int i = 0; i < numItems; ++i) {
    if (i == id) {
      cout << state;
    } else {
      cout << "...";
    }
    cout << "\t";
  }
  cout << endl;
}

void Printer::main() {
  for (;;) {
    for (unsigned int i = 0; i < numItems; ++i) {
      if (flushData[i].hasData) {
        cout << flushData[i].state;
        if (flushData[i].value1 >= 0) {
          cout << flushData[i].value1;
          if (flushData[i].value2 >= 0)
            cout << "," << flushData[i].value2;
        }
      }
      cout << "\t";
      flushData[i].hasData = false;
    }
    cout << endl;
    suspend();
  }
}
