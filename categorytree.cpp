#include <QtWidgets>

#include "categorytree.h"

CategoryTree::CategoryTree(QObject *parent)
	: QAbstractItemModel(parent)
{

}

CategoryTree::~CategoryTree()
{

}

int CategoryTree::columnCount(const QModelIndex & /* parent */) const
{
	return 0;
}

QVariant CategoryTree::data(const QModelIndex &index, int role) const
{
	return QVariant();
}

//flags of TreeModel
Qt::ItemFlags CategoryTree::flags(const QModelIndex &index) const
{
	return NULL;
}

QVariant CategoryTree::headerData(int section, Qt::Orientation orientation,
							   int role) const
{
	return QVariant();
}

QModelIndex CategoryTree::index(int row, int column, const QModelIndex &parent) const
{
	return QModelIndex();
}

bool CategoryTree::insertColumns(int position, int columns, const QModelIndex &parent)
{
	return false;
}

bool CategoryTree::insertRows(int position, int rows, const QModelIndex &parent)
{
	return false;
}

QModelIndex CategoryTree::parent(const QModelIndex &index) const
{
	return QModelIndex();
}

bool CategoryTree::removeColumns(int position, int columns, const QModelIndex &parent)
{
	return false;
}

bool CategoryTree::removeRows(int position, int rows, const QModelIndex &parent)
{
	return false;
}

int CategoryTree::rowCount(const QModelIndex &parent) const
{
return 0;
}

//setData method of TreeModel
bool CategoryTree::setData(const QModelIndex &index, const QVariant &value, int role)
{
	return false;
}

bool CategoryTree::setHeaderData(int section, Qt::Orientation orientation,
							  const QVariant &value, int role)
{
	return false;
}
