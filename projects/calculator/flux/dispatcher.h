/**
 * @file      dispatcher.h
 * @author    diendanx
 * @date      2026-6-22
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QSharedPointer>
#include "action.h"
#include "store.h"
#include "middleware.h"

class Dispatcher final : public QObject
{
    Q_OBJECT

public:
    static Dispatcher &instance()
    {
        static Dispatcher self;
        return self;
    }

    void registerMiddleWare(QSharedPointer<Middleware> middleware)
    {
        middlewares.push_back(std::move(middleware));
    }

    template<class ScopedEnum>
    void registerStore(QSharedPointer<Store> store) {
        auto it = stores.find(typeid(ScopedEnum));
        if (it == stores.end()) return;

        stores.insert(typeid(ScopedEnum), std::move(store));
    }

signals:
    void actionDispatched(QSharedPointer<Action> action);

private:
    Dispatcher()
    {
        connect(this, &Dispatcher::actionDispatched, this, &Dispatcher::onActionDispatched);
    }

    ~Dispatcher() = default;
    Dispatcher(const Dispatcher &) = delete;
    Dispatcher &operator=(const Dispatcher &) = delete;
    Dispatcher(Dispatcher &&) = delete;
    Dispatcher &operator=(Dispatcher &&) = delete;

private:
    void onActionDispatched(QSharedPointer<Action> action)
    {
        for (int i = 0; i < middlewares.size(); i++) {
            action = middlewares.at(i)->process(action);
            if (!action) return;
        }

        auto it = stores.find(action->typeIndex());
        if (it != stores.end()) {
            it.value()->process(action);
        }
    }

private:
    QList<QSharedPointer<Middleware>> middlewares;
    QHash<std::type_index, QSharedPointer<Store>> stores;
};

#endif // DISPATCHER_H
