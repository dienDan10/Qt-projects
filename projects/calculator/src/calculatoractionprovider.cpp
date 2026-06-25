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
#include <QSharedDataPointer>
#include "calculatoraction.h"
#include "../flux/dispatcher.h"
#include "../flux/action.h"

CalculatorActionProvider::CalculatorActionProvider(QObject *parent) : QObject(parent)
{

}

void CalculatorActionProvider::operandPress(QString numStr)
{
    auto action = QSharedPointer<Action>::create(CalculatorAction::PRESS_OPERAND, QVariant(numStr));
    emit Dispatcher::instance().actionDispatched(action);
}

void CalculatorActionProvider::operatorPress(QString operatorStr)
{
    auto action = QSharedPointer<Action>::create(CalculatorAction::PRESS_OPERATOR, QVariant(operatorStr));
    emit Dispatcher::instance().actionDispatched(action);
}

void CalculatorActionProvider::equalPress()
{
    auto action = QSharedPointer<Action>::create(CalculatorAction::PRESS_EQUAL);
    emit Dispatcher::instance().actionDispatched(action);
}

void CalculatorActionProvider::backspacePress()
{
    auto action = QSharedPointer<Action>::create(CalculatorAction::PRESS_BACKSPACE);
    emit Dispatcher::instance().actionDispatched(action);
}

void CalculatorActionProvider::acPress()
{
    auto action = QSharedPointer<Action>::create(CalculatorAction::PRESS_AC);
    emit Dispatcher::instance().actionDispatched(action);
}
