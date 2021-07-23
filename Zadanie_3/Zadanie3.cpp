#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define tests 10

struct floatNumbers
{
    float firstNumber;
    float secondNumber;
    float thirdNumber;
    float fourthNumber;
};

struct floatNumbers generateVector()
{
    struct floatNumbers vector;

    // Generowanie liczb losowych typu float od 1.0 do 100.0
    vector.firstNumber = (rand() % 100000 + 1) / 100.0;
    vector.secondNumber = (rand() % 100000 + 1) / 100.0;
    vector.thirdNumber = (rand() % 100000 + 1) / 100.0;
    vector.fourthNumber = (rand() % 100000 + 1) / 100.0;

    return vector;
}

double addSIMD(int size)
{
    double time = 0;
    time_t start;
    time_t end;
    struct floatNumbers firstVector = generateVector();
    struct floatNumbers secondVector = generateVector();

    for (int i = 0; i < tests; i++)
    {
        for (int j = 0; j < size; j++)
        {
            start = clock();

            asm(
                "movups (%0), %%XMM0\n"
                "movups (%1), %%XMM1\n"
                "addps %%XMM0, %%XMM1\n"
                :
                : "r"(&firstVector), "r"(&secondVector));

            end = clock();
            time += difftime(end, start) / (double)CLOCKS_PER_SEC;
        }
    }
    time = time / (double)tests;
    return time;
}

double substractSIMD(int size)
{
    double time = 0;
    time_t start;
    time_t end;
    struct floatNumbers firstVector = generateVector();
    struct floatNumbers secondVector = generateVector();

    for (int i = 0; i < tests; i++)
    {
        for (int j = 0; j < size; j++)
        {
            start = clock();
            asm(
                "movups (%0), %%XMM0\n"
                "movups (%1), %%XMM1\n"
                "subps %%XMM0, %%XMM1\n"
                :
                : "r"(&firstVector), "r"(&secondVector));
            end = clock();
            time += difftime(end, start) / (double)CLOCKS_PER_SEC;
        }
    }
    time = time / (double)tests;
    return time;
}

double multiplySIMD(int size)
{
    double time = 0;
    time_t start;
    time_t end;
    struct floatNumbers firstVector = generateVector();
    struct floatNumbers secondVector = generateVector();

    for (int i = 0; i < tests; i++)
    {
        for (int j = 0; j < size; j++)
        {
            start = clock();
            asm(
                "movups (%0), %%XMM0\n"
                "movups (%1), %%XMM1\n"
                "mulps %%XMM0, %%XMM1\n"
                :
                : "r"(&firstVector), "r"(&secondVector));
            end = clock();
            time += difftime(end, start) / (double)CLOCKS_PER_SEC;
        }
    }
    time = time / (double)tests;
    return time;
}

double divideSIMD(int size)
{
    double time = 0;
    time_t start;
    time_t end;
    struct floatNumbers firstVector = generateVector();
    struct floatNumbers secondVector = generateVector();

    for (int i = 0; i < tests; i++)
    {
        for (int j = 0; j < size; j++)
        {
            start = clock();
            asm(
                "movups (%0), %%XMM0\n"
                "movups (%1), %%XMM1\n"
                "divps %%XMM0, %%XMM1\n"
                :
                : "r"(&firstVector), "r"(&secondVector));
            end = clock();
            time += difftime(end, start) / (double)CLOCKS_PER_SEC;
        }
    }
    time = time / (double)tests;
    return time;
}

double addSISD(int size)
{
    double time = 0;
    time_t start;
    time_t end;
    struct floatNumbers firstVector = generateVector();
    struct floatNumbers secondVector = generateVector();

    for (int i = 0; i < tests; i++)
    {
        for (int j = 0; j < size; j++)
        {
            start = clock();
            asm(
                "fld (%0)\n"
                "fld (%1)\n"
                "faddp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 4(%0)\n"
                "fld 4(%1)\n"
                "faddp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 8(%0)\n"
                "fld 8(%1)\n"
                "faddp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 12(%0)\n"
                "fld 12(%1)\n"
                "faddp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"
                :
                : "r"(&firstVector), "r"(&secondVector));
            end = clock();
            time += difftime(end, start) / (double)CLOCKS_PER_SEC;
        }
    }
    time = time / (double)tests;
    return time;
}

