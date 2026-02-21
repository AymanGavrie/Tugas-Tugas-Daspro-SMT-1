#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX 50
#define DATA_FILE "data_kantin.txt"
#define EXPORT_FILE "export_kantin.txt"
#define ADMIN_PASS "admin123"

typedef enum { MAKANAN = 1, MINUMAN, SNACK } Kategori;

typedef struct {
    int id;                 // ID unik, tidak berubah
    char nama[60];
    Kategori kategori;
    float rating;           // rata-rata rating
    int jumlahRating;       // jumlah pengisi rating
    int harga;
    int isDeleted;          // 0 = aktif, 1 = dihapus (safety)
} Kantin;

Kantin data[MAX];
int jumlahData = 0;
int nextID = 1;

// ----------------- UTIL -----------------

/* Clear screen cross-platform */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    /* ANSI escape sequence: clear screen & move cursor to 1;1 */
    printf("\033[2J\033[1;1H");
    fflush(stdout);
#endif
}

/* Safe press enter (consumes the newline properly) */
void pressEnter() {
    char buf[64];
    printf("\nTekan ENTER untuk lanjut...");
    if (!fgets(buf, sizeof(buf), stdin)) { /* ignore */ }
}

/* input int via fgets + parsing, supports min/max (pass INT_MIN/INT_MAX to disable) */
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

/* input float via fgets + parsing */
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
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        printf("Gagal buka file untuk menyimpan.\n");
        return;
    }
    fprintf(fp, "%d\n", nextID);
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;
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
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        // file belum ada -> mulai fresh
        nextID = 1;
        jumlahData = 0;
        return;
    }
    char line[256];
    if (fgets(line, sizeof(line), fp)) {
        nextID = atoi(line);
        if (nextID < 1) nextID = 1;
    } else {
        nextID = 1;
    }
    jumlahData = 0;
    while (fgets(line, sizeof(line), fp)) {
        Kantin k;
        int kk;
        if (sscanf(line, "%d|%59[^|]|%d|%f|%d|%d",
                   &k.id, k.nama, &kk, &k.rating, &k.jumlahRating, &k.harga) == 6) {
            k.kategori = (Kategori)kk;
            k.isDeleted = 0;
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
    switch (k) {
        case MAKANAN: return "Makanan";
        case MINUMAN: return "Minuman";
        case SNACK:   return "Snack";
        default: return "Unknown";
    }
}

void tampilkanHeader() {
    printf("--------------------------------------------------------------------------------\n");
    printf("| ID  | Nama                             | Kategori  | Rating  | #rat | Harga |\n");
    printf("--------------------------------------------------------------------------------\n");
}

void tampilkanSatu(const Kantin *k) {
    if (k->isDeleted) return;
    printf("| %-3d | %-32s | %-9s | %6.2f | %4d | %5d |\n",
           k->id, k->nama, kategoriToStr(k->kategori), k->rating, k->jumlahRating, k->harga);
}

void tampilkanSemua() {
    if (jumlahData == 0) {
        printf("Belum ada data.\n");
        return;
    }
    tampilkanHeader();
    for (int i = 0; i < jumlahData; i++) {
        if (!data[i].isDeleted) tampilkanSatu(&data[i]);
    }
    printf("--------------------------------------------------------------------------------\n");
}

// ----------------- CRUD -----------------

void tambahData() {
    clearScreen();
    if (jumlahData >= MAX) {
        printf("Kapasitas penuh. Hapus data dulu.\n");
        return;
    }
    Kantin k;
    k.id = nextID++;
    printf("Tambah Kantin (ID %d)\n", k.id);

    printf("Nama kantin: ");
    if (!fgets(k.nama, sizeof(k.nama), stdin)) k.nama[0] = '\0';
    k.nama[strcspn(k.nama, "\n")] = 0;
    while (strlen(k.nama) == 0) {
        printf("Nama tidak boleh kosong. Input ulang: ");
        if (!fgets(k.nama, sizeof(k.nama), stdin)) k.nama[0] = '\0';
        k.nama[strcspn(k.nama, "\n")] = 0;
    }

    printf("Pilih kategori:\n1. Makanan\n2. Minuman\n3. Snack\n");
    int cat = inputInt("Kategori (1-3): ", 1, 3);
    k.kategori = (Kategori)cat;

    k.harga = inputInt("Harga (angka, >0): ", 1, INT_MAX);

    float r = inputFloat("Rating awal (0.0 - 5.0), isi 0 jika belum ada: ", 0.0f, 5.0f);
    if (r == 0.0f) {
        k.rating = 0.0f;
        k.jumlahRating = 0;
    } else {
        k.rating = r;
        k.jumlahRating = 1;
    }
    k.isDeleted = 0;

    data[jumlahData++] = k;
    printf("Data berhasil ditambahkan.\n");
}

int findIndexByID(int id) {
    for (int i = 0; i < jumlahData; i++) {
        if (!data[i].isDeleted && data[i].id == id) return i;
    }
    return -1;
}

void updateData() {
    clearScreen();
    int id = inputInt("Masukkan ID yang mau diupdate: ", 1, INT_MAX);
    int idx = findIndexByID(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }
    Kantin *k = &data[idx];
    printf("Update data ID %d (kosongkan untuk tidak mengganti)\n", k->id);

    char buf[128];
    printf("Nama baru (sekarang: %s): ", k->nama);
    if (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) > 0) strncpy(k->nama, buf, sizeof(k->nama));
    }

    printf("Kategori sekarang: %s\n", kategoriToStr(k->kategori));
    printf("1. Makanan\n2. Minuman\n3. Snack\n");
    int cat = inputInt("Masukkan kategori baru (0=tidak ganti): ", 0, 3);
    if (cat >= 1 && cat <= 3) k->kategori = (Kategori)cat;

    printf("Harga sekarang: %d\n", k->harga);
    int h = inputInt("Harga baru (0=tidak ganti): ", 0, INT_MAX);
    if (h > 0) k->harga = h;

    printf("Update selesai.\n");
}

