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
#include "itemdata.h"

class ItemStore : public QObject
{
    Q_OBJECT
public:
    explicit ItemStore(QObject *parent = nullptr);

    int rowsCount();
    int colsCount();
    QStringList headers();
    QVariantList rows();

signals:

private:
    ItemData m_itemData;
};

#endif // ITEMSTORE_H
