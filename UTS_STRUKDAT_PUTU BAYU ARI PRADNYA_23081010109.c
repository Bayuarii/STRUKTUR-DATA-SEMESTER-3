#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa {
    char nama[50];
    char jenis_kelamin;
    struct Mahasiswa* next;
};

struct Mahasiswa* buatMahasiswa(char nama[], char jenis_kelamin) {
    struct Mahasiswa* baru = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
    if (baru == NULL) {
        printf("Alokasi Memori Gagal!\n");
        exit(1);
    }
    strcpy(baru->nama, nama);
    baru->jenis_kelamin = jenis_kelamin;
    baru->next = NULL;
    return baru;
}

int hitungMahasiswi(struct Mahasiswa* head) {
    int count = 0;
    if (head == NULL) {
        return count;
    }
    struct Mahasiswa* temp = head;
    do {
        if (temp->jenis_kelamin == 'P') {
            count++;
        }
        temp = temp->next;
    } while (temp != head);
    return count;
}

void tambahMahasiswa(struct Mahasiswa** head, char nama[], char jenis_kelamin) {
    if (jenis_kelamin == 'P' && strcmp(nama, "Cindy") == 0) {
        int jumlahMahasiswi = hitungMahasiswi(*head);
        if (jumlahMahasiswi < 2) {
            printf("Cindy tidak dapat bergabung karena tidak ada cukup mahasiswi lainnya (minimal 2 mahasiswi untuk Cindy dapat bergabung).\n");
            getchar();
            return;
        }
    }

    struct Mahasiswa* baru = buatMahasiswa(nama, jenis_kelamin);

    if (*head == NULL) {
        *head = baru;
        (*head)->next = *head;
    } else {
        struct Mahasiswa* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = baru;
        baru->next = *head;
    }
}

void tampilkanLingkaran(struct Mahasiswa* head) {
    if (head == NULL) {
        printf("Lingkaran kosong tidak ada data.\n");
        return;
    }
    struct Mahasiswa* temp = head;
    do {
        printf("Nama: %s, Jenis Kelamin: %c\n", temp->nama, temp->jenis_kelamin);
        temp = temp->next;
    } while (temp != head);
}

void pisahkanLingkaran(struct Mahasiswa* head, struct Mahasiswa** lingkaranLaki, struct Mahasiswa** lingkaranPerempuan) {
    if (head == NULL) {
        printf("Lingkaran kosong, tidak ada yang bisa dipisahkan.\n");
        return;
    }

    struct Mahasiswa* temp = head;
    struct Mahasiswa* tailLaki = NULL;
    struct Mahasiswa* tailPerempuan = NULL;

    do {
        struct Mahasiswa* baru = buatMahasiswa(temp->nama, temp->jenis_kelamin);

        if (temp->jenis_kelamin == 'L') {
            if (*lingkaranLaki == NULL) {
                *lingkaranLaki = baru;
                tailLaki = baru;
            } else {
                tailLaki->next = baru;
                tailLaki = baru;
            }
            tailLaki->next = *lingkaranLaki;
        } else if (temp->jenis_kelamin == 'P') {
            if (*lingkaranPerempuan == NULL) {
                *lingkaranPerempuan = baru;
                tailPerempuan = baru;
            } else {
                tailPerempuan->next = baru;
                tailPerempuan = baru;
            }
            tailPerempuan->next = *lingkaranPerempuan;
        }

        temp = temp->next;
    } while (temp != head);
}

void hapusMahasiswa(struct Mahasiswa** head, char nama[]) {
    if (*head == NULL) {
        printf("Lingkaran kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    struct Mahasiswa *current = *head, *prev = NULL;
    int found = 0;

    do {
        if (strcmp(current->nama, nama) == 0) {
            found = 1;
            if (prev == NULL) {
                struct Mahasiswa* temp = *head;
                while (temp->next != *head) {
                    temp = temp->next;
                }
                temp->next = current->next;
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Mahasiswa %s telah dihapus.\n", nama);
            return;
        }
        prev = current;
        current = current->next;
    } while (current != *head);

    if (!found) {
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n", nama);
    }
}

void menuSetelahPemisahan(struct Mahasiswa* lingkaranLaki, struct Mahasiswa* lingkaranPerempuan) {
    int pilihan;
    do {
        printf("\nMenu Setelah Pemisahan Lingkaran:\n");
        printf("1. Tampilkan Lingkaran Untuk Mahasiswa Laki-Laki\n");
        printf("2. Tampilkan Lingkaran Untuk Mahasiswi Perempuan\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("\nLingkaran Mahasiswa Laki-Laki:\n");
                tampilkanLingkaran(lingkaranLaki);
                break;
            case 2:
                printf("\nLingkaran Mahasiswi Perempuan:\n");
                tampilkanLingkaran(lingkaranPerempuan);
                break;
            case 3:
                printf("Kembali ke menu utama\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

        if (pilihan == 1 || pilihan == 2) {
            printf("Tekan Enter untuk melanjutkan");
            getchar();
            getchar();
        }
    } while (pilihan != 3);
}

int main() {
    struct Mahasiswa* lingkaran = NULL;
    struct Mahasiswa* lingkaranLaki = NULL;
    struct Mahasiswa* lingkaranPerempuan = NULL;
    int pilihan;
    int count = 0;
    do {
        printf("1. Tambah Untuk Mahasiswa Laki-Laki\n");
        printf("2. Tambah Untuk Mahasiswi Perempuan\n");
        printf("3. Tampilkan Lingkaran\n");
        printf("4. Mahasiswa yang ingin keluar dari lingkaran\n");
        printf("5. Pisahkan Lingkaran\n");
        printf("6. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: {
                system("cls");
                if (count >= 20) {
                    printf("Jumlah maksimum mahasiswa telah tercapai (20 mahasiswa).\n");
                    break;
                }
                char nama[50];
                printf("Masukkan Nama Mahasiswa Laki-Laki: ");
                scanf("%s", nama);
                tambahMahasiswa(&lingkaran, nama, 'L');
                count++;
                break;
            }
            case 2: {
                system("cls");
                if (count >= 20) {
                    printf("Jumlah maksimum mahasiswa telah tercapai (20 mahasiswa).\n");
                    break;
                }
                char nama[50];
                printf("Masukkan Nama Mahasiswi Perempuan: ");
                scanf("%s", nama);
                tambahMahasiswa(&lingkaran, nama, 'P');
                count++;
                break;
            }
            case 3:
                system("cls");
                printf("\nLingkaran Saat Ini:\n");
                tampilkanLingkaran(lingkaran);
                break;
            case 4: {
                system("cls");
                char nama[50];
                printf("Masukkan Nama Mahasiswa yang Ingin Dihapus: ");
                scanf("%s", nama);
                hapusMahasiswa(&lingkaran, nama);
                count--;
                break;
            }
            case 5:
                system("cls");
                pisahkanLingkaran(lingkaran, &lingkaranLaki, &lingkaranPerempuan);
                menuSetelahPemisahan(lingkaranLaki, lingkaranPerempuan);
                break;
            case 6:
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 6);

    return 0;
}
