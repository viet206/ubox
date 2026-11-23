# API của uBox
## Quy ước hàm
API của uBox được thiết kế theo 1 mẫu luôn luôn là như vậy
```
rtcode name(dst,src,option...)
```
Giải thích:
- `rtcode` : Mã trả về của chương trình , ám chỉ trạng thái của hàm
- `dst` : đây là nơi chứa kết quả của hàm
- `src` : đây là nơi chứa đầu vào của hàm
- `option...` : đây là các tham số chuyên biệt khác do mỗi hàm quy định.

Tại sao tôi thiết kế như vậy ? Bởi chữ ký này giải quyết 2 vấn đề lớn nhất của ubox lúc đó giờ là "Làm thế nào để trả về lỗi mà không cần đóng gói cấu trúc".
