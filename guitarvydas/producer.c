#include "mpos.h"
#include "producer.h"

// producer
int counter;

void initProducer (Component* self) {
}

void reactProducer (Component* self, Message m) {
kernelSendc (self, m.c);
}

