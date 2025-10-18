#include "thuvien.h"

int lay_chieu_rong_terminal(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int chieu_rong = 80; 
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        chieu_rong = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return chieu_rong;
}

void in_giua_man_hinh(const string& cau) {
    int chieu_rong = lay_chieu_rong_terminal();  
    int do_dai = cau.length();
    int khoang_trang = (chieu_rong - do_dai) / 2;
    if (khoang_trang < 0) khoang_trang = 0;
    cout << string(khoang_trang, ' ') << cau;
}

void in_banner(){
    string banner = 
    R"(Github: https://github.com/trgchinhh
 _______        _      _____ _           _       ____              _    
|__   __|      | |    / ____| |         (_)     |  _ \            | |   
   | | ___  ___| |__ | |    | |__   __ _ _ _ __ | |_) | __ _ _ __ | | __
   | |/ _ \/ __| '_ \| |    | '_ \ / _` | | '_ \|  _ < / _` | '_ \| |/ /
   | |  __/ (__| | | | |____| | | | (_| | | | | | |_) | (_| | | | |   < 
   |_|\___|\___|_| |_|\_____|_| |_|\__,_|_|_| |_|____/ \__,_|_| |_|_|\_\
    )";
    stringstream ss(banner);
    string line;
    cout << "\n";
    while (getline(ss, line)) {
        in_giua_man_hinh(line);
        cout << endl;
    }
    cout << "\n";
}

string thoi_gian_hien_tai(){
    auto now = system_clock::now();
    time_t time = system_clock::to_time_t(now);
    tm* local_tm = localtime(&time);
    ostringstream oss;
    oss << put_time(local_tm, "%H:%M:%S %d-%m-%Y");
    return oss.str();
}

string dang_ky_tai_khoan_ten_nguoi_dung(TaiKhoanDangKy& taikhoan){
    cout << endl;
    cin.ignore();
    cout << "\t(?) Tao ten nguoi dung: ";
    getline(cin, taikhoan.ten_nguoi_dung);
    if(taikhoan.ten_nguoi_dung.empty() || 
        taikhoan.ten_nguoi_dung.size() < 5){
        cout << "\t\t(!) Ten nguoi dung phai tu 5 ky tu tro len !" << endl;
        return "";
    } 
    return taikhoan.ten_nguoi_dung;
}

string dang_ky_tai_khoan_mat_khau(TaiKhoanDangKy& taikhoan){
    cout << "\t(?) Tao mat khau: ";
    getline(cin, taikhoan.mat_khau);
    if(taikhoan.mat_khau.empty() ||
        taikhoan.mat_khau.size() < 4){
        cout << "\t\t(!) Mat khau phai tu 4 ky tu tro len !" << endl;
        return "";
    }
    return taikhoan.mat_khau;
}

string tao_so_tai_khoan(TaiKhoanDangKy &taikhoan){
    string so_tai_khoan = taikhoan.tao_so_tai_khoan();
    string so_tai_khoan_so_nguyen = "";
    for(char s : so_tai_khoan){
        so_tai_khoan_so_nguyen += to_string((int)s);
    }
    string so_tai_khoan_thu_gon = so_tai_khoan_so_nguyen.substr(0, 10);
    return so_tai_khoan_thu_gon;
}

void luu_du_lieu_sau_dang_ky(TaiKhoanDangKy& taikhoan) {
    json ds_tai_khoan;
    ifstream in(file_data);
    if (in.is_open()) {
        try {
            in >> ds_tai_khoan;
        } catch (...) {
            ds_tai_khoan = json::array();
        }
        in.close();
    } else {
        ds_tai_khoan = json::array();
    }

    for(auto &tai_khoan : ds_tai_khoan){
        if(taikhoan.ten_nguoi_dung == tai_khoan["ten_nguoi_dung"]){
            cout << "\t(!) Tai khoan nay da ton tai !" << endl;
            getch();
            return;
        }
    }
    taikhoan.so_tai_khoan = tao_so_tai_khoan(taikhoan);
    cout << endl;
    cout << "\t┌───────────────────────────────────────┐" << endl;
    cout << "\t├> So tai khoan cua ban la: " << taikhoan.so_tai_khoan << "  │" << endl;
    cout << "\t└───────────────────────────────────────┘" << endl;
    getch();
    json thong_tin_tai_khoan = {
        {"ten_nguoi_dung", taikhoan.ten_nguoi_dung},
        {"mat_khau", taikhoan.mat_khau},
        {"so_du", taikhoan.so_du},
        {"so_tai_khoan", taikhoan.so_tai_khoan},
        {"lich_su_chuyen_khoan", taikhoan.lich_su_chuyen_khoan}
    };

    bool da_ton_tai = false;
    for (auto& tk : ds_tai_khoan) {
        if (tk["ten_nguoi_dung"] == taikhoan.ten_nguoi_dung) {
            tk = thong_tin_tai_khoan;  
            da_ton_tai = true;
            break;
        }
    }
    if (!da_ton_tai) {
        ds_tai_khoan.push_back(thong_tin_tai_khoan);
    }
    ofstream out(file_data);
    if (!out.is_open()) {
        cout << "\t(!) Khong tim thay file " << file_data << " !" << endl;
        return;
    }
    out << setw(4) << ds_tai_khoan << endl;
    out.close();

    if (da_ton_tai)
        cout << "\t(!) Tai khoan da ton tai, da cap nhat lai thong tin thanh cong!" << endl;
    else
        cout << "\t(*) Da luu tai khoan moi vao " << file_data << " thanh cong!" << endl;
}

