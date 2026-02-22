#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

// Menentukan kapasitas maksimum jumlah data kantin yang bisa disimpan di memori.
// Jika data lebih dari 50, aplikasi tidak akan menambahkan data baru.
#define MAX 50

// Nama file utama untuk menyimpan dan memuat data kantin (mode persistent storage).
#define DATA_FILE "data_kantin.txt"

// Nama file untuk menyimpan hasil export laporan dalam format tabel yang rapi.
#define EXPORT_FILE "export_kantin.txt"

// Password default untuk masuk ke mode admin. 
// Mode admin memiliki akses penuh untuk tambah, edit, hapus, dan mengatur data.
#define ADMIN_PASS "admin123"

// Enum untuk menyederhanakan penyimpanan kategori.
// Setiap kategori diberikan nilai angka agar mudah diproses serta disimpan.
typedef enum { MAKANAN = 1, MINUMAN, SNACK } Kategori;

// Struktur data Kantin Rating
typedef struct {
    int id;                 // Deklarasi variabel ID, ID unik
    char nama[60];          // Deklarasi variabel nama
    Kategori kategori;      
    float rating;           // Deklarasi variabel rating untuk rata-rata rating
    int jumlahRating;       // Deklarasi jumlah pengisi rating
    int harga;              // Deklarasi variabel harga
    int isDeleted;          // 0 = aktif, 1 = dihapus (safety)
} Kantin;

Kantin data[MAX];
int jumlahData = 0;
int nextID = 1;

// ----------------- FUNGSI TAMBAHAN -----------------

/* Membersihkan tampilan layar menu */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // Membersihkan tampilan terminal untuk sistem selain Windows.
    // Kode pertama menghapus seluruh layar, lalu kode kedua mengarahkan kursor kembali ke posisi awal.
    printf("\033[2J\033[1;1H");
    fflush(stdout);
#endif
}

/* Tekan enter untuk lanjut diakhir menu */
void pressEnter() {
    char buf[64];
    printf("\nTekan ENTER untuk lanjut...");
    if (!fgets(buf, sizeof(buf), stdin)) { /* ignore */ }
}

/* Input int dengan fgets + parsing, supports min/max (pass INT_MIN/INT_MAX to disable) */
int inputInt(const char *prompt, int min, int max) {
    char buf[128];
    long val;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        if (sscanf(buf, "%ld", &val) != 1) {
            printf("Input harus angka. Coba lagi.\n");
            continue;
        }
        if ((min != INT_MIN && val < min) || (max != INT_MAX && val > max)) {
            if (min != INT_MIN && max != INT_MAX)
                printf("Masukkan antara %d dan %d.\n", min, max);
            else if (min != INT_MIN)
                printf("Masukkan >= %d.\n", min);
            else if (max != INT_MAX)
                printf("Masukkan <= %d.\n", max);
            continue;
        }
        return (int)val;
    }
}

/* Input float dengan fgets & parsing */
float inputFloat(const char *prompt, float min, float max) {
    char buf[128];
    double val;
    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        if (sscanf(buf, "%lf", &val) != 1) {
            printf("Input harus angka (desimal). Coba lagi.\n");
            continue;
        }
        if (val < min || val > max) {
            printf("Masukkan antara %.2f dan %.2f.\n", min, max);
            continue;
        }
        return (float)val;
    }
}

// ----------------- FILE HANDLING -----------------

void saveToFile() {
    // Membuka file dengan mode tulis untuk menyimpan seluruh data kantin
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        printf("Gagal buka file untuk menyimpan.\n");
        return;
    }
    // Baris pertama menyimpan nilai nextID agar ID selanjutnya tetap berurutan
    fprintf(fp, "%d\n", nextID);
    // Menyimpan setiap data kantin yang belum dihapus ke dalam file
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;   // Lewati data yang ditandai terhapus
        fprintf(fp, "%d|%s|%d|%.2f|%d|%d\n",
            data[i].id,
            data[i].nama,
            data[i].kategori,
            data[i].rating,
            data[i].jumlahRating,
            data[i].harga);
    }
    fclose(fp);
    printf("Data tersimpan ke %s\n", DATA_FILE);
}

