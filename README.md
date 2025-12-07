# Chương trình cơ bản mô phỏng tính năng và ứng dụng của blockchain trong ngân hàng bằng C++
-----

## Các tính năng:
```
Tên: TechChainBank (Techology BlockChain Banking)

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
├── src
│   ├── lib
│   │   ├── json.hpp
│   │   ├── picosha2.h
│   │   ├── qrcodegen.cpp
│   │   └── qrcodegen.hpp
│   ├── block.json
│   ├── blockchain.cpp
│   ├── blockchain.h
│   ├── caidat.cpp
│   ├── chuongtrinh.cpp
│   ├── data.json
│   └── thuvien.h
└── README.md
```

## Lưu ý: 
```
+ Thay đường dẫn đến các file header dùng #include 
+ Thay đường dẫn đến file lưu thông tin file_data.json
+ Lệnh biên dịch: 
    -> Duy chuyển thư mục đến file ../src/
    g++ .\chuongtrinh.cpp .\caidat.cpp .\blockchain.cpp .\lib\qrcodegen.cpp -o .\chuongtrinh.exe
```

## Hoặc biên dịch và chạy nhanh 
+ Khởi chạy file `khoichay.exe`

# Screenshot

## Đăng ký/ đăng nhập
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/2610970c-bad3-49da-80cf-654b5f27d9db" />

## Tài khoản
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/41fe16c9-d55d-483f-b001-11a62113d602" />

## Qrbank
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/8c5697b0-434c-4082-b3dd-bf9b7c63a880" />

## Nạp tiền 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/b59d47ee-fc6f-4cf5-97bf-5ca6993a2f54" />

## Chuyển tiền
<img width="1916" height="1079" alt="image" src="https://github.com/user-attachments/assets/615aae07-1d15-42b6-a678-a7d1a27b3c4e" />

## Lịch sử giao dịch 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/15845c8e-8478-4de4-b671-73cd4fe39d09" />

## Lịch sử block
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/15a3cb10-e81d-4f61-ba3f-1a60e87e7c92" />