bool xac_thuc_ten_nguoi_dung(TaiKhoanDangNhap& taikhoan){
    if(taikhoan.ten_nguoi_dung.empty() ||
        taikhoan.ten_nguoi_dung.size() < 5){
        cout << "\t(!) Ten nguoi dung phai tu 5 ky tu tro len !" << endl;
        return false;
    }
    ifstream in(file_data);
    if(! in.is_open()){
        cout << "\t(!) Khong the tim thay file" << file_data << endl;
        return false;
    }

    json ds_tai_khoan;
    in >> ds_tai_khoan;
    in.close();
    bool check = false;
    for (auto& tai_khoan : ds_tai_khoan) {
        string ten = tai_khoan["ten_nguoi_dung"];
        if (ten == taikhoan.ten_nguoi_dung) {
            check = true;
        }
    }
    if(!check){
        cout << "\t(!) Ten dang nhap khong duoc tim thay !" << endl;
        return false;
    } 
    cout << "\t(*) Ten nguoi dung dung !" << endl;
    return true;
}

bool xac_thuc_mat_khau(TaiKhoanDangNhap& taikhoan){
    if(taikhoan.mat_khau.empty() ||
        taikhoan.mat_khau.size() < 4){
        cout << "\t(!) Mat khau phai tu 4 ky tu tro len !" << endl;
        return false;
    }
    ifstream in(file_data);
    if(! in.is_open()){
        cout << "\t(!) Khong the tim thay file" << file_data << endl;
        return false;
    }

    json ds_tai_khoan;
    in >> ds_tai_khoan;
    in.close();
    bool check = false;
    for (auto& tk : ds_tai_khoan) {
        if (tk["ten_nguoi_dung"] == taikhoan.ten_nguoi_dung &&
            tk["mat_khau"] == taikhoan.mat_khau) {

            taikhoan.so_du = tk["so_du"].is_string() ? tk["so_du"].get<string>()
                                                     : to_string(tk["so_du"].get<int>());
            taikhoan.so_tai_khoan = tk["so_tai_khoan"].get<string>();
            taikhoan.lich_su_chuyen_khoan.clear();
            if (tk.contains("lich_su_chuyen_khoan") && tk["lich_su_chuyen_khoan"].is_array()) {
                for (auto& lichsu : tk["lich_su_chuyen_khoan"])
                    taikhoan.lich_su_chuyen_khoan.push_back(lichsu.get<string>());
            }

            cout << "\t(*) Dang nhap thanh cong !" << endl;
            cout << "\t(*) STK cua ban: " << taikhoan.so_tai_khoan << endl;
            return true;
        }
    }
    if(!check){
        cout << "\t(!) Ten dang nhap khong duoc tim thay !" << endl;
        return false;
    } 
    cout << "\t(*) Nhap mat khau dung !" << endl;
    return true;
}

int xem_so_du(TaiKhoanDangNhap& taikhoan){
    ifstream in(file_data);
    if(! in.is_open()){
        cout << "\t(!) Khong the tim thay file" << file_data << endl;
        return -1;
    }
    json ds_tai_khoan;
    in >> ds_tai_khoan;
    in.close();
    int so_du;
    for (auto& tai_khoan : ds_tai_khoan) {
        string ten = tai_khoan["ten_nguoi_dung"];
        if (ten == taikhoan.ten_nguoi_dung) {
            so_du = tai_khoan["so_du"];
            break;
        }
    }
    return so_du;
}