void loadFromFile() {
    // Membuka file dengan mode baca untuk memuat data jika file sudah ada
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        // Jika file belum ada, aplikasi akan mulai dari kondisi awal
        nextID = 1;
        jumlahData = 0;
        return;
    }
    char line[256];
    // Membaca baris pertama untuk mengambil nilai nextID
    if (fgets(line, sizeof(line), fp)) {
        nextID = atoi(line);
        if (nextID < 1) nextID = 1;     // Validasi agar tidak menjadi nilai aneh
    } else {
        nextID = 1;
    }
    jumlahData = 0;
    // Membaca seluruh baris berikutnya sebagai record data kantin
    while (fgets(line, sizeof(line), fp)) {
        Kantin k;
        int kk;
        // Mem-parse format data sesuai pola penyimpanan
        if (sscanf(line, "%d|%59[^|]|%d|%f|%d|%d",
                   &k.id, k.nama, &kk, &k.rating, &k.jumlahRating, &k.harga) == 6) {
            k.kategori = (Kategori)kk;   // Konversi kembali ke enum
            k.isDeleted = 0;             // Saat load, data dianggap belum terhapus

            // Menyimpan ke array jika masih dalam batas kapasitas
            if (jumlahData < MAX) {
                data[jumlahData++] = k;
            } else {
                printf("Warning: kapasitas maksimum %d terlampaui saat load.\n", MAX);
                break;
            }
        }
    }
    fclose(fp);
}

// ----------------- DISPLAY / FORMAT -----------------

const char* kategoriToStr(Kategori k) {
    // Fungsi untuk mengubah nilai enum kategori menjadi string
    switch (k) {
        case MAKANAN: return "Makanan";
        case MINUMAN: return "Minuman";
        case SNACK:   return "Snack";
        default: return "Unknown";   // Jika nilai enum tidak dikenal
    }
}

void tampilkanHeader() {
    // Menampilkan header tabel agar format data terlihat rapi
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("| ID  | Nama                               | Kategori    | Rating | Jumlah Ulasan |   Harga |\n");
    printf("----------------------------------------------------------------------------------------------------\n");
}

void tampilkanSatu(const Kantin *k) {
    // Jika datanya sudah ditandai terhapus, jangan tampilkan
    if (k->isDeleted) return;
    // Menampilkan satu baris data kantin dalam format tabel
    printf("| %-3d | %-34s | %-11s | %6.2f | %13d | %7d |\n",
           k->id,
           k->nama,
           kategoriToStr(k->kategori),  // Konversi enum ke string
           k->rating,
           k->jumlahRating,
           k->harga);
}

void tampilkanSemua() {
    // Jika tidak ada data sama sekali, tampilkan pesan
    if (jumlahData == 0) {
        printf("Belum ada data.\n");
        return;
    }
    tampilkanHeader();  // Tampilkan header tabel
    // Loop menampilkan semua data yang belum dihapus
    for (int i = 0; i < jumlahData; i++) {
        if (!data[i].isDeleted)
            tampilkanSatu(&data[i]);
    }
    // Garis penutup tabel
    printf("----------------------------------------------------------------------------------------------------\n");
}

// ----------------- CRUD -----------------

void tambahData() {
    clearScreen();
    // Mengecek apakah kapasitas data sudah penuh.
    if (jumlahData >= MAX) {
        printf("Kapasitas penuh. Hapus data dulu.\n");
        return;
    }
    Kantin k;
    k.id = nextID++;
    printf("Tambah Kantin (ID %d)\n", k.id);
    // Input nama kantin, dan memastikan agar tidak kosong.
    printf("Nama kantin: ");
    if (!fgets(k.nama, sizeof(k.nama), stdin)) k.nama[0] = '\0';
    k.nama[strcspn(k.nama, "\n")] = 0;
    while (strlen(k.nama) == 0) {
        printf("Nama tidak boleh kosong. Input ulang: ");
        if (!fgets(k.nama, sizeof(k.nama), stdin)) k.nama[0] = '\0';
        k.nama[strcspn(k.nama, "\n")] = 0;
    }
    // Memilih kategori dari tiga opsi.
    printf("Pilih kategori:\n1. Makanan\n2. Minuman\n3. Snack\n");
    int cat = inputInt("Kategori (1-3): ", 1, 3);
    k.kategori = (Kategori)cat;
    // Input harga, memastikan lebih dari 0.
    k.harga = inputInt("Harga (angka, >0): ", 1, INT_MAX);
    // Input rating awal; jika 0 berarti belum ada rating.
    float r = inputFloat("Rating awal (0.0 - 5.0), isi 0 jika belum ada: ", 0.0f, 5.0f);
    if (r == 0.0f) {
        k.rating = 0.0f;
        k.jumlahRating = 0;
    } else {
        k.rating = r;
        k.jumlahRating = 1;
    }
    k.isDeleted = 0;
    // Menyimpan data ke array.
    data[jumlahData++] = k;
    printf("Data berhasil ditambahkan.\n");
}

