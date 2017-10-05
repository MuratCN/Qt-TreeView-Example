#include "category.h"

Category::Category()
{

}

Category::Category(QList<Menu> menuList) :
	mMenuList(menuList)
{

}

QList<Menu> Category::menuList() const
{
	return mMenuList;
}

void Category::menuList(const QList<Menu> menuList)
{
	mMenuList = menuList;
}

void Category::read(const QJsonObject &json)
{
	mMenuList.clear();
	QJsonArray categoryArray = json["categories"].toArray();
	for (int i = 0; i < categoryArray.size(); ++i) {
		QJsonObject categoryObject = categoryArray[i].toObject();
		Menu category;
		category.read(categoryObject);
		mMenuList.append(category);
	}
}

void Category::write(QJsonObject &json) const
{
	QJsonArray categoryArray;
	foreach (Menu category, mMenuList) {
		QJsonObject categoryObject;
		category.write(categoryObject);
		categoryArray.append(categoryObject);
	}
	json["categories"] = categoryArray;
}
