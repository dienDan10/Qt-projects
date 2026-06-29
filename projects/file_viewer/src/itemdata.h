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

class ItemData
{
public:
    ItemData();

    QStringList headers() const;
    QVariantList rows() const;
    int rowsCount() const;
    int colsCount() const;
    bool setHeaders(QStringList& header);
    bool setRows(QVariantList& rows);

private:
    QStringList m_headers{};
    QVariantList m_rows{};
};

#endif // ITEMDATA_H
