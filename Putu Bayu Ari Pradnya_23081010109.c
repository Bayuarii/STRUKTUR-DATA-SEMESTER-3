#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
	int data;
    struct node *next;
};
typedef struct node node;

//node *createNode(void);
void tambahAwal(node **head);
void tambahData(node **head);
void tranverse(node *head);
void tambahAkhir (node **head);
void hapusAwal (node **head);
void hapusTengah (node **head);
void hapusAkhir (node **head);
void cariData (node *head);
void jumlahData (node *head);
void jumlahtotalData (node *head);


//Kode untuk menambahkan nodenyaaa memakai struct
//========================================================

int main()
{
  node *head;
  char pilih;

  head = NULL;
  do{
     system("cls");
     printf("masukkan pilihan\n");
     printf("1. tambah data di awal\n");
     printf("2. tambah data di tengah list\n");
     printf("3. tambah data di akhir list\n");
     printf("4. menghapus data di awal\n");
     printf("5. menghapus data di tengah\n");
     printf("6. menghapus data di akhir\n");
     printf("7. mencari data\n");
     printf("8. menampilkan informasi jumlah data\n");
     printf("9. menampilkan hasil penjumlahan seluruh data\n");
     printf("0. cetak isi list\n");
     printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
     fflush(stdin);
     scanf("%c", &pilih);
     if (pilih == '1')
     		tambahAwal(&head);
     else if (pilih == '2')
			tambahData(&head);
     else if (pilih == '3')
            tambahAkhir(&head);
     else if (pilih == '4')
            hapusAwal (&head);
     else if (pilih == '5')
            hapusTengah (&head);
     else if (pilih == '6')
            hapusAkhir (&head);
     else if (pilih == '7')
            cariData (head);
     else if (pilih == '8')
            jumlahData (head);
     else if (pilih == '9')
            jumlahtotalData (head);
     else if (pilih == '0'){
     		tranverse(head);
         getch();
     }
  } while (pilih != 'q');

  return 0;
}

//========================================================

/*node *createNode(void){
  node *ptr;

  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}*/

//========================================================
//KODE UNTUK MENAMBAHKAN DATA DI AWAL
void tambahAwal(node **head){
  int bil;
  node *pNew;

  system("cls");
  fflush(stdin);
  printf("masukkan bilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node)); //mengakolokasikan memori untuk node baru

  if (pNew != NULL){//memerikasa jika pnew tidak null maka memori berhasil dialokasikan
  	  pNew->data = bil; //mengisi node baru dengan bilangan yang kita inputkan
      pNew->next = NULL; // karna node baru dan diawal maka kita isi dengan pnew next = null
      //add before first logical node or to an empty list
	  pNew -> next = *head; //menuju ke head karna ini akan menuju node pertama karnakita mengisi bil pertama
      *head = pNew; //head mengatur node baru agar menjadi node pertama
  }
  else{
      printf("Alokasi memori gagal");
      getch();
  }
}

//========================================================
//KODE UNTUK MENAMBAHKAN DATA DI TENGAH
void tambahData(node **head){
  int pos, bil;
  node *pNew, *pCur;

  system("cls");
  tranverse(*head);
  printf("\nposisi penyisipan setelah data bernilai : ");
  fflush(stdin);
  scanf("%d", &pos);
  printf("\nbilangan : ");
  fflush(stdin);
  scanf("%d", &bil);

  pCur = *head;
  while (pCur != NULL && pCur -> data != pos) {
    pCur = pCur -> next;
  }

  pNew = (node *)malloc(sizeof(node));

  if (pCur == NULL){
     printf("\nnode tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){
     printf("\nalokasi memeori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = NULL;
     pNew -> next = pCur -> next;
     pCur -> next = pNew;
  }
}

//========================================================
// KODE UNTUK MENCETAK ISI LIST
void tranverse(node *head){
   //traverse a linked list
	node *pWalker;

   system("cls");
	pWalker = head;
	while (pWalker != NULL){
   	printf("%d\t", pWalker -> data);
   	pWalker = pWalker -> next;
      printf(" -> ");
	}
   printf("NULL");
}

//========================================================
//KODE UNTUK MENAMBAHKAN DATA DI AKHIR
void tambahAkhir(node **head){
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL){
        pNew->data = bil;
        pNew->next = NULL;


        if (*head == NULL) {
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================
//KODE UNTUK MENGHAPUS DATA DI AWAL
void hapusAwal (node **head){
    node *pDel;
    pDel = *head;
    *head = (*head)->next;
    free(pDel);
    printf("Node di awal berhasil dihapus");
    getch();
}

//========================================================
//KODE UNTUK MENGHAPUS DATA DI TENGAH
void hapusTengah(node **head) {
    int target,pos;
    node *pCur, *pPrev;

    system("cls");
    tranverse(*head);
    printf("\nposisi penghapusan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &target);

    pCur = *head;
    pPrev = NULL;
    while (pCur != NULL && pCur->data != target) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Node dengan data %d tidak ditemukan\n", target);
    } else {
        pPrev->next = pCur->next;
        free(pCur);
        printf("Node dengan data %d berhasil dihapus\n", target);
    }

    getch();
}

//========================================================
//KODE UNTUK MENGHAPUS DATA DI AKHIR
void hapusAkhir (node **head){
     node *pCur, *pPrev;
     system("cls");

     pCur = *head;
     pPrev = NULL;

     while (pCur->next != NULL) {
        pPrev = pCur;
        pCur = pCur->next;
    }

    free(pCur);
    pPrev->next = NULL;
    printf("Node terakhir berhasil dihapus\n");

    getch();
}

//========================================================
//KODE UNTUK MENCARI DATA
void cariData(node *head) {
    int target, posisi = 1;
    node *pCur;

    system("cls");
    printf("Masukkan nilai data yang ingin dicari: ");
    fflush(stdin);
    scanf("%d", &target);
    pCur = head;


    while (pCur != NULL) {
        if (pCur->data == target) {
            printf("Data %d ditemukan pada posisi %d\n", target, posisi);
            getch();
            return;
        }
        pCur = pCur->next;
        posisi++;
    }

    printf("Data %d tidak ditemukan dalam linked list\n", target);
    getch();
}

//========================================================
//KODE UNTUK MENAMPILKAN JUMLAH DATA YANG ADA
void jumlahData(node *head) {
    int count = 0;
    system("cls");
    node *pCur = head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }

    printf("Jumlah data dalam linked list: %d\n", count);
    getch();
}

//========================================================
//KODE UNTUK MENJUMLAHKAN TOTAL DATA
void jumlahtotalData(node *head) {
    int total = 0;
    system("cls");
    node *pCur = head;
    while (pCur != NULL) {
        total += pCur->data;
        pCur = pCur->next;
    }
    printf("Hasil penjumlahan semua data di linked list: %d\n", total);
    getch();
}










