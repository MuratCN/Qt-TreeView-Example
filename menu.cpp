#include "menu.h"

Menu::Menu()
{
}

Menu::Menu(QString name, QList<Menu> subCategories, QString id):
	mName(name),
	mId(id),
	mSubCategories(subCategories)
{

}


QString Menu::name() const
{
	return mName;
}

void Menu::setName(const QString name)
{
	mName = name;
}

QString Menu::id() const
{
	return mId;
}

void Menu::setId(const QString id)
{
	mId = id;
}

QList<Menu> Menu::subCategories() const
{
	return mSubCategories;
}

void Menu::setSubCategories(const QList<Menu> subCategories)
{
	mSubCategories = subCategories;
}

void Menu::read(const QJsonObject &json)
{
	mSubCategories.clear();
	mId = json["cat_id"].toString();
	mName = json["name"].toString();

	QJsonArray subCategoryArray = json["subcategories"].toArray();
	for (int i = 0; i < subCategoryArray.size(); ++i) {
		QJsonObject menuObject = subCategoryArray[i].toObject();
		Menu menu;
		menu.read(menuObject);
		mSubCategories.append(menu);
	}
}

void Menu::write(QJsonObject &json) const
{
	json["cat_id"] = mId;
	json["name"] = mName;
	QJsonArray subCategoryArray;
	foreach (const Menu menu, mSubCategories) {
		QJsonObject menuObject;
		menu.write(menuObject);
		subCategoryArray.append(menuObject);
	}
	json["subcategories"] = subCategoryArray;
}
