# Chương trình cơ bản mô phỏng tính năng và ứng dụng của blockchain trong ngân hàng bằng C++
-----

## Các tính năng:
```
Menu: 
    + Đăng nhập và đăng xuất 
    + Nạp tiền 
    + Chuyển tiền và đóng thành block 
    + Xem số tài khoản 
    + Xem Qrbank
    + Xem lịch sử giao dịch
    + Xem blockchain 
```

## Thư mục:
```
├── 📁 src
│   ├── 📁 lib
│   │   ├── ⚡ json.hpp
│   │   ├── ⚡ picosha2.h
│   │   ├── ⚡ qrcodegen.cpp
│   │   └── ⚡ qrcodegen.hpp
│   ├── ⚙️ block.json
│   ├── ⚡ blockchain.cpp
│   ├── ⚡ blockchain.h
│   ├── ⚡ caidat.cpp
│   ├── ⚡ chuongtrinh.cpp
│   ├── ⚙️ data.json
│   └── ⚡ thuvien.h
└── 📝 README.md
```

## Lưu ý: 
```
+ Thay đường dẫn đến các file header dùng #include 
+ Thay đường dẫn đến file lưu thông tin file_data.json
+ Lệnh biên dịch: 
    -> Duy chuyển thư mục đến file ../src/
    g++ .\chuongtrinh.cpp .\caidat.cpp .\blockchain.cpp -Ilib .\lib\qrcodegen.cpp -o .\chuongtrinh
```

# Screenshot

## Đăng nhập
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/c54d24a8-e9b7-4c10-90e5-25b94ecb2396" />
## Tài khoản
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/7e6483cd-565f-44ca-bd57-b2e857bfdd9c" />

## Qrbank
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/d359c97b-4d2b-4a7f-9462-633776410333" />

## Nạp tiền 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/0fe6db1e-10ed-47b6-a719-9a8f87b680ee" />

## Chuyển tiền
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/2a6d2dff-8a7a-469a-b6a6-0ff4cf3805d3" />

## Lịch sử giao dịch 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/a20245d8-b550-409e-b57e-175f5d2d8699" />

## Lịch sử block
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/d2eecda5-76d3-4d1f-a158-767da36d0823" />

-----
## Tác giả: Nguyễn Trường Chinh (NTC++)
