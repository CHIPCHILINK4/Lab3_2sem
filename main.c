#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Реализовать все предложенные операции для булева вектора произвольной длины.
//Способ представление булева вектора в памяти обсуждалось на занятии.
//Уметьего рассказать. Продемонстрировать работу всех операций.



//8 Функция конвертации строки в булев вектор;



unsigned char* convertStrToLongBv(char* str, size_t* sz) {
    if (str && sz) {
        *sz = strlen(str);
        unsigned char mask = 1;
        size_t byte = ((*sz + 7) / 8), ix = 0;
        if (*sz) {
            unsigned char* vec = (unsigned char*)calloc(byte, sizeof(unsigned char));
            if (vec) {
                for (size_t i = 0; i < byte; i++) {
                    mask = 1;
                    for (size_t j = 0; (j < 8) && (ix < *sz); j++) {
                        if (str[ix] != '0') {
                            vec[i] = vec[i] | mask;
                        }

                        mask = mask << 1;
                        ix++;
                    }
                }
            }
            return vec;
        }
    }
    return NULL;
}

//9 Функция конвертации булева вектора в строку;
char* convertLongBvToStr(unsigned char* vec, size_t sz) {
    if (vec && sz) {
        size_t ix = 0, byte = ((sz + 7) / 8);
        char* str = NULL;
        unsigned char mask = 1;
        str = (char*)malloc(byte * 8 + 1);
        if (str) {
            for (size_t i = 0; i < byte; i++) {
                mask = 1;
                for (size_t j = 0; (j < 8) && (ix < sz); j++) {
                    if ((vec[i] & mask) != 0) {
                        str[ix] = '1';
                    }
                    else {
                        str[ix] = '0';
                    }
                    mask = mask << 1;
                    ix++;
                }
            }
            str[ix] = '\0';
        }
        return str;
    }
    return NULL;
}

void printi(unsigned char* vec, size_t sz) {
    if (vec) {
        char* str = convertLongBvToStr(vec, sz);
        size_t byte = ((sz + 7) / 8);
        if (str)
        {
            for (size_t i = 0; i < byte * 8; i++) {
                if (i % 8 == 0)
                {
                    printf(" ");
                }
                printf("%c", str[i]);

            }
            printf("\n");
            printf("\n");
            free(str);
        }
    }
}


//1 Логическое умножение;
unsigned char* logMul(unsigned char* vec1, unsigned char* vec2, size_t bits1, size_t bits2) {
    if (vec1 && vec2 && (bits1 == bits2)) {

        size_t minByte = (bits1 + 7) / 8;
        unsigned char* res = NULL;

        if (bits1) {
            res = (unsigned char*)calloc(minByte, sizeof(unsigned char));
            if (res)
            {
                for (size_t i = 0; i < minByte; i++) {
                    res[i] = vec1[i] & vec2[i];
                }
                return res;
            }
        }
    }
    return NULL;
}


//2 Логическое сложение;
unsigned char* logSum(unsigned char* vec1, unsigned char* vec2, size_t bits1, size_t bits2) {
    if (vec1 && vec2 && (bits1 == bits2)) {

        size_t minByte = (bits1 + 7) / 8;
        unsigned char* res = NULL;

        if (bits1) {
            res = (unsigned char*)calloc(minByte, sizeof(unsigned char));
            if (res)
            {
                for (size_t i = 0; i < minByte; i++) {
                    res[i] = vec1[i] | vec2[i];
                }
                return res;
            }
        }
    }
    return NULL;
}


//3.Сумма по модулю 2;
unsigned char* sumMod2(unsigned char* vec1, unsigned char* vec2, size_t bits1, size_t bits2) {
    if (vec1 && vec2 && (bits1 == bits2)) {

        size_t minByte = (bits1 + 7) / 8;
        unsigned char* res = NULL;

        if (bits1) {
            res = (unsigned char*)calloc(minByte, sizeof(unsigned char));
            if (res)
            {
                for (size_t i = 0; i < minByte; i++) {
                    res[i] = vec1[i] ^ vec2[i];
                }
                return res;
            }
        }
    }
    return NULL;
}


//4.Инверсия;
void inversion(unsigned char* vec, size_t bits) {
    if (vec && bits) {
        size_t byts = ((bits + 7) / 8);
        for (size_t i = 0; i < byts; i++) {
            vec[i] = ~vec[i];
        }
        unsigned char k =  8 - (bits % 8);
        if (k) {
            vec[byts - 1] = (vec[byts - 1] << k);
            vec[byts - 1] = (vec[byts - 1] >> k);

        }
    }
}

//5.Сдвиг влево на K разрядов;
void shiftLeft(unsigned char* vec, size_t bits, size_t k) {
    if (vec && bits && k) {
        size_t byts = ((bits + 7) / 8);
        unsigned char tmp = 0;
        size_t bit = k % 8;
        size_t byte = k / 8;
        if (byts <= byte) {
            for (size_t i = 0; i < byts; i++) {
                vec[i] = 0;
            }
        }
        else {
            if (byte)
            {
                for (size_t i = 0; i < (byts); i++) {
                    vec[i] = vec[i + byte];
                    if (i > byte + 1) {
                        vec[i] = 0;
                    }
                }
            }
            for (size_t i = 0; i < byts - 1; i++) {
                tmp = vec[i] >> bit;
                vec[i] = tmp | (vec[i + 1] << (8 - bit));

            }
            vec[byts - 1] = vec[byts - 1] >> (bit);
        }
    }
}

