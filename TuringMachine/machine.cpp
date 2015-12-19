#include "machine.h"

Machine::Machine()
{
	_tape = new Tape;
	_controller = new Controller;
}

Machine::~Machine()
{
	delete _tape;
	delete _controller;
}

void Machine::setTape(const QStringList &tapeView, unsigned int tapePointer)
{
	_tape->setData(tapeView, tapePointer);
}
