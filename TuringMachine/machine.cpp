#include "machine.h"

Machine::Machine()
{
	tape = new Tape;
	controller = new Controller;
}

Machine::~Machine()
{
	delete tape;
	delete controller;
}

void Machine::setTape(const QStringList &tapeView, unsigned int tapePointer)
{
	tape->setData(tapeView, tapePointer);
}
