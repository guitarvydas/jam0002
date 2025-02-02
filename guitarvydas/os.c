#include <stdio.h>
#include <stdlib.h>
#include "mpos.h"
#include "kernel.h"

List* runQueue;

void DispatchTransferOutputs ();
void Dispatch ();
void DistributeOutputsToReceivers ();
void DispatchMaybe (Component*);
void DistributeOutputsFrom (Component*);
void DeliverMessageToReceiver (Component*, Message);
void RunComponentOnce (Component*);
void DistributeMaybe (Component*);
void DistributeOutputsFrom (Component*);

void Dispatcher () {
  while (kernelAnyComponentHasInputs ()) {
    Dispatch ();
    DistributeOutputsToReceivers ();
  }
  printf ("Dispatcher done\n");
}

void Dispatch () {
  /* go through list of components and dispatch (once) any component that has input(s) */
  List* componentList;
componentList = runQueue;
  while ((componentList != NULL)) {
      Component* c = componentList->datum.pcomponent;
      DispatchMaybe (c);
componentList = (componentList != NULL) ? componentList->next : (List*)NULL;
  }
;
}

int kernelAnyComponentHasInputs () {
  List* componentList;
componentList = runQueue;
  while ((componentList != NULL)) {
      Component* c = componentList->datum.pcomponent;
      if (c->inputQueue) {
	return 1;
      }
componentList = (componentList != NULL) ? componentList->next : (List*)NULL;
  }
;
  return 0;
}

void DispatchMaybe (Component* c) {
  if (c->inputQueue) {
    RunComponentOnce (c);
  }
}

void RunComponentOnce (Component* c) {
  List* cell = componentPopInput (c);
  Message msg = cell->datum.message;
componentCallReaction (c, msg);
}

void DistributeOutputsToReceivers () {
  List* componentList;
componentList = runQueue;
  while ((componentList != NULL)) {
      Component* c = componentList->datum.pcomponent;
      DistributeMaybe (c);
componentList = (componentList != NULL) ? componentList->next : (List*)NULL;
    }
;
}

void DistributeMaybe (Component* c) {
  if (c->outputQueue) {
    DistributeOutputsFrom (c);
  }
}
			    
void DistributeOutputsFrom (Component* c) {
  List* outputs;
outputs = componentGetOutputsAsSent (c);
componentGCoutputs (c);
  while ((outputs != NULL)) {
    Message m = outputs->datum.message;
    DeliverMessageToReceiver (c, m);
outputs = (outputs != NULL) ? outputListAdvanceAndGC (outputs) : (List*)NULL;
  }
;
}

void DeliverMessageToReceiver (Component* c, Message m) {
  Component* receiver = connectionsConnectedTo (c);
componentAppendInput (receiver, m);
}


void panic (char* panicMessage) {
  printf ("%s\n", panicMessage);
  exit (1);
}

void kernelSendc (Component* self, char c) {
  Message m;
  m.c = c;
componentAppendOutput (self, m);
}
 
void kernelKickStart (Component* component, char junk) {
  Message m;
  m.c = junk;
componentAppendInput (component, m);
}
  

