#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include "controller.h"
#include "tape.h"

#define TAPE_BLANK	"-"

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

	/* ���-������ */
	void setTape(const QStringList& tapeView, 
				 unsigned int tapePointer,
				 const QString& emptySymbol);
	void setStates(const QStringList& states);
	void setCurrentState(const QString& state);
	void setAlphabet(const QStringList& alphabet);
	void setBeginEndStates(const QString& beginState,
						   const QString& endState) throw(QString&);
	void addComand(const QString& key, const Command& cmd) throw(QString&);
	void appendToTape(const QString& symbol);
	void prependToTape(const QString& symbol);
	void incrementTapePointer();
	void decrementTapePointer();

	/* ���-������ */
	QStringList  getTape() const;
	QString		 getEmptySymbol() const;
	QString		 getCurrentState() const;
	QStringList  getAlphabet() const;
	unsigned int getTapePointer() const;
	QString		 getCurrentTapeSymbol() const;
	QString		 getCommand(const QString& key) const;
	QStringList  getStates(bool includeStopState) const;

	/* ������ �������� � ���������� ���������� ������ */
	bool isReady() const;
	bool isTapeLoaded() const;
	bool isControllerLoaded() const;
	bool isFinished() const;
	void setTapeLoaded();
	void setControllerLoaded();

	/* ������������ ������ */
	void reset();

	/* ������ ������ */
	void oneStep(bool emitSignals);
	void startWork();
	void stopWork();

private:
	/* ���������, ������������� �� ����� �� */
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
