#include <iostream>
#include <string>

using namespace std;
struct admin
{
    string username;
    string password;
};

void mainmenu(){
    int pilihan;

    cout << "==================================================\n";
    cout << "          SELAMAT DATANG DI STUDIO FOTO           \n";
    cout << "==================================================\n";
    cout << "1. Sign In (Masuk Akun)\n";
    cout << "2. Sign Up (Daftar Akun Baru)\n";
    cout << "3. Keluar\n";
    cout << "==================================================\n";
    cout << "Pilih opsi (1-3): ";
    cin >> pilihan;
    cout << "--------------------------------------------------\n";
}