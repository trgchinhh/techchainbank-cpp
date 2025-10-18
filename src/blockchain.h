#include <iostream>
#include <vector>
#include <string>
#include "lib//json.hpp"
using json = nlohmann::ordered_json;
using namespace std;

const int do_kho_mac_dinh = 5;
const string file_block = "block.json";

struct GiaoDich {
    string nguoi_gui;
    string nguoi_nhan;
    string stk_gui;
    string stk_nhan;
    int so_tien;
    string thoigian;

    GiaoDich(string nguoi_gui, string nguoi_nhan, string stk_gui, string stk_nhan, double so_tien, string thoigian);
};

struct Block {
    int chi_so;
    string ma_truoc;
    GiaoDich giaodich;
    string thoigian;
    int nonce;
    string ma_hash;

    Block(int chi_so, string ma_truoc, GiaoDich giaodich);
    string tinhHash() const;
};

class Blockchain {
private:
    vector<Block> chuoi;
    int do_kho;

    Block taoBlockGoc();
    Block layBlockCuoi() const;
    void daoBlock(Block &block);

public:
    Blockchain(int do_kho = do_kho_mac_dinh);
    void themGiaoDich(const GiaoDich &gd);
    bool kiemTraHopLe() const;
    void luuFile(const string &tenfile) const;
    void inChuoi() const;
};
