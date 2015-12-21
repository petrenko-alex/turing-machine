#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include "controller.h"
#include "tape.h"

#define TAPE_BLANK	"-"
#define DEFAULT_EMPTY_SYMBOL ""

class Machine : public QObject
{
	Q_OBJECT

signals:
	void machineError(QString&);
	void machineFinished();
	void machineStopped();
	void tapeChanged();
	void tapeSymbolChanged(unsigned int index, QString newSymbol);
	void tapePointerChanged(unsigned int oldPos, unsigned int newPos);

public:
	Machine();
	~Machine();

	/* Сет-методы */
	void setTape(const QStringList& tapeView, 
				 unsigned int tapePointer,
				 const QString& emptySymbol = DEFAULT_EMPTY_SYMBOL);
	void setStates(const QStringList& states);
	void setAlphabet(const QStringList& alphabet);
	void setBeginEndStates(const QString& beginState,
						   const QString& endState) throw(QString&);
	void addComand(const QString& key, const Command& cmd) throw(QString&);
	void addState(const QString& state);
	void addSymbol(const QString& symbol);
	void appendToTape(const QString& symbol);
	void prependToTape(const QString& symbol);
	void incrementTapePointer();
	void decrementTapePointer();
	void setTapeSymbol(const QString& symbol, unsigned int index);
	void setCurrentState(const QString& state);
	void setBeginState(const QString& state);
	void setEndState(const QString& state);
	void setEmptySymbol(const QString& symbol);

	/* Гет-методы */
	QStringList  getTape() const;
	QString		 getEmptySymbol() const;
	QStringList  getAlphabet() const;
	unsigned int getTapePointer() const;
	QString		 getCurrentTapeSymbol() const;
	QString		 getCommand(const QString& key) const;
	QStringList  getStates(bool includeStopState) const;
	QString		 getBeginState() const;
	QString		 getEndState() const;
	QString		 getCurrentState() const;
	QStringList  exportTape() const;
	QMap<QString, Command> getCommands() const;
	

	/* Методы проверки и управления состоянием машины */
	bool isReady() const;
	bool isTapeLoaded() const;
	bool isControllerLoaded() const;
	bool isFinished() const;
	bool isTapeSymbolValid(const QString& symbol) const;
	bool isStateValid(const QString& state) const;
	bool isStateUnique(const QString& state) const;
	bool isSymbolUnique(const QString& symbol) const;
	void setControllerLoaded();
	void setTapeLoaded();

	/* Перезагрузка машины */
	void reset();

	/* Работа машины */
	void oneStep(bool emitSignals);
	void startWork();
	void stopWork();

private:
	/* Проверить, соответствует ли лента УУ */
	void verifyTape();
	unsigned int getNewTapePointer(const QString& action, unsigned int prevPointer);

	Tape*		tape;
	Controller* controller;
	bool tapeLoaded;
	bool controllerLoaded;

	enum class MachineState
	{
		IN_WORK,
		PAUSED,
		FINISHED,
	}machineState;
};

#endif // MACHINE_H