int findIndexByID(int id) {
    // Mencari indeks data berdasarkan ID (mengabaikan yang sudah dihapus).
    for (int i = 0; i < jumlahData; i++) {
        if (!data[i].isDeleted && data[i].id == id) return i;
    }
    return -1;
}

void updateData() {
    clearScreen();
    tampilkanSemua();
    // Meminta ID yang ingin diperbarui.
    int id = inputInt("Masukkan ID yang mau diupdate: ", 1, INT_MAX);
    int idx = findIndexByID(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }
    Kantin *k = &data[idx];
    printf("Update data ID %d (kosongkan untuk tidak mengganti)\n", k->id);
    char buf[128];
    // Update nama (opsional).
    printf("Nama baru (sekarang: %s): ", k->nama);
    if (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) > 0) strncpy(k->nama, buf, sizeof(k->nama));
    }
    // Update kategori (opsional).
    printf("Kategori sekarang: %s\n", kategoriToStr(k->kategori));
    printf("1. Makanan\n2. Minuman\n3. Snack\n");
    int cat = inputInt("Masukkan kategori baru (0=tidak ganti): ", 0, 3);
    if (cat >= 1 && cat <= 3) k->kategori = (Kategori)cat;
    // Update harga (opsional).
    printf("Harga sekarang: %d\n", k->harga);
    int h = inputInt("Harga baru (0=tidak ganti): ", 0, INT_MAX);
    if (h > 0) k->harga = h;

    printf("Update selesai.\n");
}

void hapusData() {
    clearScreen();
    tampilkanSemua();
    // Meminta ID data yang akan dihapus.
    int id = inputInt("Masukkan ID yang mau dihapus: ", 1, INT_MAX);
    int idx = findIndexByID(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }
    // Mengubah status menjadi terhapus (soft delete).
    data[idx].isDeleted = 1;
    printf("Data ID %d diberi tanda dihapus (soft delete).\n", id);
}

// ----------------- RATING -----------------

void tambahRatingAkumulatif(int idx, float nilai) {
    // Mengambil pointer ke data kantin berdasarkan indeks.
    Kantin *k = &data[idx];
    // Menghitung rating baru dengan menambahkan rating sebelumnya kemudian dibagi total jumlah rating yang baru.
    k->rating = (k->rating * k->jumlahRating + nilai) / (k->jumlahRating + 1);
    // Menambah jumlah rating yang sudah diberikan.
    k->jumlahRating++;
}

void overwriteRating(int idx, float nilai) {
    // Mengambil pointer ke data kantin berdasarkan indeks.
    Kantin *k = &data[idx];
    // Mengganti rating lama dengan nilai baru secara langsung.
    k->rating = nilai;
    // Mengatur jumlah rating menjadi 1 karena rating direset.
    k->jumlahRating = 1;
}

void beriRating() {
    clearScreen();
    tampilkanSemua();
    // Meminta pengguna memilih ID kantin yang ingin diberi rating.
    int id = inputInt("Masukkan ID kantin yang mau diberi rating: ", 1, INT_MAX);
    int idx = findIndexByID(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }
    Kantin *k = &data[idx];
    // Menampilkan informasi rating saat ini.
    printf("Kantin: %s | Rating sekarang: %.2f (%d)\n",
           k->nama, k->rating, k->jumlahRating);
    // Pengguna memilih mode pemberian rating.
    printf("Pilih mode rating:\n1. Tambah rating (akumulatif)\n2. Overwrite rating (ganti)\n");
    int m = inputInt("Pilihan (1-2): ", 1, 2);
    // Meminta nilai rating baru.
    float r = inputFloat("Masukkan rating (0.0 - 5.0): ", 0.0f, 5.0f);
    // Menjalankan mode sesuai pilihan pengguna.
    if (m == 1) tambahRatingAkumulatif(idx, r);
    else overwriteRating(idx, r);
    printf("Rating berhasil disimpan.\n");
}

