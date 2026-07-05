/**
 * @file      itemstore.cpp
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "itemstore.h"
#include "flux/action.h"
#include "ItemAction.h"
#include "fileparser.h"
#include <QDebug>

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

QList<DataType> ItemStore::columnTypes()
{
    return m_itemData.dataTypes();
}

void ItemStore::process(const QSharedPointer<Action> &action)
{
    auto actionType = action->getType<ItemAction>();
    switch (actionType) {
    case ItemAction::OPEN_FILE:
        handleLoadFile(action->getPayload<QUrl>());
        break;
    case ItemAction::SORT_COLUMN:
        handleSortColumn(action->getPayload<int>());
        break;
    default:
        return;
    }
}

void ItemStore::handleLoadFile(const QUrl &url)
{
    QString path = url.toLocalFile();

    try {
        m_itemData = FileParser::parseFile(path);
        emit modelReset();

    } catch (QString& error) {
        qInfo() << error;
    }
}

void ItemStore::handleSortColumn(const int columnIndex)
{
    emit sortColumn(columnIndex);
}
