#include "controller.h"

Controller::Controller()
{

}

Controller::~Controller()
{

}

bool Controller::setCurrentState(const QString& state)
{
	if (isStateValid(state))
	{
		this->currentState = state;
		return true;
	}
	return false;
}

QString Controller::getCurrentState() const
{
	return currentState;
}

void Controller::setStates(const QStringList& states)
{
	this->states = states;
}

void Controller::setAlphabet(const QStringList& alphabet)
{
	this->alphabet = alphabet;
}

void Controller::setBeginEndStates(const QString& beginState, const QString& endState) throw(QString&)
{
	QString beginSt, endSt;

	if (isStateValid(beginState))
	{
		this->beginState = beginState;
		this->currentState = beginState;
	}
	else
	{
		QString errorString = "Начальное состояние задано не верно.\nОтсутствует в множестве состояний";
		throw errorString;
	}

	if (isStateValid(endState))
	{
		this->endState = endState;
	}
	else
	{
		QString errorString = "Конечное состояние задано не верно.\nОтсутствует в множестве состояний";
		throw errorString;
	}
}

void Controller::addComand(const QString& key, const Command& cmd) throw(QString&)
{
	if (!isAlphabetSymbolValid(cmd.newSymbol))
	{
		QString errorString = "Символ задан не верно.\nОтсутствует в алфавите.";
		throw errorString;
	}

	if (!isStateValid(cmd.newState))
	{
		QString errorString = "Cостояние задано не верно.\nОтсутствует в множестве состояний";
		throw errorString;
	}

	// #TODO: Проверка поля action
	commands.insert (key,cmd);
}

QStringList Controller::getStates(bool includeStopState) const
{
	QStringList tmpStates = states;
	if (!includeStopState)
	{
		int index = tmpStates.indexOf(endState);
		tmpStates.removeAt(index);
	}

	return tmpStates;
}

void Controller::reset()
{
	alphabet.clear();
	states.clear();
	beginState.clear();
	endState.clear();
	commands.clear();
}

QStringList Controller::getAlphabet() const
{
	return alphabet;
}

bool Controller::isStateValid(const QString& state) const
{
	return states.contains(state, Qt::CaseSensitive);
}

bool Controller::isAlphabetSymbolValid(const QString& symbol) const
{
	return alphabet.contains(symbol, Qt::CaseSensitive);
}
