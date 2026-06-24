#include "calculatorengine.h"
#include <QStringliteral>

CalculatorEngine::CalculatorEngine(QObject *parent) : QObject(parent) {}

void CalculatorEngine::process(const QSharedPointer<Action> &action)
{

}

QString CalculatorEngine::expression()
{
    switch(m_state) {
    case State::START: return "";
    default:
        return constructExpression();
    }
}

QString CalculatorEngine::result()
{
    switch(m_state) {
    case State::OPERAND_2:
        return constructResult();
    default:
        return "";
    }
}

QString CalculatorEngine::constructExpression()
{
    QString expression{m_operand_1};
    if (!m_operator.isEmpty()) expression.append(" ").append(m_operator);
    if (!m_operand_2.isEmpty()) expression.append(" ").append(m_operand_2);
    return expression;
}

QString CalculatorEngine::constructResult()
{
    double op1 = m_operand_1.toDouble();
    double op2 = m_operand_2.toDouble();

    if (m_operator == QStringLiteral("+"))
        return QString::number(op1 + op2);

    if (m_operator == QStringLiteral("-"))
        return QString::number(op1 - op2);

    if (m_operator == QStringLiteral("x"))
        return QString::number(op1 * op2);

    if (m_operator == QStringLiteral("/"))
        return QString::number(op1 / op2);

    return "";
}
