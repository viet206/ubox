# API của uBox
## Quy ước hàm
API của uBox được thiết kế theo 1 mẫu
```
	return_code name(dst,src,option...)
```
Giải thích:
- `return_code` : là giá trị trả về của hàm . Hàm sẽ trả về 2 loại giá trị là `boolean` và `non-zero` . trong đó , `non-zero` là các giá trị trả về không phải boolean ; còn các giá trị boolean được mô tả trong mục [Giá trị Boolean](#Gia-tri-Boolean)
- `dst` : tên gọi là `tham số đích` hoặc `đầu ra` .
- `src` : tên gọi là `tham số nguồn` hoặc `đầu vào`.
- `option...` : tên gọi là `tùy chọn` . các tham số tiếp theo được định nghĩa từ đây trở về sau sẽ tùy thuộc vào nhu cầu của từng hàm.  

Một Hàm thường sẽ có nhiều mẫu khác nhau , và đây là ví dụ cho hai mẫu phổ biến nhất:
```
    return_code name(dst,src,option);
    return_code name(dst,option);
```
## Giá trị Boolean
Giá trị Boolean trong uBox được lấy từ giá trị boolean của các toán tử so sánh trong C . 1 ví dụ:
```
    ( 9 > 0 ) -> 1 : đúng
    ( 4 > 5 ) -> 0 : sai

```
Các giá trị Boolean thường hữu ích khi được sử dụng làm kết quả trả về . Nhưng nó chỉ thật sự hữu ích khi hàm đó trong tài liệu có mô tả rõ là "chỉ trả về kết quả là giá trị Boolean" . Bởi nếu hàm có trả về các giá trị `non-zero` sẽ khiến cho Boolean trở nên vô dụng bởi các giá trị non-zero có thể là 1 , tương đương với Boolean True.  

Và vì các giá trị Boolean giống nhau 1:1 với Boolean trong C nên về mặt cơ bản thì chúng có thể xử lý những logic một cách khá đẹp mắt:
```c
    // so sánh sự giống nhau của chuỗi
    if (str_equal("Hello","Hello",3)) {
        puts("Giống");
    }else{
        puts("Khác");
    }
```
