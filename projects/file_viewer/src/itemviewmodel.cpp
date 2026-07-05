/**
 * @file      itemviewmodel.cpp
 * @author    diendanx
 * @date      2026-6-30
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "itemviewmodel.h"
#include "itemmodel.h"
#include <QDate>

ItemViewModel::ItemViewModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    auto itemModel = new ItemModel();
    this->setSourceModel(itemModel);
    this->connect(itemModel, &ItemModel::signalSortColumn, this, &ItemViewModel::handleColumnSort);
}

QString ItemViewModel::searchText()
{
    return m_searchText;
}

void ItemViewModel::setSearchText(const QString &text)
{
    m_searchText = text.trimmed();
    emit searchTextChanged();

    invalidateFilter();
}

void ItemViewModel::handleColumnSort(const int columnIndex)
{
    if (m_sortColumn != columnIndex) {
        m_sortColumn = columnIndex;
        m_sortState = SortState::ASCENDING;
    } else {
        switch (m_sortState) {
        case SortState::NONE:
            m_sortState = SortState::ASCENDING;
            break;
        case SortState::ASCENDING:
            m_sortState = SortState::DESCENDING;
            break;
        case SortState::DESCENDING:
            m_sortState = SortState::NONE;
            break;
        default:
            return;
        }
    }

    switch(m_sortState) {
    case SortState::ASCENDING:
        sort(m_sortColumn, Qt::AscendingOrder);
        break;

    case SortState::DESCENDING:
        sort(m_sortColumn, Qt::DescendingOrder);
        break;

    case SortState::NONE:
        sort(-1);
        break;
    }
}

bool ItemViewModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_searchText.isEmpty()) return true;

    int columnCounts = sourceModel()->columnCount(sourceParent);

    for (int i = 0; i < columnCounts; i++) {
        QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
        QString value = sourceModel()->data(index).toString();
        if (value.contains(m_searchText, Qt::CaseInsensitive)) {
            return true;
        }
    }
    return false;
}

bool ItemViewModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    auto *model = qobject_cast<ItemModel*>(sourceModel());
    if (!model)
        return false;

    QList<DataType> columnTypes = model->columnsType();

    int column = left.column();
    DataType type = columnTypes.value(column);

    QVariant leftValue = sourceModel()->data(left);
    QVariant rightValue = sourceModel()->data(right);

    switch (type) {
    case DataType::INTERGER:
        return leftValue.toInt() < rightValue.toInt();
        break;
    case DataType::DOUBLE:
        return leftValue.toDouble() < rightValue.toDouble();
        break;
    case DataType::DATE:
        return leftValue.toDate() < rightValue.toDate();
        break;
    case DataType::STRING:
        return leftValue.toString() < rightValue.toString();
        break;
    default:
        return true;
    }
}
