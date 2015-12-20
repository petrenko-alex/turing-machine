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

QStringList Machine::getTape() const
{
	return tape->getTapeView();
}

unsigned int Machine::getTapePointer() const
{
	return tape->getTapePointer();
}

bool Machine::isReady() const
{
	return tapeLoaded && controllerLoaded;
}

bool Machine::isTapeLoaded() const
{
	return tapeLoaded;
}

bool Machine::isControllerLoaded() const
{
	return controllerLoaded;
}

void Machine::setTapeLoaded()
{
	tapeLoaded = true;

	if (controllerLoaded)
	{
		verifyTape();
	}
}

void Machine::setControllerLoaded()
{
	controllerLoaded = true;

	if (tapeLoaded)
	{
		verifyTape();
	}
}

void Machine::reset()
{
	tape->reset();
	controller->reset();
	tapeLoaded = false;
	controllerLoaded = false;
}

void Machine::verifyTape() 
{
	bool isOk = true;
	QStringList tapeView = tape->getTapeView();

	for (auto i : tapeView)
	{
		if (!controller->isAlphabetSymbolValid(i))
		{
			isOk = false;
			break;
		}
	}

	if (!isOk)
	{
		QString message = "Лента машины не соответствует алфавиту управляющего устройства.";
		emit machineError(message);
	}
}

QStringList Machine::getAlphabet() const
{
	return controller->getAlphabet();
}

void Machine::setStates(const QStringList& states)
{
	controller->setStates(states);
}
