#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>

class Machine : public QObject
{
	Q_OBJECT

public:
	Machine(QObject *parent);
	~Machine();

private:
	
};

#endif // MACHINE_H
