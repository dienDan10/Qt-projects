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
#include <QVector>
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

    template <class... Args>
    void registerMiddleWare(Args &&...args)
    {
        middlewares.push_back(QSharedPointer<Middleware>::create(std::forward<Args>(args)...));
    }

    template <class... Args>
    void registerStore(Args &&...args)
    {
        stores.push_back(QSharedPointer<Store>::create(std::forward<Args>(args)...));
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
        for (const auto &middleware : middlewares)
        {
            action = middleware->process(action);
            if (!action) return;
        }

        for (const auto &store : stores)
        {
            store->process(action);
        }
    }

private:
    QVector<QSharedPointer<Middleware>> middlewares;
    QVector<QSharedPointer<Store>> stores;
};

#endif // DISPATCHER_H
