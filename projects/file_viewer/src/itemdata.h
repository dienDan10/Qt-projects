/**
 * @file      itemdata.h
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <QList>
#include <QVariant>
#include <DataType.h>

class ItemData
{
public:
    ItemData();

    QStringList headers() const;
    QVariantList rows() const;
    QList<DataType> dataTypes() const;
    int rowsCount() const;
    int colsCount() const;
    bool setHeaders(QStringList& header);
    bool setRows(QVariantList& rows);
    bool setDataType(QList<DataType>& types);

private:
    QStringList m_headers{};
    QVariantList m_rows{};
    QList<DataType> m_columnTypes{};
};

#endif // ITEMDATA_H
