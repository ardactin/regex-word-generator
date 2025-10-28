#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKS_KELIME 1000
#define MAKS_UZUNLUK 50

char alfabe[10];
int alfabeBoyutu = 0;
char kelimeler[MAKS_KELIME][MAKS_UZUNLUK];
int kelimeSayaci = 0;

int kelimeTekrarKontrol(char *kelime) {
    for (int i = 0; i < kelimeSayaci; i++)
        if (strcmp(kelimeler[i], kelime) == 0)
            return 1;
    return 0;
}

int alfabeKontrol(char *duzenliIfade) {
    for (int i = 0; duzenliIfade[i]; i++) {
        char c = duzenliIfade[i];
        if (c == '(' || c == ')' || c == '*' || c == '+' || c == ' ')
            continue;
        int bulundu = 0;
        for (int j = 0; j < alfabeBoyutu; j++) {
            if (alfabe[j] == c) {
                bulundu = 1;
                break;
            }
        }
        if (!bulundu)
            return 0;
    }
    return 1;
}

int sembolMu(char c) {
    for (int i = 0; i < alfabeBoyutu; i++)
        if (c == alfabe[i])
            return 1;
    return 0;
}

void kelimeEkle(char *kelime, int hedefSayi) {
    if (!kelimeTekrarKontrol(kelime) && kelimeSayaci < hedefSayi) {
        strcpy(kelimeler[kelimeSayaci++], kelime);
    }
}

void kelimeUret(char *duzenliIfade, char *aktifKelime, int pozisyon, int hedefSayi) {
    if (kelimeSayaci >= hedefSayi) return;

    if (*duzenliIfade == '\0') {
        aktifKelime[pozisyon] = '\0';
        kelimeEkle(aktifKelime, hedefSayi);
        return;
    }

    if (*duzenliIfade == '(') {
        int derinlik = 1, i = 1, k = 0;
        char parantezIci[MAKS_UZUNLUK] = "";
        while (duzenliIfade[i] && derinlik > 0) {
            if (duzenliIfade[i] == '(') derinlik++;
            else if (duzenliIfade[i] == ')') derinlik--;
            if (derinlik > 0) parantezIci[k++] = duzenliIfade[i];
            i++;
        }
        parantezIci[k] = '\0';

        char sonraki = duzenliIfade[i];
        char *kalan = duzenliIfade + i + 1;

        if (sonraki == '*') {
            char secenekler[10][MAKS_UZUNLUK];
            int secenekSayisi = 0, secenekPoz = 0;

            for (int j = 0; parantezIci[j]; j++) {
                if (parantezIci[j] == '+') {
                    secenekler[secenekSayisi++][secenekPoz] = '\0';
                    secenekPoz = 0;
                } else {
                    secenekler[secenekSayisi][secenekPoz++] = parantezIci[j];
                }
            }
            secenekler[secenekSayisi++][secenekPoz] = '\0';

            char gecici[MAKS_UZUNLUK];
            strcpy(gecici, aktifKelime);

            kelimeUret(kalan, gecici, pozisyon, hedefSayi);

            for (int tekrar = 1; tekrar <= 3; tekrar++) {
                for (int s = 0; s < secenekSayisi; s++) {
                    strcpy(gecici, aktifKelime);
                    for (int x = 0; x < tekrar; x++)
                        strcat(gecici, secenekler[s]);
                    kelimeUret(kalan, gecici, strlen(gecici), hedefSayi);
                }
            }
        } else {
            char secenekler[10][MAKS_UZUNLUK];
            int secenekSayisi = 0, secenekPoz = 0;
            for (int j = 0; parantezIci[j]; j++) {
                if (parantezIci[j] == '+') {
                    secenekler[secenekSayisi++][secenekPoz] = '\0';
                    secenekPoz = 0;
                } else {
                    secenekler[secenekSayisi][secenekPoz++] = parantezIci[j];
                }
            }
            secenekler[secenekSayisi++][secenekPoz] = '\0';

            for (int o = 0; o < secenekSayisi; o++) {
                char gecici[MAKS_UZUNLUK];
                strcpy(gecici, aktifKelime);
                strcat(gecici, secenekler[o]);
                kelimeUret(kalan, gecici, strlen(gecici), hedefSayi);
            }
        }
    } else if (sembolMu(*duzenliIfade) && duzenliIfade[1] == '*') {
        char gecici[MAKS_UZUNLUK];
        strcpy(gecici, aktifKelime);
        kelimeUret(duzenliIfade + 2, gecici, pozisyon, hedefSayi);

        for (int tekrar = 1; tekrar <= 3; tekrar++) {
            strcpy(gecici, aktifKelime);
            for (int j = 0; j < tekrar; j++)
                gecici[pozisyon + j] = *duzenliIfade;
            gecici[pozisyon + tekrar] = '\0';
            kelimeUret(duzenliIfade + 2, gecici, pozisyon + tekrar, hedefSayi);
        }
    } else if (sembolMu(*duzenliIfade)) {
        aktifKelime[pozisyon] = *duzenliIfade;
        kelimeUret(duzenliIfade + 1, aktifKelime, pozisyon + 1, hedefSayi);
    } else {
        kelimeUret(duzenliIfade + 1, aktifKelime, pozisyon, hedefSayi);
    }
}

int dildeVarMi(char *kelime) {
    for (int i = 0; i < kelimeSayaci; i++)
        if (strcmp(kelimeler[i], kelime) == 0)
            return 1;
    return 0;
}

int main() {
    char duzenliIfade[100], alfabeGirdisi[50], aktifKelime[MAKS_UZUNLUK];
    int hedefSayi;

    printf("Alfabeyi giriniz (ornek: a,b): ");
    scanf("%49s", alfabeGirdisi);
    alfabeBoyutu = 0;
    for (int i = 0; alfabeGirdisi[i]; i++)
        if (alfabeGirdisi[i] != ',')
            alfabe[alfabeBoyutu++] = alfabeGirdisi[i];

    printf("Duzenli ifadeyi giriniz: ");
    scanf("%99s", duzenliIfade);

    if (!alfabeKontrol(duzenliIfade)) {
        printf("Duzenli ifade alfabeden uretilemez.\n");
        return 0;
    }

    printf("Duzenli ifade S alfabesinden uretilmektedir.\n");

    printf("L dilinin kac kelimesini gormek istiyorsunuz? ");
    scanf("%d", &hedefSayi);

    kelimeSayaci = 0;
    kelimeUret(duzenliIfade, aktifKelime, 0, hedefSayi);

    printf("Kelimeleriniz listeleniyor:\nL={");
    for (int i = 0; i < kelimeSayaci; i++) {
        printf("%s", kelimeler[i]);
        if (i < kelimeSayaci - 1) printf(", ");
    }
    printf("}\n");

    char kontrolKelimesi[50];
    printf("Kontrol edilecek kelimeyi giriniz: ");
    scanf("%s", kontrolKelimesi);
    if (dildeVarMi(kontrolKelimesi))
        printf("Bu kelime L diline aittir.\n");
    else
        printf("Bu kelime L diline ait degildir.\n");

    return 0;
}