// ----------------- SORT -----------------

int cmpRatingDesc(const void *a, const void *b) {
    // Fungsi pembanding untuk sorting rating dari tinggi ke rendah.
    const Kantin *ka = (const Kantin *)a;
    const Kantin *kb = (const Kantin *)b;
    if (ka->rating < kb->rating) return 1;
    if (ka->rating > kb->rating) return -1;
    return 0;
}

int cmpHargaAsc(const void *a, const void *b) {
    // Fungsi pembanding untuk sorting harga dari paling murah ke mahal.
    const Kantin *ka = (const Kantin *)a;
    const Kantin *kb = (const Kantin *)b;
    return (ka->harga - kb->harga);
}

int cmpNamaAsc(const void *a, const void *b) {
    // Fungsi pembanding untuk sorting nama secara alfabetis (A-Z).
    const Kantin *ka = (const Kantin *)a;
    const Kantin *kb = (const Kantin *)b;
    return strcasecmp(ka->nama, kb->nama);
}

void sortMenu() {
    clearScreen();
    // Mengecek apakah data tersedia.
    if (jumlahData == 0) {
        printf("Belum ada data.\n");
        return;
    }
    // Memilih kriteria sorting.
    printf("Pilih sort:\n1. Rating (tinggi ke rendah)\n2. Harga (murah ke mahal)\n3. Nama (A-Z)\n");
    int p = inputInt("Pilihan (1-3): ", 1, 3);
    // Membuat salinan data yang tidak terhapus agar urutan asli tidak berubah.
    Kantin temp[MAX];
    int idx = 0;
    for (int i = 0; i < jumlahData; i++)
        if (!data[i].isDeleted)
            temp[idx++] = data[i];
    // Melakukan sorting sesuai pilihan pengguna.
    if (p == 1)
        qsort(temp, idx, sizeof(Kantin), cmpRatingDesc);
    else if (p == 2)
        qsort(temp, idx, sizeof(Kantin), cmpHargaAsc);
    else
        qsort(temp, idx, sizeof(Kantin), cmpNamaAsc);
    // Menampilkan hasil sorting.
    tampilkanHeader();
    for (int i = 0; i < idx; i++)
        tampilkanSatu(&temp[i]);
    printf("--------------------------------------------------------------------------------\n");
}

// ----------------- SEARCH -----------------

// -----------fungsi tambahan untuk case-insensitive substring search------------
char* my_strcasestr(const char* haystack, const char* needle) {
    if (!haystack || !needle) return NULL;
    if (needle == '\0') return (char)haystack;

    size_t nlen = strlen(needle);

    for (const char *p = haystack; *p; p++) {
        if (strncasecmp(p, needle, nlen) == 0) {
            return (char*)p;
        }
    }
    return NULL;
}

void cariNama() {
    char key[60];
    // Meminta pengguna memasukkan kata kunci pencarian.
    printf("Masukkan kata kunci nama: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;  // Menghapus karakter newline.
    // Mengecek apakah kata kunci kosong.
    if (strlen(key) == 0) {
        printf("Kata kunci kosong.\n");
        return;
    }

    int found = 0;
    tampilkanHeader();
    // Mencari nama yang mengandung kata kunci (case-insensitive).
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;

        if (my_strcasestr(data[i].nama, key) != NULL) {
            tampilkanSatu(&data[i]);
            found++;
        }
    }
    // Jika hasil tidak ditemukan.
    if (!found) printf("Tidak ditemukan.\n");
    printf("--------------------------------------------------------------------------------\n");
}

void cariKategori() {
    clearScreen();
    // Meminta pengguna memilih kategori pencarian.
    printf("Pilih kategori cari:\n1. Makanan\n2. Minuman\n3. Snack\n");
    int c = inputInt("Kategori (1-3): ", 1, 3);
    int found = 0;
    tampilkanHeader();
    // Menampilkan semua data yang memiliki kategori sesuai pilihan.
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;
        if (data[i].kategori == (Kategori)c) {
            tampilkanSatu(&data[i]);
            found++;
        }
    }
    // Jika tidak ada data yang cocok.
    if (!found) printf("Tidak ada pada kategori itu.\n");
    printf("--------------------------------------------------------------------------------\n");
}

