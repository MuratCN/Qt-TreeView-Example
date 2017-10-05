#ifndef CATEGORY_H
#define CATEGORY_H

#include <QList>
#include <QJsonObject>
#include <QJsonArray>

#include "menu.h"

class Category
{
public:
	Category();
	Category(QList<Menu> menuList);

	QList<Menu> menuList() const;
	void menuList(const QList<Menu> menuList);

	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;
private:
	QList<Menu> mMenuList;
};

#endif // CATEGORY_H
