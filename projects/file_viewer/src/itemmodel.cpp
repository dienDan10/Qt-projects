/**
 * @file      itemmodel.cpp
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "itemmodel.h"
#include "flux/dispatcher.h"
#include "ItemAction.h"

ItemModel::ItemModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_itemStore = QSharedPointer<ItemStore>::create();
    Dispatcher::instance().registerStore<ItemAction>(m_itemStore);

    this->connect(m_itemStore.get(), &ItemStore::modelReset, this, &ItemModel::onModelReset);
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    return m_itemStore->rowsCount();
}

int ItemModel::columnCount(const QModelIndex &parent) const
{
    return m_itemStore->colsCount();
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return {};

    if (role != Qt::DisplayRole) return {};

    QVariantMap row = m_itemStore->rows().at(index.row()).toMap();
    QString header = m_itemStore->headers().at(index.column());

    return row.value(header);
}

QVariant ItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // we only want to return display data, here the role can be many things
    if (role != Qt::DisplayRole) return {};

    /*
     * For each section (which is an index), this method will be called for many roles
     * the display role is when it want the actual display data, other rows can be styles of
     * the cell
     * Then orientation will decide the headers for columns or rows
     * */

    // horizontal means header of the column
    if (orientation == Qt::Horizontal)
        return m_itemStore->headers().at(section);

    // here if not header for the column, we return header for the row, which is a number, section will start at index 0
    // so we add 1 to it
    return section + 1;
}

void ItemModel::onModelReset()
{
    beginResetModel();
    endResetModel();
}
