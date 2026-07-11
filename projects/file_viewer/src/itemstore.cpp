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
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

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

    // m_itemData = FileParser::parseFile(path);
    auto future = QtConcurrent::run(FileParser::parseFile, path);
    auto watcher = new QFutureWatcher<ItemData>();

    connect(watcher, &QFutureWatcher<ItemData>::finished, this, [watcher, this](){
        try {
            m_itemData = watcher->result();
            emit modelReset();
            watcher->deleteLater();
        }
        catch (QString& error) {
            Q_UNUSED(error)
        }
    });

    watcher->setFuture(future);
}

void ItemStore::handleSortColumn(const int columnIndex)
{
    emit sortColumn(columnIndex);
}
