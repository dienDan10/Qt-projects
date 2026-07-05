/**
 * @file      itemviewmodel.h
 * @author    diendanx
 * @date      2026-6-30
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef ITEMVIEWMODEL_H
#define ITEMVIEWMODEL_H
#include <QSortFilterProxyModel>
#include <QtQml/qqmlregistration.h>

class ItemViewModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_UNCREATABLE("Cannot create ItemViewModel from QML")
public:
    explicit ItemViewModel(QObject* parent = nullptr);

private slots:
    void handleColumnSort(const int columnIndex);

protected:
    // bool filterAcceptsRow(
    //     int sourceRow,
    //     const QModelIndex &sourceParent) const override;

    bool lessThan(
        const QModelIndex &left,
        const QModelIndex &right) const override;

private:
    enum class SortState {
        NONE,
        ASCENDING,
        DESCENDING
    };

    int m_sortColumn = -1;
    SortState m_sortState = SortState::NONE;
};

#endif // ITEMVIEWMODEL_H
