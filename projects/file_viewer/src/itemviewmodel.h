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
    Q_PROPERTY(QString helloText READ helloText)
public:
    explicit ItemViewModel(QObject* parent = nullptr);

    QString helloText();
};

#endif // ITEMVIEWMODEL_H
