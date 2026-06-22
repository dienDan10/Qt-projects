#ifndef ACTION_H
#define ACTION_H

#include <QVariant>
#include <typeindex>

template <typename T, bool B = std::is_enum<T>::value>
struct is_scoped_enum : std::false_type
{
};

template <typename T>
struct is_scoped_enum<T, true>
    : std::integral_constant<bool,
                             !std::is_convertible<T, typename std::underlying_type<T>::type>::value>
{
};

class Action final
{
public:
    template <class ScopedEnum, class = typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type>
    Action(ScopedEnum type, QVariant &payload, bool error = false)
        : type_(static_cast<int>(type)), payload_(payload), typeIndex_(typeid(ScopedEnum)), error_(error) {}

    template <class ScopedEnum, class = typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type>
    Action(ScopedEnum type, QVariant &&payload = QVariant(), bool error = false)
        : type_(static_cast<int>(type)), payload_(std::move(payload)), typeIndex_(typeid(ScopedEnum)), error_(error) {}

    Action(const Action &) = default;            // copy constructor
    Action(Action &&) = default;                 // move constructor
    Action &operator=(const Action &) = default; // copy assignment
    Action &operator=(Action &&) = default;      // move assignment
    ~Action() = default;

    template <class ScopedEnum, class = typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type>
    ScopedEnum getType() const
    {
        return static_cast<ScopedEnum>(type_);
    }

    std::type_index typeIndex() const { return typeIndex_; }

    template <class T>
    T getPayload() const
    {
        return qvariant_cast<T>(payload_);
    }

    bool getError() const
    {
        return error_;
    }

private:
    int type_;
    QVariant payload_;
    std::type_index typeIndex_;
    bool error_;
};

#endif // ACTION_H
