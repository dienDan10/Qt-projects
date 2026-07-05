/**
 * @file      itemstore.h
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef ITEMSTORE_H
#define ITEMSTORE_H

#include <QObject>
#include <QUrl>
#include "itemdata.h"
#include "flux/store.h"

class ItemStore : public QObject, public Store
{
    Q_OBJECT
public:
    explicit ItemStore(QObject *parent = nullptr);

    int rowsCount();
    int colsCount();
    QStringList headers();
    QVariantList rows();
    QList<DataType> columnTypes();


    void process(const QSharedPointer<Action> &action) override;

private:
    void handleLoadFile(const QUrl& url);
    void handleSortColumn(const int columnIndex);

signals:
    void modelReset();
    void sortColumn(const int columnIndex);

private:
    ItemData m_itemData;
};

#endif // ITEMSTORE_H
