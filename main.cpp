#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;

void buatReservasi();
bool tanggalValid(const string& tanggalInput);

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
const int HARGA_PAKET[4] = {700000, 1500000, 750000, 400000};
const int biayaTambahan = 100000;
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
        size_t posisi = baris.find(" | ");
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

void clearScreen(){
    cout << "\033[2J\033[H";
}

void waitEnter(){
    cout << "Tekan ENTER untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void mainmenu()
{
    clearScreen();
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
        clearScreen();
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
            clearScreen();
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
            clearScreen();
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
                size_t posisi1 = baris.find(" | ");
                if (posisi1 != string::npos)
                {
                    size_t posisi2 = baris.find(" | ", posisi1 + 3);
                    string usernameDiFile = baris.substr(0, posisi1);
                    string passwordDiFile = baris.substr(posisi1 + 3, posisi2 - posisi1 - 3);
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
        clearScreen();
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
            clearScreen();
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
    do
    {
        clearScreen();
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
    } while (pilihan != 0);

}

void menuVisitor()
{
    int pilihan;
    do{
        clearScreen();
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
            buatReservasi();
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
    }while(pilihan != 0);
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

bool tanggalValid(const string& tanggalInput)
{
    int hari, bulan, tahun;
    if (sscanf(tanggalInput.c_str(), "%d/%d/%d", &hari, &bulan, &tahun) != 3)
    {
        return false;
    }
    time_t sekarang = time(nullptr);
    tm* hariIni = localtime(&sekarang);
    tm tanggalReservasi = {};
    tanggalReservasi.tm_mday = hari;
    tanggalReservasi.tm_mon = bulan - 1;
    tanggalReservasi.tm_year = tahun - 1900;
    tanggalReservasi.tm_hour = 0;
    tanggalReservasi.tm_min = 0;
    tanggalReservasi.tm_sec = 0;
    time_t waktuReservasi = mktime(&tanggalReservasi);
    tm besok = *hariIni;
    besok.tm_mday += 1;
    besok.tm_hour = 0;
    besok.tm_min = 0;
    besok.tm_sec = 0;
    time_t waktuBesok = mktime(&besok);
    return waktuReservasi >= waktuBesok;
}

void buatReservasi()
{
    clearScreen();
    if (jumlahreservasi >= maks_reservasi)
    {
        cout << "Kapasitas reservasi penuh!\n";
        return;
    }
    reservasi r;
    r.idReservasi = jumlahreservasi + 1;
    r.usernameVisitor = username_aktif;
    cout << "==================================================\n";
    cout << "                BUAT RESERVASI                    \n";
    cout << "==================================================\n";
    cout << left
        << setw(5)  << "No"
        << setw(15) << "Paket"
        << setw(15) << "Harga Paket"
        << endl;
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < 4; i++)
    {
        cout << left
            << setw(5)  << i + 1
            << setw(15) << DAFTAR_PAKET[i]
            << "Rp " << HARGA_PAKET[i]
            << endl;
    }
    cout << "--------------------------------------------------\n";
    cout << "* Harga sudah termasuk 2 jam sesi.\n";
    cout << "* Tambahan jam dikenakan Rp" << biayaTambahan << "/jam.\n";
    cout << "* Maksimal reservasi 8 jam.\n";
    cout << "--------------------------------------------------\n";
    int pilihanPaket;
    cout << "Pilih Paket : ";
    cin >> pilihanPaket;
    if (pilihanPaket < 1 || pilihanPaket > 4)
    {
        cout << "Pilihan paket tidak valid!\n";
        waitEnter();
        return;
    }
    r.namaPaket = DAFTAR_PAKET[pilihanPaket - 1];
    r.harga = HARGA_PAKET[pilihanPaket - 1];
    while (true)
    {
        cout << "Tanggal Reservasi (DD/MM/YYYY) : ";
        cin >> r.tanggal;
        if (tanggalValid(r.tanggal))
        {
            break;
        }
        cout << "Tanggal harus minimal H+1 dari hari ini!\n";
    }
    do
    {
        cout << "Durasi (2 - 8 jam) : ";
        cin >> r.durasi;
        if (r.durasi < 2 || r.durasi > 8)
        {
            cout << "Durasi harus antara 2 sampai 8 jam!\n";
        }
    } while (r.durasi < 2 || r.durasi > 8);
    if (r.durasi <= 2)
    {
        r.totalBiaya = r.harga;
    }
    else
    {
        r.totalBiaya = r.harga + ((r.durasi - 2) * biayaTambahan);
    }
    r.status = "Menunggu";
    reservasiList[jumlahreservasi] = r;
    jumlahreservasi++;
    cout << "--------------------------------------------------\n";
    cout << "Reservasi berhasil dibuat!\n";
    cout << "--------------------------------------------------\n";
    cout << "ID Reservasi : " << r.idReservasi << endl;
    cout << "Paket        : " << r.namaPaket << endl;
    cout << "Tanggal      : " << r.tanggal << endl;
    cout << "Harga Paket  : Rp" << r.harga << endl;
    cout << "Durasi       : " << r.durasi << " jam\n";
    if (r.durasi > 2)
    {
        cout << "Tambahan Jam : "
            << (r.durasi - 2)
            << " x Rp" << biayaTambahan << endl;
    }
    cout << "Total Biaya  : Rp" << r.totalBiaya << endl;
    cout << "Status       : " << r.status << endl;
    cout << "--------------------------------------------------\n";
    waitEnter();
}