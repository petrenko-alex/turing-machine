#ifndef TAPE_H
#define TAPE_H

#include <QObject>

class Tape : public QObject
{
	Q_OBJECT

public:
	Tape();
	~Tape();

	QStringList getTapeView() const;
	void setData(const QStringList &tapeView,unsigned int tapePointer);
	void reset();

private:
	friend class Tape;
	QStringList  tapeView;
	unsigned int tapePointer;
};

#endif // TAPE_H
