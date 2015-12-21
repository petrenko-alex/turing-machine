#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMap>

struct Command;

class Controller : public QObject
{
	Q_OBJECT

public:
	Controller();
	~Controller();

	bool setCurrentState(const QString& state);
	void setStates(const QStringList& states);
	void setAlphabet(const QStringList& alphabet);
	void setBeginEndStates(const QString& beginState,
						   const QString& endState) throw(QString&);
	void addComand(const QString& key, const Command& cmd) throw(QString&);

	QStringList getAlphabet() const;
	QStringList getStates(bool includeStopState) const;
	QString		getCurrentState() const;

	void reset();

private:
	friend class Machine;
	bool isStateValid(const QString& state) const;
	bool isAlphabetSymbolValid(const QString& symbol) const;

	QString endState;
	QString beginState;
	QString currentState;
	QStringList states;
	QStringList alphabet;
	QMap<QString, Command> commands;
};

struct Command
{
	QString newSymbol;
	QString newState;
	QString action;

	Command()
	{
		this->newSymbol = "";
		this->newState = "";
		this->action = "";
	}

	Command(const QString& newSymbol, const QString& newState, const QString& action)
	{
		this->newSymbol = newSymbol;
		this->newState = newState;
		this->action = action;
	}

	Command& operator=(const Command& other)
	{
		this->newSymbol = other.newSymbol;
		this->newState = other.newState;
		this->action = other.action;
		return *this;
	}
};

#endif // CONTROLLER_H
