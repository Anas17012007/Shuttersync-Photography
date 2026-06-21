#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string GRAY = "\033[90m";
void buatReservasi();
bool tanggalValid(const string &tanggalInput);
void loadReservasi();
void loadVisitor();
void lihatReservasiSaya();
void batalkanReservasi();
void tampilkanSemuaVisitor();
void cariVisitor();
void tambahVisitor();
void kelolapelanggan();
void laporanJumlahReservasi();
void laporanTotalPendapatan();
void menuLaporan();
void tampilSemuaReservasi();
void konfirmasiReservasi();
void batalkanReservasiAdmin();
void manajemenReservasi();

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
visitor *ptr_visitor_aktif = nullptr;
admin daftarAdmin[6] = {
    {"Solose", "Solose17012007"},
    {"Cayla", "Cayla123"},
    {"Dicky", "Dicky123"},
    {"Tiara", "Tiara123"},
    {"Putri", "Putri123"},
    {"Jihan", "Jihan123"}};
string Lower(string nama)
{
    for (size_t i = 0; i < nama.length(); i++)
    {
        if (nama[i] >= 'A' && nama[i] <= 'Z')
        {
            nama[i] = static_cast<char>(nama[i] + 32);
        }
    }
    return nama;
}

bool validasiAngka(int &angka)
{
    cin >> angka;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    return true;
}

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
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.clear();
    cin.get();
}

