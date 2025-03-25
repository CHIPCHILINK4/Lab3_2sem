Лабораторная №3 - общая часть (Тема - Булев вектор произвольной длины)

Реализовать все предложенные операции для булева вектора
произвольной длины. Способ представление булева вектора в
памяти №2. Уметь его рассказать.

Продемонстрировать работу всех операций.

Во многих функциях представлены следующие входные аргументы:
usigned char *vecA – указатель на массив, представляющий булев
вектор;
size_t bits – длина булева вектора(количество разрядов);
bytes = ((bits + 7) / 8); //вычисление количества ячеек булева вектора(количества байт необходимы для хранения булева вектора длины bits)

Функции для реализации:

1. Логическое умножение;
unsigned char* logMul(unsigned char* vec1, unsigned char* vec2, size_t bits1, size_t bits2) ;

2. Логическое сложение;
unsigned char * logSum(unsigned char* vec1, unsigned char* vec2, size_t bits1, size_t bits2);

3.Сумма по модулю 2;
unsigned char * sumMod2(unsigned char* vec1, unsigned char* vec2, size_t bits1, size_t bits2);

4.Инверсия;
void inversion(unsigned char *vec, size_t bits);

5.Сдвиг влево на K разрядов;
void shiftLeft(unsigned char *vec, size_t bits, size_t k);

6. Сдвиг вправо на K разрядов;
void shiftRight(unsigned char *vec, size_t bits, size_t k);

7. Установка/сброс К-ого разряда;
void set1(unsigned char *vec, size_t bits, size_t bit);
void set0(unsigned char *vec, size_t bits, size_t bit);

8. Функция конвертации строки в булев вектор;
unsigned char* convertStrToLongBv(char* str, size_t* sz);

9. Функция конвертации булева вектора в строку;
char* convertLongBvToStr(unsigned char* vec, size_t sz) ;