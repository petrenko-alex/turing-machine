#include "tape.h"

Tape::Tape()
{

}

Tape::~Tape()
{

}

QStringList Tape::getTapeView() const
{
	return tapeView;
}

unsigned int Tape::getTapePointer() const
{
	return tapePointer;
}

void Tape::setData(const QStringList &tapeView, unsigned int tapePointer)
{
	this->tapeView	 = tapeView;
	this->tapePointer = tapePointer;
}

void Tape::reset()
{
	tapeView.clear();
	tapePointer = 0;
}
