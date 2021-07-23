#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define liczbaPomiarow 10

//struktura do przechowywania wektorów liczb
//wektor moze miec 128 bitow, a kazdy float to 32 bity, zatem 32*4 = 128 bitow


struct wektorFloat
{
	float num1;
    	float num2;
	float num3;
    	float num4;
};

//sekcja SIMD

double dodawanieSIMD(struct wektorFloat a, struct wektorFloat b)
{
	time_t t_poczatek;
	time_t t_koniec;
    
	t_poczatek = clock();
	asm(
		"movups (%0), %%XMM0\n"
		"movups (%1), %%XMM1\n"
		"addps %%XMM0, %%XMM1\n"
		:
		: "r" (&a), "r" (&b)
	   );
	t_koniec = clock();
	return difftime(t_koniec, t_poczatek) / (double)CLOCKS_PER_SEC;
}

double odejmowanieSIMD(struct wektorFloat a, struct wektorFloat b)
{
	time_t t_poczatek;
	time_t t_koniec;
	
	t_poczatek = clock();
	asm(
		"movups (%0), %%XMM0\n"
        	"movups (%1), %%XMM1\n"
        	"subps %%XMM0, %%XMM1\n"
		:
		: "r" (&a), "r" (&b)
	   );
	t_koniec = clock();
	return difftime(t_koniec, t_poczatek) / (double)CLOCKS_PER_SEC;
}

double mnozenieSIMD(struct wektorFloat a, struct wektorFloat b)
{
	time_t t_poczatek;
	time_t t_koniec;
	
	t_poczatek = clock();
	asm(
		"movups (%0), %%XMM0\n"
        	"movups (%1), %%XMM1\n"
        	"mulps %%XMM0, %%XMM1\n"
		:
		: "r" (&a), "r" (&b)
	   );
	t_koniec = clock();
	return difftime(t_koniec, t_poczatek) / (double)CLOCKS_PER_SEC;
}

double dzielenieSIMD(struct wektorFloat a, struct wektorFloat b)
{
	time_t t_poczatek;
	time_t t_koniec;
	
	t_poczatek = clock();
	asm(
		"movups (%0), %%XMM0\n"
        	"movups (%1), %%XMM1\n"
        	"divps %%XMM0, %%XMM1\n"
		:
		: "r" (&a), "r" (&b)
	   );
	t_koniec = clock();
	return difftime(t_koniec, t_poczatek) / (double)CLOCKS_PER_SEC;
}


//sekcja SISD

double dodawanieSISD(struct wektorFloat a, struct wektorFloat b)
{
    
	time_t t_poczatek;
	time_t t_koniec;
	
	t_poczatek = clock();
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
		: "r" (&a), "r" (&b)
	   );
	t_koniec = clock();
	return difftime(t_koniec, t_poczatek) / (double)CLOCKS_PER_SEC;
}

double odejmowanieSISD(struct wektorFloat a, struct wektorFloat b)
{    
	time_t t_poczatek;
	time_t t_koniec;
	
	t_poczatek = clock();
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
		: "r" (&a), "r" (&b)
	   );
	t_koniec = clock();
	return difftime(t_koniec, t_poczatek) / (double)CLOCKS_PER_SEC;
}

double mnozenieSISD(struct wektorFloat a, struct wektorFloat b)
{
	time_t t_poczatek;
	time_t t_koniec;
	
	t_poczatek = clock();
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
		: "r" (&a), "r" (&b)
	   );
	t_koniec = clock();
	return difftime(t_koniec, t_poczatek) / (double)CLOCKS_PER_SEC;
}

double dzielenieSISD(struct wektorFloat a, struct wektorFloat b)
{
	time_t t_poczatek;
	time_t t_koniec;
	
	t_poczatek = clock();
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
		: "r" (&a), "r" (&b)
	   );
	t_koniec = clock();
	return difftime(t_koniec, t_poczatek) / (double)CLOCKS_PER_SEC;
}

//generator liczb pseudolosowych

