# Qt Learning Roadmap

Một lộ trình học Qt/QML/C++ gồm **11 project thực hành**, đi từ cơ bản đến nâng cao, được thiết kế để chuẩn bị kỹ năng cho công việc thực tế: xây dựng ứng dụng desktop Qt tích hợp bản đồ, xử lý dữ liệu realtime và kiến trúc middleware.

## Giới thiệu

Mỗi project là một ứng dụng nhỏ, độc lập, tập trung vào một nhóm kỹ năng Qt cụ thể — từ thao tác C++ ↔ QML cơ bản, xử lý đa luồng, network, database, cho đến custom rendering và kiến trúc plugin. Project cuối cùng (Capstone) tổng hợp lại toàn bộ kiến thức thành một ứng dụng dashboard hoàn chỉnh, gần với sản phẩm thực tế.

## Danh sách project

| # | Tên project | Cấp độ | Mô tả ngắn |
|---|---|---|---|
| 01 | To-do List App | Beginner | Quản lý danh sách công việc, lưu trữ dữ liệu xuống file |
| 02 | Calculator | Beginner | Máy tính cơ bản, tách biệt logic tính toán và giao diện |
| 03 | File Viewer (CSV/JSON) | Beginner | Đọc và hiển thị dữ liệu dạng bảng, có sắp xếp và tìm kiếm |
| 04 | System Monitor | Intermediate | Theo dõi CPU/RAM realtime, cập nhật giao diện không giật lag |
| 05 | REST API Client | Intermediate | Gọi API bên ngoài, hiển thị kết quả, xử lý loading/lỗi |
| 06 | TCP Chat App | Intermediate | Ứng dụng chat qua mạng, gồm cả server và client |
| 07 | Contact Manager | Intermediate | Quản lý danh bạ với cơ sở dữ liệu, tìm kiếm và chỉnh sửa |
| 08 | Headless Qt Service | Advanced | Dịch vụ chạy nền không giao diện, nhận – xử lý – chuyển tiếp dữ liệu |
| 09 | Custom QML Element | Advanced | Đồng hồ đo (gauge) tùy biến, dựng bằng C++, mượt và tái sử dụng được |
| 10 | Plugin-based App | Advanced | Ứng dụng có thể mở rộng tính năng qua plugin nạp lúc chạy |
| 11 | SCADA / HMI Dashboard | Capstone | Bảng điều khiển giám sát tổng hợp: biểu đồ, cảnh báo, lịch sử, cài đặt |

## Tính năng chung của dự án

- Trình bày trực quan từng project: mô tả, yêu cầu chức năng, kiến thức cần có trước, kiến thức sẽ học được, và công cụ sử dụng.
- Sơ đồ kiến trúc và cây thư mục minh họa cho từng project, giúp hình dung cách tổ chức code.
- Các bước thực hiện chi tiết theo trình tự, kèm ghi chú, lưu ý và mẹo thực hành.
- Phân loại theo cấp độ (Beginner → Capstone) và đánh dấu project nào liên quan trực tiếp đến công việc thực tế.

## Mục tiêu

Lộ trình được xây dựng để dẫn tới việc làm chủ một ứng dụng Qt hoàn chỉnh dạng dashboard giám sát/điều khiển (SCADA/HMI) — nền tảng gần nhất với các ứng dụng embedded/industrial thực tế, cũng như hướng tới việc tích hợp các nguồn dữ liệu realtime kiểu publish/subscribe (ví dụ DDS) trong công việc.
