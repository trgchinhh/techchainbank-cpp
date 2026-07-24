#include <cstdlib>
using namespace std;

string command_compile = "g++ chuongtrinh.cpp caidat.cpp blockchain.cpp lib\\qrcodegen.cpp -o chuongtrinh.exe";

int main(){
    system(command_compile);
    system("chuongtrinh.exe");
    return 0;
}
