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
