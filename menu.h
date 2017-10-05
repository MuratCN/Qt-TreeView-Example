#ifndef MENU_H
#define MENU_H

#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QString>

class Menu
{
public:
	Menu();
	Menu(QString name, QString id = "");
	Menu(QString name, QList<Menu> subCategories, QString id = "");

	QString name() const;
	void setName(const QString name);

	QString id() const;
	void setId(const QString id);

	QList<Menu> subCategories() const;
	void setSubCategories(const QList<Menu> subCategories);

	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;
private:
	QString mName;
	QString mId;
	QList<Menu> mSubCategories;

};

#endif // MENU_H
