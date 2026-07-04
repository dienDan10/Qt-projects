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

void ItemStore::process(const QSharedPointer<Action> &action)
{
    auto actionType = action->getType<ItemAction>();
    switch (actionType) {
    case ItemAction::OPEN_FILE:
        handleLoadFile(action->getPayload<QUrl>());
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
        // log the header
        auto headers = m_itemData.headers();
        QString header_text {};
        for (int i = 0; i < headers.length(); i++) {
            header_text.append(headers.at(i)).append(" ");
        }
        qInfo() << header_text;

        // log the row
        auto rows = m_itemData.rows();
        for (int i = 0; i < rows.length(); i++) {
            auto map = rows.at(i).toMap();
            QString row_text{};
            for (int j = 0; j < map.size(); j++) {
                row_text.append(map.value(headers.at(j)).toString()).append(" ");
            }
            qInfo() << row_text;
        }

        emit modelReset();

    } catch (QString& error) {
        qInfo() << error;
    }
}
