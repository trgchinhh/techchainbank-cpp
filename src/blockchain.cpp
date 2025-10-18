#include "thuvien.h"
#include "blockchain.h"
using namespace std;

// Giao dich 
GiaoDich::GiaoDich(string gui, string nhan, string stk_gui, string stk_nhan, double tien, string tg) {
    this->nguoi_gui = gui;
    this->nguoi_nhan = nhan;
    this->stk_gui = stk_gui;
    this->stk_nhan = stk_nhan;
    this->so_tien = tien;
    this->thoigian = tg;
}

// Block
Block::Block(int chi_so, string ma_truoc, GiaoDich giaodich): giaodich(giaodich){
    this->chi_so = chi_so;
    this->ma_truoc = ma_truoc;
    this->nonce = 0;
    this->thoigian = thoi_gian_hien_tai();
    if (!this->thoigian.empty() && this->thoigian.back() == '\n')
        this->thoigian.pop_back();
    this->ma_hash = this->tinhHash();
}

string Block::tinhHash() const {
    stringstream ss;
    ss << chi_so << ma_truoc << giaodich.nguoi_gui
       << giaodich.nguoi_nhan << giaodich.so_tien
       << giaodich.thoigian << nonce;
    return picosha2::hash256_hex_string(ss.str());
}

// Blockchain
Blockchain::Blockchain(int dokho) {
    this->do_kho = dokho;
    //chuoi.push_back(taoBlockGoc());
    docFile(file_block); 
    if (chuoi.empty()) {
        chuoi.push_back(taoBlockGoc());
    }
}

void Blockchain::docFile(const string &tenfile) {
    ifstream f(tenfile);
    if (!f.is_open()) return;  
    json j;
    f >> j;
    chuoi.clear(); 
    for (auto &blockData : j) {
        GiaoDich gd(
            blockData["giao_dich"]["nguoi_gui"],
            blockData["giao_dich"]["nguoi_nhan"],
            "0000", 
            "0000", 
            blockData["giao_dich"]["so_tien"],
            blockData["giao_dich"]["thoigian"]
        );

        Block b(blockData["chi_so"], blockData["ma_truoc"], gd);
        b.nonce = blockData["nonce"];
        b.ma_hash = blockData["ma_hash"];
        b.thoigian = blockData["thoigian"];
        chuoi.push_back(b);
    }
}

Block Blockchain::taoBlockGoc() {
    GiaoDich goc("He Thong", "Ngan Hang TCB", "0000", "0000", 0, thoi_gian_hien_tai());
    Block block0(0, "0", goc);
    block0.ma_hash = block0.tinhHash();
    return block0;
}

Block Blockchain::layBlockCuoi() const {
    return chuoi.back();
}

void Blockchain::daoBlock(Block &block) {
    string muc_tieu(do_kho, '0');
    while (block.ma_hash.substr(0, do_kho) != muc_tieu) {
        block.nonce++;
        block.ma_hash = block.tinhHash();
    }
}

void Blockchain::themGiaoDich(const GiaoDich &gd) {
    Block block_moi(chuoi.size(), layBlockCuoi().ma_hash, gd);
    cout << "\n[⛏️] Dang dao block cho giao dich: "
         << gd.nguoi_gui << " → " << gd.nguoi_nhan
         << " (" << gd.so_tien << " VND)...\n";
    daoBlock(block_moi);
    cout << "[✅] Đào thành công !" << endl 
         << "Hash: " << block_moi.ma_hash << "\n";
    chuoi.push_back(block_moi);
    luuFile(file_block);
}

bool Blockchain::kiemTraHopLe() const {
    for (size_t i = 1; i < chuoi.size(); i++) {
        const Block &hien_tai = chuoi[i];
        const Block &truoc = chuoi[i - 1];
        if (hien_tai.ma_hash != hien_tai.tinhHash()) return false;
        if (hien_tai.ma_truoc != truoc.ma_hash) return false;
    }
    return true;
}

void Blockchain::luuFile(const string &tenfile) const {
    json j;
    for (auto &b : chuoi) {
        json blockData;
        blockData["chi_so"] = b.chi_so;
        blockData["ma_truoc"] = b.ma_truoc;
        blockData["thoigian"] = b.thoigian;
        blockData["nonce"] = b.nonce;
        blockData["ma_hash"] = b.ma_hash;
        json gd;
        gd["nguoi_gui"] = b.giaodich.nguoi_gui;
        gd["nguoi_nhan"] = b.giaodich.nguoi_nhan;
        gd["so_tien"] = b.giaodich.so_tien;
        gd["thoigian"] = b.giaodich.thoigian;
        blockData["giao_dich"] = gd;
        j.push_back(blockData);
    }
    ofstream f(tenfile);
    f << setw(4) << j;
}

void Blockchain::inChuoi() const {
    cout << "\n\n\t─────────────── DANH SACH BLOCKCHAIN ───────────────\n\n";
    for (auto &b : chuoi) {
        cout << "┌────────────────────────────────────────────\n";
        cout << "├> Block: " << b.chi_so << "\n";
        cout << "├> Người gửi: " << b.giaodich.nguoi_gui << "\n";
        cout << "│  ││└─> Người nhận: " << b.giaodich.nguoi_nhan << "\n";
        cout << "│  │└──> Số tiền: " << b.giaodich.so_tien << " VND\n";
        cout << "│  └───> Thời gian: " << b.thoigian << "\n";
        cout << "├> Hash trước: " << b.ma_truoc << "\n";
        cout << "├> Hash hiện tại: " << b.ma_hash << "\n";
        cout << "├> Nonce: " << b.nonce << "\n";
        cout << "└────────────────────────────────────────────\n";
    }
}
