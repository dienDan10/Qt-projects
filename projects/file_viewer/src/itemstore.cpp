/**
 * @file      itemstore.cpp
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "itemstore.h"

ItemStore::ItemStore(QObject *parent)
    : QObject{parent}
{}

int ItemStore::rowsCount()
{
    return m_itemData.rowsCount();
}

int ItemStore::colsCount()
{
    return m_itemData.colsCount();
}

QStringList ItemStore::headers()
{
    return m_itemData.headers();
}

QVariantList ItemStore::rows()
{
    return m_itemData.rows();
}
