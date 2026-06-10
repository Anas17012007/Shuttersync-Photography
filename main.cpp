#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;
struct admin
{
    string username;
    string password;
};
admin daftarAdmin[6] = {
        {"Solose", "Solose17012007"},
        {"Cayla", "Cayla123"},
        {"Dicky", "Dicky123"}, 
        {"Tiara", "Tiara123"},
        {"Putri", "Putri123"},
        {"siapalah", "okgasokgasprabowogibranoranggas"}
    };
void mainmenu(){
    int pilihan;

    cout << "==================================================\n";
    cout << "          SELAMAT DATANG DI STUDIO FOTO           \n";
    cout << "==================================================\n";
    cout << "1. Admin \n";
    cout << "2. Visitor\n";
    cout << "3. Keluar\n";
    cout << "==================================================\n";
    cout << "Pilih opsi (1-3): ";
    cin >> pilihan;
    cout << "--------------------------------------------------\n";
}