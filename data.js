const PROJECTS = {

  "01": {
    num: "01",
    title: "To-do List App",
    level: "beginner",
    levelLabel: "Beginner",
    workRelevant: false,
    time: "1–2 tuần",
    when: "Ngay sau khi học xong signals/slots trong khóa Intermediate",
    desc: "Project đầu tiên kết hợp C++ và QML: toàn bộ logic lưu trữ và xử lý dữ liệu nằm ở C++, giao diện người dùng hoàn toàn viết bằng QML. Đây là project học cách 'nói chuyện' giữa hai lớp — nền tảng của mọi Qt app thực tế.",
    requirements: [
      "Thêm, sửa, xóa task từ giao diện QML",
      "Đánh dấu task hoàn thành (checkbox)",
      "Lọc task theo trạng thái: All / Active / Completed",
      "Lưu danh sách xuống file JSON — restore lại khi mở app",
      "Hiển thị số lượng task còn lại"
    ],
    prereqs: ["QObject & Q_OBJECT macro", "Signals & slots cơ bản", "QML syntax: Rectangle, Text, Button, anchors", "Q_PROPERTY với NOTIFY signal"],
    learns: ["QAbstractListModel (rowCount, data, roleNames)", "QJsonDocument đọc ghi file", "QML ListView + delegate", "qt_add_qml_module trong CMake", "beginInsertRows / endInsertRows"],
    tools: ["Qt 6.11", "CMake + qt_add_qml_module", "QAbstractListModel", "QJsonDocument", "QFile", "QML ListView"],
    fileTree: `<span class="dir">todo-app/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">TaskModel.h</span>      <span class="comment">// QAbstractListModel</span>
│   ├── <span class="file-cpp">TaskModel.cpp</span>
│   ├── <span class="file-cpp">Task.h</span>            <span class="comment">// data struct</span>
│   └── <span class="file-cpp">TaskStorage.h/cpp</span> <span class="comment">// QJsonDocument I/O</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>
    ├── <span class="file-qml">TaskDelegate.qml</span>
    └── <span class="file-qml">FilterBar.qml</span>`,
    architecture: `<span class="hl">[ QML Layer ]</span>
  Main.qml
  └── ListView { model: taskModel }      <span class="arch-comment">// bind to C++ model</span>
      └── TaskDelegate.qml
          ├── onChecked → taskModel.setDone(index, true)
          └── onDeleteClicked → taskModel.remove(index)

<span class="arch-comment">     ↕  Q_PROPERTY / Q_INVOKABLE / signals</span>

<span class="hl-green">[ C++ Layer ]</span>
  TaskModel : QAbstractListModel
  ├── data()       → trả về Task fields theo role
  ├── setDone()    → Q_INVOKABLE, emit dataChanged
  ├── addTask()    → beginInsertRows → endInsertRows
  ├── remove()     → beginRemoveRows → endRemoveRows
  └── TaskStorage  → QJsonDocument load/save`,
    steps: [
      { title: "Setup CMake project", desc: "Tạo project Qt 6 với cmake, cấu hình qt_add_qml_module. Chạy được Hello World bằng QML trước." },
      { title: "Tạo struct Task", desc: "C++ struct đơn giản: id, title, done. Không cần QObject ở đây — chỉ là data container thuần." },
      { title: "Implement TaskModel", desc: "Kế thừa QAbstractListModel. Implement rowCount(), data(), roleNames(). Test bằng hard-coded data trước khi có UI." },
      { title: "Expose sang QML", desc: "Dùng QML_ELEMENT hoặc setContextProperty. Tạo ListView đơn giản hiển thị title của mỗi task." },
      { title: "Thêm interactions", desc: "Q_INVOKABLE addTask(), remove(), setDone(). Kết nối với Button và CheckBox trong QML." },
      { title: "Thêm filter", desc: "Dùng QSortFilterProxyModel để lọc theo trạng thái. Thêm FilterBar.qml với 3 nút." },
      { title: "Persist với JSON", desc: "TaskStorage: save() và load() bằng QJsonDocument. Gọi load() trong constructor, save() trong destructor hoặc mỗi khi data thay đổi." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "beginInsertRows() và endInsertRows() phải được gọi cặp đôi — thiếu một trong hai sẽ crash hoặc UI không cập nhật." },
      { type: "info", icon: "💡", text: "Dùng QML_ELEMENT (Qt 6 style) thay vì qmlRegisterType() — modern hơn và ít code hơn." },
      { type: "tip", icon: "✅", text: "Vòng 2: refactor TaskStorage thành class riêng biệt hoàn toàn tách khỏi TaskModel để tập separation of concerns." },
    ]
  },

  "02": {
    num: "02",
    title: "Calculator",
    level: "beginner",
    levelLabel: "Beginner",
    workRelevant: false,
    time: "1 tuần",
    when: "Song song hoặc ngay sau project 01",
    desc: "Xây một máy tính với toàn bộ logic tính toán đặt trong C++ và UI trong QML. Nghe đơn giản nhưng đây là cách luyện tập tách biệt logic/UI và hiểu property binding sâu hơn.",
    requirements: [
      "4 phép tính cơ bản: +, −, ×, ÷",
      "Hiển thị expression và result riêng biệt",
      "Xử lý chia cho 0, overflow",
      "Nút Clear và Backspace",
      "Keyboard input (phím số và phép tính)"
    ],
    prereqs: ["Q_INVOKABLE", "Q_PROPERTY + NOTIFY", "QML GridLayout hoặc Grid", "Property binding cơ bản"],
    learns: ["QML States & Transitions", "Tách logic C++ khỏi QML đúng cách", "Property binding nâng cao", "Keys.onPressed trong QML", "Xử lý edge case trong C++"],
    tools: ["Qt 6.11", "CMake", "QObject", "QML Grid / GridLayout", "QML Keys"],
    fileTree: `<span class="dir">calculator/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">Calculator.h</span>     <span class="comment">// QObject, Q_PROPERTY</span>
│   └── <span class="file-cpp">Calculator.cpp</span>   <span class="comment">// toàn bộ logic tính toán</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>
    ├── <span class="file-qml">Display.qml</span>      <span class="comment">// hiển thị expression/result</span>
    └── <span class="file-qml">CalcButton.qml</span>  <span class="comment">// reusable button</span>`,
    architecture: `<span class="hl">[ QML Layer ]</span>
  Main.qml
  ├── Display.qml
  │   ├── Text { text: calc.expression }   <span class="arch-comment">// Q_PROPERTY binding</span>
  │   └── Text { text: calc.result }
  └── Grid (buttons)
      └── CalcButton → onClicked: calc.input(value)

<span class="arch-comment">     ↕  Q_PROPERTY + Q_INVOKABLE</span>

<span class="hl-green">[ C++ Layer ]</span>
  Calculator : QObject
  ├── Q_PROPERTY expression READ expression NOTIFY expressionChanged
  ├── Q_PROPERTY result READ result NOTIFY resultChanged
  ├── Q_INVOKABLE void input(QString key)
  ├── Q_INVOKABLE void calculate()
  └── Q_INVOKABLE void clear()`,
    steps: [
      { title: "Calculator C++ class", desc: "QObject với 2 Q_PROPERTY: expression (string hiện tại) và result. Logic state machine trong C++: đang nhập số 1, đã nhập operator, đang nhập số 2." },
      { title: "QML UI cơ bản", desc: "Display + Grid layout cho các nút. CalcButton.qml là reusable component với property text và signal clicked(value)." },
      { title: "Kết nối C++ ↔ QML", desc: "Expose Calculator bằng QML_ELEMENT. Bind text của Display vào calc.expression và calc.result." },
      { title: "Keyboard support", desc: "Thêm Keys.onPressed trong Main.qml, forward key events vào calc.input(). Item phải có focus: true." },
      { title: "Error handling & edge cases", desc: "Chia cho 0 → hiển thị 'Error'. Số quá dài → giới hạn display. Operator ngay sau operator → replace." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "Đừng đặt logic tính toán trong QML. Binding như 'result: num1 + num2' thoạt nhìn tiện nhưng sẽ rất khó maintain và test." },
      { type: "tip", icon: "✅", text: "Dùng một string 'expression' duy nhất trong C++ để track toàn bộ input state thay vì nhiều biến riêng lẻ." },
      { type: "info", icon: "💡", text: "Vòng 2: thêm history log (danh sách các phép tính đã thực hiện) bằng QAbstractListModel tái dùng kiến thức từ project 01." },
    ]
  },

  "03": {
    num: "03",
    title: "File Viewer (CSV / JSON)",
    level: "beginner",
    levelLabel: "Beginner",
    workRelevant: false,
    time: "1–2 tuần",
    when: "Sau khi học module File I/O trong khóa Intermediate",
    desc: "Đọc file CSV hoặc JSON từ disk và hiển thị dạng bảng trong QML. Project này giúp nắm vững QAbstractTableModel — cần thiết cho mọi app hiển thị dữ liệu dạng bảng — và Qt file I/O.",
    requirements: [
      "Mở file CSV hoặc JSON qua dialog",
      "Parse và hiển thị dạng bảng với header",
      "Sort theo cột khi click header",
      "Search/filter realtime theo text",
      "Hiển thị tổng số hàng / cột"
    ],
    prereqs: ["QFile & QTextStream", "QAbstractListModel (project 01)", "QML TableView cơ bản"],
    learns: ["QAbstractTableModel", "QSortFilterProxyModel", "QML FileDialog (Qt 6)", "Parse CSV với QString::split", "QJsonDocument parse array"],
    tools: ["Qt 6.11", "CMake", "QAbstractTableModel", "QSortFilterProxyModel", "QML FileDialog", "QFile", "QTextStream"],
    fileTree: `<span class="dir">file-viewer/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">FileTableModel.h/cpp</span>  <span class="comment">// QAbstractTableModel</span>
│   ├── <span class="file-cpp">CsvParser.h/cpp</span>       <span class="comment">// parse CSV thuần</span>
│   └── <span class="file-cpp">JsonParser.h/cpp</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>
    ├── <span class="file-qml">DataTable.qml</span>
    └── <span class="file-qml">SearchBar.qml</span>`,
    architecture: `<span class="hl">[ QML Layer ]</span>
  Main.qml
  ├── FileDialog → onAccepted: model.loadFile(file)
  ├── SearchBar → onTextChanged: proxyModel.filterText = text
  └── DataTable.qml
      └── TableView { model: proxyModel }

<span class="arch-comment">     ↕  Q_PROPERTY + Q_INVOKABLE</span>

<span class="hl-green">[ C++ Layer ]</span>
  FileTableModel : QAbstractTableModel
  ├── loadFile(path) → detect CSV/JSON → parse
  ├── rowCount() / columnCount() / data() / headerData()
  └── data: QVector&lt;QStringList&gt; rows

  QSortFilterProxyModel (built-in Qt)
  ├── setSourceModel(&fileTableModel)
  ├── setFilterKeyColumn(-1)           <span class="arch-comment">// filter all columns</span>
  └── setFilterCaseSensitivity(...)`,
    steps: [
      { title: "FileTableModel cơ bản", desc: "Kế thừa QAbstractTableModel. Implement rowCount(), columnCount(), data(), headerData(). Test với hard-coded QVector<QStringList>." },
      { title: "CSV Parser", desc: "Dùng QFile + QTextStream đọc từng dòng. QString::split(',') cho các cột. Xử lý quoted fields (field có dấu phẩy bên trong)." },
      { title: "JSON Parser", desc: "QJsonDocument::fromJson(). Detect nếu root là array → mỗi object là một row. Extract keys từ first object làm header." },
      { title: "FileDialog trong QML", desc: "Qt 6 dùng FileDialog từ QtQuick.Dialogs. onAccepted trả về URL, cần convert sang path: model.loadFile(selectedFile.toString())." },
      { title: "Sort và Filter", desc: "Wrap FileTableModel trong QSortFilterProxyModel. Expose proxy lên QML. Kết nối SearchBar.text với proxy.filterFixedString." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "Khi load file lớn (> 10k dòng), parse trên main thread sẽ freeze UI. Vòng 2 hãy thử chuyển parse sang QThread." },
      { type: "info", icon: "💡", text: "QSortFilterProxyModel là built-in Qt, không cần tự viết. Chỉ cần setSourceModel() và setFilterKeyColumn(-1) là đã có filter toàn bộ cột." },
      { type: "tip", icon: "✅", text: "CSV thực tế thường có edge case: dòng trống, field có dấu phẩy trong quotes. Test với file CSV export từ Excel để gặp đủ trường hợp." },
    ]
  },

  "04": {
    num: "04",
    title: "System Monitor",
    level: "intermediate",
    levelLabel: "Intermediate",
    workRelevant: true,
    time: "2 tuần",
    when: "Sau khi học module QThread trong khóa Intermediate — đây là module quan trọng nhất",
    desc: "Đọc CPU và RAM usage mỗi giây từ một worker thread và cập nhật chart realtime trên QML mà không block UI. Project này dạy pattern quan trọng nhất trong mọi Qt app xử lý data async: thread-safe update.",
    requirements: [
      "Hiển thị CPU usage realtime dạng line chart",
      "Hiển thị RAM used / total",
      "Update mỗi 1 giây, không block UI thread",
      "Chart lưu lịch sử 60 giây gần nhất",
      "Có thể pause / resume monitoring"
    ],
    prereqs: ["QThread + worker object pattern", "QTimer", "Qt::QueuedConnection — bắt buộc phải hiểu"],
    learns: ["Worker thread pattern đúng cách", "QML Canvas vẽ line chart", "Thread-safe signal emission", "System metrics API (Linux/Windows)", "moveToThread() và tại sao không new QObject với parent trong thread khác"],
    tools: ["Qt 6.11", "CMake", "QThread", "QTimer", "Qt::QueuedConnection", "QML Canvas", "QProcess (Linux: đọc /proc/stat)"],
    fileTree: `<span class="dir">sys-monitor/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">MonitorController.h/cpp</span>  <span class="comment">// exposed to QML</span>
│   ├── <span class="file-cpp">MetricsWorker.h/cpp</span>     <span class="comment">// runs on worker thread</span>
│   └── <span class="file-cpp">SystemMetrics.h/cpp</span>     <span class="comment">// OS-level reads</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>
    ├── <span class="file-qml">CpuChart.qml</span>            <span class="comment">// Canvas chart</span>
    └── <span class="file-qml">RamBar.qml</span>`,
    architecture: `<span class="hl">[ QML Layer ]</span>
  CpuChart.qml
  └── Canvas { onPaint: draw history[] as line chart }
      └── Connections { target: controller
              onCpuUpdated: { history.push(v); canvas.requestPaint() } }

<span class="arch-comment">     ↕  Qt::QueuedConnection (cross-thread safe)</span>

<span class="hl-green">[ Main Thread ]</span>
  MonitorController : QObject
  ├── Q_PROPERTY cpuPercent, ramUsed, ramTotal
  ├── signal cpuUpdated(double)           <span class="arch-comment">// emitted on worker thread</span>
  └── slot onMetricsReady(CpuData, RamData)

<span class="arch-comment">     ↕  moveToThread()</span>

<span class="hl-green">[ Worker Thread ]</span>
  MetricsWorker : QObject
  ├── QTimer (1000ms interval)
  ├── slot doWork() → SystemMetrics::read()
  └── signal metricsReady(CpuData, RamData)`,
    steps: [
      { title: "SystemMetrics: đọc CPU/RAM", desc: "Linux: đọc /proc/stat cho CPU, /proc/meminfo cho RAM. Windows: dùng GetSystemTimes() và GlobalMemoryStatusEx(). Viết và test class này độc lập trước." },
      { title: "MetricsWorker với QTimer", desc: "QObject subclass với QTimer interval 1000ms. Slot doWork() gọi SystemMetrics::read(). Emit signal metricsReady() với data. Chưa có thread — test trên main thread trước." },
      { title: "moveToThread pattern", desc: "Tạo QThread, gọi worker.moveToThread(&thread). Kết nối thread.started() → worker.startTimer(). Bắt đầu thread. Đây là worker object pattern chuẩn — không subclass QThread." },
      { title: "MonitorController bridge", desc: "QObject nằm trên main thread. Connect metricsReady signal từ worker tới slot onMetricsReady bằng Qt::QueuedConnection. Update Q_PROPERTY và emit signals sang QML." },
      { title: "Canvas chart trong QML", desc: "Canvas với onPaint function. Maintain JS array history[] max 60 phần tử. Mỗi khi nhận cpuUpdated: push vào history, requestPaint(). Vẽ line chart trong onPaint." },
      { title: "Pause / Resume", desc: "Q_INVOKABLE pause() / resume() gọi QTimer::stop() / start() trên worker thread — nhớ thread-safe: dùng QMetaObject::invokeMethod hoặc signal." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "KHÔNG tạo QObject với parent khi dùng moveToThread() — object có parent không thể move sang thread khác, Qt sẽ print warning và ignore." },
      { type: "warn", icon: "⚠️", text: "Kết nối signal xuyên thread PHẢI dùng Qt::QueuedConnection (hoặc để Qt tự detect AutoConnection). Direct connection sẽ chạy slot trên worker thread — nguy hiểm nếu slot đụng UI." },
      { type: "tip", icon: "✅", text: "Pattern này — worker thread emit signal, main thread nhận bằng QueuedConnection và update Q_PROPERTY — là chính xác cái bạn sẽ dùng với FastDDS sau này." },
      { type: "info", icon: "💡", text: "QML Canvas requestPaint() chỉ schedule repaint, không vẽ ngay. Đừng gọi requestPaint() liên tục trong loop — gọi mỗi khi data thực sự thay đổi." },
    ]
  },

  "05": {
    num: "05",
    title: "REST API Client",
    level: "intermediate",
    levelLabel: "Intermediate",
    workRelevant: true,
    time: "1–2 tuần",
    when: "Sau khi học module Qt Network trong khóa Intermediate",
    desc: "Gọi một public REST API (gợi ý: OpenWeatherMap hoặc GitHub API), parse JSON response, hiển thị data lên QML. Học async HTTP request đúng cách — không block UI, có loading state và error handling.",
    requirements: [
      "Gõ query → fetch data từ API khi nhấn Search",
      "Hiển thị loading indicator khi đang fetch",
      "Hiển thị kết quả dạng list hoặc card",
      "Xử lý lỗi: network error, HTTP 4xx/5xx, timeout",
      "Cache response gần nhất (không gọi lại nếu cùng query)"
    ],
    prereqs: ["QNetworkAccessManager & QNetworkReply", "QJsonDocument nâng cao (QJsonObject, QJsonArray)", "Async pattern với Qt signals"],
    learns: ["Non-blocking HTTP request", "QNetworkReply::finished signal", "Loading / error state management", "Simple in-memory cache với QHash", "QML BusyIndicator và conditional rendering"],
    tools: ["Qt 6.11", "CMake + Qt6::Network", "QNetworkAccessManager", "QNetworkRequest", "QNetworkReply", "QJsonDocument", "QML BusyIndicator"],
    fileTree: `<span class="dir">api-client/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">ApiClient.h/cpp</span>       <span class="comment">// QNetworkAccessManager wrapper</span>
│   ├── <span class="file-cpp">WeatherModel.h/cpp</span>    <span class="comment">// QAbstractListModel</span>
│   └── <span class="file-cpp">AppController.h/cpp</span>   <span class="comment">// exposed to QML</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>
    ├── <span class="file-qml">SearchBar.qml</span>
    └── <span class="file-qml">ResultCard.qml</span>`,
    architecture: `<span class="hl">[ QML Layer ]</span>
  Main.qml
  ├── SearchBar → onSearch: controller.fetch(query)
  ├── BusyIndicator { visible: controller.loading }
  ├── Text { visible: controller.error; text: controller.errorMsg }
  └── ListView { model: controller.resultModel }

<span class="arch-comment">     ↕  Q_PROPERTY (loading, error, errorMsg)</span>

<span class="hl-green">[ C++ AppController ]</span>
  ├── Q_PROPERTY bool loading
  ├── Q_PROPERTY bool error
  ├── Q_INVOKABLE void fetch(query)
  │   └── apiClient.get(url)
  └── slot onReplyFinished(QNetworkReply*)
      ├── parse JSON → populate model
      └── update loading/error state

  ApiClient : QObject
  ├── QNetworkAccessManager nam
  ├── get(url) → nam.get() → return QNetworkReply*
  └── signal replyFinished(QNetworkReply*)`,
    steps: [
      { title: "Setup Qt Network trong CMake", desc: "Thêm Qt6::Network vào find_package và target_link_libraries. Tạo ApiClient wrapper đơn giản quanh QNetworkAccessManager." },
      { title: "Gọi API đầu tiên", desc: "QNetworkRequest với URL. nam.get(request) trả về QNetworkReply*. Connect reply->finished signal. Trong slot: đọc reply->readAll(), in ra console trước." },
      { title: "Parse JSON response", desc: "QJsonDocument::fromJson(). Extract fields cần thiết. Đừng cố parse toàn bộ response — chỉ lấy những field sẽ hiển thị." },
      { title: "Loading & Error state", desc: "Set loading=true trước khi gọi, false sau khi nhận reply. Kiểm tra reply->error() và HTTP status code. Emit errorOccurred signal với message." },
      { title: "Hiển thị trong QML", desc: "BusyIndicator bind vào controller.loading. Conditional visibility cho error text. ListView với ResultCard delegate." },
      { title: "Cache với QHash", desc: "QHash<QString, QJsonDocument> cache. Trong fetch(): kiểm tra cache trước, nếu có thì dùng luôn không gọi API. Giới hạn cache size nếu muốn." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "QNetworkAccessManager phải là member variable (hoặc singleton), không tạo new mỗi lần gọi. Tạo/xóa liên tục sẽ leak resources và mất pending connections." },
      { type: "info", icon: "💡", text: "reply->deleteLater() sau khi xử lý xong — đừng delete trực tiếp vì reply vẫn có thể đang được dùng trong event loop." },
      { type: "tip", icon: "✅", text: "Thêm QNetworkRequest::setTransferTimeout(5000) để tự động timeout sau 5 giây — không cần QTimer manual." },
    ]
  },

  "06": {
    num: "06",
    title: "TCP Chat App",
    level: "intermediate",
    levelLabel: "Intermediate",
    workRelevant: true,
    time: "2 tuần",
    when: "Cùng lúc hoặc ngay sau project 05",
    desc: "Server và client trong cùng một codebase. Gửi nhận message qua TCP, hiển thị lên QML chat UI. Đây là nền tảng trực tiếp cho IPC giữa các service — cấu trúc gần giống với app FastDDS của bạn.",
    requirements: [
      "Server lắng nghe kết nối từ nhiều client",
      "Client kết nối tới server, gửi/nhận message",
      "Chat UI: hiển thị message với timestamp và username",
      "Graceful disconnect — không crash khi một bên ngắt",
      "Server có thể broadcast message tới tất cả clients"
    ],
    prereqs: ["QTcpServer & QTcpSocket", "QDataStream để serialize", "QThread kết hợp với socket"],
    learns: ["Multi-client server architecture", "QDataStream framing protocol", "Socket lifecycle management", "QML dynamic list với timestamp", "Graceful shutdown pattern"],
    tools: ["Qt 6.11", "CMake + Qt6::Network", "QTcpServer", "QTcpSocket", "QDataStream", "QThread", "QML ScrollView"],
    fileTree: `<span class="dir">tcp-chat/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">ChatServer.h/cpp</span>      <span class="comment">// QTcpServer, manages clients</span>
│   ├── <span class="file-cpp">ClientHandler.h/cpp</span>  <span class="comment">// one per connection</span>
│   ├── <span class="file-cpp">ChatClient.h/cpp</span>      <span class="comment">// client side</span>
│   └── <span class="file-cpp">MessageModel.h/cpp</span>   <span class="comment">// QAbstractListModel</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>
    ├── <span class="file-qml">ServerPanel.qml</span>
    ├── <span class="file-qml">ClientPanel.qml</span>
    └── <span class="file-qml">MessageBubble.qml</span>`,
    architecture: `<span class="hl">[ QML Layer ]</span>
  Main.qml (SplitView: Server | Client)
  ServerPanel ←→ ChatServer (Q_PROPERTY clientCount, log)
  ClientPanel ←→ ChatClient (Q_PROPERTY connected, messages)

<span class="hl-green">[ Server Side ]</span>
  ChatServer : QObject
  ├── QTcpServer
  ├── newConnection → create ClientHandler
  └── QList&lt;ClientHandler*&gt; clients

  ClientHandler : QObject (one per client)
  ├── QTcpSocket* socket
  ├── readyRead → readMessage()
  ├── disconnected → cleanup
  └── signal messageReceived(QString from, QString msg)

<span class="hl-green">[ Client Side ]</span>
  ChatClient : QObject
  ├── QTcpSocket
  ├── connectToHost(ip, port)
  ├── sendMessage(text) → QDataStream << msg
  └── readyRead → readMessage() → emit received`,
    steps: [
      { title: "Protocol design", desc: "Quyết định format message trước khi code socket. Đề xuất: QDataStream với quint32 size prefix + QString payload. Size prefix giải quyết vấn đề TCP framing (message có thể bị split)." },
      { title: "ChatServer cơ bản", desc: "QTcpServer::listen(). Override incomingConnection() hoặc connect newConnection signal. Mỗi connection tạo một ClientHandler giữ QTcpSocket*." },
      { title: "ClientHandler", desc: "connect socket->readyRead → slot readMessage(). Dùng QDataStream để đọc — check nếu bytesAvailable() đủ để đọc một message hoàn chỉnh trước khi parse." },
      { title: "ChatClient", desc: "QTcpSocket connectToHost(). sendMessage() dùng QDataStream write. Tương tự server: readyRead → readMessage()." },
      { title: "MessageModel cho QML", desc: "QAbstractListModel lưu list Message {username, text, timestamp}. Append khi nhận được message mới. ScrollView tự scroll xuống cuối." },
      { title: "Graceful disconnect", desc: "Connect socket->disconnected signal. Server xóa ClientHandler khỏi danh sách. Client hiển thị 'Disconnected'. Xử lý cả trường hợp network drop đột ngột." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "TCP stream không đảm bảo message boundary — một write() có thể được nhận thành nhiều readyRead events. Luôn dùng size-prefixed framing với QDataStream." },
      { type: "warn", icon: "⚠️", text: "QTcpSocket không thread-safe. Nếu dùng multi-thread, mỗi socket phải được tạo và dùng trong cùng một thread." },
      { type: "tip", icon: "✅", text: "Pattern ClientHandler này — một QObject per connection — chính xác là pattern bạn sẽ dùng cho mỗi DDS subscriber/publisher trong app FastDDS sau này." },
    ]
  },

  "07": {
    num: "07",
    title: "Contact / Inventory Manager",
    level: "intermediate",
    levelLabel: "Intermediate",
    workRelevant: false,
    time: "2 tuần",
    when: "Sau khi học module Qt SQL trong khóa Intermediate",
    desc: "App CRUD đầy đủ với SQLite. Đây là project luyện MVVM pattern nghiêm túc: Model (SQL), ViewModel (C++), View (QML) tách biệt hoàn toàn. Kỹ năng architect này áp dụng cho hầu hết Qt app thực tế.",
    requirements: [
      "Thêm, sửa, xóa contact/item",
      "Tìm kiếm realtime theo tên",
      "Sort theo các cột khác nhau",
      "Chi tiết item trong panel riêng",
      "Database persist giữa các lần chạy app"
    ],
    prereqs: ["QSqlDatabase & QSqlQuery", "MVVM pattern cơ bản", "QAbstractTableModel (project 03)"],
    learns: ["QSqlTableModel vs custom model", "QSortFilterProxyModel nâng cao", "MVVM trong Qt thực tế", "QML form với validation", "Repository pattern để tách DB logic"],
    tools: ["Qt 6.11", "CMake + Qt6::Sql", "QSqlDatabase (SQLite)", "QSqlQuery", "QSortFilterProxyModel", "QML TextField, ComboBox"],
    fileTree: `<span class="dir">contact-manager/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">ContactRepository.h/cpp</span>  <span class="comment">// SQL, data access only</span>
│   ├── <span class="file-cpp">ContactModel.h/cpp</span>       <span class="comment">// QAbstractListModel</span>
│   ├── <span class="file-cpp">ContactViewModel.h/cpp</span>   <span class="comment">// exposed to QML</span>
│   └── <span class="file-cpp">Contact.h</span>               <span class="comment">// plain struct</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>
    ├── <span class="file-qml">ContactList.qml</span>
    ├── <span class="file-qml">ContactDetail.qml</span>
    └── <span class="file-qml">ContactForm.qml</span>`,
    architecture: `<span class="hl">[ View — QML ]</span>
  ContactList.qml → model: viewModel.proxyModel
  ContactDetail.qml ← viewModel.selectedContact
  ContactForm.qml → onSave: viewModel.save(data)

<span class="arch-comment">     ↕  Q_PROPERTY + Q_INVOKABLE</span>

<span class="hl-green">[ ViewModel — C++ ]</span>
  ContactViewModel : QObject
  ├── Q_PROPERTY selectedContact
  ├── Q_PROPERTY ContactModel* model
  ├── Q_INVOKABLE save(ContactData)
  ├── Q_INVOKABLE deleteContact(id)
  └── Q_INVOKABLE setFilter(text)

<span class="hl-green">[ Model — C++ ]</span>
  ContactModel : QAbstractListModel
  └── data source: ContactRepository

  ContactRepository
  ├── getAll() → QVector&lt;Contact&gt;
  ├── insert(Contact) → bool
  ├── update(Contact) → bool
  └── remove(id) → bool   <span class="arch-comment">// SQL only, no Qt signals</span>`,
    steps: [
      { title: "Database setup", desc: "QSqlDatabase::addDatabase('QSQLITE'). Tạo file db trong QStandardPaths::AppDataLocation. Viết CREATE TABLE nếu chưa tồn tại trong một hàm initDb()." },
      { title: "ContactRepository", desc: "Class thuần C++ (không cần QObject). Các method CRUD trả về bool hoặc QVector<Contact>. Không có Qt signals ở đây — đây là data layer thuần." },
      { title: "ContactModel", desc: "QAbstractListModel load data từ repository. Reload model sau mỗi insert/update/delete thay vì patch từng row — đơn giản hơn khi học, optimize sau." },
      { title: "ContactViewModel", desc: "QObject expose lên QML. Giữ QSortFilterProxyModel wrap ContactModel. Q_INVOKABLE cho save/delete/filter. Đây là bridge duy nhất giữa QML và C++ logic." },
      { title: "QML form với validation", desc: "ContactForm.qml với TextField cho từng field. Validation inline: border đỏ nếu rỗng. Disable Save button nếu form invalid." },
      { title: "Selected item detail", desc: "Q_PROPERTY selectedContact (exposed contact struct hoặc index). Click item trong list → cập nhật selectedContact → ContactDetail tự update qua binding." },
    ],
    notes: [
      { type: "info", icon: "💡", text: "ContactRepository không cần là QObject. Tách SQL logic khỏi QObject giúp dễ test và reuse hơn — đây là Repository pattern." },
      { type: "warn", icon: "⚠️", text: "QSqlQuery không thread-safe và không thể dùng connection được tạo ở thread khác. Nếu sau này chuyển DB sang background thread, phải tạo connection mới trong thread đó." },
      { type: "tip", icon: "✅", text: "Vòng 2: thêm QSqlQueryModel cho các read-only view (thống kê, báo cáo) — nhanh hơn custom model khi chỉ cần display không edit." },
    ]
  },

  "08": {
    num: "08",
    title: "Headless Qt Service",
    level: "advanced",
    levelLabel: "Advanced",
    workRelevant: true,
    time: "2–3 tuần",
    when: "Sau project 06. Đây là bản luyện tập trực tiếp cho công việc FastDDS",
    desc: "App Qt không có UI, chạy như background service: nhận data từ một nguồn (TCP socket hoặc stdin), xử lý, rồi forward tới nguồn khác. Kiến trúc này gần như y hệt app FastDDS middleware bạn sẽ cần viết trong công việc.",
    requirements: [
      "Nhận data qua TCP socket (đóng vai Data Source)",
      "Xử lý / transform data (ví dụ: filter, enrich, aggregate)",
      "Forward tới TCP sink (đóng vai Data Sink)",
      "Log mọi message ra file với timestamp",
      "Graceful shutdown khi nhận SIGTERM/SIGINT",
      "Config qua file JSON hoặc command-line args"
    ],
    prereqs: ["QCoreApplication (không phải QApplication)", "QThread nâng cao + worker pattern", "QTcpServer & QTcpSocket (project 06)", "Thread-safe signal emission"],
    learns: ["QCoreApplication event loop", "UNIX signal handling trong Qt", "QCommandLineParser", "QLoggingCategory + rotating log", "Service lifecycle management", "Tích hợp C++ library ngoài vào CMake"],
    tools: ["Qt 6.11", "CMake", "QCoreApplication", "QTcpServer/Socket", "QCommandLineParser", "QLoggingCategory", "QFile (logging)"],
    fileTree: `<span class="dir">qt-service/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>                  <span class="comment">// QCoreApplication, signal setup</span>
│   ├── <span class="file-cpp">ServiceController.h/cpp</span>   <span class="comment">// orchestrates everything</span>
│   ├── <span class="file-cpp">DataReceiver.h/cpp</span>        <span class="comment">// input: TCP server</span>
│   ├── <span class="file-cpp">DataProcessor.h/cpp</span>       <span class="comment">// business logic worker</span>
│   ├── <span class="file-cpp">DataForwarder.h/cpp</span>       <span class="comment">// output: TCP client</span>
│   └── <span class="file-cpp">Logger.h/cpp</span>              <span class="comment">// QLoggingCategory + file</span>
└── <span class="file-cmake">config.json</span>`,
    architecture: `<span class="hl">[ External Source ]</span>   →TCP→   <span class="hl-green">[ Qt Service ]</span>   →TCP→   <span class="hl">[ External Sink ]</span>

<span class="hl-green">Service internal architecture:</span>

  main.cpp
  ├── QCoreApplication a(argc, argv)
  ├── QCommandLineParser → load config
  ├── Setup SIGTERM/SIGINT → a.quit()
  └── ServiceController::start()

  ServiceController
  ├── DataReceiver (worker thread)   <span class="arch-comment">// listens, emits rawData</span>
  │   └── signal: rawDataReceived(QByteArray)
  ├── DataProcessor (worker thread)  <span class="arch-comment">// transforms data</span>
  │   ├── slot: process(QByteArray)
  │   └── signal: processedData(QByteArray)
  └── DataForwarder (worker thread)  <span class="arch-comment">// sends out</span>
      └── slot: forward(QByteArray)

  <span class="arch-comment">All connections: Qt::QueuedConnection</span>`,
    steps: [
      { title: "QCoreApplication skeleton", desc: "main.cpp với QCoreApplication (không phải QApplication — không cần GUI). Parse args với QCommandLineParser: --port, --config, --log-level." },
      { title: "UNIX signal handling", desc: "Bắt SIGTERM và SIGINT để shutdown gracefully. Qt cách hay nhất: dùng QSocketNotifier với self-pipe trick, hoặc đơn giản hơn: signal(SIGTERM, handler) và trong handler gọi QCoreApplication::quit()." },
      { title: "DataReceiver", desc: "QObject trên worker thread. QTcpServer nhận kết nối. Khi nhận data: emit rawDataReceived(QByteArray). Tách hoàn toàn việc nhận data khỏi xử lý." },
      { title: "DataProcessor", desc: "QObject trên worker thread riêng. Slot process() nhận raw data, transform, emit processedData(). Business logic nằm ở đây — độc lập, dễ test." },
      { title: "DataForwarder", desc: "QObject kết nối tới TCP sink. Slot forward() nhận data đã xử lý và gửi đi. Reconnect tự động nếu connection bị dropped." },
      { title: "Logger với QLoggingCategory", desc: "Define Q_LOGGING_CATEGORY cho mỗi component. Install custom message handler bằng qInstallMessageHandler. Ghi ra file với timestamp, tự rotate khi quá 10MB." },
      { title: "Config từ JSON", desc: "QJsonDocument đọc config.json: port, sink address, log level, processor settings. Validate khi load — fail fast với error message rõ ràng." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "QCoreApplication::quit() an toàn để gọi từ signal handler vì nó chỉ set một flag. Event loop sẽ thoát sạch sau khi xử lý xong event hiện tại." },
      { type: "tip", icon: "✅", text: "Khi chuyển sang FastDDS: thay DataReceiver bằng DDS Subscriber (bọc trong QObject, emit signal khi có message), thay DataForwarder bằng DDS Publisher. DataProcessor không thay đổi gì." },
      { type: "info", icon: "💡", text: "Để test service này: viết một Python script nhỏ gửi TCP data liên tục. Không cần Qt test client." },
      { type: "warn", icon: "⚠️", text: "Đừng dùng QApplication cho headless service — nó khởi tạo display connection không cần thiết và sẽ crash trên headless Linux server không có display." },
    ]
  },

  "09": {
    num: "09",
    title: "Custom QML Element (C++ backed)",
    level: "advanced",
    levelLabel: "Advanced",
    workRelevant: false,
    time: "2–3 tuần",
    when: "Sau project 04 (đã quen Canvas), trước Capstone",
    desc: "Viết một gauge widget hoàn chỉnh bằng C++ QQuickItem, sử dụng được trong QML như built-in element. Đây là kỹ năng cần thiết cho embedded HMI — khi QML Canvas không đủ mượt hoặc cần rendering tùy biến cao.",
    requirements: [
      "Gauge hiển thị value từ min đến max",
      "Animated khi value thay đổi",
      "Properties: value, min, max, unit, label, color",
      "Tái dùng được: nhiều gauge trên cùng màn hình không giật lag",
      "Có warning zone (vùng màu đỏ khi value cao)"
    ],
    prereqs: ["QQuickItem cơ bản", "Qt Scene Graph (QSGNode)", "QML_ELEMENT macro (Qt 6)"],
    learns: ["QQuickItem geometry và paint cycle", "QSGGeometryNode vẽ arc hiệu quả", "updatePaintNode() pattern", "Dirty flag để tránh repaint thừa", "Custom QML properties với NOTIFY"],
    tools: ["Qt 6.11", "CMake + Qt6::Quick", "QQuickItem", "QSGNode", "QSGGeometryNode", "QSGFlatColorMaterial", "QPropertyAnimation"],
    fileTree: `<span class="dir">gauge-widget/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">GaugeItem.h/cpp</span>      <span class="comment">// QQuickItem subclass</span>
│   └── <span class="file-cpp">GaugeNode.h/cpp</span>      <span class="comment">// QSGNode for rendering</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>             <span class="comment">// demo: nhiều gauge</span>
    └── <span class="file-qml">GaugeDemoPanel.qml</span>`,
    architecture: `<span class="hl">[ QML ]</span>
  GaugeItem {           <span class="arch-comment">// C++ type, dùng như built-in</span>
    value: 75
    min: 0; max: 100
    unit: "°C"
    warningThreshold: 80
    color: "#58A6FF"
  }

<span class="hl-green">[ C++ GaugeItem : QQuickItem ]</span>
  ├── Q_PROPERTY qreal value WRITE setValue NOTIFY valueChanged
  ├── Q_PROPERTY qreal min, max, warningThreshold
  ├── setValue() → m_value = v → setFlag(ItemHasContents, true)
  │              → update()  <span class="arch-comment">// schedule repaint</span>
  └── updatePaintNode(QSGNode*, UpdatePaintNodeData*)
      └── create/update GaugeNode geometry

<span class="hl-green">[ C++ GaugeNode : QSGGeometryNode ]</span>
  └── updateGeometry(value, min, max, warningThreshold)
      ├── arc background (gray)
      ├── arc value (colored, length proportional to value)
      └── warning arc (red, from threshold to max)`,
    steps: [
      { title: "QQuickItem skeleton", desc: "Kế thừa QQuickItem. setFlag(ItemHasContents, true). Override updatePaintNode(). Bắt đầu bằng vẽ một hình chữ nhật đơn giản để hiểu flow trước khi làm gauge." },
      { title: "QSGGeometryNode arc cơ bản", desc: "Tạo QSGGeometry với GL_TRIANGLE_STRIP. Tính toán vertices cho arc từ góc start đến góc hiện tại. QSGFlatColorMaterial cho màu." },
      { title: "Properties và dirty flag", desc: "setValue() kiểm tra nếu giá trị thực sự thay đổi mới set m_dirty = true và gọi update(). updatePaintNode() chỉ rebuild geometry khi m_dirty." },
      { title: "Animation", desc: "QPropertyAnimation animate từ old value sang new value. Mỗi frame của animation gọi setValue() → update() → updatePaintNode(). Smooth 60fps." },
      { title: "Warning zone", desc: "Render thêm một arc màu đỏ từ warningThreshold đến max. Khi value vượt threshold, đổi màu arc chính sang đỏ." },
      { title: "Demo với nhiều gauge", desc: "Main.qml đặt 4-6 GaugeItem cùng lúc. Dùng QTimer simulate sensor data thay đổi. Verify không có lag hay flickering." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "updatePaintNode() chạy trên render thread, không phải main thread. KHÔNG access bất kỳ non-trivial QObject hay Qt API nào trong đó — chỉ làm việc với QSGNode." },
      { type: "info", icon: "💡", text: "Nếu chỉ cần vẽ đơn giản và không cần hiệu năng cao, QQuickPaintedItem (dùng QPainter) dễ hơn QQuickItem + QSGNode. QSGNode mới cần cho animation 60fps mượt." },
      { type: "tip", icon: "✅", text: "Vòng 2: thêm QML_ATTACHED_PROPERTIES để GaugeItem.attached có thể dùng như Gauge.unit: 'rpm' trực tiếp trong QML — đây là pattern của Qt Quick Controls." },
    ]
  },

  "10": {
    num: "10",
    title: "Plugin-based App",
    level: "advanced",
    levelLabel: "Advanced",
    workRelevant: false,
    time: "2 tuần",
    when: "Có thể làm song song với project 08–09, không phụ thuộc nhau",
    desc: "App core load plugin (.so/.dll) lúc runtime — không cần recompile app khi thêm tính năng mới. Mỗi plugin implement cùng một C++ interface. Đây là kiến trúc extensible dùng trong nhiều commercial Qt app.",
    requirements: [
      "App core scan thư mục plugins/, load tất cả .so/.dll tìm thấy",
      "Mỗi plugin implement interface IDataProcessor",
      "App liệt kê plugins đã load với tên và version",
      "Có thể unload và reload plugin lúc runtime",
      "Ít nhất 2 plugin demo: một filter, một transform"
    ],
    prereqs: ["QPluginLoader", "C++ abstract interface class (pure virtual)", "CMake build shared library"],
    learns: ["Qt plugin system internals", "Q_INTERFACES và Q_PLUGIN_METADATA", "CMake MODULE library", "Dynamic loading pattern", "Plugin version management"],
    tools: ["Qt 6.11", "CMake (MODULE library)", "QPluginLoader", "QDir (scan plugins)", "QJsonObject (plugin metadata)"],
    fileTree: `<span class="dir">plugin-app/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">core/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="file-cpp">IDataProcessor.h</span>       <span class="comment">// pure abstract interface</span>
│   ├── <span class="file-cpp">PluginManager.h/cpp</span>    <span class="comment">// load/unload</span>
│   └── <span class="file-cpp">AppController.h/cpp</span>
├── <span class="dir">plugins/</span>
│   ├── <span class="dir">filter-plugin/</span>
│   │   ├── <span class="file-cmake">CMakeLists.txt</span>
│   │   └── <span class="file-cpp">FilterPlugin.h/cpp</span>
│   └── <span class="dir">transform-plugin/</span>
│       ├── <span class="file-cmake">CMakeLists.txt</span>
│       └── <span class="file-cpp">TransformPlugin.h/cpp</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>
    └── <span class="file-qml">PluginPanel.qml</span>`,
    architecture: `<span class="hl">[ Interface — shared header ]</span>
  IDataProcessor
  ├── virtual QString name() const = 0
  ├── virtual QString version() const = 0
  ├── virtual QVariant process(QVariant input) = 0
  └── virtual ~IDataProcessor() = default

<span class="hl-green">[ Core App ]</span>
  PluginManager
  ├── loadAll(pluginsDir)
  │   └── QDir scan → QPluginLoader::load() → qobject_cast&lt;IDataProcessor*&gt;
  ├── QList&lt;IDataProcessor*&gt; plugins
  └── unload(name) → QPluginLoader::unload()

  AppController
  └── runPipeline(input) → foreach plugin: plugin->process(data)

<span class="hl-green">[ Each Plugin ]</span>
  FilterPlugin : QObject, IDataProcessor
  ├── Q_OBJECT; Q_INTERFACES(IDataProcessor)
  ├── Q_PLUGIN_METADATA(IID "com.example.IDataProcessor" FILE "filter.json")
  └── process(input) → filter logic`,
    steps: [
      { title: "IDataProcessor interface", desc: "Pure abstract class với pure virtual methods. Khai báo IID string. Đây là contract giữa app và plugins — viết cẩn thận vì khó thay đổi sau." },
      { title: "FilterPlugin đầu tiên", desc: "QObject subclass implement IDataProcessor. Q_PLUGIN_METADATA với JSON file chứa name, version. CMakeLists.txt dùng add_library(filter-plugin MODULE)." },
      { title: "PluginManager", desc: "QDir scan thư mục plugins/. QPluginLoader::load() từng file. qobject_cast<IDataProcessor*> để verify interface. Lưu vào QList." },
      { title: "Expose lên QML", desc: "AppController expose danh sách plugin names qua QAbstractListModel. Q_INVOKABLE runWithPlugin(name, input)." },
      { title: "Unload / Reload", desc: "QPluginLoader::unload() giải phóng .so. Load lại để reload. Test: thay file .so trong khi app đang chạy → reload → tính năng mới có hiệu lực." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "Plugin phải được build với cùng compiler và Qt version với app core. ABI mismatch sẽ crash runtime." },
      { type: "info", icon: "💡", text: "Q_PLUGIN_METADATA JSON cho phép app đọc metadata (name, version) mà không cần load plugin — dùng QPluginLoader::metaData() trước khi load." },
      { type: "tip", icon: "✅", text: "Đặt IDataProcessor.h trong thư mục chung (không phải core/ hay plugin/) để cả app và plugin đều include cùng một file." },
    ]
  },

  "11": {
    num: "11",
    title: "SCADA / HMI Dashboard",
    level: "capstone",
    levelLabel: "Capstone",
    workRelevant: true,
    time: "4–6 tuần",
    when: "Sau khi hoàn thành ít nhất project 01, 04, 07, 08, 09",
    desc: "Project tổng hợp toàn bộ Qt stack: dashboard realtime hiển thị data từ C++ backend giả lập sensor, multi-screen QML navigation, custom gauge widget, alarm system, và SQLite data logging. Đây là loại app bạn sẽ gặp trong công việc embedded/industrial.",
    requirements: [
      "Dashboard chính: nhiều gauge, chart realtime, alarm panel",
      "Screen cài đặt: cấu hình ngưỡng alarm, refresh rate",
      "Screen lịch sử: bảng log từ SQLite, có thể filter theo thời gian",
      "C++ backend giả lập 4–6 sensor với noise ngẫu nhiên",
      "Alarm system: phát hiện ngưỡng, log alarm, hiển thị notification",
      "Dark/light theme toggle",
      "Graceful shutdown (lưu config trước khi thoát)"
    ],
    prereqs: ["QAbstractListModel (01)", "QThread + worker pattern (04)", "MVVM + SQLite (07)", "Service architecture (08)", "Custom QQuickItem — GaugeItem (09)"],
    learns: ["QML StackView multi-screen navigation", "Qt Quick Controls 2 theming", "Alarm & event system design", "Config persistence với QSettings", "Qt profiler — tìm và fix bottleneck", "Full app architecture Qt thực tế"],
    tools: ["Qt 6.11", "CMake (nhiều module)", "QQuickItem (GaugeItem từ 09)", "QThread", "QSqlDatabase", "QSettings", "QML StackView", "Qt Quick Controls 2"],
    fileTree: `<span class="dir">hmi-dashboard/</span>
├── <span class="file-cmake">CMakeLists.txt</span>
├── <span class="dir">src/</span>
│   ├── <span class="file-cpp">main.cpp</span>
│   ├── <span class="dir">core/</span>
│   │   ├── <span class="file-cpp">AppController.h/cpp</span>    <span class="comment">// root QML context</span>
│   │   └── <span class="file-cpp">ConfigManager.h/cpp</span>   <span class="comment">// QSettings</span>
│   ├── <span class="dir">sensor/</span>
│   │   ├── <span class="file-cpp">SensorSimulator.h/cpp</span> <span class="comment">// worker thread</span>
│   │   └── <span class="file-cpp">SensorModel.h/cpp</span>
│   ├── <span class="dir">alarm/</span>
│   │   ├── <span class="file-cpp">AlarmEngine.h/cpp</span>
│   │   └── <span class="file-cpp">AlarmModel.h/cpp</span>
│   ├── <span class="dir">history/</span>
│   │   └── <span class="file-cpp">HistoryRepository.h/cpp</span>
│   └── <span class="dir">widgets/</span>
│       └── <span class="file-cpp">GaugeItem.h/cpp</span>        <span class="comment">// từ project 09</span>
└── <span class="dir">qml/</span>
    ├── <span class="file-qml">Main.qml</span>               <span class="comment">// StackView root</span>
    ├── <span class="dir">screens/</span>
    │   ├── <span class="file-qml">DashboardScreen.qml</span>
    │   ├── <span class="file-qml">HistoryScreen.qml</span>
    │   └── <span class="file-qml">SettingsScreen.qml</span>
    └── <span class="dir">components/</span>
        ├── <span class="file-qml">AlarmBanner.qml</span>
        ├── <span class="file-qml">SensorCard.qml</span>
        └── <span class="file-qml">NavBar.qml</span>`,
    architecture: `<span class="hl">[ QML Layer ]</span>
  Main.qml (StackView)
  ├── DashboardScreen
  │   ├── GaugeItem × N (từ project 09)
  │   ├── RealtimeChart (Canvas)
  │   └── AlarmBanner ← alarmModel
  ├── HistoryScreen
  │   └── TableView ← historyModel (SQLite)
  └── SettingsScreen
      └── Form ← configManager (QSettings)

<span class="arch-comment">     ↕  Q_PROPERTY + signals (Qt::QueuedConnection)</span>

<span class="hl-green">[ Main Thread — Controllers ]</span>
  AppController
  ├── SensorModel (QAbstractListModel)
  ├── AlarmEngine  → AlarmModel
  ├── HistoryRepository (SQLite write)
  └── ConfigManager (QSettings)

<span class="arch-comment">     ↕  QueuedConnection</span>

<span class="hl-green">[ Worker Thread ]</span>
  SensorSimulator
  ├── QTimer 200ms
  ├── Simulate 6 sensors (Gaussian noise)
  └── signal: sensorDataReady(SensorDataBatch)`,
    steps: [
      { title: "Project setup & architecture plan", desc: "Sketch toàn bộ class diagram trước khi code. Xác định rõ: ai owns ai, signal nào chạy trên thread nào. 30 phút thiết kế tiết kiệm nhiều giờ debug sau." },
      { title: "SensorSimulator worker", desc: "QObject trên worker thread. QTimer 200ms emit SensorDataBatch với 6 sensor values (Gaussian noise quanh base value). Tái dùng pattern từ project 04." },
      { title: "Dashboard screen", desc: "StackView với DashboardScreen là trang đầu. GaugeItem tái dùng từ project 09. SensorCard.qml hiển thị value, unit, trend arrow." },
      { title: "AlarmEngine", desc: "Nhận SensorDataBatch. So sánh với threshold từ ConfigManager. Emit alarmTriggered(AlarmEvent). AlarmModel lưu danh sách alarm active. AlarmBanner.qml hiển thị." },
      { title: "HistoryRepository", desc: "SQLite table: timestamp, sensor_id, value, alarm_flag. Insert mỗi batch từ SensorSimulator. HistoryScreen query với filter theo date range." },
      { title: "Settings screen", desc: "Form chỉnh threshold cho từng sensor, refresh rate. QSettings persist. ConfigManager emit settingsChanged signal → AlarmEngine và SensorSimulator reload config." },
      { title: "Theming", desc: "Define color palette trong một QML singleton (ThemeManager). Dark/light toggle swap palette. Tất cả màu reference ThemeManager.primary, .background, v.v." },
      { title: "Polish & profiling", desc: "Chạy Qt Creator QML Profiler. Tìm binding evaluations nhiều nhất — đây thường là bottleneck. Fix: dùng property caching, tránh binding chain dài." },
    ],
    notes: [
      { type: "warn", icon: "⚠️", text: "Đừng cố làm tất cả cùng lúc. Build từng layer: Simulator → Dashboard → Alarm → History → Settings. Mỗi layer chạy được trước khi thêm layer tiếp theo." },
      { type: "tip", icon: "✅", text: "Project này thay SensorSimulator bằng FastDDS Subscriber thì gần như ra thẳng app production. Đây là lý do lộ trình kết thúc ở đây." },
      { type: "info", icon: "💡", text: "QSettings tự động chọn đúng storage backend theo OS: Registry trên Windows, .conf file trên Linux, plist trên macOS." },
      { type: "warn", icon: "⚠️", text: "HistoryRepository nên chạy trên thread riêng nếu log rate cao — SQLite write trên main thread sẽ stutter UI khi load." },
    ]
  }
};
