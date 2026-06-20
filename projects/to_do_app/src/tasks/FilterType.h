#pragma once

#include <QObject>
#include <QQmlEngine>

class FilterType: public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("FilterType chỉ dùng để export enum, không tạo instance")
public:
    enum Type {
        All,
        Active,
        Completed
    };
    Q_ENUM(Type)

signals:
};
