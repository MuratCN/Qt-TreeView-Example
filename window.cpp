#include "window.h"

Window::Window(QWidget *parent) :
	QWidget(parent)
{
	if(!loadCategory(Json))
		return;
	int i = 0;
}

Window::~Window()
{
	delete ui;
}


void Window::newCategory()
{
}

bool Window::loadCategory(Window::SaveFormat saveFormat)
{
	QFile loadFile(saveFormat == Json
				   ? QStringLiteral("save.json")
				   : QStringLiteral("save.dat"));

	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Couldn't open save file.");
		return false;
	}

	QByteArray saveData = loadFile.readAll();
	QJsonDocument loadDoc(saveFormat == Json
						  ? QJsonDocument::fromJson(saveData)
						  : QJsonDocument::fromBinaryData(saveData));
	read(loadDoc.object());

	return true;
}

bool Window::saveCategory(Window::SaveFormat saveFormat) const
{
	return true;
}

void Window::read(const QJsonObject &json)
{
	mCategory.read(json);
}

void Window::write(QJsonObject &json) const
{

}
