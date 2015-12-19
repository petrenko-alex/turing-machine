#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include "controller.h"
#include "tape.h"

class Machine : public QObject
{
	Q_OBJECT

public:
	Machine(QObject *parent);
	~Machine();

private:
	Tape* _tape;
	Controller* _controller;
};

#endif // MACHINE_H
