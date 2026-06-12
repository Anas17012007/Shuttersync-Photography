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
    string nama;
    string noTelp;
    string email;
};

struct reservasi
{
    int idReservasi;
    string usernameVisitor;
    string namaPaket;
    string tanggal;
    int durasi;
    int harga;
    int totalBiaya;
    string status;
};
const string DAFTAR_PAKET[4] = {"Wisuda", "Prewedding", "Keluarga", "Produk"};
const int HARGA_PAKET[4] = {700000, 150000, 750000, 400000};
const int maks_visitor = 100;
const int maks_reservasi = 100;

int jumlahvisitor = 0;
int jumlahreservasi = 0;

visitor visit[maks_visitor];
reservasi reservasiList[maks_reservasi];

string username_aktif;
bool admin_aktif = false;

admin daftarAdmin[6] = {
    {"Solose", "Solose17012007"},
    {"Cayla", "Cayla123"},
    {"Dicky", "Dicky123"},
    {"Tiara", "Tiara123"},
    {"Putri", "Putri123"},
    {"siapalah", "okgasokgasprabowogibranoranggas"}};

bool cekUsernameDuplikat(string usernameBaru)
{
    ifstream fileVisitor("visitor.txt");
    string baris;
    while (getline(fileVisitor, baris))
    {
        int posisi = baris.find(" | ");
        if (posisi != string::npos)
        {
            string usernameDiFile = baris.substr(0, posisi);
            if (usernameDiFile == usernameBaru)
            {
                fileVisitor.close();
                return true;
            }
        }
    }
    fileVisitor.close();
    return false;
}
void mainmenu()
{
    int pilihan;

    cout << "==================================================\n";
    cout << "          SELAMAT DATANG DI STUDIO FOTO           \n";
    cout << "==================================================\n";
    cout << "1. Admin \n";
    cout << "2. Visitor\n";
    cout << "0. Keluar\n";
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
        cout << "0. Kembali ke Menu Utama\n";
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
            getline(cin >> ws, visit[jumlahvisitor].username);
            cout << "Masukkan Password Baru : ";
            getline(cin >> ws, visit[jumlahvisitor].password);
            cout << "Masukkan Nama Lengkap  : ";
            getline(cin >> ws, visit[jumlahvisitor].nama);
            cout << "Masukkan No. Telepon   : ";
            getline(cin >> ws, visit[jumlahvisitor].noTelp);
            cout << "Masukkan Email         : ";
            getline(cin >> ws, visit[jumlahvisitor].email);
            cout << "--------------------------------------------------\n";

            if (visit[jumlahvisitor].username.empty() ||
                visit[jumlahvisitor].password.empty() ||
                visit[jumlahvisitor].nama.empty() ||
                visit[jumlahvisitor].noTelp.empty())
            {
                cout << "Semua field tidak boleh kosong!\n";
            }
            else if (cekUsernameDuplikat(visit[jumlahvisitor].username))
            {
                cout << "Username sudah digunakan!\n";
            }
            else
            {
                ofstream fileVisitor("visitor.txt", ios::app);
                if (fileVisitor.is_open())
                {
                    fileVisitor << visit[jumlahvisitor].username << " | "
                                << visit[jumlahvisitor].password << " | "
                                << visit[jumlahvisitor].nama << " | "
                                << visit[jumlahvisitor].noTelp << " | "
                                << visit[jumlahvisitor].email << endl;
                    fileVisitor.close();
                    jumlahvisitor++;
                    cout << "Registrasi Berhasil!\n";
                }
                else
                {
                    cout << "Gagal membuka file!\n";
                }
            }
        }
        else if (pilihanVisitor == 0)
        {
            return;
        }
        else if (pilihanVisitor == 1)
        {
            string tempvisitorUsername, tempvisitorPassword;
            cout << "==================================================\n";
            cout << "               SIGN IN VISITOR                    \n";
            cout << "==================================================\n";
            cout << "Masukkan Username : ";
            getline(cin >> ws, tempvisitorUsername);
            cout << "Masukkan Password : ";
            getline(cin >> ws, tempvisitorPassword);
            cout << "--------------------------------------------------\n";
            ifstream fileVisitor("visitor.txt");
            bool berhasil = false;
            string baris;
            while (getline(fileVisitor, baris))
            {
                int posisi = baris.find(" | ");

                if (posisi != string::npos)
                {
                    int pos1 = baris.find(" | ", posisi + 3);
                    string usernameDiFile = baris.substr(0, posisi);
                    string passwordDiFile = baris.substr(posisi + 3, pos1 - posisi - 3);
                    if (usernameDiFile == tempvisitorUsername && passwordDiFile == tempvisitorPassword)
                    {
                        berhasil = true;
                        break;
                    }
                }
            }
            fileVisitor.close();

            if (berhasil)
            {
                username_aktif = tempvisitorUsername;
                cout << "Sign In Berhasil! Selamat datang, " << username_aktif << endl;
                system("pause");
            }
            else
            {
                cout << "Username atau password salah!\n";
                system("pause");
            }
        }
    }
    else if (pilihan == 0)
    {
        cout << "Terima kasih telah berkunjung. Sampai jumpa!\n";
        exit(0);
    }
    else if (pilihan == 1)
    {
        int pilihanAdmin;
        cout << "==================================================\n";
        cout << "                  MENU ADMIN                      \n";
        cout << "==================================================\n";
        cout << "1. Sign In (Masuk)\n";
        cout << "0. Kembali\n";
        cout << "==================================================\n";
        cout << "Pilih opsi (1-2): ";
        cin >> pilihanAdmin;
        cout << "--------------------------------------------------\n";
        system("cls");
        if (pilihanAdmin == 1)
        {
            string tempadminUsername, tempadminPassword;
            cout << "==================================================\n";
            cout << "               SIGN IN ADMIN                    \n";
            cout << "==================================================\n";
            cout << "Masukkan Username : ";
            getline(cin >> ws, tempadminUsername);
            cout << "Masukkan Password : ";
            getline(cin >> ws, tempadminPassword);
            cout << "--------------------------------------------------\n";
            bool berhasil = false;
            for (int i = 0; i < 6; i++)
            {
                if (daftarAdmin[i].username == tempadminUsername && daftarAdmin[i].password == tempadminPassword)
                {
                    berhasil = true;
                    break;
                }
            }
            if (berhasil)
            {

                admin_aktif = true;
                cout << "Sign In Berhasil! Selamat datang, " << tempadminUsername << endl;
                system("pause");
            }
            else
            {
                cout << "Username atau password salah!\n";
                system("pause");
            }
        }
        else if (pilihanAdmin == 0)
        {
            return;
        }
    }
}
void menuadmin()
{
    int pilihan;
    cout << "==================================================\n";
    cout << "                  MENU ADMIN                      \n";
    cout << "==================================================\n";
    cout << "1. Lihat Data Visitor\n";
    cout << "2. Manajemen reservasi\n";
    cout << "3. Laporan\n";
    cout << "0. Keluar\n";
    cout << "==================================================\n";
    cout << "Pilih opsi (1-3): ";
    cin >> pilihan;
    cout << "--------------------------------------------------\n";
    system("cls");
    switch (pilihan)
    {
    case 1:
        cout << "[Kelola Pelanggan]\n";
        break;
    case 2:
        cout << "[Manajemen Reservasi]\n";
        break;
    case 3:
        cout << "[Laporan]\n";
        break;
    case 0:
        cout << "Keluar dari Menu Admin...\n";
        break;
    default:
        cout << "Pilihan tidak valid!\n";
    }
}

void menuVisitor()
{
    int pilihan;
    system("cls");
    cout << "==================================================\n";
    cout << "                 MENU VISITOR                     \n";
    cout << "==================================================\n";
    cout << "Selamat datang, " << username_aktif << "!\n";
    cout << "--------------------------------------------------\n";
    cout << "1. Buat Reservasi\n";
    cout << "2. Lihat Reservasi Saya\n";
    cout << "3. Batalkan Reservasi\n";
    cout << "0. Keluar\n";
    cout << "==================================================\n";
    cout << "Pilih opsi (0-3): ";
    cin >> pilihan;
    cout << "--------------------------------------------------\n";

    switch (pilihan)
    {
    case 1:
        cout << "[Buat Reservasi]\n";
        break;
    case 2:
        cout << "[Lihat Reservasi]\n";
        break;
    case 3:
        cout << "[Batalkan Reservasi]\n";
        break;
    case 0:
        cout << "Keluar dari Menu Visitor...\n";
        break;
    default:
        cout << "Pilihan tidak valid!\n";
    }
}

int main()
{
    while (true)
    {
        mainmenu();
        if (admin_aktif)
        {
            menuadmin();
        }
        else if (!username_aktif.empty())
        {
            menuVisitor();
        }
    }
    return 0;
}