void xem_so_tai_khoan(TaiKhoanDangNhap& taikhoan){
    ifstream in(file_data);
    if(! in.is_open()){
        cout << "\t(!) Khong the tim thay file" << file_data << endl;
        return;
    }

    json ds_tai_khoan;
    in >> ds_tai_khoan;
    in.close();
    for (auto& tai_khoan : ds_tai_khoan) {
        string ten = tai_khoan["ten_nguoi_dung"];
        if (ten == taikhoan.ten_nguoi_dung) {
            cout << endl;
            cout << "\t┌──────────────────────────────┐" << endl;
            cout << "\t├> So tai khoan: " << tai_khoan["so_tai_khoan"] << "  │" << endl;
            cout << "\t└──────────────────────────────┘" << endl;
            break;
        }
    }
}

void xem_ma_qr(TaiKhoanDangNhap& taikhoan){
    ifstream in(file_data);
    if(! in.is_open()){
        cout << "\t\t(!) Khong the tim thay file" << file_data << endl;
        return;
    }
    json ds_tai_khoan;
    in >> ds_tai_khoan;
    in.close();
    string data = "";
    for(auto& tai_khoan : ds_tai_khoan){
        if(taikhoan.ten_nguoi_dung == tai_khoan["ten_nguoi_dung"]){
            data += tai_khoan["ten_nguoi_dung"];
            data += tai_khoan["mat_khau"]; 
            data += tai_khoan["so_tai_khoan"];
            break;
        }
    }
    if(data.empty()){
        cout << "\t\t(!) Khong tim thay tai khoan." << endl;
        return;
    }
    cout << endl;
    QrCode qr = QrCode::encodeText(data.c_str(), QrCode::Ecc::LOW);
    int size = qr.getSize();
    cout << "\t┌";
    for (int i = 0; i < size * 2; i++)
        cout << "─";
    cout << "┐" << endl;
    for (int y = 0; y < size; y++) {
        cout << "\t│";
        for (int x = 0; x < size; x++)
            cout << (qr.getModule(x, y) ? "██" : "  ");
        cout << "│" << endl;
    }
    cout << "\t└";
    for (int i = 0; i < size * 2; i++)
        cout << "─";
    cout << "┘" << endl;
}

void nhap_so_du(TaiKhoanDangNhap& taikhoan){
    cin.ignore();
    cout << "\t(?) Nhap so du cho tai khoan cua ban: ";
    getline(cin, taikhoan.so_du);
    if (taikhoan.so_du.empty()) {
        cout << "\t\t(!) So du khong duoc de trong!" << endl;
        return;
    }
    for(char c : taikhoan.so_du){
        if(!isdigit(c)){
            cout << "\t\t(!) Nhap so du khong hop le !" << endl;
            return;
        }
    }
    int so_du = stoi(taikhoan.so_du);
    if(so_du < 10000 || so_du > 10000000){
        cout << "\t\t(!) Han muc nap 1 lan (10k -> 10tr) !" << endl;
        return;
    } 
    ifstream in(file_data);
    if(! in.is_open()){
        cout << "\t\t(!) Khong the tim thay file" << file_data << endl;
        return;
    }

    json ds_tai_khoan;
    in >> ds_tai_khoan;
    in.close();
    bool check = false;
    int so_du_hien_tai = 0;
    for (auto& tai_khoan : ds_tai_khoan) {
        string ten = tai_khoan["ten_nguoi_dung"];
        if (ten == taikhoan.ten_nguoi_dung) {
            int so_du_cu = 0;
            try {
                so_du_cu = tai_khoan["so_du"].get<int>();
            } catch (...) {
                try {
                    so_du_cu = stoi(tai_khoan["so_du"].get<string>());
                } catch (...) {
                    so_du_cu = 0;
                }
            }
            tai_khoan["so_du"] = so_du_cu + so_du;
            check = true;
            so_du_hien_tai = tai_khoan["so_du"].get<int>();
        }
    }
    if(!check){
        cout << "\t\t(!) Thong tin tai khoan khong duoc tim thay !" << endl;
        cout << "\t\t(!) Them so du khong thanh cong !" << endl;
        return;
    } 
    ofstream out(file_data);
    if (!out.is_open()) {
        cout << "\t\t(!) Khong the ghi de file " << file_data << endl;
        return;
    }
    out << setw(4) << ds_tai_khoan;
    out.close();
    cout << "\t\t(*) Nap tien thanh cong! So du hien tai la: " << so_du_hien_tai << " VND" << endl; 
}

