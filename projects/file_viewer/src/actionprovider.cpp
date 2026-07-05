/**
 * @file      actionprovider.cpp
 * @author    diendanx
 * @date      2026-7-4
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include <QSharedPointer>
#include "actionprovider.h"
#include "ItemAction.h"
#include "flux/dispatcher.h"
#include "flux/action.h"
ActionProvider::ActionProvider(QObject *parent)
    : QObject{parent}
{}

void ActionProvider::loadFile(const QUrl &fileUrl)
{
    auto action = QSharedPointer<Action>::create(ItemAction::OPEN_FILE, QVariant(fileUrl));
    emit Dispatcher::instance().actionDispatched(action);
}

void ActionProvider::sortColumn(const int columnIndex)
{
    auto action = QSharedPointer<Action>::create(ItemAction::SORT_COLUMN, QVariant(columnIndex));
    emit Dispatcher::instance().actionDispatched(action);
}
