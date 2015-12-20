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

QString Tape::getCurrentSymbol() const
{
	return tapeView.at(tapePointer);
}

QString Tape::getEmptySymbol() const
{
	return emptySymbol;
}

void Tape::setCurrentSymbol(const QString& symbol)
{
	tapeView[tapePointer] = symbol;
}

void Tape::setSymbolAt(const QString& symbol, unsigned int index)
{
	tapeView[index] = symbol;
}

void Tape::setCurrentTapePointer(int index) throw(QString&)
{
	int size = tapeView.size();

	/* Текущая лента в крайней левой позиции */
	if (index == size)
	{
		tapeView.push_back (emptySymbol);
		tapePointer = index;
	}
	else if (index == -1)
	{
		tapeView.push_front(emptySymbol);
		tapePointer = 0;
	}
	else if (index > size)
	{
		QString errorString = "Некорректное смещение головки ленты";
		throw errorString;
	}
	else
	{
		tapePointer = index;
	}

}

void Tape::setData(const QStringList &tapeView, unsigned int tapePointer, const QString& emptySymbol)
{
	this->tapeView	  = tapeView;
	this->tapePointer = tapePointer;
	this->emptySymbol = emptySymbol;
}

void Tape::reset()
{
	tapeView.clear();
	tapePointer = 0;
	emptySymbol.clear();
}
