#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;

void buatReservasi();
bool tanggalValid(const string &tanggalInput);
void loadReservasi();
void loadVisitor();
void lihatReservasiSaya();
void batalkanReservasi();
void tampilkanSemuaVisitor();
void cariVisitor();

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

void clearScreen()
{
    cout << "\033[2J\033[H";
}

void waitEnter()
{
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
                    username_aktif = visit[jumlahvisitor].username;
                    fileVisitor.close();
                    jumlahvisitor++;
                    cout << "Registrasi Berhasil!\n";
                    waitEnter();
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
            admin_aktif = false;
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
    do
    {
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
            lihatReservasiSaya();
            break;
        case 3:
            batalkanReservasi();
            break;
        case 0:
            username_aktif = "";
            cout << "Keluar dari Menu Visitor...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);
}

int main()
{
    loadReservasi();
    loadVisitor();
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

bool tanggalValid(const string &tanggalInput)
{
    int hari, bulan, tahun;
    if (sscanf(tanggalInput.c_str(), "%d/%d/%d", &hari, &bulan, &tahun) != 3)
    {
        return false;
    }
    time_t sekarang = time(nullptr);
    tm *hariIni = localtime(&sekarang);
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
    reservasi reservasi_baru;
    reservasi_baru.idReservasi = jumlahreservasi + 1;
    reservasi_baru.usernameVisitor = username_aktif;
    cout << "==================================================\n";
    cout << "                BUAT RESERVASI                    \n";
    cout << "==================================================\n";
    cout << left
         << setw(5) << "No"
         << setw(15) << "Paket"
         << setw(15) << "Harga Paket"
         << endl;
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < 4; i++)
    {
        cout << left
             << setw(5) << i + 1
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
    reservasi_baru.namaPaket = DAFTAR_PAKET[pilihanPaket - 1];
    reservasi_baru.harga = HARGA_PAKET[pilihanPaket - 1];
    while (true)
    {
        cout << "Tanggal Reservasi (DD/MM/YYYY) : ";
        cin >> reservasi_baru.tanggal;
        if (tanggalValid(reservasi_baru.tanggal))
        {
            break;
        }
        cout << "Tanggal harus minimal H+1 dari hari ini!\n";
    }
    do
    {
        cout << "Durasi (2 - 8 jam) : ";
        cin >> reservasi_baru.durasi;
        if (reservasi_baru.durasi < 2 || reservasi_baru.durasi > 8)
        {
            cout << "Durasi harus antara 2 sampai 8 jam!\n";
        }
    } while (reservasi_baru.durasi < 2 || reservasi_baru.durasi > 8);
    if (reservasi_baru.durasi <= 2)
    {
        reservasi_baru.totalBiaya = reservasi_baru.harga;
    }
    else
    {
        reservasi_baru.totalBiaya = reservasi_baru.harga + ((reservasi_baru.durasi - 2) * biayaTambahan);
    }
    reservasi_baru.status = "Menunggu";
    reservasiList[jumlahreservasi] = reservasi_baru;
    jumlahreservasi++;
    ofstream fileReservasi("reservasi.txt", ios::app);
    if (fileReservasi.is_open())
    {
        fileReservasi << reservasi_baru.idReservasi << " | "
                      << reservasi_baru.usernameVisitor << " | "
                      << reservasi_baru.namaPaket << " | "
                      << reservasi_baru.tanggal << " | "
                      << reservasi_baru.durasi << " | "
                      << reservasi_baru.harga << " | "
                      << reservasi_baru.totalBiaya << " | "
                      << reservasi_baru.status << endl;
        fileReservasi.close();
    }
    else
    {
        cout << "Gagal menyimpan reservasi ke file!\n";
    }
    cout << "--------------------------------------------------\n";
    cout << "Reservasi berhasil dibuat!\n";
    cout << "--------------------------------------------------\n";
    cout << "ID Reservasi : " << reservasi_baru.idReservasi << endl;
    cout << "Paket        : " << reservasi_baru.namaPaket << endl;
    cout << "Tanggal      : " << reservasi_baru.tanggal << endl;
    cout << "Harga Paket  : Rp" << reservasi_baru.harga << endl;
    cout << "Durasi       : " << reservasi_baru.durasi << " jam\n";
    if (reservasi_baru.durasi > 2)
    {
        cout << "Tambahan Jam : "
             << (reservasi_baru.durasi - 2)
             << " x Rp" << biayaTambahan << endl;
    }
    cout << "Total Biaya  : Rp" << reservasi_baru.totalBiaya << endl;
    cout << "Status       : " << reservasi_baru.status << endl;
    cout << "--------------------------------------------------\n";
    waitEnter();
}
void loadVisitor()
{
    ifstream fileVisitor("visitor.txt");
    string baris;
    while (getline(fileVisitor, baris) && jumlahvisitor < maks_visitor)
    {
        visitor visit_load;
        size_t p1 = baris.find(" | ");
        size_t p2 = baris.find(" | ", p1 + 3);
        size_t p3 = baris.find(" | ", p2 + 3);
        size_t p4 = baris.find(" | ", p3 + 3);

        if (p1 == string::npos || p2 == string::npos ||
            p3 == string::npos || p4 == string::npos)
        {
            continue;
        }

        visit_load.username = baris.substr(0, p1);
        visit_load.password = baris.substr(p1 + 3, p2 - p1 - 3);
        visit_load.nama = baris.substr(p2 + 3, p3 - p2 - 3);
        visit_load.noTelp = baris.substr(p3 + 3, p4 - p3 - 3);
        visit_load.email = baris.substr(p4 + 3);

        visit[jumlahvisitor] = visit_load;
        jumlahvisitor++;
    }
    fileVisitor.close();
}
void loadReservasi()
{
    ifstream fileReservasi("reservasi.txt");
    string baris;
    while (getline(fileReservasi, baris) && jumlahreservasi < maks_reservasi)
    {
        reservasi reservasi_load;
        size_t p1 = baris.find(" | ");
        size_t p2 = baris.find(" | ", p1 + 3);
        size_t p3 = baris.find(" | ", p2 + 3);
        size_t p4 = baris.find(" | ", p3 + 3);
        size_t p5 = baris.find(" | ", p4 + 3);
        size_t p6 = baris.find(" | ", p5 + 3);
        size_t p7 = baris.find(" | ", p6 + 3);

        reservasi_load.idReservasi = stoi(baris.substr(0, p1));
        reservasi_load.usernameVisitor = baris.substr(p1 + 3, p2 - p1 - 3);
        reservasi_load.namaPaket = baris.substr(p2 + 3, p3 - p2 - 3);
        reservasi_load.tanggal = baris.substr(p3 + 3, p4 - p3 - 3);
        reservasi_load.durasi = stoi(baris.substr(p4 + 3, p5 - p4 - 3));
        reservasi_load.harga = stoi(baris.substr(p5 + 3, p6 - p5 - 3));
        reservasi_load.totalBiaya = stoi(baris.substr(p6 + 3, p7 - p6 - 3));
        reservasi_load.status = baris.substr(p7 + 3);

        reservasiList[jumlahreservasi] = reservasi_load;
        jumlahreservasi++;
    }
    fileReservasi.close();
}

void lihatReservasiSaya()
{
    clearScreen();
    cout << "==============================================================\n";
    cout << "                      RESERVASI SAYA                          \n";
    cout << "==============================================================\n";
    bool ditemukan = false;
    cout << left
         << setw(5)  << "ID"
         << setw(12) << "Paket"
         << setw(15) << "Tanggal"
         << setw(8)  << "Jam"
         << setw(12) << "Total"
         << setw(10) << "Status"
         << endl;
    cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < jumlahreservasi; i++)
    {
        if (reservasiList[i].usernameVisitor == username_aktif)
        {
            ditemukan = true;
            cout << left
                 << setw(5)  << reservasiList[i].idReservasi
                 << setw(12) << reservasiList[i].namaPaket
                 << setw(15) << reservasiList[i].tanggal
                 << setw(8)  << (to_string(reservasiList[i].durasi) + " jam")
                 << setw(12) << ("Rp" + to_string(reservasiList[i].totalBiaya))
                 << setw(10) << reservasiList[i].status
                 << endl;
                 cout << "--------------------------------------------------------------\n";
        }
    }
    if (!ditemukan)
    {
        cout << "Belum ada reservasi.\n";
        cout << "--------------------------------------------------------------\n";
    }
    waitEnter();
}
void batalkanReservasi() {
    clearScreen();
    cout << "==============================================================\n";
    cout << "                      BATALKAN RESERVASI                      \n";
    cout << "==============================================================\n";
    
    if (jumlahreservasi == 0) {
        cout << "Belum ada data reservasi di sistem.\n";
        waitEnter();
        return;
    }

    int idCari;
    cout << "Masukkan ID Reservasi yang ingin dibatalkan: ";
    cin >> idCari;

    bool ditemukan = false;
    for (int i = 0; i < jumlahreservasi; i++) {
        if (reservasiList[i].idReservasi == idCari && reservasiList[i].usernameVisitor == username_aktif) {
            ditemukan = true;
            
            if (reservasiList[i].status != "Menunggu") {
                cout << "Gagal! Reservasi tidak bisa dibatalkan karena statusnya sudah '" << reservasiList[i].status << "'.\n";
            } else {
                reservasiList[i].status = "Dibatalkan";
                
                ofstream fileReservasi("reservasi.txt", ios::trunc);
                for (int j = 0; j < jumlahreservasi; j++) {
                    fileReservasi << reservasiList[j].idReservasi << " | "
                                  << reservasiList[j].usernameVisitor << " | "
                                  << reservasiList[j].namaPaket << " | "
                                  << reservasiList[j].tanggal << " | "
                                  << reservasiList[j].durasi << " | "
                                  << reservasiList[j].harga << " | "
                                  << reservasiList[j].totalBiaya << " | "
                                  << reservasiList[j].status << endl;
                }
                fileReservasi.close();
                cout << "Sukses! Reservasi dengan ID " << idCari << " telah dibatalkan.\n";
            }
            break;
        }
    }

    if (!ditemukan) {
        cout << "ID Reservasi tidak ditemukan atau bukan milik akun Anda.\n";
    }
    waitEnter();
}

void tampilkanSemuaVisitor(){
    clearScreen();
    cout << "==============================================================\n";
    cout << "                      DAFTAR PELANGGAN                        \n";
    cout << "==============================================================\n";
    if (jumlahvisitor == 0){
        cout << "Belum ada pelanggan yang terdaftar\n";
    }else{
        cout << left << setw(15) << "Username"
             << setw(20) << "Nama Lengkap"
             << setw(15) << "No.Telepon"
             << setw(25) << "Email"
             << endl;
        cout << "--------------------------------------------------------------\n";
        for(int i = 0; i < jumlahvisitor; i++){
            cout << left
                 << setw(15) << visit[i].username
                 << setw(20) << visit[i].nama
                 << setw(15) << visit[i].noTelp
                 << setw(25) << visit[i].email
                 << endl;
        }
    }
    cout << "==============================================================\n";
    waitEnter();
}
void cariVisitor(){
    clearScreen();
    cout << "==============================================================\n";
    cout << "                         CARI PELANGGAN                       \n";
    cout << "==============================================================\n";
    if (jumlahvisitor == 0){
        cout << "Belum ada data pelanggan yang ditemukan\n";
        waitEnter();
        return;
    }
    string keyword;
    cout << "Masukkan Username atau Nama Pelanggan: ";
    getline(cin >> ws, keyword);
    cout << "--------------------------------------------------------------\n";
    bool ditemukan = false;
    for (int i = 0; i < jumlahvisitor; i++){
    if (visit[i].username == keyword || visit[i].nama == keyword){
        cout << "Data Pelanggan Ditemukan:\n\n";
            cout << "Username     : " << visit[i].username << endl;
            cout << "Nama Lengkap : " << visit[i].nama << endl;
            cout << "No. Telepon  : " << visit[i].noTelp << endl;
            cout << "Email        : " << visit[i].email << endl;
            cout << "--------------------------------------------------\n";
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "Pelanggan dengan kata kunci '" << keyword << "' tidak ditemukan.\n";
        cout << "--------------------------------------------------\n";
    }
    waitEnter();
}
