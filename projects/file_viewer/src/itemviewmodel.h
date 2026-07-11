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
#include <QTimer>

class ItemViewModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_UNCREATABLE("Cannot create ItemViewModel from QML")
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged FINAL)
    Q_PROPERTY(int rowsCount READ rowCount NOTIFY rowsCountChanged FINAL)
    Q_PROPERTY(int columnsCount READ columnCount NOTIFY columnsCountChanged FINAL)
public:
    explicit ItemViewModel(QObject* parent = nullptr);

    QString searchText();
    void setSearchText(const QString& text);

private slots:
    void handleColumnSort(const int columnIndex);

signals:
    void searchTextChanged();
    void rowsCountChanged();

protected:
    bool filterAcceptsRow(
        int sourceRow,
        const QModelIndex &sourceParent) const override;

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
    QString m_searchText{};
    QTimer* m_debounceTimer;
};

#endif // ITEMVIEWMODEL_H
