/**
 * @file      itemdata.cpp
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "itemdata.h"

ItemData::ItemData() {}

QStringList ItemData::headers() const
{
    return m_headers;
}

QVariantList ItemData::rows() const
{
    return m_rows;
}

int ItemData::rowsCount() const
{
    return m_rows.length();
}

int ItemData::colsCount() const
{
    return m_headers.length();
}

bool ItemData::setHeaders(QStringList &header)
{
    m_headers = header;
    return true;
}

bool ItemData::setRows(QVariantList &rows)
{
    m_rows = rows;
    return true;
}
