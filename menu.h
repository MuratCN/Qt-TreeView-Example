#ifndef MENU_H
#define MENU_H

#include <QList>
#include <QVariant>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QString>

class Menu
{
public:
	explicit Menu(Menu *parent = 0);
	explicit Menu(const QVector<QVariant> &data, Menu *parent = 0);
	~Menu();

	Menu *child(int number);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	Menu *parent();
	void setParent(Menu *parent);
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	int childNumber() const;
	bool setData(int column, const QVariant &value);
	void setChecked( bool set );
	bool isChecked();
	void setCheckState(Qt::CheckState cs);
	void setCheckStateAll(Qt::CheckState cs);
	Qt::CheckState getCheckState();
	void read(const QJsonObject &json, Menu *parent = 0);
	void write(QJsonObject &json) const;
	QList<Menu*> getSubCategories() const;
	void setSubCategories(const QList<Menu*> gSubCategories);

private:
	QList<Menu*> subCategories;
	QVector<QVariant> itemData; // sütun değerleri
	Menu *parentItem;
	bool checked;
	Qt::CheckState checkState;
	QString name;
	QString id;
};

#endif // MENU_H
