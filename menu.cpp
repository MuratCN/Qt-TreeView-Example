#include "menu.h"

#include <QStringList>
#include <QDebug>

Menu::Menu(Menu *parent)
{
	parentItem = parent;
}

Menu::Menu(const QVector<QVariant> &data, Menu *parent)
{
	parentItem = parent;
	itemData = data;
}

Menu::~Menu()
{
	qDeleteAll(subCategories);
}

Menu *Menu::child(int number)
{
	return subCategories.value(number);
}

int Menu::childCount() const
{
	return subCategories.count();
}

int Menu::childNumber() const
{
	if (parentItem)
		return parentItem->subCategories.indexOf(const_cast<Menu*>(this));

	return 0;
}

int Menu::columnCount() const
{
	return itemData.count();
}

QVariant Menu::data(int column) const
{
	return itemData.value(column);
}

bool Menu::insertChildren(int position, int count, int columns)
{
	if (position < 0 || position > subCategories.size())
		return false;

	for (int row = 0; row < count; ++row) {
		QVector<QVariant> data(columns);
		Menu *item = new Menu(data, this);
		subCategories.insert(position, item);
	}

	return true;
}

bool Menu::insertColumns(int position, int columns)
{
	if (position < 0 || position > itemData.size())
		return false;

	for (int column = 0; column < columns; ++column)
		itemData.insert(position, QVariant());

	foreach (Menu *child, subCategories)
		child->insertColumns(position, columns);

	return true;
}

Menu *Menu::parent()
{
	return parentItem;
}

void Menu::setParent(Menu *parent)
{
	parentItem = parent;
}

bool Menu::removeChildren(int position, int count)
{
	if (position < 0 || position + count > subCategories.size())
		return false;

	for (int row = 0; row < count; ++row)
		delete subCategories.takeAt(position);

	return true;
}

bool Menu::removeColumns(int position, int columns)
{
	if (position < 0 || position + columns > itemData.size())
		return false;

	for (int column = 0; column < columns; ++column)
		itemData.remove(position);

	foreach (Menu *child, subCategories)
		child->removeColumns(position, columns);

	return true;
}

bool Menu::setData(int column, const QVariant &value)
{
	if (column < 0 || column >= itemData.size())
		return false;

	itemData[column] = value;
	return true;
}

//SetChecked function for Menu class
void Menu::setChecked( bool set )
{
	checked = set;
	foreach (Menu *category, subCategories) {
		category->setChecked(set);
	}
}

bool Menu::isChecked()
{
	return checked;
}

void Menu::setCheckState(Qt::CheckState cs)
{
	checkState = cs;
}

void Menu::setCheckStateAll(Qt::CheckState cs)
{
	checkState = cs;
	if(cs == Qt::PartiallyChecked)
		return;
	foreach (Menu *category, subCategories) {
		category->setCheckStateAll(cs);
	}
}

Qt::CheckState Menu::getCheckState()
{
	return checkState;
}

void Menu::read(const QJsonObject &json, Menu *parent)
{

	subCategories.clear();

	id = json["cat_id"].toString();//Gerek yok - itemData[1]
	name = json["name"].toString();//Gerek yok - itemData[2]
	//	checked = false;
	checkState = Qt::CheckState(0);

	itemData << 0;
	itemData << name;
	itemData << id;

	parentItem = parent;
	//	qDebug()<< name << "this: "<< this << " parent: " << parent;

	QJsonArray subCategoryArray = json["subcategories"].toArray();
	for (int i = 0; i < subCategoryArray.size(); ++i) {
		QJsonObject menuObject = subCategoryArray[i].toObject();
		Menu *menu = new Menu();
		menu->read(menuObject,this);
		subCategories.append(menu);
	}
}

void Menu::write(QJsonObject &json) const
{

}

QList<Menu*> Menu::getSubCategories() const
{
	return subCategories;
}

void Menu::setSubCategories(const QList<Menu*> gSubCategories)
{
	subCategories = gSubCategories;
}