void hapusData() {
    clearScreen();
    int id = inputInt("Masukkan ID yang mau dihapus: ", 1, INT_MAX);
    int idx = findIndexByID(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }
    data[idx].isDeleted = 1; // flag delete
    printf("Data ID %d diberi tanda dihapus (soft delete).\n", id);
}

// ----------------- RATING -----------------

void tambahRatingAkumulatif(int idx, float nilai) {
    Kantin *k = &data[idx];
    k->rating = (k->rating * k->jumlahRating + nilai) / (k->jumlahRating + 1);
    k->jumlahRating++;
}

void overwriteRating(int idx, float nilai) {
    Kantin *k = &data[idx];
    k->rating = nilai;
    k->jumlahRating = 1;
}

void beriRating() {
    clearScreen();
    int id = inputInt("Masukkan ID kantin yang mau diberi rating: ", 1, INT_MAX);
    int idx = findIndexByID(id);
    if (idx == -1) {
        printf("ID tidak ditemukan.\n");
        return;
    }
    Kantin *k = &data[idx];
    printf("Kantin: %s | Rating sekarang: %.2f (%d)\n", k->nama, k->rating, k->jumlahRating);
    printf("Pilih mode rating:\n1. Tambah rating (akumulatif)\n2. Overwrite rating (ganti)\n");
    int m = inputInt("Pilihan (1-2): ", 1, 2);
    float r = inputFloat("Masukkan rating (0.0 - 5.0): ", 0.0f, 5.0f);
    if (m == 1) tambahRatingAkumulatif(idx, r);
    else overwriteRating(idx, r);
    printf("Rating berhasil disimpan.\n");
}

// ----------------- SORT -----------------

int cmpRatingDesc(const void *a, const void *b) {
    const Kantin *ka = (const Kantin *)a;
    const Kantin *kb = (const Kantin *)b;
    if (ka->rating < kb->rating) return 1;
    if (ka->rating > kb->rating) return -1;
    return 0;
}
int cmpHargaAsc(const void *a, const void *b) {
    const Kantin *ka = (const Kantin *)a;
    const Kantin *kb = (const Kantin *)b;
    return (ka->harga - kb->harga);
}
int cmpNamaAsc(const void *a, const void *b) {
    const Kantin *ka = (const Kantin *)a;
    const Kantin *kb = (const Kantin *)b;
    return strcasecmp(ka->nama, kb->nama);
}

