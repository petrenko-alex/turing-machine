#include "machine.h"

Machine::Machine()
{
	tape = new Tape;
	controller = new Controller;
	tapeLoaded = false;
	controllerLoaded = false;
}

Machine::~Machine()
{
	delete tape;
	delete controller;
}

void Machine::setTape(const QStringList& tapeView, unsigned int tapePointer)
{
	tape->setData(tapeView, tapePointer);
}

void Machine::setAlphabet(const QStringList& alphabet)
{
	controller->setAlphabet(alphabet);
}

void Machine::setBeginEndStates(const QString& beginState, const QString& endState) throw(QString&)
{
	controller->setBeginEndStates(beginState, endState);
}

void Machine::addComand(const QString& key, const Command& cmd) throw(QString&)
{
	controller->addComand(key, cmd);
}

QStringList Machine::getStates(bool includeStopState) const
{
	return controller->getStates(includeStopState);
}

bool Machine::isReady() const
{
	return tapeLoaded && controllerLoaded;
}

void Machine::setTapeLoaded()
{
	tapeLoaded = true;
}

void Machine::setControllerLoaded()
{
	controllerLoaded = true;
}

void Machine::reset()
{
	tape->reset();
	controller->reset();
	tapeLoaded = false;
	controllerLoaded = false;
}

QStringList Machine::getAlphabet() const
{
	return controller->getAlphabet();
}

void Machine::setStates(const QStringList& states)
{
	controller->setStates(states);
}
