/**
 * @file      actionprovider.h
 * @author    diendanx
 * @date      2026-7-4
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef ACTIONPROVIDER_H
#define ACTIONPROVIDER_H

#include <QObject>
#include <QUrl>
#include <QtQmlIntegration/qqmlintegration.h>

class ActionProvider : public QObject
{
    Q_OBJECT
    QML_UNCREATABLE("Cannot create ActionProvider from QML")
public:
    explicit ActionProvider(QObject *parent = nullptr);

    Q_INVOKABLE void loadFile(const QUrl& fileUrl);

signals:
};

#endif // ACTIONPROVIDER_H
