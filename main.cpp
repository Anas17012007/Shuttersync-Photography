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
struct visitor
{
    string username;
    string password;
};
const int maks_visitor=100;
int jumlahvisitor = 0;
visitor visit[maks_visitor];
admin daftarAdmin[6] = {
    {"Solose", "Solose17012007"},
    {"Cayla", "Cayla123"},
    {"Dicky", "Dicky123"},
    {"Tiara", "Tiara123"},
    {"Putri", "Putri123"},
    {"siapalah", "okgasokgasprabowogibranoranggas"}};
void mainmenu()
{
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
    if (pilihan == 2)
    {
        int pilihanVisitor;
        cout << "==================================================\n";
        cout << "                  MENU VISITOR                    \n";
        cout << "==================================================\n";
        cout << "1. Sign In (Masuk)\n";
        cout << "2. Sign Up (Daftar Akun Baru)\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "==================================================\n";
        cout << "Pilih opsi (1-3): ";
        cin >> pilihanVisitor;
        cout << "--------------------------------------------------\n";
        system("cls");
        if (pilihanVisitor == 2)
        {
            cout << "==================================================\n";
            cout << "               REGISTRASI VISITOR                 \n";
            cout << "==================================================\n";
            cout << "Masukkan Username Baru : ";
            cin >> visit[jumlahvisitor].username;
            cout << "Masukkan Password Baru : ";
            cin >> visit[jumlahvisitor].password;
            cout << "--------------------------------------------------\n";

            ofstream fileVisitor("visitor.txt", ios::app);
            if (fileVisitor.is_open())
            {
                fileVisitor << visit[jumlahvisitor].username << " | " << visit[jumlahvisitor].password << endl;
                fileVisitor.close();
                cout << "Registrasi Berhasil! Akun Anda telah terdaftar.\n";
            }
            if (visit[jumlahvisitor].username.empty() || visit[jumlahvisitor].password.empty())
            {
                cout << "Username/password tidak boleh kosong!\n";
            }
            else
            {
                cout << "Gagal membuka file database untuk menyimpan data.\n";
            }
            cout << "==================================================\n";
        }
    }
}
