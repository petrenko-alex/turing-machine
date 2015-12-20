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

public:
	Machine();
	~Machine();

	void setTape(const QStringList& tapeView, unsigned int tapePointer);

	void setCurrentState(const QString& state);
	void setStates(const QStringList& states);
	void setAlphabet(const QStringList& alphabet);
	void setBeginEndStates(	const QString& beginState,
							const QString& endState) throw(QString&);
	void addComand(const QString& key, const Command& cmd) throw(QString&);

	QStringList getAlphabet() const;
	QStringList getStates(bool includeStopState) const;
	QStringList getTape() const;
	unsigned int getTapePointer() const;
	QString getCommand(const QString& key) const;
	QString getCurrentState() const;
	QString getCurrentTapeSymbol() const;


	bool isReady() const;
	bool isTapeLoaded() const;
	bool isControllerLoaded() const;
	void setTapeLoaded();
	void setControllerLoaded();

	void reset();

private:
	void verifyTape();

	Tape*		tape;
	Controller* controller;
	bool tapeLoaded;
	bool controllerLoaded;
};

#endif // MACHINE_H
