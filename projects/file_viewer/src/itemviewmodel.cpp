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

ItemViewModel::ItemViewModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    auto itemModel = new ItemModel();
    this->setSourceModel(itemModel);
}

QString ItemViewModel::helloText()
{
    return "Hello from view model";
}
