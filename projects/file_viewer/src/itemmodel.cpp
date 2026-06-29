/**
 * @file      itemmodel.cpp
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "itemmodel.h"

ItemModel::ItemModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_itemStore = new ItemStore(this);
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
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal)
        return m_itemStore->headers().at(section);

    return section + 1;
}
