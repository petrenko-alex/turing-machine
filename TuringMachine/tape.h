#ifndef TAPE_H
#define TAPE_H

#include <QObject>

#define TAPE_BLANK	"-"

class Tape : public QObject
{
	Q_OBJECT

public:
	Tape();
	~Tape();

	void setData(const QStringList &tapeView,
				 unsigned int tapePointer,
				 const QString& emptySymbol);
	void reset();

	QStringList  getTapeView() const;
	unsigned int getTapePointer() const;
	QString		 getCurrentSymbol() const;
	QString		 getEmptySymbol() const;

	void		 setCurrentSymbol(const QString& symbol);
	void		 setSymbolAt(const QString& symbol, unsigned int index);
	void		 setCurrentTapePointer(int index) throw(QString&);
	void		 appendToTape(const QString &symbol);
	void		 prependToTape(const QString &symbol);
	void		 incrementPointer();
	void	     decrementPointer();

private:
	friend class Tape;
	QStringList  tapeView;
	unsigned int tapePointer;
	QString		 emptySymbol;
};

#endif // TAPE_H
