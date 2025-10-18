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
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/c43aa593-a62a-44b5-8df2-83f86777cd1c" />

## Qrbank
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/9f898da4-8a38-498c-a226-04828fc7b489" />

## Nạp tiền 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/6bb3c825-c3ec-460b-86e9-ab056737ce84" />

## Chuyển tiền
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/a1a5b4d3-4877-46cb-a75b-2c9ed11f297d" />

## Lịch sử giao dịch 
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/11297bb2-2ffb-4669-96c6-8bec84a47c57" />

## Lịch sử block
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/2c2da653-ef8b-4dfc-867c-4490dab5aa2a" />

-----
## Tác giả: Nguyễn Trường Chinh (NTC++)


