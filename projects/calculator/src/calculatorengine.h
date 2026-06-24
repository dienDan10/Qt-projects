#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include <QObject>
#include <QString>
#include "flux/store.h"

class CalculatorEngine : public QObject, public Store
{
    Q_OBJECT
    Q_PROPERTY(QString expression READ expression NOTIFY expressionChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)
public:
    explicit CalculatorEngine(QObject *parent = nullptr);

    void process(const QSharedPointer<Action> &action) override;

    QString expression();
    QString result();

private:
    QString constructExpression();
    QString constructResult();

signals:
    void expressionChanged();
    void resultChanged();

private:
    enum class State {
        START,      // chưa có gì cả
        OPERAND_1,  // nhập số đầu tiên và sau khi ấn =, kết quả sẽ được lưu lại, state trở lại đây
        OPERATOR,   // nhập operator
        OPERAND_2   // nhập số thứ 2
    };

private:
    State m_state = State::START;
    QString m_operand_1{};
    QString m_operand_2{};
    QString m_operator{};
    const static int OPERAND_MAX_LENGTH = 5;
    const static int RESULT_MAX_LENGTH = 10;

};

#endif // CALCULATORENGINE_H
