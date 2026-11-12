#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int saglik, enerji, oksijen, su, yedekParca, modulHasar;
int kilitMuhurlu = 0, gun = 1, tur = 0;
int firtinaTur, firtinaHasar;
int oyunaDevam = 1, turHarcandi;

void sinirla() {
  if (saglik < 0)
    saglik = 0;
  if (saglik > 100)
    saglik = 100;
  if (enerji < 0)
    enerji = 0;
  if (enerji > 100)
    enerji = 100;
  if (oksijen < 0)
    oksijen = 0;
  if (oksijen > 100)
    oksijen = 100;
  if (modulHasar < 0)
    modulHasar = 0;
  if (modulHasar > 100)
    modulHasar = 100;
}

int main(void) {

  srand(time(NULL));

  char secim;
  int gecerli;
  do {
    gecerli = 1;
    printf("Zorluk secin (K: Kolay, N: Normal, Z: Zor): ");
    scanf(" %c", &secim);
    switch (secim) {
    case 'K':
    case 'k':
      su = 10;
      yedekParca = 4;
      firtinaTur = 3;
      firtinaHasar = 5;
      oksijen = 100;
      saglik = 100;
      enerji = 100;
      modulHasar = 0;
      break;
    case 'N':
    case 'n':
      su = 6;
      yedekParca = 3;
      firtinaTur = 5;
      firtinaHasar = 10;
      oksijen = 100;
      saglik = 100;
      enerji = 100;
      modulHasar = 0;
      break;
    case 'Z':
    case 'z':
      su = 3;
      yedekParca = 1;
      firtinaTur = 7;
      firtinaHasar = 15;
      oksijen = 80;
      saglik = 100;
      enerji = 100;
      modulHasar = 0;
      break;
    default:
      printf("Gecersiz bir secim yaptiniz! \n");
      gecerli = 0;
    }

  } while (gecerli == 0);
}
