#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <uC++.h>

_Cormonitor Printer {
  unsigned int numStudents_, numVendingMachines_, numCouriers_, numItems;

  struct FlushData {
    bool hasData;
    char state;
    int value1, value2;
    unsigned int lid;
  } *flushData;

  void printFinished(unsigned int id, char state);
  void main();

public:
  enum Kind {
    Parent,
    WATCardOffice,
    NameServer,
    Truck,
    BottlingPlant,
    Student,
    Vending,
    Courier
  };
  Printer(unsigned int numStudents, unsigned int numVendingMachines,
          unsigned int numCouriers);
  ~Printer();
  void print(Kind kind, char state);
  void print(Kind kind, char state, int value1);
  void print(Kind kind, char state, int value1, int value2);
  void print(Kind kind, unsigned int lid, char state);
  void print(Kind kind, unsigned int lid, char state, int value1);
  void print(Kind kind, unsigned int lid, char state, int value1, int value2);
}
;

#endif // __PRINTER_H__
