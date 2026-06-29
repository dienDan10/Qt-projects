/**
 * @file      itemmodel.h
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef ITEMMODEL_H
#define ITEMMODEL_H
#include <QAbstractTableModel>
#include "itemstore.h"
class ItemModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ItemModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex &index,
        int role = Qt::DisplayRole) const override;

    QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;

private:
    ItemStore* m_itemStore = nullptr;
};

#endif // ITEMMODEL_H
