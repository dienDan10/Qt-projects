#ifndef TASKFILTERPROXY_H
#define TASKFILTERPROXY_H

#include <QQmlEngine>
#include <QSortFilterProxyModel>

class TaskFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int filter READ filter WRITE setFilter NOTIFY filterChanged)
public:
    enum Filter {
        All = 0,
        Active,
        Completed
    };
    Q_ENUM(Filter)

    explicit TaskFilterProxy(QObject* parent = nullptr);

    int filter();
    void setFilter(int filter);

signals:
    void filterChanged();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    int m_filter = All;
};

#endif // TASKFILTERPROXY_H
