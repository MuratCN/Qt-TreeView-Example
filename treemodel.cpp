#include <QtWidgets>

#include "menu.h"
#include "treemodel.h"

TreeModel::TreeModel(const QStringList &headers, const QByteArray &data, QObject *parent)
	: QAbstractItemModel(parent)
{
	QJsonDocument loadDoc(QJsonDocument::fromJson(data));
	QJsonObject json = loadDoc.object();


	QVector<QVariant> rootData;
	foreach (QString header, headers)
		rootData << header;

	rootItem = new Menu(rootData);

	setupModelData(json, rootItem);
	//	setupModelData(QString(data).split(QString("\n")), rootItem);
}

TreeModel::~TreeModel()
{
	delete rootItem;
}

void TreeModel::dataChangedR(const QModelIndex &index)
{
	int childCount = index.model()->rowCount(index);
	for (int i = 0; i < childCount; i++) {
		const QModelIndex &child = index.child(i, 0);
		dataChangedR(child);
	}
	emit dataChanged(index,index);
}

int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
	return rootItem->columnCount();
}

//data method of TreeModel
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	Menu *item1 = static_cast<Menu*>(index.internalPointer());

	//	qDebug() << Qt::ItemDataRole(role) << " -- " << QString::number(index.row())<< "-"<<QString::number(index.column());
	if ( role == Qt::CheckStateRole && index.column() == 0 )
	{
		return static_cast< int >( item1->isChecked() ? Qt::Checked : Qt::Unchecked );
	}
	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return QVariant();

	Menu *item = getItem(index);

	return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEditable | QAbstractItemModel::flags(index)|Qt::ItemIsUserCheckable;
	//	return Qt::ItemIsEditable | QAbstractItemModel::flags(index)|Qt::ItemIsUserCheckable;
	//	return Qt::ItemIsEditable | QAbstractItemModel::flags(index)|Qt::ItemIsTristate;
}

Menu *TreeModel::getItem(const QModelIndex &index) const
{
	if (index.isValid()) {
		Menu *item = static_cast<Menu*>(index.internalPointer());
		if (item)
			return item;
	}
	return rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
							   int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItem->data(section);

	return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	Menu *parentItem = getItem(parent);

	Menu *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
	bool success;

	beginInsertColumns(parent, position, position + columns - 1);
	success = rootItem->insertColumns(position, columns);
	endInsertColumns();

	return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	Menu *parentItem = getItem(parent);
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	success = parentItem->insertChildren(position, rows, rootItem->columnCount());
	endInsertRows();

	return success;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	Menu *childItem = getItem(index);
	Menu *parentItem = childItem->parent();

	if (parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
	bool success;

	beginRemoveColumns(parent, position, position + columns - 1);
	success = rootItem->removeColumns(position, columns);
	endRemoveColumns();

	if (rootItem->columnCount() == 0)
		removeRows(0, rowCount());

	return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	Menu *parentItem = getItem(parent);
	bool success = true;

	beginRemoveRows(parent, position, position + rows - 1);
	success = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return success;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
	Menu *parentItem = getItem(parent);

	return parentItem->childCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	//	if (!index.isValid()) {
	//           return;
	//    }
	qDebug()<<"data-role: "<< Qt::ItemDataRole(role);
	Menu *item = getItem(index);
	if(role == Qt::CheckStateRole)
	{
		qDebug()<<"Checked? "<<item->isChecked() << " Value: " << value;

		if(Qt::CheckState(value.toInt())==Qt::Checked) { // veya if(value.toInt()==Qt::Checked) {
			item->setChecked(true);
		} else if(Qt::CheckState(value.toInt())==Qt::PartiallyChecked) {

		} else { // if(Qt::CheckState(value.toInt())==Qt::Unchecked)
			item->setChecked(false);
		}
		dataChangedR(index);

		int childCount = index.model()->rowCount(index);
		qDebug()<<"child count: "<<QString::number(childCount);
		for (int i = 0; i < childCount; i++) {
			const QModelIndex &child = index.child(i, 0);
			emit dataChanged(child, child);
		}

		return true;
	}

	if (role != Qt::EditRole)
		return false;

	bool result = item->setData(index.column(), value);
	if (result)
		emit dataChanged(index, index);

	return result;
}



bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
							  const QVariant &value, int role)
{
	if (role != Qt::EditRole || orientation != Qt::Horizontal)
		return false;

	bool result = rootItem->setData(section, value);

	if (result)
		emit headerDataChanged(orientation, section, section);

	return result;
}


void TreeModel::setupModelData(const QJsonObject &json, Menu *parent)
{
	QList<Menu*> parents;

	QJsonArray categoryArray = json["categories"].toArray();
	for (int i = 0; i < categoryArray.size(); ++i) {
		QJsonObject categoryObject = categoryArray[i].toObject();
		Menu *category = new Menu();
		category->read(categoryObject,parent);
		parents << category;
	}

	parent->setSubCategories(parents);
}

void TreeModel::setupModelData(const QStringList &lines, Menu *parent)
{
	QList<Menu*> parents;
	QList<int> indentations;
	parents << parent;
	indentations << 0;

	int number = 0;

	while (number < lines.count()) {
		int position = 0;
		while (position < lines[number].length()) {
			if (lines[number].at(position) != ' ')
				break;
			++position;
		}

		QString lineData = lines[number].mid(position).trimmed();

		if (!lineData.isEmpty()) {
			// Read the column data from the rest of the line.
			QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
			QVector<QVariant> columnData;
			for (int column = 0; column < columnStrings.count(); ++column)
				columnData << columnStrings[column];

			if (position > indentations.last()) {
				// The last child of the current parent is now the new parent
				// unless the current parent has no children.

				if (parents.last()->childCount() > 0) {
					parents << parents.last()->child(parents.last()->childCount()-1);
					indentations << position;
				}
			} else {
				while (position < indentations.last() && parents.count() > 0) {
					parents.pop_back();
					indentations.pop_back();
				}
			}

			// Append a new item to the current parent's list of children.
			Menu *parent = parents.last();
			parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
			for (int column = 0; column < columnData.size(); ++column)
				parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
		}

		++number;
	}
}
