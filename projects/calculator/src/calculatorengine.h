#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <QObject>
#include <QQmlEngine>

class CalculatorEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit CalculatorEngine(QObject *parent = nullptr);
};

#endif // CALCULATORENGINE_H
