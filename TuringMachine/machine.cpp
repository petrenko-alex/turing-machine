#include "machine.h"

Machine::Machine(QObject *parent)
	: QObject(parent)
{
	_tape = new Tape;
	_controller = new Controller;
}

Machine::~Machine()
{

}