void mainmenu()
{
    int pilihan;
    while (true)
    {
        clearScreen();
        cout << CYAN << "+=============================================================================================+\n"
             << RESET;
        cout << "\n";
        cout << CYAN << " ____  _               _   _                                      _____      _\n";
        cout << MAGENTA << "/ ___|| |__  _   _ ___| |_| |_ ___ _ __ ___ _   _ _ __   ___      |  ___|___ | |_ ___\n";
        cout << BLUE << "\\___ \\| '_ \\| | | / __| __| __/ _ \\ '__/ __| | | | '_ \\ / __|     | |_  / _ \\| __/ _ \\\n";
        cout << CYAN << " ___) | | | | |_| \\__ \\ |_| ||  __/ |  \\__ \\ |_| | | | | (__      |  _|| (_) | || (_) |\n";
        cout << MAGENTA << "|____/|_| |_|\\__,_|___/\\__|\\__\\___|_|  |___/\\__, |_| |_|\\___|     |_|   \\___/ \\__\\___/\n";
        cout << BLUE << "                                              |___/\n";
        cout << RESET;
        cout << "\n";
        cout << CYAN << "+=============================================================================================+\n"
             << RESET;
        cout << YELLOW << "[1] " << RESET << "Admin\n";
        cout << YELLOW << "[2] " << RESET << "Visitor\n";
        cout << RED << "[0] " << RESET << "Keluar\n";
        cout << CYAN << "==================================================\n"
             << RESET;
        cout << "Pilih opsi (0-2): ";
        if (!validasiAngka(pilihan))
        {
            cout << "--------------------------------------------------\n";
            cout << RED << "[!]" << RESET << "Input harus berupa angka!";
            waitEnter();
            continue;
        }
        if (pilihan < 0 || pilihan > 2)
        {
            cout << "--------------------------------------------------\n";
            cout << RED << "[!]" << RESET << "Pilihan tidak valid!";
            cin.ignore(1000, '\n');
            waitEnter();
            continue;
        }
        break;
    }
    if (pilihan == 2)
    {
        int pilihanVisitor;
        while (true)
        {
            clearScreen();
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << CYAN << "|" << RESET << YELLOW << BOLD << "              MENU VISITOR              " << RESET << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << CYAN << "|" << RESET << "  " << YELLOW << "[1]" << RESET << " Sign In (Masuk)                 " << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "|" << RESET << "  " << YELLOW << "[2]" << RESET << " Sign Up (Daftar Akun Baru)      " << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "|" << RESET << "  " << RED << "[0]" << RESET << " Kembali ke Menu Utama           " << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << "Pilih opsi (0-2): ";
            if (!validasiAngka(pilihanVisitor))
            {
                cout << "--------------------------------------------------\n";
                cout << RED << "[!]" << RESET << "Input harus berupa angka!";
                waitEnter();
                continue;
            }
            if (pilihanVisitor < 0 || pilihanVisitor > 2)
            {
                cout << "--------------------------------------------------\n";
                cout << RED << "[!]" << RESET << "Pilihan tidak valid!";
                cin.ignore(1000, '\n');
                waitEnter();
                continue;
            }
            break;
        }
        if (pilihanVisitor == 2)
        {
            clearScreen();
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << CYAN << "|" << RESET << YELLOW << BOLD << "           REGISTRASI VISITOR           " << RESET << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
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
                cout << RED << "[!]" << RESET << "Semua field tidak boleh kosong!\n";
            }
            else if (cekUsernameDuplikat(visit[jumlahvisitor].username))
            {
                cout << RED << "[!]" << RESET << "Username sudah digunakan!\n";
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
                    ptr_visitor_aktif = &visit[jumlahvisitor];
                    fileVisitor.close();
                    jumlahvisitor++;
                    cout << "Registrasi Berhasil!\n";
                    waitEnter();
                }
                else
                {
                    cout << RED << "[!]" << RESET << "Gagal membuka file!\n";
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
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << CYAN << "|" << RESET << YELLOW << BOLD << "             SIGN IN VISITOR            " << RESET << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
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

                for (int i = 0; i < jumlahvisitor; i++)
                {
                    if (visit[i].username == username_aktif)
                    {
                        ptr_visitor_aktif = &visit[i];
                        break;
                    }
                }

                if (ptr_visitor_aktif != nullptr)
                {
                    cout << "Sign In Berhasil! Selamat Datang, " << ptr_visitor_aktif->nama << endl;
                }
                else
                {
                    cout << "Sign In Berhasil! Selamat datang, " << username_aktif << endl;
                }
                waitEnter();
            }
            else
            {
                cout << RED << "[!]" << RESET << "Username atau password salah!\n";
                waitEnter();
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

        while (true)
        {
            clearScreen();

            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << CYAN << "|" << RESET << YELLOW << BOLD << "               MENU ADMIN               " << RESET << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << CYAN << "|" << RESET << "  " << YELLOW << "[1]" << RESET << " Sign In (Masuk)                 " << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "|" << RESET << "  " << RED << "[0]" << RESET << " Kembali                         " << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << "Pilih opsi (0-1): ";
            if (!validasiAngka(pilihanAdmin))
            {
                cout << "--------------------------------------------------\n";
                cout << RED << "[!]" << RESET << "Input harus berupa angka!";
                waitEnter();
                continue;
            }

            if (pilihanAdmin < 0 || pilihanAdmin > 1)
            {
                cout << "--------------------------------------------------\n";
                cout << RED << "[!]" << RESET << "Pilihan tidak valid!";
                cin.ignore(1000, '\n');
                waitEnter();
                continue;
            }

            break;
        }
        if (pilihanAdmin == 1)
        {
            clearScreen();
            string tempadminUsername, tempadminPassword;
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << CYAN << "|" << RESET << YELLOW << BOLD << "              SIGN IN ADMIN             " << RESET << CYAN << "|\n"
                 << RESET;
            cout << CYAN << "+----------------------------------------+\n"
                 << RESET;
            cout << "Masukkan Username : ";
            getline(cin >> ws, tempadminUsername);
            cout << "Masukkan Password : ";
            getline(cin >> ws, tempadminPassword);
            cout << "--------------------------------------------------\n";
            bool berhasil = false;
            admin *ptrAdmin = daftarAdmin;
            for (int i = 0; i < 6; i++)
            {
                if ((ptrAdmin + i)->username == tempadminUsername && (ptrAdmin + i)->password == tempadminPassword)
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
                cout << RED << "[!]" << RESET << "Username atau password salah!\n";
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
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << CYAN << "|" << RESET << YELLOW << BOLD << "               MENU ADMIN               " << RESET << CYAN << "|\n"
             << RESET;
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[1]" << RESET << " Lihat Data Visitor              " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[2]" << RESET << " Manajemen Reservasi             " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[3]" << RESET << " Laporan                         " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << RED << "[0]" << RESET << " Keluar                          " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << "Pilih opsi (0-3): ";
        if (!validasiAngka(pilihan))
        {
            pilihan = -1;
            cout << "--------------------------------------------------\n";
            cout << RED << "[!] " << RESET << "Input harus berupa angka!";
            waitEnter();
            continue;
        }
        if (pilihan < 0 || pilihan > 3)
        {
            cout << "--------------------------------------------------\n";
            cout << RED << "[!] " << RESET << "Pilihan tidak valid!";
            cin.ignore(1000, '\n');
            waitEnter();
            continue;
        }
        cout << "--------------------------------------------------\n";
        switch (pilihan)
        {
        case 1:
            kelolapelanggan();
            break;
        case 2:
            manajemenReservasi();
            break;
        case 3:
            menuLaporan();
            break;
        case 0:
            admin_aktif = false;
            cout << "Keluar dari Menu Admin...\n";
            break;
        }
    } while (pilihan != 0);
}

void menuVisitor()
{
    int pilihan;
    do
    {
        clearScreen();
        cout << CYAN;
        cout << "+----------------------------------------+\n";
        cout << "|" << YELLOW << BOLD << "         MENU VISITOR                   " << RESET << CYAN << "|\n";
        cout << "+----------------------------------------+\n";
        cout << RESET;
        if (ptr_visitor_aktif != nullptr)
        {
            cout << CYAN << "|" << RESET << "Selamat datang, " << GREEN << ptr_visitor_aktif->nama << "(" << username_aktif << ")!\n";
        }
        else
        {
            cout << CYAN << "|" << RESET << "Selamat datang, " << username_aktif << "!\n"
                 << CYAN << "|" << RESET;
        }
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << CYAN << RESET << "|  " << YELLOW << "[1]" << RESET << " Buat Reservasi                    " << CYAN << "|\n"
             << RESET;
        cout << CYAN << RESET << "|  " << YELLOW << "[2]" << RESET << " Lihat Reservasi Saya              " << CYAN << "|\n"
             << RESET;
        cout << CYAN << RESET << "|  " << YELLOW << "[3]" << RESET << " Batalkan Reservasi                " << CYAN << "|\n"
             << RESET;
        cout << CYAN << RESET << "|  " << RED << "[0]" << RESET << " Keluar                            " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << "Pilih opsi (0-3): ";
        if (!validasiAngka(pilihan))
        {
            pilihan = -1;
            cout << "--------------------------------------------------\n";
            cout << RED << "[!] " << RESET << "Input harus berupa angka!";
            waitEnter();
            continue;
        }
        if (pilihan < 0 || pilihan > 3)
        {
            cout << "--------------------------------------------------\n";
            cout << RED << "[!] " << RESET << "Pilihan tidak valid!";
            cin.ignore(1000, '\n');
            waitEnter();
            continue;
        }
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
            ptr_visitor_aktif = nullptr;
            cout << "Keluar dari Menu Visitor...\n";
            break;
        default:
            cout << RED << "[!] " << RESET << "Pilihan tidak valid!";
            waitEnter();
            break;
        }
    } while (pilihan != 0);
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

void tampilDetailReservasi(const reservasi *res)
{
    cout << "ID Reservasi : " << res->idReservasi << endl;
    cout << "Paket        : " << res->namaPaket << endl;
    cout << "Tanggal      : " << res->tanggal << endl;
    cout << "Harga Paket  : Rp" << res->harga << endl;
    cout << "Durasi       : " << res->durasi << " jam\n";
    if (res->durasi > 2)
    {
        cout << "Tambahan Jam : "
             << (res->durasi - 2)
             << " x Rp" << biayaTambahan << endl;
    }
    cout << "Total Biaya  : Rp" << res->totalBiaya << endl;
    cout << "Status       : " << res->status << endl;
    cout << "--------------------------------------------------\n";
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
    int pilihanPaket;
    while (true)
    {
        clearScreen();
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << CYAN << "|" << RESET << YELLOW << BOLD << "             BUAT RESERVASI             " << RESET << CYAN << "|\n"
             << RESET;
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << left
             << setw(5) << "No"
             << setw(15) << "Paket"
             << setw(15) << "Harga Paket"
             << endl;
        cout << CYAN <<"--------------------------------------------------\n"<< RESET;
        for (int i = 0; i < 4; i++)
        {
            cout << left
                 << setw(5) << i + 1
                 << setw(15) << DAFTAR_PAKET[i]
                 << "Rp " << HARGA_PAKET[i]
                 << endl;
        }
        cout << CYAN <<"--------------------------------------------------\n"<< RESET;
        cout << "* Harga sudah termasuk 2 jam sesi.\n";
        cout << "* Tambahan jam dikenakan Rp" << biayaTambahan << "/jam.\n";
        cout << "* Maksimal reservasi 8 jam.\n";
        cout << CYAN <<"--------------------------------------------------\n"<< RESET;
        cout << "Pilih Paket : ";
        if (!validasiAngka(pilihanPaket))
        {
            cout << RED << "[!] " << RESET << "Input harus berupa angka!";
            waitEnter();
            return;
        }
        if (pilihanPaket < 1 || pilihanPaket > 4)
        {
            cout << RED << "[!] " << RESET << "Pilihan paket tidak valid!";
            cin.ignore(1000, '\n');
            waitEnter();
            return;
        }
        break;
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
        cout << RED << "[!] " << RESET << "Tanggal harus minimal H+1 dari hari ini!\n";
    }
    do
    {
        cout << "Durasi (2 - 8 jam) : ";
        cin >> reservasi_baru.durasi;
        if (reservasi_baru.durasi < 2 || reservasi_baru.durasi > 8)
        {
            cout << RED << "[!] " << RESET << "Durasi harus antara 2 sampai 8 jam!\n";
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
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    cout << CYAN << "|" << RESET << GREEN << BOLD << "           RESERVASI BERHASIL            " << RESET << CYAN << "|\n"
         << RESET;
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    tampilDetailReservasi(&reservasi_baru);
    cin.ignore(1000, '\n');
    waitEnter();
    //    cout << "ID Reservasi : " << reservasi_baru.idReservasi << endl;
    //    cout << "Paket        : " << reservasi_baru.namaPaket << endl;
    //    cout << "Tanggal      : " << reservasi_baru.tanggal << endl;
    //    cout << "Harga Paket  : Rp" << reservasi_baru.harga << endl;
    //    cout << "Durasi       : " << reservasi_baru.durasi << " jam\n";
    //    if (reservasi_baru.durasi > 2)
    //    {
    //        cout << "Tambahan Jam : "
    //             << (reservasi_baru.durasi - 2)
    //             << " x Rp" << biayaTambahan << endl;
    //    }
    //    cout << "Total Biaya  : Rp" << reservasi_baru.totalBiaya << endl;
    //    cout << "Status       : " << reservasi_baru.status << endl;
    //    cout << "--------------------------------------------------\n";
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
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    cout << CYAN << "|" << RESET << YELLOW << BOLD << "             RESERVASI SAYA             " << RESET << CYAN << "|\n"
         << RESET;
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    bool ditemukan = false;
    cout << left
         << setw(5) << "ID"
         << setw(12) << "Paket"
         << setw(15) << "Tanggal"
         << setw(8) << "Jam"
         << setw(12) << "Total"
         << setw(10) << "Status"
         << endl;
    cout <<CYAN<< "--------------------------------------------------------------\n" << RESET;
    for (int i = 0; i < jumlahreservasi; i++)
    {
        if (reservasiList[i].usernameVisitor == username_aktif)
        {
            ditemukan = true;
            cout << left
                 << setw(5) << reservasiList[i].idReservasi
                 << setw(12) << reservasiList[i].namaPaket
                 << setw(15) << reservasiList[i].tanggal
                 << setw(8) << (to_string(reservasiList[i].durasi) + " jam")
                 << setw(12) << ("Rp" + to_string(reservasiList[i].totalBiaya))
                 << setw(10) << reservasiList[i].status
                 << endl;
            cout <<CYAN<< "--------------------------------------------------------------\n" << RESET;
        }
    }
    if (!ditemukan)
    {
        cout << "Belum ada reservasi.\n";
        cout <<CYAN<< "--------------------------------------------------------------\n" << RESET;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    waitEnter();
}
void batalkanReservasi()
{
    clearScreen();
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    cout << CYAN << "|" << RESET << RED << BOLD << "           BATALKAN RESERVASI           " << RESET << CYAN << "|\n"
         << RESET;
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;

    int idTarget;
    bool ditemukan = false;
    int index = -1;
    cout << "Daftar reservasi Anda yang bisa dibatalkan:\n";
    for (int i = 0; i < jumlahreservasi; i++) {
        if (reservasiList[i].usernameVisitor == username_aktif && reservasiList[i].status == "Menunggu") {
            cout << "ID: " << reservasiList[i].idReservasi << " | Paket: " << reservasiList[i].namaPaket 
                 << " | Tanggal: " << reservasiList[i].tanggal << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << RED << "[!] Tidak ada reservasi dengan status 'Menunggu' untuk dibatalkan.\n" << RESET;
        system("pause");
        waitEnter();
        return;
    }

    cout << "\nMasukkan ID Reservasi yang ingin dibatalkan: ";
    cin >> idTarget;

    for (int i = 0; i < jumlahreservasi; i++) {
        if (reservasiList[i].idReservasi == idTarget && reservasiList[i].usernameVisitor == username_aktif && reservasiList[i].status == "Menunggu") {
            reservasiList[i].status = "Dibatalkan";
            index = i;
            break;
        }
    }

    if (index != -1) {
        ofstream fileReservasi("reservasi.txt", ios::trunc);
        for (int i = 0; i < jumlahreservasi; i++) {
            fileReservasi << reservasiList[i].idReservasi << " | "
                          << reservasiList[i].usernameVisitor << " | "
                          << reservasiList[i].namaPaket << " | "
                          << reservasiList[i].tanggal << " | "
                          << reservasiList[i].durasi << " | "
                          << reservasiList[i].harga << " | "
                          << reservasiList[i].totalBiaya << " | "
                          << reservasiList[i].status << endl;
        }
        fileReservasi.close();
        cout << GREEN << "[+] Reservasi berhasil dibatalkan!\n" << RESET;
        system("pause");
    } else {
        cout << RED << "[!] ID tidak ditemukan atau reservasi tidak dapat dibatalkan.\n" << RESET;
        system("pause");
    }
    waitEnter();
}
void tampilkanSemuaVisitor()
{
    clearScreen();
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    cout << CYAN << "|" << RESET << BLUE << BOLD << "            DAFTAR PELANGGAN            " << RESET << CYAN << "|\n"
         << RESET;
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    if (jumlahvisitor == 0)
    {
        cout << "Belum ada pelanggan yang terdaftar\n";
    }
    else
    {
        cout << left << setw(15) << "Username"
             << setw(20) << "Nama Lengkap"
             << setw(15) << "No.Telepon"
             << setw(25) << "Email"
             << endl;
        cout << CYAN << "--------------------------------------------------------------\n"
             << RESET;
        for (int i = 0; i < jumlahvisitor; i++)
        {
            cout << left
                 << setw(15) << visit[i].username
                 << setw(20) << visit[i].nama
                 << setw(15) << visit[i].noTelp
                 << setw(25) << visit[i].email
                 << endl;
        }
    }
    cout << CYAN << "==============================================================\n"
         << RESET;
    cin.clear();
    cin.ignore(1000, '\n');
    waitEnter();
}
void cariVisitor()
{
    clearScreen();
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    cout << CYAN << "|" << RESET << YELLOW << BOLD << "            CARI PELANGGAN              " << RESET << CYAN << "|\n"
         << RESET;
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    if (jumlahvisitor == 0)
    {
        cout << "Belum ada data pelanggan yang ditemukan\n";
        waitEnter();
        return;
    }
    string keyword;
    cout << "Masukkan Username atau Nama Pelanggan: ";
    getline(cin >> ws, keyword);
    cout << CYAN << "--------------------------------------------------------------\n"
         << RESET;
    bool ditemukan = false;
    for (int i = 0; i < jumlahvisitor; i++)
    {
        if (Lower(visit[i].username) == Lower(keyword) || Lower(visit[i].nama) == Lower(keyword))
        {
            cout << "Data Pelanggan Ditemukan:\n\n";
            cout << "Username     : " << visit[i].username << endl;
            cout << "Nama Lengkap : " << visit[i].nama << endl;
            cout << "No. Telepon  : " << visit[i].noTelp << endl;
            cout << "Email        : " << visit[i].email << endl;
            cout << CYAN << "--------------------------------------------------\n"
                 << RESET;
            ditemukan = true;
        }
    }
    if (!ditemukan)
    {
        cout << "Pelanggan dengan kata kunci '" << keyword << "' tidak ditemukan.\n";
        cout << CYAN << "--------------------------------------------------\n"
             << RESET;
    }
    waitEnter();
}
void tambahVisitor()
{
    clearScreen();
    cout << CYAN << "==============================================================\n"
         << RESET;
    cout << CYAN << "                      TAMBAH PELANGGAN                       \n"
         << RESET;
    cout << CYAN << "==============================================================\n"
         << RESET;
    if (jumlahvisitor >= maks_visitor)
    {
        cout << "Kapasitas pelanggan penuh! Tidak bisa menambah pelanggan baru.\n";
        waitEnter();
        return;
    }
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
            cout << "Registrasi Pelanggan Baru Berhasil!\n";
            waitEnter();
        }
        else
        {
            cout << "Gagal membuka file!\n";
        }
    }
}
void kelolapelanggan()
{
    int pilihan;
    do
    {
        clearScreen();
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << CYAN << "|" << RESET << YELLOW << BOLD << "           KELOLA PELANGGAN             " << RESET << CYAN << "|\n"
             << RESET;
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[1]" << RESET << " Tampilkan Semua Pelanggan       " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[2]" << RESET << " Cari Pelanggan                  " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[3]" << RESET << " Tambah Pelanggan                " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << RED << "[0]" << RESET << " Kembali                         " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << "Pilih opsi (0-3): ";
        if (!validasiAngka(pilihan))
        {
            pilihan = -1;
            cout << CYAN << "--------------------------------------------------\n"
                 << RESET;
            cout << "Input harus berupa angka!";
            waitEnter();
            continue;
        }
        if (pilihan < 0 || pilihan > 3)
        {
            cout << CYAN << "--------------------------------------------------\n"
                 << RESET;
            cout << "Pilihan tidak valid!";
            cin.ignore(1000, '\n');
            waitEnter();
            continue;
        }
        cout << CYAN << "--------------------------------------------------------------\n"
             << RESET;
        switch (pilihan)
        {
        case 1:
            tampilkanSemuaVisitor();
            break;
        case 2:
            cariVisitor();
            break;
        case 3:
            tambahVisitor();
            break;
        case 0:
            return;
        default:
            cout << "Pilihan tidak valid!\n";
            waitEnter();
        }
    } while (pilihan != 0);
}

void laporanJumlahReservasi()
{
    clearScreen();
    cout << CYAN << "=======================================================================\n"
         << RESET;
    cout << CYAN << "                         LAPORAN JUMLAH RESERVASI                      \n"
         << RESET;
    cout << CYAN << "=======================================================================\n"
         << RESET;

    if (jumlahreservasi == 0)
    {
        cout << "Belum ada data reservasi.\n";
        cout << "=======================================================================\n";
        waitEnter();
        return;
    }

    int totalMenunggu = 0;
    int totalDikonfirmasi = 0;
    int totalDibatalkan = 0;
    int totalLainnya = 0;

    for (int i = 0; i < jumlahreservasi; i++)
    {
        if (reservasiList[i].status == "Menunggu")
            totalMenunggu++;
        else if (reservasiList[i].status == "Dikonfirmasi")
            totalDikonfirmasi++;
        else if (reservasiList[i].status == "Dibatalkan")
            totalDibatalkan++;
        else
            totalLainnya++;
    }

    cout << left
         << setw(5) << "No"
         << setw(15) << "Paket"
         << setw(15) << "Tanggal"
         << setw(12) << "Visitor"
         << setw(15) << "Total Biaya"
         << setw(12) << "Status"
         << endl;
    cout << "-----------------------------------------------------------------------\n";

    for (int i = 0; i < jumlahreservasi; i++)
    {
        cout << left
             << setw(5) << reservasiList[i].idReservasi
             << setw(15) << reservasiList[i].namaPaket
             << setw(15) << reservasiList[i].tanggal
             << setw(12) << reservasiList[i].usernameVisitor
             << setw(15) << ("Rp" + to_string(reservasiList[i].totalBiaya))
             << setw(12) << reservasiList[i].status
             << endl;
    }

    cout << "=======================================================================\n";
    cin.clear();
    cin.ignore(1000, '\n');
    waitEnter();
}

void laporanTotalPendapatan()
{
    clearScreen();
    cout << CYAN << "=======================================================================\n"
         << RESET;
    cout << CYAN << "                       LAPORAN TOTAL PENDAPATAN                        \n"
         << RESET;
    cout << CYAN << "=======================================================================\n"
         << RESET;

    if (jumlahreservasi == 0)
    {
        cout << "Belum ada data reservasi.\n";
        cout << CYAN << "================================================================\n"
             << RESET;
        waitEnter();
        return;
    }

    int pendapatanTotal = 0;
    int pendapatanKonfirmasi = 0;
    int pendapatanMenunggu = 0;

    int pendapatanPerPaket[4] = {0, 0, 0, 0};
    int jumlahPerPaket[4] = {0, 0, 0, 0};

    for (int i = 0; i < jumlahreservasi; i++)
    {
        if (reservasiList[i].status != "Dibatalkan")
        {
            pendapatanTotal += reservasiList[i].totalBiaya;

            if (reservasiList[i].status == "Dikonfirmasi")
                pendapatanKonfirmasi += reservasiList[i].totalBiaya;
            else if (reservasiList[i].status == "Menunggu")
                pendapatanMenunggu += reservasiList[i].totalBiaya;

            for (int p = 0; p < 4; p++)
            {
                if (reservasiList[i].namaPaket == DAFTAR_PAKET[p])
                {
                    pendapatanPerPaket[p] += reservasiList[i].totalBiaya;
                    jumlahPerPaket[p]++;
                    break;
                }
            }
        }
    }

    cout << "PENDAPATAN PER PAKET (tidak termasuk yang dibatalkan):\n";
    cout << "--------------------------------------------------------------\n";
    cout << left
         << setw(15) << "Paket"
         << setw(15) << "Jml Reservasi"
         << setw(18) << "Total Pendapatan"
         << endl;
    cout << "--------------------------------------------------------------\n";

    for (int p = 0; p < 4; p++)
    {
        cout << left
             << setw(15) << DAFTAR_PAKET[p]
             << setw(15) << jumlahPerPaket[p]
             << "Rp" << pendapatanPerPaket[p]
             << endl;
    }

    cout << CYAN << "==============================================================\n"
         << RESET;
    cout << CYAN << "  TOTAL PENDAPATAN         : Rp" << pendapatanTotal << "\n"
         << RESET;
    cout << CYAN << "  (tidak termasuk reservasi yang dibatalkan)\n"
         << RESET;
    cout << CYAN << "==============================================================\n"
         << RESET;
    cin.ignore(1000, '\n');
    waitEnter();
}

void menuLaporan()
{
    int pilihan;
    do
    {
        clearScreen();
        cout << CYAN << "==================================================\n"
             << RESET;
        cout << CYAN << "                   MENU LAPORAN                   \n"
             << RESET;
        cout << CYAN << "==================================================\n"
             << RESET;
        cout << YELLOW<< "[1]" << RESET << " Laporan Jumlah Reservasi\n";
        cout << YELLOW<< "[2]" << RESET << " Laporan Total Pendapatan\n";
        cout << RED<< "[0]" << RESET << " Kembali\n";
        cout << "==================================================\n";
        cout << "Pilih opsi (0-2): ";
        cin >> pilihan;
        cout << CYAN << "--------------------------------------------------\n"
             << RESET;
        system("cls");
        switch (pilihan)
        {
        case 1:
            laporanJumlahReservasi();
            break;
        case 2:
            laporanTotalPendapatan();
            break;
        case 0:
            cout << "Kembali ke Menu Admin...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            waitEnter();
        }
    } while (pilihan != 0);
}

void manajemenReservasi()
{
    int pilihan;
    do
    {
        clearScreen();
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << CYAN << "|" << RESET << YELLOW << BOLD << "          MANAJEMEN RESERVASI           " << RESET << CYAN << "|\n"
             << RESET;
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[1]" << RESET << " Tampilkan Semua Reservasi       " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[2]" << RESET << " Konfirmasi Reservasi            " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << YELLOW << "[3]" << RESET << " Batalkan Reservasi              " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "|" << RESET << "  " << RED << "[0]" << RESET << " Kembali                         " << CYAN << "|\n"
             << RESET;
        cout << CYAN << "+----------------------------------------+\n"
             << RESET;
        cout << "Pilih opsi (0-3): ";
        if (!validasiAngka(pilihan))
        {
            pilihan = -1;
            cout << "--------------------------------------------------\n";
            cout << "Input harus berupa angka!";
            waitEnter();
            continue;
        }
        if (pilihan < 0 || pilihan > 3)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "--------------------------------------------------\n";
            cout << "Pilihan tidak valid!";
            waitEnter();
            continue;
        }
        cout << "--------------------------------------------------\n";
        switch (pilihan)
        {
        case 1:
            tampilSemuaReservasi();
            break;
        case 2:
            konfirmasiReservasi();
            break;
        case 3:
            batalkanReservasiAdmin();
            break;
        case 0:
            cout << "Kembali ke Menu Admin...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            waitEnter();
        }
    } while (pilihan != 0);
}
void tampilSemuaReservasi()
{
    clearScreen();
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    cout << CYAN << "|" << RESET << YELLOW << BOLD << "             SEMUA RESERVASI            " << RESET << CYAN << "|\n"
         << RESET;
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    if (jumlahreservasi == 0)
    {
        cout << "Belum ada data reservasi.\n";
        cout << "=======================================================================\n";
        waitEnter();
        return;
    }

    cout << left
         << setw(5) << "ID"
         << setw(12) << "Visitor"
         << setw(12) << "Paket"
         << setw(15) << "Tanggal"
         << setw(8) << "Durasi"
         << setw(14) << "Total"
         << setw(12) << "Status"
         << endl;
    cout << "-----------------------------------------------------------------------\n";

    for (int i = 0; i < jumlahreservasi; i++)
    {
        cout << left
             << setw(5) << reservasiList[i].idReservasi
             << setw(12) << reservasiList[i].usernameVisitor
             << setw(12) << reservasiList[i].namaPaket
             << setw(15) << reservasiList[i].tanggal
             << setw(8) << (to_string(reservasiList[i].durasi) + " jam")
             << setw(14) << ("Rp" + to_string(reservasiList[i].totalBiaya))
             << setw(12) << reservasiList[i].status
             << endl;
    }
    cout << "=======================================================================\n";
    cin.ignore(1000, '\n');
    waitEnter();
}
void konfirmasiReservasi()
{
    clearScreen();
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    cout << CYAN << "|" << RESET << YELLOW << BOLD << "              KONFIRMASI RESERVASI            " << RESET << CYAN << "|\n"
         << RESET;
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;

    if (jumlahreservasi == 0)
    {
        cout << "Belum ada data reservasi.\n";
        waitEnter();
        return;
    }
    cout << left
         << setw(5) << "ID"
         << setw(12) << "Visitor"
         << setw(12) << "Paket"
         << setw(15) << "Tanggal"
         << setw(12) << "Status"
         << endl;
    cout << "-----------------------------------------------------------------------\n";

    bool Menunggu = false;
    for (int i = 0; i < jumlahreservasi; i++)
    {
        if (reservasiList[i].status == "Menunggu")
        {
            Menunggu = true;
            cout << left
                 << setw(5) << reservasiList[i].idReservasi
                 << setw(12) << reservasiList[i].usernameVisitor
                 << setw(12) << reservasiList[i].namaPaket
                 << setw(15) << reservasiList[i].tanggal
                 << setw(12) << reservasiList[i].status
                 << endl;
        }
    }

    if (!Menunggu)
    {
        cout << "Tidak ada reservasi yang menunggu konfirmasi.\n";
        waitEnter();
        return;
    }

    cout << "-----------------------------------------------------------------------\n";
    int idCari;
    cout << "Masukkan ID Reservasi yang ingin dikonfirmasi: ";
    cin >> idCari;

    bool ditemukan = false;
    for (int i = 0; i < jumlahreservasi; i++)
    {
        if (reservasiList[i].idReservasi == idCari)
        {
            ditemukan = true;
            if (reservasiList[i].status != "Menunggu")
            {
                cout << "Gagal! Status reservasi sudah '" << reservasiList[i].status << "'.\n";
            }
            else
            {
                char konfirmasi;
                cout << "Yakin konfirmasi reservasi ID " << idCari << "? (Y/N): ";
                cin >> konfirmasi;

                if (konfirmasi == 'y' || konfirmasi == 'Y')
                {
                    reservasiList[i].status = "Dikonfirmasi";

                    ofstream fileReservasi("reservasi.txt", ios::trunc);
                    for (int j = 0; j < jumlahreservasi; j++)
                    {
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
                    cout << "Reservasi ID " << idCari << " berhasil dikonfirmasi!\n";
                }
                else if (konfirmasi == 'n' || konfirmasi == 'N')
                {
                    cout << "Konfirmasi dibatalkan.\n";
                }
                else
                {
                    cout << "Input tidak valid, konfirmasi dibatalkan.\n";
                }
            }
            break;
        }
    }

    if (!ditemukan)
        cout << "ID Reservasi tidak ditemukan.\n";

    waitEnter();
}
void batalkanReservasiAdmin()
{
    clearScreen();
    cout << CYAN << "+----------------------------------------+\n"
         << RESET;
    cout << CYAN << "|" << RESET << YELLOW << BOLD << "            BATALKAN RESERVASI ADMIN          " << RESET << CYAN << "|\n"
         << RESET;
    cout << CYAN << "+" << RESET << YELLOW << BOLD << "----------------------------------------" << RESET << CYAN << "+\n"
         << RESET;

    if (jumlahreservasi == 0)
    {
        cout << "Belum ada data reservasi.\n";
        waitEnter();
        return;
    }

    cout << left
         << setw(5) << "ID"
         << setw(12) << "Visitor"
         << setw(12) << "Paket"
         << setw(15) << "Tanggal"
         << setw(12) << "Status"
         << endl;
    cout << "-----------------------------------------------------------------------\n";

    for (int i = 0; i < jumlahreservasi; i++)
    {
        cout << left
             << setw(5) << reservasiList[i].idReservasi
             << setw(12) << reservasiList[i].usernameVisitor
             << setw(12) << reservasiList[i].namaPaket
             << setw(15) << reservasiList[i].tanggal
             << setw(12) << reservasiList[i].status
             << endl;
    }

    cout << "-----------------------------------------------------------------------\n";
    int idCari;
    cout << "Masukkan ID Reservasi yang ingin dibatalkan: ";
    cin >> idCari;

    bool ditemukan = false;
    for (int i = 0; i < jumlahreservasi; i++)
    {
        if (reservasiList[i].idReservasi == idCari)
        {
            ditemukan = true;
            if (reservasiList[i].status == "Dibatalkan")
            {
                cout << "Reservasi ini sudah dibatalkan sebelumnya.\n";
            }
            else
            {
                char konfirmasi;
                cout << "Yakin batalkan reservasi ID " << idCari << "? (Y/N): ";
                cin >> konfirmasi;

                if (konfirmasi == 'y' || konfirmasi == 'Y')
                {
                    reservasiList[i].status = "Dibatalkan";

                    ofstream fileReservasi("reservasi.txt", ios::trunc);
                    for (int j = 0; j < jumlahreservasi; j++)
                    {
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
                    cout << "Reservasi ID " << idCari << " berhasil dibatalkan oleh admin.\n";
                }
                else if (konfirmasi == 'n' || konfirmasi == 'N')
                {
                    cout << "Pembatalan dibatalkan.\n";
                }
                else
                {
                    cout << "Input tidak valid, pembatalan dibatalkan.\n";
                }
            }
            break;
        }
    }

    if (!ditemukan)
        cout << "ID Reservasi tidak ditemukan.\n";

    waitEnter();
}

int main()
{
    loadVisitor();
    loadReservasi();
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