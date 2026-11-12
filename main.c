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
  char komut;
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
  do {
    turHarcandi = 1;

    printf("\n--- Gun: %d/15 | Tur: %d ---\n", gun, tur);
    printf("Komut (G,O,T,D,U,K,H,Q): ");
    scanf(" %c", &komut);

    switch (komut) {

    case 'd':
    case 'D':
      // buraya durum raporu gelcek
      printf("Durum raporu testi");
      turHarcandi = 0;
      break;

    case 'U':
    case 'u':
      if (enerji < 100) {
        enerji += 25;
        oksijen -= 5;
        printf("Bu gece uyuyorsun\n");
        if (oksijen < 20) {
          saglik -= 5;
          printf("Bogularak uyandin!\n");
          printf("Saglik -5\n");
          printf("Oksijen az!\n");
        } else {
          saglik += 5;
          printf("Dinlendin ve canin artti! \n");
          printf("Saglik +5\n");
        }
      } else {
        printf("Enerjin tamamen dolu uyuyamiyorsun! \n");
        turHarcandi = 0;
      }
      break;

    case 'q':
    case 'Q':
      oyunaDevam = 0;
      turHarcandi = 0;
      break;
    default:
      printf("Tanimsiz komut!\n");
      turHarcandi = 0;
    }
    if (turHarcandi == 1) {
      tur++;
      if (tur % 3 == 0) {
        gun++;
        oksijen -= 8;
        if (modulHasar > 70)
          saglik -= 5;
      }
    }

    sinirla();

    if (saglik <= 0 || oksijen <= 0) {
      printf("Kaybettin!\n");
      oyunaDevam = 0;
    } else if (gun > 15) {
      printf("Kurtarma ekibi geldi! Kazandin! \n");
      oyunaDevam = 0;
    }
  } while (oyunaDevam == 1);
  return 0;
}
