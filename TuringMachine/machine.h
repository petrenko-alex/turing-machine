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

	void setStates(const QStringList& states);
	void setAlphabet(const QStringList& alphabet);
	void setBeginEndStates(	const QString& beginState,
							const QString& endState) throw(QString&);
	void addComand(const QString& key, const Command& cmd) throw(QString&);

	QStringList getAlphabet() const;
	QStringList getStates(bool includeStopState) const;


	bool isReady() const;
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