void cariRatingMin() {
    clearScreen();
    // Meminta pengguna memasukkan rating minimal.
    float r = inputFloat("Masukkan rating minimal (0.0 - 5.0): ", 0.0f, 5.0f);
    int found = 0;
    tampilkanHeader();
    // Mencari semua data dengan rating >= nilai minimal.
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;

        if (data[i].rating >= r) {
            tampilkanSatu(&data[i]);
            found++;
        }
    }
    // Jika tidak ada data yang memenuhi syarat.
    if (!found) printf("Tidak ada yang memenuhi.\n");
    printf("--------------------------------------------------------------------------------\n");
}

// ----------------- REKOMENDASI & EXPORT -----------------

void rekomendasi() {
    clearScreen();
    // Meminta pengguna memasukkan nilai rating minimal untuk rekomendasi.
    float threshold = inputFloat("Tampilkan kantin dengan rating >= (0.0 - 5.0): ", 0.0f, 5.0f);
    int found = 0;
    tampilkanHeader();
    // Menampilkan semua kantin yang memiliki rating di atas atau sama dengan threshold.
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;

        if (data[i].rating >= threshold) {
            tampilkanSatu(&data[i]);
            found++;
        }
    }
    // Jika tidak ada yang memenuhi syarat.
    if (!found) printf("Tidak ada rekomendasi.\n");
    printf("--------------------------------------------------------------------------------\n");
}

void exportNiceFile() {
    FILE *fp = fopen(EXPORT_FILE, "w");
    // Mengecek apakah file berhasil dibuat atau tidak.
    if (!fp) {
        printf("Gagal membuat file export.\n");
        return;
    }
    // Menulis header laporan ke dalam file.
    fprintf(fp, "LAPORAN DATA KANTIN\n");
    fprintf(fp, "----------------------------------------------------------------------------------------------------\n");
    fprintf(fp, "| ID  | Nama                               | Kategori    | Rating | Jumlah Ulasan |   Harga |\n");
    fprintf(fp, "----------------------------------------------------------------------------------------------------\n");
    // Menuliskan seluruh data kantin yang belum dihapus.
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;
        fprintf(fp,
            "| %-3d | %-34s | %-11s | %6.2f | %13d | %7d |\n",
            data[i].id,
            data[i].nama,
            kategoriToStr(data[i].kategori),
            data[i].rating,
            data[i].jumlahRating,
            data[i].harga
        );
    }
    fprintf(fp, "----------------------------------------------------------------------------------------------------\n");
    // Menutup file setelah selesai menulis.
    fclose(fp);
    printf("Export berhasil ke %s\n", EXPORT_FILE);
}

// ----------------- MENU (Admin & User) -----------------

void menuUser() {
    int pilihan;
    do {
        clearScreen();   // Membersihkan tampilan agar menu terlihat rapi
        printf("=== MODE USER ===\n");
        printf("[1] Lihat semua\n");
        printf("[2] Cari nama\n");
        printf("[3] Cari kategori\n");
        printf("[4] Cari rating minimal\n");
        printf("[5] Rekomendasi (filter rating)\n");
        printf("[6] Beri rating (hanya tambah/overwrite)\n");
        printf("[7] Kembali ke menu awal\n");
        // Meminta input pilihan dari user, dibatasi hanya angka 1–7
        pilihan = inputInt("Pilihan: ", 1, 7);
        clearScreen();   // Membersihkan layar sebelum menampilkan hasil pilihan user
        switch (pilihan) {
            case 1: tampilkanSemua(); break;      // Menampilkan semua data kantin
            case 2: cariNama(); break;            // Mencari berdasarkan nama
            case 3: cariKategori(); break;        // Mencari berdasarkan kategori
            case 4: cariRatingMin(); break;       // Mencari berdasarkan rating minimal
            case 5: rekomendasi(); break;         // Menampilkan rekomendasi sesuai rating
            case 6: beriRating(); break;          // User memberikan rating pada item
            case 7: break;                        // Kembali ke menu utama
            default: printf("Pilihan tidak valid.\n");
        }
        pressEnter();    // Menunggu user menekan Enter sebelum kembali ke menu
    } while (pilihan != 7);   // Loop selama user belum memilih keluar
}

