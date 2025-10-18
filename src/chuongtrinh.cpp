#include "thuvien.h"

int main(){
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);
    while(true){
        system("cls");
        in_banner();
        cout << "┌──────────────────── TCBank ────────────────────" << endl;
        cout << "├• 1. Dang ky tai khoan" << endl;
        cout << "├• 2. Dang nhap tai khoan" << endl;
        cout << "├• 3. Thoat ngan hang" << endl;
        cout << "└──────────> Ban chon: "; char c = getche();
        if(c == '1') {
            TaiKhoanDangKy taikhoan("", "");
            string ten_nguoi_dung = dang_ky_tai_khoan_ten_nguoi_dung(taikhoan);
            string mat_khau = dang_ky_tai_khoan_mat_khau(taikhoan);
            if(ten_nguoi_dung.empty() || ten_nguoi_dung.size() < 5 
                || mat_khau.empty() || mat_khau.size() < 4){
                cout << "\t(!) Ten nguoi dung hoac mat khau khong hop le !" << endl;
                getch();
                continue;
            }
            taikhoan.so_tai_khoan = taikhoan.tao_so_tai_khoan();
            luu_du_lieu_sau_dang_ky(taikhoan);
        } else if(c == '2') {
            ifstream in(file_data);
            if(in.peek() == ifstream::traits_type::eof()){
                cout << "\t(!) Chua co du lieu nguoi dung ! Vui long dang ky truoc";
                getch();
                continue;
            }
            string ten_nguoi_dung, mat_khau;
            cout << endl;
            cin.ignore();
            cout << "\t(?) Nhap ten nguoi dung: "; getline(cin, ten_nguoi_dung);
            cout << "\t(?) Nhap mat khau: "; getline(cin, mat_khau);
            TaiKhoanDangNhap taikhoan(ten_nguoi_dung, mat_khau, 0, "");
            if(!xac_thuc_ten_nguoi_dung(taikhoan) || !xac_thuc_mat_khau(taikhoan)){
                cout << "(!) Dang nhap that bai !" << endl;
                getch();
                continue;
            }
            while(true){
                system("cls");
                in_banner();
                cout << "┌──────────────────── TCBank ────────────────────" << endl;
                cout << "├• [Tai khoan] " << taikhoan.ten_nguoi_dung << endl;
                cout << "│     └──> [*] So du: " << xem_so_du(taikhoan) << " VND" << endl;
                cout << "├• 1. Xem so tai khoan" << endl;
                cout << "├• 2. Xem ma Qrbank" << endl;  
                cout << "├• 3. Nhap so du" << endl;
                cout << "├• 4. Chuyen khoan" << endl;
                cout << "├• 5. Xem lich su giao dich" << endl;
                cout << "├• 6. Dang xuat" << endl;
                cout << "└──────────> Ban chon: "; char z = getche();
                cout << endl;
                if (z == '1'){
                    xem_so_tai_khoan(taikhoan);
                    getch();
                } else if(z == '2'){
                    xem_ma_qr(taikhoan);
                    getch();
                } else if(z == '3'){
                    nhap_so_du(taikhoan);
                    getch();
                } else if(z == '4'){
                    string sotaikhoan2; int so_tien_muon_chuyen; 
                    cin.ignore();
                    cout << "\n\t(?) Nhap so tai khoan muon chuyen: "; getline(cin, sotaikhoan2);
                    cout << "\t(?) Nhap so tien muon chuyen: "; cin >> so_tien_muon_chuyen;
                    chuyen_khoan(taikhoan, sotaikhoan2, so_tien_muon_chuyen);
                    getch();
                } else if(z == '5'){
                    tra_lich_su_chuyen_khoan(taikhoan);
                    getch();
                } else if(z == '6'){
                    cout << "\n(-) Ban chon dang xuat !" << endl;
                    getch();
                    break;
                } else{ 
                    cout << "\n(!) Vui long chon tu 1 -> 5" << endl;
                    getch();
                }
            }
        } else if(c == '3'){
            cout << "\n\n(-) Ban da chon thoat ngan hang !" << endl;
            getch();
            break;
        } else {
            cout << "\n\n(!) Vui long chon 1 -> 3" << endl;
            getch();
        } 
    }
    return 0;
}