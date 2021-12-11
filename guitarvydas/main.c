#include "mpos.h"
#include "producer.h"
#include "consumer.h"
#include "kernel.h"

int main (int argc, char **argv) {
  Component* p =  componentNew (initProducer, reactProducer, "producer") ;
  Component* c =  componentNew (initConsumer, reactConsumer, "consumer") ;
  List* lis1 = listNewCellComponent (p);
  List* lis2 = listNewCellComponent (c);
lis1 = listAppend (lis1, lis2);
  runQueue = lis1;
connectionsConnect (p, c);
kernelKickStart (p, '1');
kernelKickStart (p, '2');
kernelKickStart (p, '3');
kernelKickStart (p, '4');
kernelKickStart (p, '5');
kernelStart ();
  Dispatcher ();
  return 0;
}

