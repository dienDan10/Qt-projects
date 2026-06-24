/**
 * @file      calculatoractionprovider.cpp
 * @author    diendanx
 * @date      2026-6-24
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "calculatoractionprovider.h"
#include <QDebug>

CalculatorActionProvider::CalculatorActionProvider(QObject *parent) : QObject(parent)
{

}

void CalculatorActionProvider::operandPress(QString numStr)
{
    qInfo() << numStr << " button pressed";
}
