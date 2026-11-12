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
  if (su < 0)
    su = 0;
  if (yedekParca < 0)
    yedekParca = 0;
}

int main(void) {

  srand(time(NULL));

  char secim;
  char komut;
  int gecerli;

  // zorluk
  do {
    gecerli = 1;
    printf("Zorluk seçin (K: Kolay, N: Normal, Z: Zor): ");
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
      printf("Geçersiz bir seçim yaptınız!\n");
      gecerli = 0;
    }
  } while (gecerli == 0);

  // ana dongu
  do {
    turHarcandi = 1;

    printf("\n--- Gün: %d/15 | Tur: %d ---\n", gun, tur);
    printf("Komut (G: Keşif, O: Oksijen üret, T: Tamir, D: Durum, U: Uyu, "
           "K: Kum fırtınası, H: Hava kilidi, Q: Çıkış): ");
    scanf(" %c", &komut);

    switch (komut) {

    // durum raporu
    case 'd':
    case 'D':
      printf("\n===== DURUM RAPORU =====\n");
      printf("Sağlık: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji,
             oksijen);
      printf("Su: %d | Yedek parça: %d | Modül hasarı: %d\n", su, yedekParca,
             modulHasar);
      printf("Hava kilidi: %s\n", kilitMuhurlu == 1 ? "Mühürlü" : "Mühürsüz");
      // hepsi icin ayri uyari
      if (oksijen < 25)
        printf("UYARI: Oksijen kritik seviyede!\n");
      if (saglik < 30)
        printf("UYARI: Sağlık kritik seviyede!\n");
      if (modulHasar > 70)
        printf("UYARI: Modül hasarı çok yüksek!\n");
      if (enerji < 20)
        printf("UYARI: Enerji kritik seviyede!\n");
      if (saglik >= 30 && oksijen >= 25 && modulHasar <= 70 && enerji >= 20)
        printf("TÜM SİSTEMLER NORMAL\n");
      turHarcandi = 0;
      break;

    // uyuma
    case 'U':
    case 'u':
      if (enerji < 100) {
        enerji += 25;
        oksijen -= 5;
        printf("Bu gece uyuyorsun... Enerji +25, Oksijen -5\n");
        if (oksijen < 20) {
          saglik -= 5;
          printf("Oksijen az olduğu için boğularak uyandın! Sağlık -5\n");
        } else {
          saglik += 5;
          printf("Dinlendin ve canın arttı! Sağlık +5\n");
        }
      } else {
        printf("Enerjin tamamen dolu, uyuyamıyorsun!\n");
        turHarcandi = 0;
      }
      break;

    // kesif
    case 'G':
    case 'g': {
      int zar1, zar2, esik;

      if (enerji < 15) {
        printf("Keşif için yeterli enerjin yok! Komut iptal edildi.\n");
        turHarcandi = 0;
        break;
      }
      enerji -= 15;
      oksijen -= 10;
      printf("Keşfe çıktın... Enerji -15, Oksijen -10\n");

      zar1 = rand() % 100; // yaralanma
      zar2 = rand() % 100; // bulgu

      if (enerji > 40 && oksijen > 30)
        esik = 50;
      else
        esik = 25;

      // yaralnma kontrolu
      if (zar1 < 10 || modulHasar > 70) {
        saglik -= 10;
        printf(
            "Yaralanma zarı -> Zar: %d / Eşik: 10 | Yaralandın! Sağlık -10\n",
            zar1);
      } else {
        printf("Yaralanma zarı -> Zar: %d / Eşik: 10 | Yara almadın.\n", zar1);
      }

      // kesif sonucu
      printf("Bulgu zarı -> Zar: %d / Eşik: %d -> %s\n", zar2, esik,
             zar2 < esik ? "BAŞARILI" : "BAŞARISIZ");
      if (zar2 < esik) {
        su += 3;
        printf("Su kaynağı buldun! Su +3\n");
      } else if (zar2 < esik + 20) {
        yedekParca += 1;
        printf("Yedek parça buldun! Yedek parça +1\n");
      } else {
        printf("Eli boş döndün.\n");
      }
      break;
    }

    // oksijen uretme
    case 'O':
    case 'o': {
      int miktar, cevrilen;

      if (enerji < 10) {
        printf("Oksijen üretmek için yeterli enerjin yok! Komut iptal "
               "edildi.\n");
        turHarcandi = 0;
        break;
      }
      printf("Kaç birim su harcayacaksın? (Mevcut su: %d): ", su);
      scanf("%d", &miktar);

      if (miktar < 2 || miktar > su) {
        printf("Geçersiz miktar! En az 2, en çok mevcut su kadar girebilirsin. "
               "Komut iptal edildi.\n");
        turHarcandi = 0;
        break;
      }
      cevrilen = miktar - (miktar % 2); // tekse 1 birim artık kalır
      oksijen += (cevrilen / 2) * 3;    // 2 su = 3 oksijen
      su -= cevrilen;
      enerji -= 10;
      printf("%d su harcandı, Oksijen +%d, Enerji -10.\n", cevrilen,
             (cevrilen / 2) * 3);
      if (miktar % 2 == 1)
        printf("1 birim su artık olarak depoda kaldı.\n");
      break;
    }

    // tamir
    case 'T':
    case 't': {
      int gerekenParca, onarilan;

      if (yedekParca <= 0) {
        printf("Yedek parçan yok, tamir yapılamaz!\n");
        turHarcandi = 0;
        break;
      }
      if (enerji < 10) {
        printf("Tamir için yeterli enerjin yok! Komut iptal edildi.\n");
        turHarcandi = 0;
        break;
      }
      if (modulHasar == 0) {
        printf("Modülde hasar yok, tamire gerek yok.\n");
        turHarcandi = 0;
        break;
      }

      // hasara gore duzelen kisim degisiyo
      if (modulHasar <= 30) {
        gerekenParca = 1;
        onarilan = 15;
        printf("Hafif hasar: ");
      } else if (modulHasar <= 70) {
        gerekenParca = 2;
        onarilan = 25;
        printf("Orta hasar: ");
      } else {
        gerekenParca = 3;
        onarilan = 35;
        printf("Ağır hasar: ");
      }

      if (yedekParca < gerekenParca) {
        printf("Bu kademe için %d parça gerekli, yetersiz parça! Komut iptal "
               "edildi.\n",
               gerekenParca);
        turHarcandi = 0;
        break;
      }
      yedekParca -= gerekenParca;
      modulHasar -= onarilan;
      enerji -= 10;
      printf("%d parça harcandı, Modül hasarı -%d, Enerji -10.\n", gerekenParca,
             onarilan);
      break;
    }

    // kum firtinasi
    case 'K':
    case 'k': {
      int hasarliTur = 0, topSaglik = 0, topOksijen = 0, topModul = 0;

      printf("\nKUM FIRTINASI BAŞLADI! (%d tur)\n", firtinaTur);
      for (int i = 1; i <= firtinaTur; i++) {
        int zar = rand() % 100;
        int hasar = firtinaHasar;

        if (modulHasar > 70)
          zar -= 15;
        if (i % 2 == 0) {
          hasar *= 2;
          printf("Tur %d (rüzgar şiddetli): ", i);
        } else {
          printf("Tur %d: ", i);
        }
        printf("Zar: %d / Eşik: 75 -> ", zar);

        if (zar < 25) {
          saglik -= hasar;
          topSaglik += hasar;
          hasarliTur++;
          printf("Savruldun! Sağlık -%d\n", hasar);
        } else if (zar < 50) {
          if (kilitMuhurlu == 1) {
            printf("Hava kilidi mühürlü, oksijen sızıntısı engellendi.\n");
            continue;
          }
          oksijen -= hasar;
          topOksijen += hasar;
          hasarliTur++;
          printf("Oksijen sızıntısı! Oksijen -%d\n", hasar);
        } else if (zar < 75) {
          modulHasar += hasar;
          topModul += hasar;
          hasarliTur++;
          printf("Modül hasar aldı! Modül hasarı +%d\n", hasar);
        } else {
          printf("Fırtınadan zarar görmeden korundun.\n");
        }

        sinirla();
        if (saglik <= 0 || oksijen <= 0) {
          printf("Fırtınada hayati değerlerin tükendi!\n");
          break;
        }
      }
      printf("--- Fırtına özeti ---\n");
      printf("Hasar alınan tur: %d | Kaybedilen sağlık: %d | Kaybedilen "
             "oksijen: %d | Modül hasarı: +%d\n",
             hasarliTur, topSaglik, topOksijen, topModul);
      break;
    }

    // hava kilidi sifresi
    case 'H':
    case 'h': {
      char sifre, girilen;
      int deneme = 0;

      if (kilitMuhurlu == 1) {
        printf("Hava kilidi zaten mühürlü.\n");
        turHarcandi = 0;
        break;
      }
      if (enerji < 5) {
        printf("Şifre denemek için yeterli enerjin yok! Komut iptal "
               "edildi.\n");
        turHarcandi = 0;
        break;
      }
      sifre = 'A' + (gun % 26);
      printf("İpucu: Şifre, alfabede A harfinden bugünün gün sayısı kadar "
             "ilerideki harftir.\n");
      do {
        printf("Şifre (%d. deneme): ", deneme + 1);
        scanf(" %c", &girilen);
        if (girilen >= 'a' && girilen <= 'z') // kucuk harfi buyuge cevir
          girilen = girilen - 32;
        deneme++;
        if (girilen != sifre) {
          enerji -= 5;
          printf("Yanlış! Enerji -5. ");
          if (girilen < sifre)
            printf("İleri git.\n");
          else
            printf("Geri git.\n");
        }
      } while (girilen != sifre && deneme < 3);

      if (girilen == sifre) {
        kilitMuhurlu = 1;
        printf("Doğru şifre! Hava kilidi mühürlendi.\n");
      } else {
        modulHasar += 20;
        printf("3 deneme de başarısız! Modül hasarı +20.\n");
      }
      break;
    }

    // cikis
    case 'q':
    case 'Q':
      printf("Simülasyondan çıkılıyor...\n");
      oyunaDevam = 0;
      turHarcandi = 0;
      break;

    default:
      printf("Tanımsız komut!\n");
      turHarcandi = 0;
    }

    // zaman akisi
    if (turHarcandi == 1) {
      tur++;
      if (tur % 3 == 0) {
        gun++;
        oksijen -= 8;
        printf("\n*** Yeni gün başladı: %d. gün. Oksijen -8 ***\n", gun);
        if (modulHasar > 70) {
          saglik -= 5;
          printf("Modül hasarı yüksek, Sağlık -5\n");
        }
      }
    }

    sinirla();

    // oyun sonu kontrolu
    if (saglik <= 0 || oksijen <= 0) {
      printf("\nKAYBETTİN! Sağlığın ya da oksijenin tükendi.\n");
      oyunaDevam = 0;
    } else if (gun > 15) {
      printf("\nKurtarma ekibi geldi! KAZANDIN!\n");
      oyunaDevam = 0;
    }
  } while (oyunaDevam == 1);

  // sonuc raporu
  if (gun > 15)
    gun = 15;
  int puan = (gun * 100) + saglik + oksijen - modulHasar;
  printf("\n===== SONUÇ RAPORU =====\n");
  printf("Hayatta kalınan gün: %d\n", gun);
  printf("Toplam tur: %d\n", tur);
  printf("Sağlık: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
  printf("Su: %d | Yedek parça: %d | Modül hasarı: %d\n", su, yedekParca,
         modulHasar);
  printf("PUAN: %d\n", puan);
  return 0;
}
