/*
 * Mars Kolonisi Yaşam Destek Simülatörü
 * C ile metin tabanlı, tek karakterli komutlarla kontrol edilen oyun.
 * Hedef: kurtarma ekibi gelene kadar (15 gün) hayatta kalmak.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Durum değişkenleri ---------- */
int saglik, enerji, oksijen, su, yedekParca, modulHasar;
int kilitMuhurlu = 0, gun = 1, tur = 0;

/* Zorluk seviyesine göre atanan değerler */
int firtinaTur, firtinaHasar, kesifEsik;

/* Ana döngü bayrakları */
int oyunaDevam = 1, turHarcandi;

/* ---------- Yardımcı fonksiyonlar ---------- */

/* Sağlık, enerji, oksijen ve modül hasarını 0-100 aralığında tutar.
   Su ve yedek parça için yalnızca 0'ın altı engellenir. */
void sinirla(void) {
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

/* Bir satırdan tek karakterlik giriş okur.
   - Baştaki boşluk ve boş satırlar atlanır.
   - Satırın kalanı tampondan temizlenir (taşan girişler sonraki komutu bozmaz).
   - Birden fazla karakter girilirse '?' döner (tanımsız/geçersiz sayılır).
   - Giriş sonu (EOF) durumunda EOF döner. */
int karakterOku(void) {
  int c, ilk, fazla = 0;

  do {
    c = getchar();
  } while (c == ' ' || c == '\t' || c == '\r' || c == '\n');
  if (c == EOF)
    return EOF;

  ilk = c;
  c = getchar();
  while (c != '\n' && c != EOF) {
    if (c != ' ' && c != '\t' && c != '\r')
      fazla = 1;
    c = getchar();
  }
  if (fazla == 1)
    return '?';
  return ilk;
}

/* Bir satırdan tam sayı okur. Sayı değilse -1 döner. */
int sayiOku(void) {
  char tampon[32];
  int n;

  if (fgets(tampon, sizeof(tampon), stdin) == NULL)
    return -1;
  if (sscanf(tampon, "%d", &n) != 1)
    return -1;
  return n;
}

int main(void) {
  int secim, komut;
  int gecerli;

  srand(time(NULL));

  printf("=== MARS KOLONİSİ YAŞAM DESTEK SİMÜLATÖRÜ ===\n");
  printf("Kurtarma ekibi gelene kadar 15 gün hayatta kal!\n\n");

  /* ---------- Zorluk seçimi (do-while + switch-case) ---------- */
  do {
    gecerli = 1;
    printf("Zorluk seçin (K: Kolay, N: Normal, Z: Zor): ");
    secim = karakterOku();
    if (secim == EOF)
      return 0;

    switch (secim) {
    case 'K':
    case 'k':
      su = 80;
      yedekParca = 4;
      oksijen = 100;
      firtinaTur = 3;
      firtinaHasar = 5;
      kesifEsik = 60;
      printf("Kolay seviye seçildi.\n");
      break;
    case 'N':
    case 'n':
      su = 65;
      yedekParca = 4;
      oksijen = 100;
      firtinaTur = 5;
      firtinaHasar = 10;
      kesifEsik = 50;
      printf("Normal seviye seçildi.\n");
      break;
    case 'Z':
    case 'z':
      su = 85;
      yedekParca = 3;
      oksijen = 80;
      firtinaTur = 7;
      firtinaHasar = 15;
      kesifEsik = 40;
      printf("Zor seviye seçildi.\n");
      break;
    default:
      printf("Geçersiz zorluk seviyesi! Lütfen K, N veya Z girin.\n");
      gecerli = 0;
    }
  } while (gecerli == 0);

  saglik = 100;
  enerji = 100;
  modulHasar = 0;

  /* ---------- Ana komut döngüsü (do-while) ---------- */
  do {
    turHarcandi = 1;

    printf("\n--- Gün: %d/15 | Tur: %d ---\n", gun, tur);
    printf("Komut (G: Keşif, O: Oksijen üret, T: Tamir, D: Durum, U: Uyu, "
           "K: Kum fırtınası, H: Hava kilidi, Q: Çıkış): ");
    komut = karakterOku();
    if (komut == EOF)
      komut = 'Q'; /* giriş bittiyse güvenli çıkış */

    switch (komut) {

    /* ===== D: Durum raporu (tur harcamaz) ===== */
    case 'd':
    case 'D':
      printf("\n===== DURUM RAPORU =====\n");
      printf("Sağlık: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji,
             oksijen);
      printf("Su: %d | Yedek parça: %d | Modül hasarı: %d\n", su, yedekParca,
             modulHasar);
      printf("Hava kilidi: %s\n", kilitMuhurlu == 1 ? "Mühürlü" : "Mühürsüz");
      /* Her kritik değer için ayrı uyarı (else if değil, hepsi bağımsız) */
      if (oksijen < 25)
        printf("UYARI: Oksijen kritik seviyede!\n");
      if (saglik < 30)
        printf("UYARI: Sağlık kritik seviyede!\n");
      if (modulHasar > 70)
        printf("UYARI: Modül hasarı çok yüksek!\n");
      if (enerji < 20)
        printf("UYARI: Enerji kritik seviyede!\n");
      /* Tüm değerler güvenliyse tek bir && koşulu */
      if (oksijen >= 25 && saglik >= 30 && modulHasar <= 70 && enerji >= 20)
        printf("TÜM SİSTEMLER NORMAL\n");
      turHarcandi = 0;
      break;

    /* ===== U: Uyu / dinlen ===== */
    case 'U':
    case 'u':
      if (enerji < 100 || saglik < 100) {
        enerji += 25;
        oksijen -= 1;
        printf("Dinleniyorsun... Enerji +25, Oksijen -1\n");
        if (oksijen < 20) { /* iç içe if: oksijen yetersizse sağlık düşer */
          saglik -= 5;
          printf("Oksijen az olduğu için nefes alamadın! Sağlık -5\n");
        } else {
          saglik += 5;
          printf("Dinlendin, iyileştin! Sağlık +5\n");
        }
      } else {
        printf("Enerjin ve sağlığın tamamen dolu, dinlenmene gerek yok! "
               "Komut iptal edildi.\n");
        turHarcandi = 0;
      }
      break;

    /* ===== G: Keşif ===== */
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

      zar1 = rand() % 100; /* yaralanma zarı */
      zar2 = rand() % 100; /* bulgu zarı */

      /* Enerji ve oksijen yüksekse bulgu eşiği yüksek, değilse düşük */
      if (enerji > 40 && oksijen > 30)
        esik = kesifEsik;
      else
        esik = kesifEsik / 2;

      /* Yaralanma: düşük zar VEYA yüksek modül hasarı */
      if (zar1 < 10 || modulHasar > 70) {
        saglik -= 10;
        if (zar1 < 10)
          printf("Yaralanma zarı -> Zar: %d / Esik: 10 -> YARALANDIN! "
                 "Sağlık -10\n",
                 zar1);
        else
          printf("Yaralanma zarı -> Zar: %d / Esik: 10 -> Zar güvenli ama "
                 "modül hasarı (%d) çok yüksek, yaralandın! Sağlık -10\n",
                 zar1, modulHasar);
      } else {
        printf("Yaralanma zarı -> Zar: %d / Esik: 10 -> Yara almadın.\n", zar1);
      }

      /* Keşif sonucu: 3 farklı sonuç */
      printf("Bulgu zarı -> Zar: %d / Esik: %d -> %s\n", zar2, esik,
             zar2 < esik ? "BASARILI" : "BASARISIZ");
      if (zar2 < esik) {
        su += 6;
        printf("Su kaynağı buldun! Su +6\n");
      } else if (zar2 < esik + 20) {
        yedekParca += 1;
        printf("Yedek parça buldun! Yedek parça +1\n");
      } else {
        printf("Eli boş döndün.\n");
      }
      break;
    }

    /* ===== O: Oksijen üretimi ===== */
    case 'O':
    case 'o': {
      int miktar, cevrilen, maksSu, uretilen;

      if (enerji < 10) {
        printf("Oksijen üretmek için yeterli enerjin yok! Komut iptal "
               "edildi.\n");
        turHarcandi = 0;
        break;
      }
      if (oksijen >= 100) {
        printf("Oksijen deposu zaten dolu! Komut iptal edildi.\n");
        turHarcandi = 0;
        break;
      }
      if (su < 2) {
        printf("Oksijen üretmek için en az 2 su gerekli! Komut iptal "
               "edildi.\n");
        turHarcandi = 0;
        break;
      }

      /* Oksijeni 100'ü aşırmayacak en büyük su miktarı (2 su = 3 oksijen) */
      maksSu = ((100 - oksijen + 2) / 3) * 2;
      if (maksSu > su)
        maksSu = su;

      printf(
          "Kaç birim su harcayacaksın? (Mevcut su: %d, en az 2, en çok %d): ",
          su, maksSu);
      miktar = sayiOku();

      if (miktar < 2) {
        printf("Geçersiz miktar! En az 2 birim girmelisin. Komut iptal "
               "edildi.\n");
        turHarcandi = 0;
        break;
      }
      if (miktar > su) {
        printf("Mevcut sudan (%d) fazla giremezsin! Komut iptal edildi.\n", su);
        turHarcandi = 0;
        break;
      }
      if (miktar > maksSu) {
        printf("Bu miktar oksijeni 100'ün üstüne çıkarır! En fazla %d girin. "
               "Komut iptal edildi.\n",
               maksSu);
        turHarcandi = 0;
        break;
      }

      cevrilen = miktar - (miktar % 2); /* tekse 1 birim artık kalır */
      uretilen = (cevrilen / 2) * 3;    /* 2 su = 3 oksijen */
      oksijen += uretilen;
      su -= cevrilen;
      enerji -= 10;
      printf("%d su harcandı, Oksijen +%d, Enerji -10.\n", cevrilen, uretilen);
      if (miktar % 2 == 1)
        printf("1 birim su artık olarak depoda kaldı.\n");
      break;
    }

    /* ===== T: Tamir ===== */
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
        printf("Modülde hasar yok, tamire gerek yok. Komut iptal edildi.\n");
        turHarcandi = 0;
        break;
      }

      /* Hasar kademesine göre harcanan parça ve onarım değişir */
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

    /* ===== K: Kum fırtınası (for döngüsü) ===== */
    case 'K':
    case 'k': {
      int hasarliTur = 0, topSaglik = 0, topOksijen = 0, topModul = 0;
      int i;

      printf("\nKUM FIRTINASI BAŞLADI! (%d tur)\n", firtinaTur);
      for (i = 1; i <= firtinaTur; i++) {
        int zar = rand() % 100;
        int etkin = zar;
        int hasar = firtinaHasar;

        /* Oyuncunun durumuna bağlılık: modül zayıfsa kötü olay ihtimali artar
         */
        if (modulHasar > 70)
          etkin = zar - 15;

        /* Çift numaralı turlarda rüzgar şiddetlenir, hasar iki katı */
        if (i % 2 == 0) {
          hasar *= 2;
          printf("Tur %d (rüzgar şiddetli): ", i);
        } else {
          printf("Tur %d: ", i);
        }

        if (etkin != zar)
          printf("Zar: %d (hasarlı modül nedeniyle etkin: %d) / Esikler: "
                 "25-50-75 -> ",
                 zar, etkin);
        else
          printf("Zar: %d / Esikler: 25-50-75 -> ", zar);

        if (etkin < 25) {
          saglik -= hasar;
          topSaglik += hasar;
          hasarliTur++;
          printf("Savruldun! Sağlık -%d\n", hasar);
        } else if (etkin < 50) {
          if (kilitMuhurlu == 1) {
            printf("Hava kilidi mühürlü, oksijen sızıntısı engellendi.\n");
            continue; /* bu tur için sızıntı olayı atlanır */
          }
          oksijen -= hasar;
          topOksijen += hasar;
          hasarliTur++;
          printf("Oksijen sızıntısı! Oksijen -%d\n", hasar);
        } else if (etkin < 75) {
          modulHasar += hasar;
          topModul += hasar;
          hasarliTur++;
          printf("Modül hasar aldı! Modül hasarı +%d\n", hasar);
        } else {
          printf("Fırtınadan zarar görmeden korundun.\n");
        }

        sinirla();
        if (saglik <= 0 || oksijen <= 0) {
          printf("Fırtınada hayati değerlerin tükendi! Fırtına kesildi.\n");
          break; /* karakter öldü, döngü derhal biter */
        }
      }

      printf("--- Fırtına özeti ---\n");
      printf("Hasar alınan tur: %d | Kaybedilen sağlık: %d | Kaybedilen "
             "oksijen: %d | Modül hasarı: +%d\n",
             hasarliTur, topSaglik, topOksijen, topModul);
      break;
    }

    /* ===== H: Hava kilidi şifresi (do-while) ===== */
    case 'H':
    case 'h': {
      int sifre, girilen, deneme = 0;

      if (kilitMuhurlu == 1) {
        printf("Hava kilidi zaten mühürlü. Komut iptal edildi.\n");
        turHarcandi = 0;
        break;
      }
      if (enerji < 5) {
        printf("Şifre denemek için yeterli enerjin yok! Komut iptal "
               "edildi.\n");
        turHarcandi = 0;
        break;
      }

      sifre = 'A' + (gun % 26); /* şifre günden türetilir */
      printf("İpucu: Şifre, alfabede A harfinden bugünün gün sayısı kadar "
             "ilerideki harftir.\n");
      printf("(3 deneme hakkın var, her yanlış denemede enerji -5)\n");

      do {
        printf("Şifre (%d. deneme): ", deneme + 1);
        girilen = karakterOku();
        if (girilen == EOF)
          girilen = '?';
        if (girilen >= 'a' && girilen <= 'z') /* küçük harf de kabul */
          girilen = girilen - 'a' + 'A';
        deneme++;

        if (girilen != sifre) {
          enerji -= 5;
          if (enerji < 0)
            enerji = 0;
          printf("Yanlış! Enerji -5. ");
          if (girilen < 'A' || girilen > 'Z')
            printf("Şifre A-Z arasında bir harf olmalı.\n");
          else if (girilen < sifre)
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

    /* ===== Q: Çıkış ===== */
    case 'q':
    case 'Q':
      printf("Simülasyondan çıkılıyor...\n");
      oyunaDevam = 0;
      turHarcandi = 0;
      break;

    /* ===== Tanımsız komut (tur harcamaz) ===== */
    default:
      printf("Tanımsız komut! Lütfen listedeki tek harfli komutlardan birini "
             "girin.\n");
      turHarcandi = 0;
    }

    /* ---------- Zaman akışı ---------- */
    if (turHarcandi == 1) {
      tur++;
      if (tur % 3 == 0) { /* her 3 turda bir yeni gün */
        gun++;
        oksijen -= 8;
        printf("\n*** Yeni gün başladı: %d. gün. Oksijen -8 ***\n", gun);
        if (modulHasar > 70) {
          saglik -= 5;
          printf("Modül hasarı yüksek! Sağlık -5\n");
        }
      }
    }

    sinirla();

    /* ---------- Oyun sonu kontrolü (her turun sonunda) ---------- */
    if (saglik <= 0 || oksijen <= 0) {
      if (saglik <= 0 && oksijen <= 0)
        printf("\nKAYBETTİN! Sağlığın ve oksijenin tükendi.\n");
      else if (saglik <= 0)
        printf("\nKAYBETTİN! Sağlığın tükendi.\n");
      else
        printf("\nKAYBETTİN! Oksijenin tükendi.\n");
      oyunaDevam = 0;
    } else if (gun > 15) {
      printf("\nKurtarma ekibi geldi! KAZANDIN!\n");
      oyunaDevam = 0;
    }
  } while (oyunaDevam == 1);

  /* ---------- Sonuç raporu ---------- */
  {
    int tamamlananGun, puan;

    if (gun > 15)
      tamamlananGun = 15;
    else
      tamamlananGun = gun - 1; /* tamamlanan gün sayısı */

    puan = (tamamlananGun * 100) + saglik + oksijen - modulHasar;

    printf("\n===== SONUÇ RAPORU =====\n");
    printf("Hayatta kalınan gün: %d\n", tamamlananGun);
    printf("Toplam tur: %d\n", tur);
    printf("Sağlık: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d | Yedek parça: %d | Modül hasarı: %d\n", su, yedekParca,
           modulHasar);
    printf("PUAN: %d\n", puan);
  }

  return 0;
}
