#include <cstdlib>
using namespace std;

int main(){
    system("g++ chuongtrinh.cpp caidat.cpp blockchain.cpp lib\\qrcodegen.cpp -o chuongtrinh.exe");
    system("chuongtrinh.exe");
    return 0;
}
