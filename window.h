#ifndef WINDOW_H
#define WINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QModelIndex>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include "category.h"
#include "treemodel.h"


namespace Ui {
class Window;
}

class Window : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	explicit Window(QWidget *parent = 0);
	~Window();

	enum SaveFormat {
		Json, Binary
	};

	void newCategory();
	bool loadCategory(SaveFormat saveFormat);
	bool saveCategory(SaveFormat saveFormat) const;
	bool showCategory(SaveFormat saveFormat) const;

	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;

public slots:
	void updateActions();
private slots:
	void insertChild();
	bool insertColumn();
	void insertRow();
	bool removeColumn();
	void removeRow();
private:
	Category mCategory;
};

#endif // WINDOW_H
