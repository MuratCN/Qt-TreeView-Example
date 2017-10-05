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

	bool insertColumns(int columns);
	bool removeColumns(int columns);

	bool insertCategory(const Menu &category, int position);
	bool removeCategory(const Menu &category, int position);

	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;
private:
	QList<Menu> mMenuList;
};

#endif // CATEGORY_H