struct wektorFloat generatorWektorow()
{
        struct wektorFloat wektor;
        wektor.num1 = (rand() % 10000000) / 100.0;
        wektor.num2 = (rand() % 10000000) / 100.0;
        wektor.num3 = (rand() % 10000000) / 100.0;
        wektor.num4 = (rand() % 10000000) / 100.0;

        return wektor;
}

//pomiary

double testDodawanie(int wielkosc, int typ)
{
	double suma = 0;
	int i;
	int j;
	
	for(i = 0; i < liczbaPomiarow; i++)
	{
		for(j = 0; j < wielkosc; j++)
			if(typ == 1)
				suma += dodawanieSIMD(generatorWektorow(), generatorWektorow());
			else
				suma += dodawanieSISD(generatorWektorow(), generatorWektorow());
	}
	suma /= (double) liczbaPomiarow;
	
	return suma;
}

double testOdejmowanie(int wielkosc, int typ)
{
	double suma = 0;
	int i;
	int j;        
	
	for(i = 0; i < liczbaPomiarow; i++)
        {
		for(j = 0; j < wielkosc; j++)
		if(typ == 1)
			suma += odejmowanieSIMD(generatorWektorow(), generatorWektorow());
		else
			suma += odejmowanieSISD(generatorWektorow(), generatorWektorow());
	}
	suma /= (double) liczbaPomiarow;
	
	return suma;
}

double testMnozenie(int wielkosc, int typ)
{
	double suma = 0;
	int i;
	int j;
        
	for(i = 0; i < liczbaPomiarow; i++)
	{
		for(j = 0; j < wielkosc; j++)
			if(typ == 1)
				suma += mnozenieSIMD(generatorWektorow(), generatorWektorow());
			else
				suma += mnozenieSISD(generatorWektorow(), generatorWektorow());
	}
	suma /= (double) liczbaPomiarow;
	
	return suma;
}

double testDzielenie(int wielkosc, int typ)
{
	double suma;
	int i; 
	int j;
	
	for(i = 0; i < liczbaPomiarow; i++)
	{
		for(j = 0; j < wielkosc; j++)
			if(typ == 1)
				suma += dzielenieSIMD(generatorWektorow(), generatorWektorow());
			else
				suma += dzielenieSISD(generatorWektorow(), generatorWektorow());
	}
	suma /= (double) liczbaPomiarow;

	return suma;
}

//wyniki

void wynik(int wielkosc)
{
	FILE *file;
			char name[10] = {"Wyniki.txt"};

			if(file = fopen(name, "a"))
			{
				fprintf(file, "Typ obliczen: SISD\n");
                                fprintf(file, "Liczba liczb: %d \n", wielkosc);
                                fprintf(file, "Liczba pomiarow: %d \n", liczbaPomiarow);
                                fprintf(file, "Sredni czas [s]:\n");
                                fprintf(file, "+ %f \n", testDodawanie(wielkosc, 0));
                                fprintf(file, "- %f \n", testOdejmowanie(wielkosc, 0));
                                fprintf(file, "* %f \n", testMnozenie(wielkosc, 0));
                                fprintf(file, "/ %f \n\n", testDzielenie(wielkosc, 0));

                                fprintf(file, "Typ obliczen: SIMD\n");
                                fprintf(file, "Liczba liczb: %d \n", wielkosc);
                                fprintf(file, "Liczba pomiarow: %d \n", liczbaPomiarow);
                                fprintf(file, "Sredni czas [s]:\n");
                                fprintf(file, "+ %f \n", testDodawanie(wielkosc, 1));
                                fprintf(file, "- %f \n", testOdejmowanie(wielkosc, 1));
                                fprintf(file, "* %f \n", testMnozenie(wielkosc, 1));
                                fprintf(file, "/ %f \n\n", testDzielenie(wielkosc, 1));
			}
			else
			{
				printf("Blad.\n");
			}


}

int main()
{
	srand(time(NULL));
	wynik(2048);
	wynik(4096);
	wynik(8192);
	printf("Prawdopodobnie wykonano obliczenia.\n");
}
