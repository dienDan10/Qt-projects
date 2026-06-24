# Register C++ Types vào QML thủ công — Manual Registration

Dùng khi cần **control lifetime**, **inject dependency**, hoặc class có **multiple inheritance**
với non-QObject base (như `Store`, `Middleware`...). Không dùng macro trong header.

---

## Điều kiện tiên quyết

```cpp
#include <QQmlEngine>   // chứa các hàm qmlRegister*
```

Các hàm register phải được gọi **trước** khi `QQmlApplicationEngine` load file QML.
Nếu gọi sau `loadFromModule()` thì QML không nhận ra type.

```cpp
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // ✅ register TRƯỚC khi tạo QQmlApplicationEngine
    qmlRegisterSingletonInstance<MyClass>("myapp", 1, 0, "MyClass", ptr);

    QQmlApplicationEngine engine;
    engine.loadFromModule("myapp", "Main");

    return app.exec();
}
```

**Không cần** `QML_ELEMENT`, `QML_SINGLETON`, `QML_UNCREATABLE` trong header.
**Không cần** file `.h` nằm trong `SOURCES` của `qt_add_qml_module()` nếu không dùng macro.
Trộn lẫn macro và register thủ công cho cùng một class sẽ gây conflict — chỉ dùng một trong hai.

---

## 1. `qmlRegisterSingletonInstance` — Singleton từ instance có sẵn

Dùng khi bạn **tự tạo instance** và muốn QML dùng nó như singleton.
Engine **không own** instance — bạn tự quản lý lifetime.

```cpp
// calculatorengine.h — không cần macro nào
class CalculatorEngine : public QObject, public Store {
    Q_OBJECT
    Q_PROPERTY(QString expression READ expression NOTIFY expressionChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)
public:
    explicit CalculatorEngine(QObject *parent = nullptr);
    void process(const QSharedPointer<Action> &action) override;
    // ...
};
```

```cpp
// main.cpp
#include <QQmlEngine>
#include "calculatorengine.h"

void registerMetaData() {
    auto calcEngine = QSharedPointer<CalculatorEngine>::create();

    // lấy raw pointer trước khi move
    CalculatorEngine *rawPtr = calcEngine.get();

    // inject vào Dispatcher — move ownership
    Dispatcher::instance().registerStore<CalculatorAction>(std::move(calcEngine));

    // register vào QML — không transfer ownership
    qmlRegisterSingletonInstance<CalculatorEngine>(
        "calculator",   // URI — phải khớp với qt_add_qml_module URI
        1, 0,           // major, minor version
        "CalculatorEngine",  // tên dùng trong QML
        rawPtr
    );
}
```

**Dùng trong QML — phải import:**
```qml
import calculator

Text {
    text: CalculatorEngine.expression   // bind vào singleton
}
Button {
    onClicked: CalculatorEngine.input("5")
}
```

**Lưu ý lifetime:** instance phải sống lâu hơn `QQmlApplicationEngine`.
Đảm bảo bằng thứ tự khai báo trong `main()` — stack unwind theo thứ tự ngược:

```cpp
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    registerMetaData();              // tạo và register instance

    QQmlApplicationEngine engine;   // khai báo SAU → destroy TRƯỚC instance
    engine.loadFromModule("calculator", "Main");

    return app.exec();
}
```

---

## 2. `qmlRegisterType` — Instantiable type, tạo được từ QML

Dùng khi muốn QML có thể tạo instance trực tiếp bằng `MyClass { }`.

```cpp
// message.h — không cần macro
class Message : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
public:
    explicit Message(QObject *parent = nullptr);
    // ...
};
```

```cpp
// main.cpp
qmlRegisterType<Message>(
    "com.mycompany.messaging",  // URI
    1, 0,                       // major, minor version
    "Message"                   // tên trong QML
);
```

**Dùng trong QML:**
```qml
import com.mycompany.messaging

Message {
    author: "Amelie"
}
```

---

## 3. `qmlRegisterUncreatableType` — Visible nhưng không tạo được

Dùng khi muốn expose **enum** hoặc dùng làm kiểu property, nhưng không cho QML tạo instance.

