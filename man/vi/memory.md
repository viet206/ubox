# Bộ nhớ trong uBox
## Lý thuyết
Bộ nhớ trong uBox được chia làm 2 loại để xử lý , dựa trên kiểu cơ sở mà người gọi đã khai báo:  
- kiểu `byte_t` : Chuyên xử lý bộ nhớ thô , thường được dùng bởi các hàm như `mem_copy` , `mem_clear` , ...
- kiểu `char*` : Nó chuyên xử lý chuỗi , bạn có thể kham khảo các hàm thao tác với kiểu này thì có trong [String API](string.md)  

Và trang tài liệu này chủ yếu sẽ nói về `byte_t` nhiều hơn
## Cấp phát bộ nhớ
### Lý thuyết
Bộ nhớ trong ubox lưu trữ dưới dạng các Word ( kiểu `uint_t` ) . Điều này giúp đảm bảo căn chỉnh dữ liệu tự nhiên cho các Chunk . Chúng ta thử việc thực nghiệm với 3 , 5 , 7 cho 1 chunk:
```
4 x 3 = 12 byte
4 x 5 = 20 byte
4 x 7 = 28 byte
```
Chúng đều chia hết cho 4 , bất kể là số chẵn hay số lẽ . Còn kích thước kiểu sơ sở 4 byte là nhằm để chạy ổn định hơn trên các CPU 32 bit do không dính các vấn đề về căn chỉnh , đồng thời giúp tối uư tốc độ vì có cùng độ rộng với thanh ghi . Trên các CPU 64 bit có hỗ trợ việc xử lý địa chỉ không căn chỉnh nên hoàn toàn có thể yên tâm.
Phạm vi thao tác của các hàm cấp phát thường được chia ra làm 2 loại : Theo Chunk , và theo Word . Trong đó , Word là phần tử nhỏ nhất của bộ nhớ . còn chunk là 1 tập hợp các Word . 2 loại này được triển khai bằng kiểu `uint_t` và `byte_t`.
Các hàm cấp phát bộ nhớ thường hoạt động trên bộ nhớ stack , hoặc bộ nhớ tính . Về kỹ thuật cấp phát , các hàm cấp phát sử dụng kiểu linear allocator , index allocator với các phạm vi thao tác khác nhau.
### Các hàm cấp phát
#### pool_init()
```c
#define pool_init(name,max,chunk)
```
Đây là Macro khởi tạo bộ nhớ tĩnh , với 3 tham số:
- name : Tên của vùng nhớ
- max : kích thước tối đa của vùng nhớ ( tính theo word )
- chunk : kích thước tối đa của mỗi chunk
Lưu ý :
- `pool_init()` khởi tạo metadata tại `name[0]` bao gồm chunk , max , cur
- tuyệt đối không ghi vào metadata để tránh các lỗi cấp phát
#### lalloc()
Hàm cấp phát bộ nhớ theo kiểu Linear Allocator theo Chunk
```c
byte_t* lalloc(word_t* pool,byte_t* data,uint_t size)
```
- pool : vùng nhớ
- data : dữ liệu
- size : kích thước
Khi thành công , hàm trả về con trỏ trỏ tới chunk đó trong bộ nhớ
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