void sortMenu() {
    clearScreen();
    if (jumlahData == 0) {
        printf("Belum ada data.\n");
        return;
    }
    printf("Pilih sort:\n1. Rating (tinggi ke rendah)\n2. Harga (murah ke mahal)\n3. Nama (A-Z)\n");
    int p = inputInt("Pilihan (1-3): ", 1, 3);
    // buat salinan data aktif supaya kita ga kehilangan urutan asli
    Kantin temp[MAX];
    int idx = 0;
    for (int i = 0; i < jumlahData; i++) if (!data[i].isDeleted) temp[idx++] = data[i];
    if (p == 1) qsort(temp, idx, sizeof(Kantin), cmpRatingDesc);
    else if (p == 2) qsort(temp, idx, sizeof(Kantin), cmpHargaAsc);
    else qsort(temp, idx, sizeof(Kantin), cmpNamaAsc);

    // tampilkan hasil
    tampilkanHeader();
    for (int i = 0; i < idx; i++) tampilkanSatu(&temp[i]);
    printf("--------------------------------------------------------------------------------\n");
}

// ----------------- SEARCH -----------------

void cariNama() {
    clearScreen();
    char key[60];
    printf("Masukkan kata kunci nama: ");
    if (!fgets(key, sizeof(key), stdin)) key[0] = '\0';
    key[strcspn(key, "\n")] = 0;
    if (strlen(key) == 0) {
        printf("Kata kunci kosong.\n");
        return;
    }
    int found = 0;
    tampilkanHeader();
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;
        if (strcasecmp(data[i].nama, key) == 0) {
            tampilkanSatu(&data[i]);
            found++;
        }
    }
    if (!found) printf("Tidak ditemukan.\n");
    printf("--------------------------------------------------------------------------------\n");
}

void cariKategori() {
    clearScreen();
    printf("Pilih kategori cari:\n1. Makanan\n2. Minuman\n3. Snack\n");
    int c = inputInt("Kategori (1-3): ", 1, 3);
    int found = 0;
    tampilkanHeader();
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;
        if (data[i].kategori == (Kategori)c) {
            tampilkanSatu(&data[i]);
            found++;
        }
    }
    if (!found) printf("Tidak ada pada kategori itu.\n");
    printf("--------------------------------------------------------------------------------\n");
}

void cariRatingMin() {
    clearScreen();
    float r = inputFloat("Masukkan rating minimal (0.0 - 5.0): ", 0.0f, 5.0f);
    int found = 0;
    tampilkanHeader();
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;
        if (data[i].rating >= r) {
            tampilkanSatu(&data[i]);
            found++;
        }
    }
    if (!found) printf("Tidak ada yang memenuhi.\n");
    printf("--------------------------------------------------------------------------------\n");
}

// ----------------- REKOMENDASI & EXPORT -----------------

void rekomendasi() {
    clearScreen();
    float threshold = inputFloat("Tampilkan kantin dengan rating >= (0.0 - 5.0): ", 0.0f, 5.0f);
    int found = 0;
    tampilkanHeader();
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;
        if (data[i].rating >= threshold) {
            tampilkanSatu(&data[i]);
            found++;
        }
    }
    if (!found) printf("Tidak ada rekomendasi.\n");
    printf("--------------------------------------------------------------------------------\n");
}