```cpp
// filtertype.h — không cần macro
class FilterType : public QObject {
    Q_OBJECT
public:
    enum Type { All, Active, Completed };
    Q_ENUM(Type)
};
```

```cpp
// main.cpp
qmlRegisterUncreatableType<FilterType>(
    "myapp",
    1, 0,
    "FilterType",
    "FilterType chỉ dùng để export enum, không tạo instance"
);
```

**Dùng trong QML:**
```qml
import myapp

// Dùng enum OK:
dispatcher.setFilter(FilterType.Active)

// KHÔNG được tạo instance:
// FilterType { }  ← runtime error với message trên
```

---

## 4. `qmlRegisterSingletonType` — Singleton với factory function

Dùng khi cần **factory function** để tạo singleton — ví dụ singleton cần
khởi tạo phức tạp hoặc cần tham số từ engine.

```cpp
// appconfig.h
class AppConfig : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme NOTIFY themeChanged)
public:
    explicit AppConfig(QObject *parent = nullptr);
    static AppConfig *create(QQmlEngine *engine, QJSEngine *scriptEngine);
    // ...
};
```

```cpp
// appconfig.cpp
AppConfig *AppConfig::create(QQmlEngine *, QJSEngine *) {
    // factory function — engine gọi hàm này để tạo instance
    // engine sẽ own instance trả về
    return new AppConfig();
}
```

```cpp
// main.cpp
qmlRegisterSingletonType<AppConfig>(
    "myapp",
    1, 0,
    "AppConfig",
    AppConfig::create   // factory function pointer
);
```

**Dùng trong QML:**
```qml
import myapp

Rectangle {
    color: AppConfig.theme === "dark" ? "#1E1E1E" : "white"
}
```

**Khác với `qmlRegisterSingletonInstance`:**

| | `qmlRegisterSingletonInstance` | `qmlRegisterSingletonType` |
|---|---|---|
| Instance tạo bởi | Bạn tạo trước | Engine gọi factory khi cần |
| Ownership | Bạn giữ | Engine owns |
| Dùng khi | Cần inject dependency | Singleton đơn giản, không cần inject |

---

## 5. `qmlRegisterAnonymousType` — Không tạo được, không tham chiếu được

Dùng cho base class hoặc type mà QML không cần biết tên,
nhưng engine cần biết để coerce subtype.

```cpp
// baseprocessor.h
class BaseProcessor : public QObject {
    Q_OBJECT
public:
    // ...
};
```

```cpp
// main.cpp
qmlRegisterAnonymousType<BaseProcessor>("myapp", 1);
```

QML không thể dùng `BaseProcessor` trực tiếp, nhưng engine nhận ra
các subclass của nó khi được expose qua property.

---

## Bảng so sánh nhanh

| Hàm | Tạo được từ QML | Visible với QML | Cần import | Dùng khi |
|---|:---:|:---:|:---:|---|
| `qmlRegisterSingletonInstance` | ❌ engine dùng instance có sẵn | ✅ | ✅ | Singleton cần inject dependency |
| `qmlRegisterSingletonType` | ❌ engine tạo qua factory | ✅ | ✅ | Singleton đơn giản, engine owns |
| `qmlRegisterType` | ✅ | ✅ | ✅ | Type thông thường, instantiable |
| `qmlRegisterUncreatableType` | ❌ | ✅ | ✅ | Chỉ expose enum / làm kiểu property |
| `qmlRegisterAnonymousType` | ❌ | ❌ | N/A | Base class ẩn |

---

## Macro vs Manual — chọn cái nào

| Tình huống | Dùng |
|---|---|
| Class đơn giản, không cần inject | Macro (`QML_ELEMENT`, `QML_SINGLETON`...) |
| Cần inject vào Dispatcher / Service | `qmlRegisterSingletonInstance` |
| Multiple inheritance với non-QObject base | `qmlRegisterSingletonInstance` |
| Class từ thư viện ngoài, không sửa được | `QML_FOREIGN` (macro) hoặc `qmlRegisterType` |
| Cùng một class | **Chỉ dùng một trong hai — không trộn lẫn** |
