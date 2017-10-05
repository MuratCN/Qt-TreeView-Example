#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

#include "category.h"

namespace Ui {
class Window;
}

class Window : public QWidget
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

	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;

private:
	Ui::Window *ui;
	Category mCategory;
};

#endif // WINDOW_H
