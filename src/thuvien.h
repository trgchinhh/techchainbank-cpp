#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include <cctype>
#include <sstream>
#include <chrono>
#include <windows.h>
#include "lib\\picosha2.h"
#include "lib\\json.hpp"
#include "lib\\qrcodegen.hpp"

using namespace std;
using namespace chrono;
using namespace picosha2;
using namespace qrcodegen;
using json = nlohmann::ordered_json;

const int chieu_dai_stk = 10;
const string file_data = "..\\src\\data.json";

string thoi_gian_hien_tai();

struct TaiKhoanDangKy {
    string ten_nguoi_dung;
    string mat_khau;
    string so_du;
    vector<string> lich_su_chuyen_khoan;
    string so_tai_khoan;

    TaiKhoanDangKy(string ten_nguoi_dung, string mat_khau){
        this->ten_nguoi_dung = ten_nguoi_dung;
        this->mat_khau = mat_khau;
        this->so_du = "0";
        this->so_tai_khoan = "";
    }

    string tao_so_tai_khoan(){
        string du_lieu_tai_khoan = this->ten_nguoi_dung 
                + this->mat_khau + thoi_gian_hien_tai(); 
        return hash256_hex_string(du_lieu_tai_khoan);
    }
};

struct TaiKhoanDangNhap {
    string ten_nguoi_dung;
    string mat_khau;
    string so_du;
    vector<string> lich_su_chuyen_khoan;
    string so_tai_khoan;

    TaiKhoanDangNhap(string ten_nguoi_dung, string mat_khau, int so_du, string so_tai_khoan){
        this->ten_nguoi_dung = ten_nguoi_dung;
        this->mat_khau = mat_khau;
        this->so_du = so_du;
        this->so_tai_khoan = so_tai_khoan;
    }
};

// Banner
int lay_chieu_rong_terminal();
void in_giua_man_hinh();
void in_banner();

// Dang ky 
string dang_ky_tai_khoan_ten_nguoi_dung(TaiKhoanDangKy& taikhoan);
string dang_ky_tai_khoan_mat_khau(TaiKhoanDangKy& taikhoan);
string tao_so_tai_khoan(TaiKhoanDangKy& taikhoan);
void luu_du_lieu_sau_dang_ky(TaiKhoanDangKy& taikhoan);

// Dang nhap 
bool xac_thuc_ten_nguoi_dung(TaiKhoanDangNhap& taikhoan);
bool xac_thuc_mat_khau(TaiKhoanDangNhap& taikhoan);

// Tinh nang 
int xem_so_du(TaiKhoanDangNhap& taikhoan);
void xem_so_tai_khoan(TaiKhoanDangNhap& taikhoan);
void xem_ma_qr(TaiKhoanDangNhap& taikhoan);
void nhap_so_du(TaiKhoanDangNhap& taikhoan);
void chuyen_khoan(TaiKhoanDangNhap& taikhoan, string sotaikhoan2, int so_tien_muon_chuyen);
void tra_lich_su_chuyen_khoan(TaiKhoanDangNhap& taikhoan);