double substractSISD(int size)
{
    double time = 0;
    time_t start;
    time_t end;
    struct floatNumbers firstVector = generateVector();
    struct floatNumbers secondVector = generateVector();

    for (int i = 0; i < tests; i++)
    {
        for (int j = 0; j < size; j++)
        {
            start = clock();
            asm(
                "fld (%0)\n"
                "fld (%1)\n"
                "fsubp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 4(%0)\n"
                "fld 4(%1)\n"
                "fsubp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 8(%0)\n"
                "fld 8(%1)\n"
                "fsubp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 12(%0)\n"
                "fld 12(%1)\n"
                "fsubp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"
                :
                : "r"(&firstVector), "r"(&secondVector));
            end = clock();
            time += difftime(end, start) / (double)CLOCKS_PER_SEC;
        }
    }
    time = time / (double)tests;
    return time;
}

double multiplySISD(int size)
{
    double time = 0;
    time_t start;
    time_t end;
    struct floatNumbers firstVector = generateVector();
    struct floatNumbers secondVector = generateVector();

    for (int i = 0; i < tests; i++)
    {
        for (int j = 0; j < size; j++)
        {
            start = clock();
            asm(
                "fld (%0)\n"
                "fld (%1)\n"
                "fmulp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 4(%0)\n"
                "fld 4(%1)\n"
                "fmulp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 8(%0)\n"
                "fld 8(%1)\n"
                "fmulp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 12(%0)\n"
                "fld 12(%1)\n"
                "fmulp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"
                :
                : "r"(&firstVector), "r"(&secondVector));
            end = clock();
            time += difftime(end, start) / (double)CLOCKS_PER_SEC;
        }
    }
    time = time / (double)tests;
    return time;
}

double divideSISD(int size)
{
    double time = 0;
    time_t start;
    time_t end;
    struct floatNumbers firstVector = generateVector();
    struct floatNumbers secondVector = generateVector();

    for (int i = 0; i < tests; i++)
    {
        for (int j = 0; j < size; j++)
        {
            start = clock();
            asm(
                "fld (%0)\n"
                "fld (%1)\n"
                "fdivp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 4(%0)\n"
                "fld 4(%1)\n"
                "fdivp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 8(%0)\n"
                "fld 8(%1)\n"
                "fdivp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"

                "fld 12(%0)\n"
                "fld 12(%1)\n"
                "fdivp %%st(0), %%st(1)\n"
                "fstp %%st(3)\n"
                :
                : "r"(&firstVector), "r"(&secondVector));
            end = clock();
            time += difftime(end, start) / (double)CLOCKS_PER_SEC;
        }
    }
    time = time / (double)tests;
    return time;
}

void calculate(int size, std::string file)
{
    std::ofstream result;
    result.open(file + ".txt", std::ios::out | std::ios::app);
    if (result.is_open())
    {
        result << "-------------------------------------------------\n";
        result << "Typ obliczen: SIMD\n";
        result << "Liczba liczb: " << size << "\n";
        result << "Operacja '+': " << addSIMD(size) << "\n";
        result << "Operacja '-': " << substractSIMD(size) << "\n";
        result << "Operacja '*': " << multiplySIMD(size) << "\n";
        result << "Operacja '/': " << divideSIMD(size) << "\n\n";
        result << "Typ obliczen: SISD\n";
        result << "Liczba liczb: " << size << "\n";
        result << "Operacja '+': " << addSISD(size) << "\n";
        result << "Operacja '-': " << substractSISD(size) << "\n";
        result << "Operacja '*': " << multiplySISD(size) << "\n";
        result << "Operacja '/': " << divideSISD(size) << "\n";
        result.close();
    }
    else
    {
        std::cout << "Podczas otwierania pliku wystąpił błąd!\n";
    }
}

int main()
{
    srand(time(NULL));
    std::string fileName;
    std::cout << "Podaj nazwe pliku, do ktorego zapisane zostana wyniki (bez rozszerzenia .txt):\n";
    std::cin >> fileName;
    calculate(2048, fileName);
    calculate(4096, fileName);
    calculate(8192, fileName);
    std::cout << "Zakończono obliczenia oraz zapisano je w pliku " << fileName << ".txt\n";
}