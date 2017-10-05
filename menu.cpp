#include "menu.h"

Menu::Menu()
{
}

Menu::Menu(QString name, QString id, Menu *parent) :
	mName(name),
	mId(id),
	mParent(parent)
{
	Menu();
}

Menu::Menu(QString name, QString id, QList<Menu> subCategories, Menu *parent):
	mSubCategories(subCategories)
{
	Menu(name,id,parent);
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

bool Menu::checked() const
{
	return mChecked;
}

void Menu::setChecked(const bool checked)
{
	mChecked = checked;
}

QList<Menu> Menu::subCategories() const
{
	return mSubCategories;
}

void Menu::setSubCategories(const QList<Menu> subCategories)
{
	mSubCategories = subCategories;
}

void Menu::addSubCategory(const Menu &menu)
{
	mSubCategories.append(menu);
}

void Menu::addSubCategory(const Menu &menu, int position)
{
	if(position != -1)
		mSubCategories.insert(position, menu);
	else
		mSubCategories.append(menu);
}

void Menu::removeSubCategory(const int position)
{
	//TODO alt kategorileri de sil
	mSubCategories.removeAt(position);
}

void Menu::removeSubCategory(const Menu &menu)
{
	mSubCategories.removeAt(mSubCategories.indexOf(menu));
}

void Menu::removeSubCategories()
{
	//TODO alt kategorileri sil
	mSubCategories.clear();
}

void Menu::addCategory(const Menu &menu, int position, const Menu *parent)
{
	if(parent != 0) {
		parent->addSubCategory(menu,position);
	} else {
		mParent->addSubCategory(menu,position);
	}
}

void Menu::removeCategory(const Menu &menu, const Menu *parent)
{
	if(parent != 0) {
		parent->removeSubCategory(menu);
	} else {
		mParent->removeSubCategory(menu);
	}
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
