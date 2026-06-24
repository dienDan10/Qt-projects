/**
 * @file      calculatoractionprovider.h
 * @author    diendanx
 * @date      2026-6-24
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef CALCULATORACTIONPROVIDER_H
#define CALCULATORACTIONPROVIDER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QString>

class CalculatorActionProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    explicit CalculatorActionProvider(QObject* parent = nullptr);

    Q_INVOKABLE void operandPress(QString numStr);
};

#endif // CALCULATORACTIONPROVIDER_H
