#include "tape.h"

Tape::Tape()
{

}

Tape::~Tape()
{

}

void Tape::setData(const QStringList &tapeView, unsigned int tapePointer)
{
	_tapeView	 = tapeView;
	_tapePointer = tapePointer;
}
