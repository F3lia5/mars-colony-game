# Mars Kolonisi Yaşam Destek Simülatörü

C diliyle yazılmış, metin tabanlı ve tek karakterli komutlarla kontrol edilen bir hayatta kalma simülatörüdür. Oyuncu, Mars'taki küçük bir araştırma istasyonunda tek başına kalmış bir mühendisi yönetir ve kurtarma ekibi gelene kadar **15 gün** hayatta kalmaya çalışır.

Proje yalnızca C dilinin temel yapılarıyla (`if–else`, `switch–case`, `for`, `do–while`, aritmetik ve mantıksal operatörler) yazılmıştır.

## Derleme ve Çalıştırma

```bash
gcc main.c -o mars
./mars
```

Windows'ta (MinGW) çıktı: `mars.exe`. Türkçe karakterler bozuk görünürse terminalde `chcp 65001` komutunu çalıştırın.

## Oyun Kuralları

Program başlarken zorluk seviyesi seçilir. Ardından oyun, oyuncu çıkış yapana, karakter ölene veya 15. gün tamamlanana kadar komut döngüsüyle devam eder.

### Zorluk Seviyeleri

| Seviye | Su | Yedek parça | Oksijen | Fırtına süresi | Fırtına hasarı |
|---|---|---|---|---|---|
| K (Kolay) | 10 | 4 | 100 | 3 tur | 5 |
| N (Normal) | 6 | 3 | 100 | 5 tur | 10 |
| Z (Zor) | 3 | 1 | 80 | 7 tur | 15 |

Sağlık ve enerji her seviyede 100, modül hasarı 0 ile başlar. Geçersiz seçimde soru tekrarlanır.

### Komutlar

Komutlar büyük/küçük harf duyarsızdır.

| Komut | İşlev | Etkisi |
|---|---|---|
| `G` | Keşif | Enerji -15, oksijen -10. Su, yedek parça bulabilir veya eli boş dönebilir. Yaralanma riski vardır. |
| `O` | Oksijen üret | 2 su → 3 oksijen, enerji -10. Tek sayıda su girilirse 1 birim artık olarak depoda kalır. |
| `T` | Tamir | Yedek parça harcayarak modül hasarını azaltır. Hasar seviyesine göre harcanan parça ve onarım değişir. |
| `D` | Durum raporu | Tüm değerleri ve kritik uyarıları gösterir. Tur harcamaz. |
| `U` | Uyu / dinlen | Enerji +25, oksijen -5. Oksijen 20'nin altındaysa sağlık azalır, değilse artar. |
| `K` | Kum fırtınası | Zorluğa göre 3/5/7 turluk fırtınayı `for` döngüsüyle simüle eder. |
| `H` | Hava kilidi şifresi | 3 denemelik `do–while` şifre mekanizması. Doğruysa hava kilidi mühürlenir. |
| `Q` | Çıkış | Oyunu bitirir ve sonuç raporunu gösterir. |

Tanımsız komut uyarı verir ve tur harcamaz.

### Tamir Kademeleri

| Modül hasarı | Seviye | Harcanan parça | Onarılan hasar |
|---|---|---|---|
| 1-30 | Hafif | 1 | 15 |
| 31-70 | Orta | 2 | 25 |
| 71-100 | Ağır | 3 | 35 |

### Zaman Akışı

- Geçerli her komut tur sayacını 1 artırır (`D`, tanımsız ve iptal edilen komutlar hariç).
- Her 3 turda bir yeni gün başlar (`tur % 3 == 0`). Gün başında oksijen 8 azalır, modül hasarı 70'in üzerindeyse ek olarak 5 sağlık kaybedilir.
- Sağlık, enerji, oksijen ve modül hasarı her komuttan sonra 0-100 aralığında tutulur.

### Oyun Sonu

- **Kayıp:** Sağlık veya oksijen 0'a düşerse.
- **Kazanma:** 15. gün tamamlanırsa (3 tur = 1 gün, toplam 45 tur) kurtarma ekibi gelir.
- Oyun nasıl biterse bitsin hayatta kalınan gün, toplam tur, son değerler ve puan yazdırılır.

```
Puan = (gun * 100) + saglik + oksijen - modulHasar
```

### Rastgelelik

`srand(time(NULL))` ve `rand() % 100` kullanılır. Üretilen zar ve karşılaştırıldığı eşik ekrana yazdırılır:

```
Bulgu zarı -> Zar: 37 / Eşik: 50 -> BAŞARILI
```

## Kullanılan C Yapıları

| Yapı | Nerede kullanıldı |
|---|---|
| `switch–case` (fall-through) | Komut ve zorluk seçimi (`case 'g': case 'G':`) |
| `if – else if – else` | Tamir kademeleri, keşif sonucu, fırtına olayları |
| İç içe `if` | Dinlenme (`U`): enerji kontrolü içinde oksijen kontrolü |
| `for` + `break` / `continue` | Kum fırtınası: ölümde `break`, mühürlü kilitte `continue` |
| `do–while` | Zorluk seçimi, ana komut döngüsü, şifre denemeleri |
| Mod operatörü `%` | Gün hesabı, çift tur kontrolü, su artığı hesabı, şifre türetme |
| Mantıksal operatörler `&&`, `\|\|` | Keşif eşiği, yaralanma, şifre döngü koşulu, "tüm sistemler normal" |

## Proje Yapısı

```
mars-kolonisi/
├── main.c       # tüm oyun kodu
├── README.md    # bu dosya
└── rapor.pdf    # proje raporu
```