//6 Сдвиг вправо на K разрядов;
void shiftRight(unsigned char* vec, size_t bits, size_t k) {
    if (vec && bits && k) {
        size_t byts = ((bits + 7) / 8);
        unsigned char tmp = 0;
        size_t bit = k % 8;
        size_t byte = k / 8;
        if (byts <= byte) {
            for (size_t i = 0; i < byts; i++) {
                vec[i] = 0;
            }
        }
        else {
            if (byte)
            {
                for (size_t i = byts - 1; i > 0; i--) {
                    vec[i] = vec[i - byte];
                    if (i <= byte) {
                        vec[i - 1] = 0;
                    }
                }
            }
            for (size_t i = 1; i < byts - 1; i++) {
                tmp = vec[i] << bit;
                vec[i] = tmp | (vec[i - 1] >> (8 - bit));

            }
            vec[0] = vec[0] << (bit);
        }
    }
}

//7.1 Установка / сброс К - ого разряда;
void set1(unsigned char* vec, size_t bits, size_t bit) {
    if (vec && bits && bit) {
        if (bit < bits) {
            int mask = 1;
            mask = mask << (bit % 8);
            vec[bit / 8] = vec[bit / 8] | mask;
        }
    }
}

//7.2 Установка / сброс К - ого разряда;
void set0(unsigned char* vec, size_t bits, size_t bit) {
    if (vec && bits && bit) {
        if (bit < bits) {
            int mask = 1;
            mask = mask << (bit % 8);
            vec[bit / 8] = vec[bit / 8] & ~(mask);
        }
    }
}





int main() {

    unsigned char* vektor1 = NULL;
    unsigned char* vektor2 = NULL;
    size_t lenRes = 0;
    size_t len1 = 0;
    size_t len2 = 0;
    size_t k = 9;
    size_t set1_0 = 4;
    unsigned char* vektorRes = NULL;

    ////
    char str1[32] = "0000tr0werty000pf0000fgfgd000dg";//00001101 11110001 10000111 1100011
    char str2[32] = "tr00trrughiros000rgd0grd0rdg0g0";
    ////
    //
    //
    //char str1[32] = "0000000000000000000000000000000";
    //char str2[32] = "tr00trrughiros000rgd0grd0rdg0g0";
    //

    //
    //char str1[32] = "rtrttr0wertyuiopf0000fgfgdfgfdg";
    //char str2[32] = "0000000000000000000000000000000";
    //

    //
    //char str1[32] = "0000000000000000000000000000000";
    //char str2[32] = "0000000000000000000000000000000";
    //

    ////
    //char str1[32] = "rtrttr0wertyuiopf0000fgfgdfgfdg";//11111101 11111111 10000111 91111111
    //char str2[16] = "tr00t00ug0iros0";
    ////

    ////
    //char str1[32] = "0000tr0werty000pf0000fgfgd000dg";//00001101 11110001 10000111 1100011
    //char str2[16] = "tr00t00ug0iros0";
    ////

    ////
    //char str1[16] = "00rttr0wertyuio";//00111101 91111111
    //char str2[32] = "tr00trrughiros000rgd0grd0rdg0g0";
    ////

    //V1
    printf("V1\n");
    vektor1 = convertStrToLongBv(str1, &len1);
    printi(vektor1, len1);

    //V2
    printf("V2\n");
    vektor2 = convertStrToLongBv(str2, &len2);
    printi(vektor2, len2);

    lenRes = len1;

    //&
    printf("&\n");
    vektorRes = logMul(vektor1, vektor2, len1, len2);
    printi(vektorRes, lenRes);
    if (vektorRes)
    {
        free(vektorRes);
    }

    //|
    printf("|\n");
    vektorRes = logSum(vektor1, vektor2, len1, len2);
    printi(vektorRes, lenRes);
    if (vektorRes)
    {
        free(vektorRes);
    }

    //^
    printf("^\n");
    vektorRes = sumMod2(vektor1, vektor2, len1, len2);
    printi(vektorRes, lenRes);
    if (vektorRes)
    {
        free(vektorRes);
    }

    //~
    printf("~\n");
    inversion(vektor1, len1);
    printi(vektor1, len1);

    printf("~\n");
    inversion(vektor1, len1);
    printi(vektor1, len1);

    //<<
    printf("<<\n");
    shiftLeft(vektor1, len1, k);
    printi(vektor1, len1);

    //>>
    printf(">>\n");
    shiftRight(vektor1, len1, k);
    printi(vektor1, len1);

    //1
    printf("1\n");
    set1(vektor1, len1, set1_0);
    printi(vektor1, len1);

    //0
    printf("0\n");
    set0(vektor1, len1, set1_0);
    printi(vektor1, len1);

    free(vektor1);
    free(vektor2);


    return 0;
}
//векторы одинаковой длинны yt не обрезай не дополняй и смещение просто с отбрасыванием
