#include <iostream>
using namespace std;

string lenhbiendich = "g++ src\\chuongtrinh.cpp src\\caidat.cpp src\\blockchain.cpp src\\lib\\qrcodegen.cpp -o chuongtrinh.exe" ;

int main(){
    system(lenhbiendich.c_str());
    system("chuongtrinh.exe");
    return 0;
}
