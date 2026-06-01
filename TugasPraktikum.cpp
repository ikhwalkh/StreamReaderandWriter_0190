#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// ======================
// CLASS TOKO ELEKTRONIK
// ======================
class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    // Constructor isi data awal otomatis
    TokoElektronik() {
        etalase[0] = "Laptop ASUS";
        etalase[1] = "Smartphone Samsung";
        etalase[2] = "Headset JBL";
    }

    // Ambil produk berdasarkan nomor rak
    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string(
                "Gagal Mengambil Barang : Rak nomor " +
                to_string(nomorRak) +
                " kosong atau tidak tersedia!"
            );
        }
    }
};

// ======================
// CRUD FILE GUDANG
// ======================
string namaFile = "gudang.txt";

// Read
void tampilkanBarang() {
    ifstream file(namaFile);
    string barang;
    int nomor = 1;

    cout << "\n=== DAFTAR BARANG GUDANG ===\n";

    if (!file) {
        cout << "File belum tersedia.\n";
        return;
    }

    while (getline(file, barang)) {
        cout << nomor++ << ". " << barang << endl;
    }

    if (nomor == 1) {
        cout << "Gudang masih kosong.\n";
    }

    file.close();
}

// Create
void tambahBarang() {
    ofstream file(namaFile, ios::app);
    string barang;

    cin.ignore();
    cout << "Masukkan nama barang baru: ";
    getline(cin, barang);

    file << barang << endl;
    file.close();

    cout << "Barang berhasil ditambahkan.\n";
}

// Update
void updateBarang() {
    ifstream file(namaFile);
    vector<string> daftar;
    string barang;

    while (getline(file, barang)) {
        daftar.push_back(barang);
    }

    file.close();

    if (daftar.empty()) {
        cout << "Gudang kosong.\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "Pilih nomor barang yang diubah: ";
    cin >> nomor;

    if (nomor < 1 || nomor > daftar.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    cin.ignore();
    cout << "Nama baru: ";
    getline(cin, daftar[nomor - 1]);

    ofstream tulis(namaFile);
    for (string item : daftar) {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Barang berhasil diperbarui.\n";
}

// Delete
void hapusBarang() {
    ifstream file(namaFile);
    vector<string> daftar;
    string barang;

    while (getline(file, barang)) {
        daftar.push_back(barang);
    }

    file.close();

    if (daftar.empty()) {
        cout << "Gudang kosong.\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "Pilih nomor barang yang dihapus: ";
    cin >> nomor;

    if (nomor < 1 || nomor > daftar.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    daftar.erase(daftar.begin() + nomor - 1);

    ofstream tulis(namaFile);
    for (string item : daftar) {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Barang berhasil dihapus.\n";
}

// ======================
// SIMULASI ETALASE
// ======================
void simulasiEtalase() {
    TokoElektronik toko;

    cout << "\n=== SIMULASI ETALASE ===\n";

    // Skenario 1
    try {
        cout << "Rak 1: " << toko.ambilProduk(1) << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }

    // Skenario 2
    try {
        cout << "Rak 5: " << toko.ambilProduk(5) << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }
}

// ======================
// MAIN
// ======================
int main() {
    int pilihan;

    do {
        tampilkanBarang();

        cout << "\n=== MENU UTAMA TOKO GIBRAN JAYA ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Update Barang\n";
        cout << "3. Hapus Barang\n";
        cout << "4. Simulasi Etalase\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahBarang();
            break;

        case 2:
            updateBarang();
            break;

        case 3:
            hapusBarang();
            break;

        case 4:
            simulasiEtalase();
            break;

        case 5:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 5);

    return 0;
}