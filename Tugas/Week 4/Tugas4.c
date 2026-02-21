#include <stdio.h>

int main() {
    char nama[50];
    int hadir, sakit, alpha, sakit2, hasilAbsensi;
    int ujian; 
    float persenAbsensi, nilaiAkhir; 

    printf("Masukan Nama Mahasiswa: ");
    fgets(nama, sizeof(nama), stdin);

    printf("Hadir: ");
    scanf("%d", &hadir);

    if (hadir > 14) {
        hadir = 14; 
        printf("Kehadiran dibatasi maksimal 14.\n");
    }

    printf("Sakit: ");
    scanf("%d", &sakit);

    printf("Alpha: ");
    scanf("%d", &alpha);

    // Operator Aritmatika
    sakit2 = sakit / 2;                     
    hasilAbsensi = hadir - sakit2 - alpha;  
    printf("\n=== Hasil Absensi ===\n");
    printf("Absensi dihitung (hadir - (sakit/2) - alpha) = %d\n", hasilAbsensi);

    // Operator Relasional
    if (hasilAbsensi <= 10) {  
        printf("Mahasiswa %sTIDAK BISA mengikuti ujian.\n", nama);
        return 0;
    }

    printf("Mahasiswa %sBISA mengikuti ujian.\n", nama);

    printf("\nMasukkan Nilai Ujian: ");
    scanf("%d", &ujian);

    persenAbsensi = (hasilAbsensi / 14.0) * 100;

    nilaiAkhir = (persenAbsensi * 0.2) + (ujian * 0.8);

    printf("\n=== Nilai Akhir ===\n");
    printf("Persentase Absensi = %.2f\n", persenAbsensi);
    printf("Nilai Akhir = (20%% Absensi + 80%% Ujian) = %.2f\n", nilaiAkhir);

    // Operator Logika
    if (hasilAbsensi > 10 && ujian >= 0) { 
        if (nilaiAkhir >= 70) {            
            printf("Mahasiswa %sDINYATAKAN LULUS.\n", nama);
        } else {
            printf("Mahasiswa %sDINYATAKAN TIDAK LULUS.\n", nama);
        }
    }
    // Operator Bitwise 
    printf("\n=== Operator Bitwise ===\n");
    printf("hadir & alpha = %d\n", hadir & alpha);   
    printf("hadir | alpha = %d\n", hadir | alpha);   
    printf("hadir ^ alpha = %d\n", hadir ^ alpha);   
    printf("hadir << 1   = %d\n", hadir << 1);       
    printf("alpha >> 1   = %d\n", alpha >> 1);       

    return 0;
}
