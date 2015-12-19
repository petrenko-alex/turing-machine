#include "tape.h"

Tape::Tape()
{

}

Tape::~Tape()
{

}

void Tape::setData(const QStringList &tapeView, unsigned int tapePointer)
{
	this->tapeView	 = tapeView;
	this->tapePointer = tapePointer;
}
