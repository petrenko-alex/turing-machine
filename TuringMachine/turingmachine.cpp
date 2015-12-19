#include "turingmachine.h"

TuringMachine::TuringMachine(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	machine = new Machine;
	setConnections();
}

TuringMachine::~TuringMachine()
{
	delete machine;
}

void TuringMachine::importTape()
{
	/*QString fileName = QFileDialog::getOpenFileName( this, 
													 "Выберите файл ленты", 
													 "./", 
													 "JSON файлы(*.json)");*/
	QString fileName = DEFAULT_TAPE_FILE;

	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QDataStream stream(&file);
			QString data = file.readAll();

			try
			{
				auto tuple = parseTapeFile(data);

				machine->setTape(	std::get<0>(tuple),
									std::get<1>(tuple));
			}
			catch (QString& errorString)
			{
				QMessageBox::critical(this, "Ошибка разбора файла \"" + fileName + "\"", errorString);
				return;
			}
			file.close();
		}
	}
}

void TuringMachine::exportTape()
{
	// #TODO: Сохранение ленты в json файл.
}

void TuringMachine::importController()
{
	/*QString fileName = QFileDialog::getOpenFileName( this,
	"Выберите файл ленты",
	"./",
	"JSON файлы(*.json)");*/
	QString fileName = DEFAULT_TAPE_FILE;

	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QDataStream stream(&file);
			QString data = file.readAll();
		}
	}

}

void TuringMachine::exportController()
{
	// #TODO: Сохранение УУ в json файл.
}

void TuringMachine::machineStep()
{
	// #TODO: Один шаг машины.
}

void TuringMachine::machineBeginWork()
{
	// #TODO: Начать работу машины.
}

void TuringMachine::machineStopWork()
{
	// #TODO: Остановать работу машины.
}

void TuringMachine::setConnections()
{
	connect(ui.step, SIGNAL(clicked(bool)), SLOT(machineStep ()));
	connect(ui.stop, SIGNAL(clicked(bool)), SLOT(machineStopWork()));
	connect(ui.exportTape, SIGNAL(clicked(bool)), SLOT(exportTape()));
	connect(ui.importTape, SIGNAL(clicked(bool)), SLOT(importTape()));
	connect(ui.begin, SIGNAL(clicked(bool)), SLOT(machineBeginWork()));
	connect(ui.exportController, SIGNAL(clicked(bool)), SLOT(exportController()));
	connect(ui.importController, SIGNAL(clicked(bool)), SLOT(importController()));
}

std::tuple<QStringList, unsigned int> TuringMachine::parseTapeFile(const QString &data) const throw(QString&)
{
	QStringList list;
	unsigned int number;

	QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
	QJsonObject obj = doc.object();

	if (obj.contains("tape-view"))
	{
		QJsonArray arr = obj["tape-view"].toArray();

		for (auto i : arr)
		{
			QString tmp = i.toString();
			list << tmp;
		}
	}
	else
	{
		QString errorString = "Не найдены данные о состоянии ленты по тегу \"tape-view\"";
		throw errorString;
	}

	if (obj.contains("pointer-index"))
	{
		number = obj["pointer-index"].toInt();
	}
	else
	{
		QString errorString = "Не найдены данные об указателе ленты по тегу \"pointer-index\"";
		throw errorString;
	}

	return std::make_tuple(list, number);
}
