/* NIM/Nama : 13517101/Jeremy Arden Hartono
   Tanggal : 24 Oktober 2018
   Topik : ADT List Linier
   Deskripsi : membuat ADT list linier
*/

#include "boolean.h"
#include "listlinier.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong */
{
  return (First(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
  First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  address P;

  P = (address) malloc (sizeof(ElmtList));

  if(P != Nil)
  {
    Info(P) = X;
    Next(P) = Nil;
    return P;
  }
  else
  {
    return Nil;
  }
}
void Dealokasi (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
  free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
  address P;

  P = First(L);
  while(Next(P) != Nil && Info(P) != X)
  {
    P = Next(P);
  }

  if (Info(P) == X)
  {
    return P;
  }
  else
  {
    return Nil;
  }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
  address P;

  P = Alokasi(X);
  if (P != Nil)
  {
    if (!IsEmpty(*L))
    {
      Next(P) = First(*L);
    }
    First(*L) = P;
  }
}
void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
  address P, P1;

  P = Alokasi(X);
  if (P != Nil)
  {
    if(IsEmpty(*L))
    {
      InsVFirst(L, X);
    }
    else
    {
      P1 = First(*L);
      while (Next(P1) != Nil)
      {
        P1 = Next(P1);
      }
      Next(P1) = P ;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
  address P;

  *X = Info(First(*L));
  P = First(*L);
  First(*L) = Next(First(*L));
  Dealokasi(&P);
}
void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
  address Last, Prec;

  Last = First(*L);
  Prec = Nil;
  while(Next(Last) != Nil)
  {
    Prec = Last;
    Last = Next(Last);
  }

  if (Prec == Nil)
  {
    First(*L) = Nil;
  }
  else
  {
    Next(Prec) = Nil;
  }
  *X = Info(Last);
  Dealokasi(&Last);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
  Next(P) = First(*L);
  First(*L) = P;
}
void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
  Next(P) = Next(Prec);
  Next(Prec) = P;
}
void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
  address Last;

  if (IsEmpty(*L))
  {
    InsertFirst(L, P);
  }
  else
  {
    Last = First(*L);
    while(Next(Last) != Nil)
    {
      Last = Next(Last);
    }

    Next(P) = Nil;
    Next(Last) = P;
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
  *P = First(*L);
  First(*L) = Next(First(*L));
  Next(*P) = Nil;
}
void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
  address P, Prec;

  if (!IsEmpty(*L))
  {
    P = First(*L);
    Prec = Nil;
    while(Info(P) != X && Next(P) != Nil)
    {
      Prec = P;
      P = Next(P);
    }

    if (Info(P) == X)
    {
      if (Prec == Nil)
      {
        First(*L) = Next(First(*L));
      }
      else
      {
        Next(Prec) = Next(P);
      }

      Dealokasi(&P);
    }
  }
}
void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
  address Last, Prec;

  Last = First(*L);
  Prec = Nil;
  while(Next(Last) != Nil)
  {
    Prec = Last;
    Last = Next(Last);
  }

  *P = Last;
  if (Prec == Nil)
  {
    First(*L) = Nil;
  }
  else
  {
    Next(Prec) = Nil;
  }
  Next(*P) = Nil;
}
void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
  *Pdel = Next(Prec);
  Next(Prec) = Next(Next(Prec));
  Next(*Pdel) = Nil;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
  address P;

  P = First(L);
  if(Next(P) == Nil)
  {
    printf("[%d]", Info(P));
  }
  else
  {
    printf("[");
    while(Next(P) != Nil)
    {
      printf("%d,", Info(P));
      P = Next(P);
    }
    printf("%d]", Info(P));
  }
}
int NbElmt (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
  int Count;
  address P;

  if (IsEmpty(L))
  {
    return 0;
  }
  else
  {
    P = First(L);
    Count = 1;
    while(Next(P) != Nil)
    {
      P = Next(P);
      Count++;
    }

    return Count;
  }
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max (List L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
  address P;
  infotype infoMax;

  P = First(L);
  infoMax = Info(P);
  while(P != Nil)
  {
    if (Info(P) > infoMax)
    {
      infoMax = Info(P);
    }
    P = Next(P);
  }

  return infoMax;
}
/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
  infotype X;

  CreateEmpty(L3);
  if (IsEmpty(*L1))
  {
    while(!IsEmpty(*L2))
    {
      DelVFirst(L2, &X);
      InsVLast(L3, X);
    }
  }
  else if (IsEmpty(*L2))
  {
    while(!IsEmpty(*L1))
    {
      DelVFirst(L1, &X);
      InsVLast(L3, X);
    }
  }
  else if ((!IsEmpty(*L1)) && (!IsEmpty(*L2)))
  {
    while(!IsEmpty(*L1))
    {
      DelVFirst(L1, &X);
      InsVLast(L3, X);
    }

    while(!IsEmpty(*L2))
    {
      DelVFirst(L2, &X);
      InsVLast(L3, X);
    }
  }
}