void exportNiceFile() {
    FILE *fp = fopen(EXPORT_FILE, "w");
    if (!fp) {
        printf("Gagal membuat file export.\n");
        return;
    }
    fprintf(fp, "LAPORAN DATA KANTIN\n");
    fprintf(fp, "--------------------------------------------------------------------------------\n");
    fprintf(fp, "| ID  | Nama                             | Kategori  | Rating  | #rat | Harga |\n");
    fprintf(fp, "--------------------------------------------------------------------------------\n");
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].isDeleted) continue;
        fprintf(fp, "| %-3d | %-32s | %-9s | %6.2f | %4d | %5d |\n",
            data[i].id, data[i].nama, kategoriToStr(data[i].kategori),
            data[i].rating, data[i].jumlahRating, data[i].harga);
    }
    fprintf(fp, "--------------------------------------------------------------------------------\n");
    fclose(fp);
    printf("Export berhasil ke %s\n", EXPORT_FILE);
}

// ----------------- MENU (Admin & User) -----------------

void menuUser() {
    int pilihan;
    do {
        clearScreen();
        printf("=== MODE USER ===\n");
        printf("[1] Lihat semua\n");
        printf("[2] Cari nama\n");
        printf("[3] Cari kategori\n");
        printf("[4] Cari rating minimal\n");
        printf("[5] Rekomendasi (filter rating)\n");
        printf("[6] Beri rating (hanya tambah/overwrite)\n");
        printf("[7] Kembali ke menu awal\n");
        pilihan = inputInt("Pilihan: ", 1, 7);

        clearScreen();
        switch (pilihan) {
            case 1: tampilkanSemua(); break;
            case 2: cariNama(); break;
            case 3: cariKategori(); break;
            case 4: cariRatingMin(); break;
            case 5: rekomendasi(); break;
            case 6: beriRating(); break;
            case 7: break;
            default: printf("Pilihan tidak valid.\n");
        }
        pressEnter();
    } while (pilihan != 7);
}

void menuAdmin() {
    int pilihan;
    do {
        clearScreen();
        printf("=== MODE ADMIN ===\n");
        printf("[1] Tambah data\n");
        printf("[2] Update data\n");
        printf("[3] Hapus data\n");
        printf("[4] Lihat semua\n");
        printf("[5] Sort (rating/harga/nama)\n");
        printf("[6] Cari (nama/kategori/rating)\n");
        printf("[7] Beri rating (admin)\n");
        printf("[8] Rekomendasi\n");
        printf("[9] Export rapi\n");
        printf("[10] Simpan data\n");
        printf("[11] Logout\n");
        pilihan = inputInt("Pilihan: ", 1, 11);

        clearScreen();
        switch (pilihan) {
            case 1: tambahData(); break;
            case 2: updateData(); break;
            case 3: hapusData(); break;
            case 4: tampilkanSemua(); break;
            case 5: sortMenu(); break;
            case 6:
                printf("Cari by: 1) nama 2) kategori 3) rating min\n");
                {
                    int c = inputInt("Pilihan: ", 1, 3);
                    clearScreen();
                    if (c == 1) cariNama();
                    else if (c == 2) cariKategori();
                    else cariRatingMin();
                }
                break;
            case 7: beriRating(); break;
            case 8: rekomendasi(); break;
            case 9: exportNiceFile(); break;
            case 10: saveToFile(); break;
            case 11: break;
            default: printf("Pilihan tidak valid.\n");
        }
        pressEnter();
    } while (pilihan != 11);
}

// ----------------- MAIN -----------------

int main() {
    loadFromFile();
    while (1) {
        clearScreen();
        printf("=== APLIKASI RATING KANTIN ===\n");
        printf("\nPilih mode:\n1) User (lihat & beri rating)\n2) Admin (CRUD lengkap)\n3) Simpan & Keluar\n");
        int mode = inputInt("Pilihan: ", 1, 3);

        clearScreen();
        if (mode == 1) {
            menuUser();
        } else if (mode == 2) {
            char pass[64];
            printf("Masukkan password admin: ");
            if (!fgets(pass, sizeof(pass), stdin)) pass[0] = '\0';
            pass[strcspn(pass, "\n")] = 0;
            if (strcmp(pass, ADMIN_PASS) == 0) {
                menuAdmin();
            } else {
                printf("Password salah.\n");
                pressEnter();
            }
        } else if (mode == 3) {
            saveToFile();
            printf("Keluar. Bye.\n");
            break;
        }
    }
    return 0;
}
