#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include "controller.h"
#include "tape.h"


class Machine : public QObject
{
	Q_OBJECT

signals:
	void machineError(QString&);
	void machineFinished();
	void tapeSymbolChanged(unsigned int index, QString newSymbol);
	void tapePointerChanged(unsigned int oldPos, unsigned int newPos);

public:
	Machine();
	~Machine();

	/* Сет-методы */
	void setTape(const QStringList& tapeView, 
				 unsigned int tapePointer,
				 const QString& emptySymbol);
	void setStates(const QStringList& states);
	void setCurrentState(const QString& state);
	void setAlphabet(const QStringList& alphabet);
	void setBeginEndStates(const QString& beginState,
						   const QString& endState) throw(QString&);
	void addComand(const QString& key, const Command& cmd) throw(QString&);

	/* Гет-методы */
	QStringList  getTape() const;
	QString		 getEmptySymbol() const;
	QString		 getCurrentState() const;
	QStringList  getAlphabet() const;
	unsigned int getTapePointer() const;
	QString		 getCurrentTapeSymbol() const;
	QString		 getCommand(const QString& key) const;
	QStringList  getStates(bool includeStopState) const;

	/* Методы проверки и управления состоянием машины */
	bool isReady() const;
	bool isTapeLoaded() const;
	bool isControllerLoaded() const;
	bool isFinished() const;
	void setTapeLoaded();
	void setControllerLoaded();

	/* Перезагрузка машины */
	void reset();

	/* Работа машины */
	void oneStep();
	void startWork();

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
