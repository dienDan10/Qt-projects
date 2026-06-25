#include "calculatorengine.h"
#include <QStringliteral>
#include "action.h"
#include "calculatoraction.h"

CalculatorEngine::CalculatorEngine(QObject *parent) : QObject(parent) {}

void CalculatorEngine::process(const QSharedPointer<Action> &action)
{
    auto actionType = action->getType<CalculatorAction>();
    switch(actionType) {
    case CalculatorAction::PRESS_OPERAND:
        handleOperandPressed(action->getPayload<QString>());
        break;
    case CalculatorAction::PRESS_OPERATOR:
        handleOperatorPressed(action->getPayload<QString>());
        break;
    case CalculatorAction::PRESS_EQUAL:
        handleEqualPressed();
        break;
    case CalculatorAction::PRESS_AC:
        handleACPressed();
        break;
    case CalculatorAction::PRESS_BACKSPACE:
        handleBackspacePressed();
        break;
    default:
        return;
    }
}

void CalculatorEngine::handleOperandPressed(const QString& numStr)
{
    if (m_state == State::START) {
        m_state = State::OPERAND_1;
    }

    if (m_state == State::OPERAND_1 && m_operand_1.length() <= OPERAND_MAX_LENGTH) {
        m_operand_1.append(numStr);
        constructExpression();
        return;
    }

    if (m_state == State::OPERATOR) {
        m_state = State::OPERAND_2;
        m_operand_2.append(numStr);
        constructExpression();
        return;
    }

    if (m_state == State::OPERAND_2 && m_operand_2.length() <= OPERAND_MAX_LENGTH) {
        m_operand_2.append(numStr);
        constructExpression();
        return;
    }
}

void CalculatorEngine::handleOperatorPressed(const QString &operatorStr)
{
    if (m_state != State::OPERAND_1) return;

    m_state = State::OPERATOR;
    m_operator.append(operatorStr);
    constructExpression();
}

void CalculatorEngine::handleEqualPressed()
{
    if (m_state != State::OPERAND_2) return;

    double num1 = m_operand_1.toDouble();
    double num2 = m_operand_2.toDouble();

    if (m_operator == QStringLiteral("+")) {
        m_result = num1 + num2;
    }

    if (m_operator == QStringLiteral("-")) {
        m_result = num1 - num2;
    }

    if (m_operator == QStringLiteral("x")) {
        m_result = num1 * num2;
    }

    if (m_operator == QStringLiteral("/") && num2 != 0) {
        m_result = num1 / num2;
    }

    if (num2 == 0) {
        m_error = true;
    }

    m_state = State::STOP;
    emit resultChanged();
}

void CalculatorEngine::handleACPressed()
{
    m_state = State::START;
    m_expression = "";
    m_result = 0;
    m_operand_1 = "";
    m_operand_2 = "";
    m_operator = "";
    m_error = false;
    emit resultChanged();
    constructExpression();
}

void CalculatorEngine::handleBackspacePressed()
{
    if (m_state == State::START) return;

    if ((m_state == State::STOP || m_state == State::OPERAND_2) && !m_operand_2.isEmpty()) {
        m_operand_2.remove(m_operand_2.length() - 1, 1);
        m_state = m_operand_2.isEmpty() ? State::OPERATOR : State::OPERAND_2;
    }
    else if (m_state == State::OPERATOR) {
        m_state = State::OPERAND_1;
        m_operator.remove(m_operator.length() - 1, 1);
    }
    else if (m_state == State::OPERAND_1 && !m_operand_1.isEmpty()) {
        m_operand_1.remove(m_operand_1.length() - 1, 1);
        m_state = m_operand_1.isEmpty() ? State::START : State::OPERAND_1;
    }

    m_result = 0;
    m_error = false;
    constructExpression();
    emit resultChanged();
}

QString CalculatorEngine::expression()
{
    return m_expression;
}

QString CalculatorEngine::result()
{
    if (m_state != State::STOP) return "";
    if (m_error) return "ERROR";
    return QString::number(m_result, 'g', RESULT_MAX_LENGTH);
}

void CalculatorEngine::constructExpression()
{
    m_expression = QString {m_operand_1};
    if (!m_operator.isEmpty()) m_expression.append(" ").append(m_operator);
    if (!m_operand_2.isEmpty()) m_expression.append(" ").append(m_operand_2);
    emit expressionChanged();
}


