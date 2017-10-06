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
	Menu(QString name, QString id = "", Menu *parent = 0);
	Menu(QString name, QString id, QList<Menu> subCategories, Menu *parent = 0);

	Menu* parent() const;
	void setParent(Menu *parent);

	QString name() const;
	void setName(const QString name);

	QString id() const;
	void setId(const QString id);

	bool checked() const;
	void setChecked(const bool checked);

	void addSubCategory(const Menu &menu);
	void addSubCategory(const Menu &menu, int position = -1);
	void removeSubCategory(const int position);
	void removeSubCategory(const Menu &menu);
	void removeSubCategories();

	void addCategory(const Menu &menu, int position = -1, Menu *parent = 0);
	void removeCategory(const Menu &menu, Menu *parent = 0);

	QList<Menu> subCategories() const;
	void setSubCategories(const QList<Menu> subCategories);

	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;
private:
	Menu *mParent;
	QString mName;
	QString mId;
	bool mChecked;
	QList<Menu> mSubCategories;

};

#endif // MENU_H
