#ifndef TAPE_H
#define TAPE_H

#include <QObject>

class Tape : public QObject
{
	Q_OBJECT

public:
	Tape();
	~Tape();

	void setData(const QStringList &tapeView,unsigned int tapePointer);
	void reset();

private:
	QStringList  tapeView;
	unsigned int tapePointer;
};

#endif // TAPE_H
