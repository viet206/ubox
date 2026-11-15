# Bộ nhớ trong uBox
## Lý thuyết
Bộ nhớ trong uBox được chia làm 2 loại để xử lý , dựa trên kiểu cơ sở mà người gọi đã khai báo:  
- kiểu `byte_t` : Chuyên xử lý bộ nhớ thô , thường được dùng bởi các hàm như `mem_copy` , `mem_clear` , ...
- kiểu `char*` : Nó chuyên xử lý chuỗi , bạn có thể kham khảo các hàm thao tác với kiểu này thì có trong [String API](string.md)  

Và trang tài liệu này chủ yếu sẽ nói về `byte_t` nhiều hơn
## Các hàm xử lý bộ nhớ thô
Đâu đó sẽ có khoảng vài ba hàm như phần trước đó đã đề cập . bạn có thể xem mã nguồn trông như thế nào trong tệp `src/memory.c`
### Hàm mem_copy()
Nó là 1 hàm copy vùng nhớ của ubox , giống như `memcpy`:
```
int mem_copy(byte_t* restrict dst,byte_t* restrict src,uint_t size);
```
Giải thích:
- `int` : Hàm chỉ trả về giá trị Boolean
- `dst` : là vùng nhớ bạn muốn copy từ `src` vào , với điều kiện là không phải con trỏ chồng lấp với `src`
- `src` : là vùng nhớ để copy sang `src` ,  với điều kiện là không phải con trỏ chồng lấp với `dst`
### Hàm mem_clear()
Nó là 1 hàm làm sạch buffer , bằng cách duyệt buffer và điền số 0 vào từng phần tử
```
int mem_clear(byte_t* restrict mem,uint_t size);
```
Giải thích:
- `int` : Hàm chỉ trả về giá trị Boolean
- `mem` : Vùng nhớ muốn làm sạch ( với điều kiện thì nó không bị chồng lấp )
- `size` : Kích thước của vùng nhớ , với điều kiện kích thước phải lớn hơn 0
