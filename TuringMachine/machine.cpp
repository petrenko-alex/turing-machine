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

void Machine::setBeginState(const QString& state)
{
	controller->beginState = state;
}

void Machine::setEndState(const QString& state)
{
	controller->endState = state;
}

void Machine::setEmptySymbol(const QString& symbol)
{
	tape->emptySymbol = symbol;
}

void Machine::setAlphabet(const QStringList& alphabet)
{
	controller->setAlphabet(alphabet);
}

void Machine::setBeginEndStates(const QString& beginState, const QString& endState) throw(QString&)
{
	try
	{
		controller->setBeginEndStates(beginState, endState);
	}
	catch (QString& errorString)
	{
		emit machineError(errorString);
	}
}

void Machine::addComand(const QString& key, const Command& cmd) throw(QString&)
{
	try
	{
		controller->addComand(key, cmd);
	}
	catch (QString& errorString)
	{
		emit machineError(errorString);
	}
}

void Machine::addState(const QString& state)
{
	controller->states.append(state);
}

void Machine::addSymbol(const QString& symbol)
{
	controller->alphabet.append(symbol);
}

void Machine::appendToTape(const QString& symbol)
{
	tape->appendToTape(symbol);
}

void Machine::prependToTape(const QString& symbol)
{
	tape->prependToTape(symbol);
}

void Machine::incrementTapePointer()
{
	tape->incrementPointer();
}

void Machine::decrementTapePointer()
{
	tape->decrementPointer();
}

void Machine::setTapeSymbol(const QString& symbol, unsigned int index)
{
	tape->setSymbolAt(symbol, index);
}

QStringList Machine::getStates(bool includeStopState) const
{
	return controller->getStates(includeStopState);
}

QString Machine::getBeginState() const
{
	return controller->beginState;
}

QString Machine::getEndState() const
{
	return controller->endState;
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

QStringList Machine::exportTape() const
{
	QStringList toExport = tape->getTapeView();
	toExport.removeAll(TAPE_BLANK);
	return toExport;
}

QMap<QString, Command> Machine::getCommands() const
{
	return controller->commands;
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

bool Machine::isTapeSymbolValid(const QString& symbol) const
{
	if (controllerLoaded)
	{
		return controller->isAlphabetSymbolValid(symbol);
	}
	return true;
}

bool Machine::isStateValid(const QString& state) const
{
	if (controllerLoaded)
	{
		return controller->isStateValid(state);
	}
	return true;
}

bool Machine::isStateUnique(const QString& state) const
{
	return !(controller->states.contains(state, Qt::CaseSensitive));
}

bool Machine::isSymbolUnique(const QString& symbol) const
{
	return !(controller->alphabet.contains(symbol, Qt::CaseSensitive));
}

void Machine::reset()
{
	tape->reset();
	controller->reset();
	tapeLoaded = false;
	controllerLoaded = false;
}

void Machine::resetController()
{
	controller->reset();
	controllerLoaded = false;
}

void Machine::resetTape()
{
	tape->reset();
	tapeLoaded = false;
}

void Machine::oneStep(bool emitSignals)
{
	/* Получаем команду по символу ленты и текущему состоянию */
	QString currentState = getCurrentState();
	QString currentSymbol = getCurrentTapeSymbol();

	QString command = getCommand(currentSymbol + currentState);
	if (command.isEmpty())
	{
		machineState = MachineState::FINISHED;
		QString errorString = "Не задана команда для символа \"" + 
							   currentSymbol + "\" и состояния \"" + 
							   currentState + "\".";
		emit machineError(errorString);
		return;
	}

	/* Разбираем команду на данные */
	QStringList splittedCommand = command.split('-');
	QString newSymbol = splittedCommand.at(0);
	QString newState = splittedCommand.at(1);
	QString action = splittedCommand.at(2);
	unsigned int oldTapePointer = tape->getTapePointer();

	/* Устанавливаем новый символ в старую позицию ленты */
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
		machineState = MachineState::FINISHED;
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
	emit tapeChanged();
}

void Machine::stopWork()
{
	machineState = MachineState::FINISHED;
	emit machineStopped();
}

void Machine::verifyTape()
{
	bool isOk = true;
	QStringList tapeView = tape->getTapeView();
	QString emptySymbol = tape->getEmptySymbol();

	for (auto i : tapeView)
	{
		if (i != TAPE_BLANK && !controller->isAlphabetSymbolValid(i))
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
		tapeLoaded = false;
		emit machineError(message);
	}
	else
	{
		emit machineReady(true);
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
