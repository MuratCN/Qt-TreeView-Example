#include "window.h"

Window::Window(QWidget *parent) :
	QMainWindow(parent)
{
	setupUi(this);

	if(!loadCategory(Json))
		return;

	QStringList headers;
	headers << tr("Selected") << tr("Title") << tr("Description");

	//	TODO tree model oluşturulacakk
	TreeModel *model = new TreeModel(headers,"");

	view->setModel(model); // Set custom tree view
	for (int column = 0; column < model->columnCount(); ++column)
		view->resizeColumnToContents(column);

	connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

	// Tree view selection changed
	//	connect(view->selectionModel(), &QItemSelectionModel::selectionChanged,
	//			this, &Window::updateActions);

	// Menu items triggered
	connect(actionsMenu, &QMenu::aboutToShow, this, &Window::updateActions);
	connect(insertRowAction, &QAction::triggered, this, &Window::insertRow);
	connect(insertColumnAction, &QAction::triggered, this, &Window::insertColumn);
	connect(removeRowAction, &QAction::triggered, this, &Window::removeRow);
	connect(removeColumnAction, &QAction::triggered, this, &Window::removeColumn);
	connect(insertChildAction, &QAction::triggered, this, &Window::insertChild);

}

Window::~Window()
{

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

void Window::updateActions()
{

}

void Window::insertChild()
{

}

bool Window::insertColumn()
{

}

void Window::insertRow()
{

}

bool Window::removeColumn()
{

}

void Window::removeRow()
{

}