void menuAdmin() {
    int pilihan;
    do {
        clearScreen();   // Membersihkan tampilan agar menu admin terlihat rapi
        printf("=== MODE ADMIN ===\n");
        printf("[1] Tambah data kantin\n");
        printf("[2] Update data kantin\n");
        printf("[3] Hapus data kantin\n");
        printf("[4] Lihat semua data kantin\n");
        printf("[5] Sort (rating/harga/nama)\n");
        printf("[6] Cari (nama/kategori/rating)\n");
        printf("[7] Beri rating (admin)\n");
        printf("[8] Rekomendasi\n");
        printf("[9] Export data kantin\n");
        printf("[10] Simpan data kantin\n");
        printf("[11] Logout\n");
        // Meminta input dengan batas pilihan 1–11
        pilihan = inputInt("Pilihan: ", 1, 11);
        clearScreen();   // Membersihkan layar sebelum menjalankan fitur yang dipilih
        switch (pilihan) {
            case 1: tambahData(); break;          // Admin menambahkan data kantin baru
            case 2: updateData(); break;          // Admin mengubah data kantin yang sudah ada
            case 3: hapusData(); break;           // Admin menghapus data kantin
            case 4: tampilkanSemua(); break;      // Menampilkan semua data kantin
            case 5: sortMenu(); break;            // Menu sorting berdasarkan kriteria tertentu
            case 6:
                printf("Cari by: 1) nama 2) kategori 3) rating min\n");

                // Sub-menu untuk memilih jenis pencarian
                {
                    int c = inputInt("Pilihan: ", 1, 3);
                    clearScreen();
                    if (c == 1) cariNama();
                    else if (c == 2) cariKategori();
                    else cariRatingMin();
                }
                break;
            case 7: beriRating(); break;          // Admin memberikan/menyesuaikan rating
            case 8: rekomendasi(); break;         // Menampilkan daftar rekomendasi
            case 9: exportNiceFile(); break;      // Mengekspor data kantin ke file rapi
            case 10: saveToFile(); break;         // Menyimpan data kantin ke file utama
            case 11: break;                       // Keluar dari mode admin
            default: printf("Pilihan tidak valid.\n");
        }
        pressEnter();   // Pause sebelum kembali ke menu admin
    } while (pilihan != 11);   // Berjalan sampai admin memilih logout
}


// ----------------- MAIN -----------------

int main() {
    loadFromFile();  
    // Saat program dimulai, data awal langsung dibaca dari file penyimpanan
    while (1) {  
        clearScreen();   // Membersihkan layar agar menu utama terlihat rapi
        printf("=========== KaTing ===========\n");
        printf("=== APLIKASI RATING KANTIN ===\n");
        printf("\nPilih mode:\n1) User (lihat & beri rating)\n2) Admin (CRUD lengkap)\n3) Simpan & Keluar\n");
        // Meminta input mode aplikasi yang ingin digunakan
        int mode = inputInt("Pilihan: ", 1, 3);
        clearScreen();   // Membersihkan layar sebelum masuk ke mode tertentu
        if (mode == 1) {
            // Mode User: hanya bisa melihat data dan memberi rating
            menuUser();
        } else if (mode == 2) {
            // Mode Admin: membutuhkan password sebelum masuk
            char pass[64];
            printf("Masukkan password admin: ");
            // Mengambil input password dengan fgets
            if (!fgets(pass, sizeof(pass), stdin)) 
                pass[0] = '\0';  // Jika error input, set string kosong
            pass[strcspn(pass, "\n")] = 0;  // Menghapus newline dari password
            // Validasi password admin
            if (strcmp(pass, ADMIN_PASS) == 0) {
                menuAdmin();   // Password benar → masuk ke menu admin
            } else {
                printf("Password salah.\n");
                pressEnter();  // Pause supaya pesan bisa dibaca
            }
        } else if (mode == 3) {
            // Mode keluar: simpan semua data sebelum exit
            saveToFile();
            printf("Keluar. Bye.\n");
            break;   // Menghentikan loop utama dan mengakhiri program
        }
    }
    return 0;  // Program selesai dijalankan
}