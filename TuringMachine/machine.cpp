#include "machine.h"

Machine::Machine()
{
	tape = new Tape;
	controller = new Controller;
	tapeLoaded = false;
	controllerLoaded = false;
	machineState = MachineState::PAUSED;
}

Machine::~Machine()
{
	delete tape;
	delete controller;
}

void Machine::setTape(const QStringList& tapeView, unsigned int tapePointer, const QString& emptySymbol)
{
	tape->setData(tapeView, tapePointer,emptySymbol);
}

void Machine::setCurrentState(const QString& state)
{
	controller->setCurrentState(state);
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

QString Machine::getEmptySymbol() const
{
	return tape->getEmptySymbol();
}

unsigned int Machine::getTapePointer() const
{
	return tape->getTapePointer();
}

QString Machine::getCommand(const QString& key) const
{
	// #TODO: не обращаться напрямую к полю
	QString command = "";

	if (controller->commands.contains(key))
	{
		Command cmd = controller->commands.value(key);
		command = cmd.newSymbol + "-" + cmd.newState + "-" + cmd.action;
	}
	return command;
}

QString Machine::getCurrentState() const
{
	return controller->getCurrentState();
}

QString Machine::getCurrentTapeSymbol() const
{
	return tape->getCurrentSymbol();
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

bool Machine::isFinished() const
{
	return machineState == MachineState::FINISHED;
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

void Machine::oneStep(bool emitSignals)
{
	QString currentState = getCurrentState();
	QString currentSymbol = getCurrentTapeSymbol();
	QString command = getCommand(currentSymbol + currentState);
	QStringList splittedCommand = command.split('-');
	QString newSymbol = splittedCommand.at(0);
	QString newState = splittedCommand.at(1);
	QString action = splittedCommand.at(2);
	unsigned int oldTapePointer = tape->getTapePointer();

	/* Устанавливаем ноый символ в старую позицию ленты */
	tape->setSymbolAt(newSymbol,oldTapePointer);
	if (emitSignals)
	{
		emit tapeSymbolChanged(oldTapePointer, newSymbol);
	}

	/* Перемещаем головку ленты на новую позицию */
	int newTapePointer = getNewTapePointer(action, oldTapePointer);
	try
	{
		tape->setCurrentTapePointer(newTapePointer);
		newTapePointer = tape->getTapePointer();
	}
	catch (QString& errorString)
	{
		emit machineError(errorString);
		return;
	}

	if (action != "N" && emitSignals)
	{
		emit tapePointerChanged(oldTapePointer, newTapePointer);
	}

	/* Устанавливаем новое состояние УУ */
	setCurrentState(newState);

	/* Проверка конечного состояния */
	// #TODO: Не обращаться к полям напрямую
	if (controller->currentState == controller->endState)
	{
		machineState = MachineState::FINISHED;
		emit machineFinished();
	}
}

void Machine::startWork()
{
	while (machineState != MachineState::FINISHED)
	{
		oneStep(false);
	}
}

void Machine::stopWork()
{
	machineState = MachineState::FINISHED;
}

void Machine::verifyTape()
{
	bool isOk = true;
	QStringList tapeView = tape->getTapeView();
	QString emptySymbol = tape->getEmptySymbol();

	for (auto i : tapeView)
	{
		if (!controller->isAlphabetSymbolValid(i))
		{
			isOk = false;
			break;
		}
	}

	if (!controller->isAlphabetSymbolValid(emptySymbol))
	{
		isOk = false;
	}

	if (!isOk)
	{
		QString message = "Лента машины не соответствует алфавиту управляющего устройства.";
		emit machineError(message);
	}
}

unsigned int Machine::getNewTapePointer(const QString& action, unsigned int prevPointer)
{
	if (action == "R")
	{
		return (prevPointer + 1);
	}
	else if (action == "L")
	{
		return (prevPointer - 1);
	}
	else if (action == "N")
	{
		return prevPointer;
	}
	else
	{
		QString errorString = "Найдена неизвестная команда \"" + action + "\".";
		emit machineError(errorString);
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