void chuyen_khoan(TaiKhoanDangNhap& taikhoan1, string sotaikhoan2, int so_tien_muon_chuyen) {
    if (taikhoan1.so_tai_khoan == sotaikhoan2) {
        cout << "\t(!) STK nhan va chuyen phai khac nhau !" << endl;
        return;
    }
    if (taikhoan1.so_tai_khoan.size() != chieu_dai_stk || sotaikhoan2.size() != chieu_dai_stk) {
        cout << "\t(!) STK phai du " << chieu_dai_stk << " ky tu !" << endl;
        return;
    }

    ifstream in(file_data);
    if (!in.is_open()) {
        cout << "\t(!) Khong the tim thay file " << file_data << endl;
        return;
    }

    json ds_tai_khoan;
    in >> ds_tai_khoan;
    in.close();

    string ten_nguoi_nhan;
    for (auto& tk : ds_tai_khoan) {
        if (!tk.contains("lich_su_chuyen_khoan") || !tk["lich_su_chuyen_khoan"].is_array()) {
            tk["lich_su_chuyen_khoan"] = json::array();
        }
    }

    bool co_tk_gui = false, co_tk_nhan = false;
    for (auto& tai_khoan : ds_tai_khoan) {
        string stk = tai_khoan["so_tai_khoan"];
        if (stk == taikhoan1.so_tai_khoan) {
            co_tk_gui = true;

            int so_du_gui = tai_khoan["so_du"].is_string() ? stoi(tai_khoan["so_du"].get<string>()) : tai_khoan["so_du"].get<int>();
            if (so_du_gui < so_tien_muon_chuyen) {
                cout << "\t(!) So du khong du de thuc hien giao dich !" << endl;
                return;
            }

            so_du_gui -= so_tien_muon_chuyen;
            tai_khoan["so_du"] = so_du_gui;

            string lich_su = thoi_gian_hien_tai() + " da chuyen: " +
                             to_string(so_tien_muon_chuyen) + " VND den STK: " + sotaikhoan2;
            tai_khoan["lich_su_chuyen_khoan"].push_back(lich_su);

            cout << "\t(*) So du con lai: " << so_du_gui << " VND" << endl;
        }

        if (stk == sotaikhoan2) {
            co_tk_nhan = true;
            ten_nguoi_nhan = tai_khoan["ten_nguoi_dung"];
            int so_du_nhan = tai_khoan["so_du"].is_string() ? stoi(tai_khoan["so_du"].get<string>()) : tai_khoan["so_du"].get<int>();
            so_du_nhan += so_tien_muon_chuyen;
            tai_khoan["so_du"] = so_du_nhan;

            string lich_su = thoi_gian_hien_tai() + " da nhan: " +
                             to_string(so_tien_muon_chuyen) + " VND tu STK: " + taikhoan1.so_tai_khoan;
            tai_khoan["lich_su_chuyen_khoan"].push_back(lich_su);
        }
    }

    if (!co_tk_gui || !co_tk_nhan) {
        cout << "\t(!) Mot trong hai STK khong ton tai!" << endl;
        return;
    }
    ofstream out(file_data);
    if (!out.is_open()) {
        cout << "\t(!) Khong the ghi de file " << file_data << endl;
        return;
    }
    out << setw(4) << ds_tai_khoan;
    out.close();

    cout << "\t(*) Da chuyen thanh cong " << so_tien_muon_chuyen << " VND den STK: " << sotaikhoan2 << " - " << ten_nguoi_nhan << endl;
}


void tra_lich_su_chuyen_khoan(TaiKhoanDangNhap& taikhoan){
    ifstream file(file_data);
    if(! file.is_open()){
        cout << "\t(!) Khong the tim thay file" << file_data << endl;
        return;
    }

    json ds_tai_khoan;
    file >> ds_tai_khoan;
    file.close();

    vector<string> lich_su_chuyen_khoan; 

    bool tim_thay = false;
    for(auto& tai_khoan : ds_tai_khoan){
        if(tai_khoan["so_tai_khoan"] == taikhoan.so_tai_khoan){
            tim_thay = true;
            if(tai_khoan.contains("lich_su_chuyen_khoan") && tai_khoan["lich_su_chuyen_khoan"].is_array()){
                for(auto& lich_su : tai_khoan["lich_su_chuyen_khoan"]){
                    lich_su_chuyen_khoan.push_back(lich_su.get<string>());
                }
            }
            break;
        }
    }

    cout << "\n\t(*) Lich su chuyen khoan ";
    if(lich_su_chuyen_khoan.empty()){
        cout << " (!) Khong co" << endl;
        return;
    }
    int i = 1;
    cout << endl;
    cout << "\t\t┌─────────────────────────────────────────────────────────────────────" << endl;
    for(auto& lich_su : lich_su_chuyen_khoan){
        cout << "\t\t├> " << i << ". " <<   lich_su << endl;
        i++;
    }
    cout << "\t\t└─────────────────────────────────────────────────────────────────────" << endl;
}