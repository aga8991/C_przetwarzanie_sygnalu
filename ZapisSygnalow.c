#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<locale.h>


void wczytaj_zakres_dziedziny(float *D1, float *D2);
void wczytaj_wspolczynniki(float *tab_wspolczynniki);
int wczytaj_rozmiar_tab_wynikowej(float D1, float D2, float *dx);
int wczytaj_float(float *liczba);
void idioto_ochrona(float *liczba);
void idioto_ochrona_dla_D(float *liczba);
void przebieg_funkcji(float *wspolczynniki, float D1, float D2, float **wyniki, float dx, int N);
void zaklocenie(float **wyniki, int N);
void zapisz(float *wyniki, int N);
void filtr_medianowy(float **wyniki, int N);
void filtr_sr_ruchomej(float ** wyniki, int N);
int wczytaj(float **wyniki);



int main()
{
	int a, b, c;							//zmienne pomocnicze do funkcji switch
	int N = 0; 									//ilosc argumentow tablicy wynikowej
	float D1, D2, dx;						//poczatek dziedziny, koniec dziedziny, zakres probkowania
	float tab_wspolczynniki[4];
	float *wyniki=NULL;

	srand(time(NULL));
	setlocale(LC_ALL, "pl_PL.utf8");

	printf("Witam w menu uzytkownika. Powiedz mi co chcesz zrobic:\n\n   1. Wygenerowac nowy sygnal.\n   2. Dokonac zmian na swoim sygnale.\n\n");

	scanf("%d", &b);
	printf("\n");

	switch (b) {
	case 1:
		b = 1;
		system("cls");
		break;
	case 2:
		b = 2;
		system("cls");
		break;
	}

	if (b == 1)
	{
		printf("Wprowadz niezbedne dane:\n   1. Zakres dziedziny.\n   2. Wspolczynniki funkcji.\n   3. Zakres probkowania. \n   *4. Wprowadzilem wszystkie parametry i nie bede juz ich zmieniac.\n\nZ Dzialan oznaczonych numerami z symbolem * mozna korzystac tylko po wykananiu wszystkich innych dostepnych opcji.\n\n Wybieram opcje: ");

		do {
			scanf("%d", &a);
			printf("\n");

			switch (a) {
			case 1:
				wczytaj_zakres_dziedziny(&D1, &D2);
				printf("Co chcesz zrobic teraz? ");
				break;
			case 2:
				wczytaj_wspolczynniki(tab_wspolczynniki);
				printf("Wspolczynniki wczytane prawidlowo. Co chcesz zrobic teraz? ");
				break;
			case 3:
				printf("Podaj przedzial probkowania: ");
				idioto_ochrona(&dx);
				printf("Przedzial probkowania wprowadzony prawdilowo. Co chcesz zrobic teraz? ");
				break;
			case 4:
				system("cls");
				printf("Wprowadzone przez Ciebie parametry:\n\n - Poczatek dziedziny %f\n - Koniec dziedziny %f\n - Wspolczynniki:\n    1. %f\n    2. %f\n    3. %f\n    4. %f\n - Probkowanie %f\n\n", D1, D2, tab_wspolczynniki[0], tab_wspolczynniki[1], tab_wspolczynniki[2], tab_wspolczynniki[3], dx);
				break;
			default:
				a = 6;
				printf("Wybierz liczbe z menu uzytkownika: ");
			}
		} while (a == 1 || a == 2 || a == 3 || a == 6);

		if (a == 4)
		{
			N = wczytaj_rozmiar_tab_wynikowej(D1, D2, &dx);
			wyniki = (float*)calloc(N, sizeof(float));
			printf("\n\nMenu uzytkownika:\n   1. Sprawdz rozmiar tablicy wynikowej.\n   2. Wygeneruj funkcje o powyzszych parametrach.\n   *3. Zapisz wygenerowana funkcje i przejdz dalej.\n\n");
			do {
				scanf("%d", &a);
				printf("\n");

				switch (a) {
				case 1:
					printf("Tablica wynikowa ma %d argumentow.\n", N);
					printf("Co chcesz zrobic teraz? ");
					break;
				case 2:
					wyniki = (float*)calloc(N, sizeof(float));
					przebieg_funkcji(tab_wspolczynniki, D1, D2, &wyniki, dx, N);
					printf("Funkcja wygenerowana prawidlowo. Co chcesz zrobic teraz? ");
					break;
				case 3:
					zapisz(wyniki, N);
					free(wyniki);
					a = 3;
					system("cls");
					printf("Twoja funkcja zostala zapisana.\n\n");
					printf("Menu uzytkownika:\n");
					break;

				default:
					a = 6;
					printf("Wybierz liczbe z menu uzytkownika: ");
				}
			} while (a == 1 || a == 2 || a == 6);

			if (a == 3)
			{

				printf("\n   1. Dodaj zaszumienie.\n   2. Dodaj filtr sredniej ruchomej\n   3. Dodaj filtr medianowy\n   4. Zapisz zmiany do excel'a.\n   5. Zakoncz\n");
				do {
					scanf("%d", &a);
					printf("\n");

					switch (a) {
					case 1:
						N = wczytaj(&wyniki);
						zaklocenie(&wyniki, N);
						printf("Zaklocenia dodane. Co chcesz zrobic teraz?\n");
						break;
					case 2:
						N = wczytaj(&wyniki);
						filtr_sr_ruchomej(&wyniki, N);
						printf("Filtr sredniej ruchomej zastosowany.\n");
						break;
					case 3:
						N = wczytaj(&wyniki);
						filtr_medianowy(&wyniki, N);
						printf("Filtr medianowy zastosowany.\n");
						break;
					case 4:
						zapisz(wyniki, N);
						free(wyniki);
						printf("Funkcja zostala zapisana. Co chcesz zrobic teraz? ");
						break;
					case 5:
						exit(0);
					default:
						a = 6;
						printf("Wybierz liczbe z menu uzytkownika: ");
					}
				} while (a == 1 || a == 2 || a == 3 || a == 4 || a == 6);
			}
		}
	}



	if (b == 2)
	{
		N = wczytaj(&wyniki);
		printf("Jakich zmian chcesz dokonac na swoim sygnale?\n   1. Dodac zaklocenia.\n   2. Dodaj filtr medianowy.\n   3. Dodaj filtr sredniej ruchomej.\n   4. Zapisz zmiany.\n   5. Zakoncz program. \n\n   ");

		do {

			scanf("%d", &c);
			switch (c) {
			case 1:
				zaklocenie(&wyniki, N);
				printf("Zaklocenia dodane poprawnie. Co chcesz zrobic teraz? ");
				break;
			case 2:
				filtr_medianowy(&wyniki, N);
				printf("\nFiltr medianowy zastosowany. Co chcesz zrobic teraz? ");
				break;
			case 3:
				filtr_sr_ruchomej(&wyniki, N);
				printf("\nFiltr sredniej ruchomej zastosowany. Co chcesz zrobic teraz? ");
				break;
			case 4:
				zapisz(wyniki, N);
				free(wyniki);
				printf("\nZmiany zostaly zapisane. Co chcesz zrobic teraz? ");
				break;
			case 5:
				exit(0);
			default:
				c = 6;
				printf("Wybierz liczbe z menu uzytkownika: ");
			}
		} while (c == 1 || c == 2 || c == 3 || c==4 || c == 6);
	}
}


void wczytaj_zakres_dziedziny(float *D1, float *D2) 
{

	do {
		printf("Podaj poczatek dziedziny: ");
		idioto_ochrona_dla_D(D1);

		printf("Podaj koniec dziedziny: ");
		idioto_ochrona_dla_D(D2);

		if (*D1 > *D2)
		{
			printf("Podales poczatek i koniec dziedziny w odwrotnej kolejnosci. Sprobuj jeszcze raz.\n");
		}

		if (*D1 == *D2)
		{
			printf("Poczatek i koniec dziedziny nie moga byc sobie rowne. Sproboj ponownie.\n");
		}

	} while (*D1 >= *D2);

	printf("Dziedzina wprowadzona prawidlowo.");
}

void wczytaj_wspolczynniki(float *tab) 
{
	int i;

	for (i = 0; i < 4; i++) {
		printf("Podaj wspolczynnik %d: ", i + 1);
		idioto_ochrona(&tab[i]);
	}
}

int wczytaj_rozmiar_tab_wynikowej(float D1, float D2, float* dx)
{
	int N;
	N = (D2 - D1) / *dx;
	N += 1;
	return N;
}

void przebieg_funkcji(float *wspolczynniki, float D1, float D2, float **wyniki, float dx, int N)
{
	int i;
	float x;

	for (i = 0; i < N; i++) {
		x = D1 + (i*dx);
		*(*wyniki + i) = (wspolczynniki[0] * x) + (wspolczynniki[1] * sin(wspolczynniki[2] * x)) + wspolczynniki[3];
	}
}

void zaklocenie(float **wyniki, int N)
{
	int i;
	float x;
	float zaklocenie = (rand() % 101) / 100.0;
	int a,b;

	
	for (i = 0; i < N; i++)
	{
		a = rand() % 5;
		b = rand() % 3;
		if (a != 2)
		{
			if (b == 2)
			{
				*(*wyniki + i) += zaklocenie;
			}
			else
			{
				*(*wyniki + i) -= zaklocenie;
			}
		}
	}
}

void zapisz(float *wyniki, int N)
{
	int i = 0;
	FILE* zapissygnalow;
	zapissygnalow = fopen("C:\\Users\\awilk\\Desktop\\zapissygnalow.CSV", "w");

	if (zapissygnalow == NULL)
	{
		printf("blad zapisu");
	}

	else
	{
		for (i = 0; i < N; i++)
		{
			fprintf(zapissygnalow, "%f;", wyniki[i]);
		}
	}

	fclose(zapissygnalow);
}

void filtr_medianowy(float ** wyniki, int N)
{
	float okno[5];
	float *wyniki_po_filtracji_med;
	int i = 0, j = 0, k = 0, x = 0, l = 0;
	int M = N - 4;

	wyniki_po_filtracji_med = (float*)calloc(N, sizeof(float));

	for (i = 0; i < 2; i++)
	{
		wyniki_po_filtracji_med[i] = *(*wyniki + i);
	}

	for (i = N - 2; i < N; i++)
	{
		wyniki_po_filtracji_med[i] = *(*wyniki + i);
	}


	for (l = 0; l < M; l++)
	{

		for (i = l; i < 5 + l; i++)
		{
			okno[i - l] = *(*wyniki + i);
		}
		for (k = 0; k < 5; k++)
		{
			for (j = 1; j < 5; j++)
			{
				if (okno[j - 1] > okno[j])
				{
					x = okno[j];
					okno[j] = okno[j - 1];
					okno[j - 1] = x;
				}
			}
		}
		wyniki_po_filtracji_med[l + 2] = okno[2];
	}
		
		i = 0;
		for (i = 0; i < N; i++)
		{
			*(*wyniki + i) = wyniki_po_filtracji_med[i];
		}
	free(wyniki_po_filtracji_med);
}

void filtr_sr_ruchomej(float ** wyniki, int N)
{
	float okno[5];
	float *wyniki_po_filtracji_sr_ruch;
	int i = 0, l = 0, k = 0;
	int M = N - 4;
	float suma = 0;
	float srednia;

	wyniki_po_filtracji_sr_ruch = (float*)calloc(N, sizeof(float));

	for (i = 0; i < 2; i++)
	{
		wyniki_po_filtracji_sr_ruch[i] = *(*wyniki + i);
	}

	for (i = N - 2; i < N; i++)
	{
		wyniki_po_filtracji_sr_ruch[i] = *(*wyniki + i);
	}


	for (l = 0; l < M; l++)
	{

		for (i = 0; i < 5; i++)
		{
			okno[i] = *(*wyniki + i) + l;
			suma += okno[i];
		}

		srednia = suma / 5;
		wyniki_po_filtracji_sr_ruch[l + 2] = srednia;
		suma = 0;
	}
	
	i = 0;
	for (i = 0; i < N; i++)
	{
		*(*wyniki + i) = wyniki_po_filtracji_sr_ruch[i];
	}
	free(wyniki_po_filtracji_sr_ruch);
}


int wczytaj_float(float * liczba)
{
	float number;
	if (scanf("%f", &number) != 1)
	{
		scanf("%*s");
		return 0;
	}
	else
	{
		*liczba = number;
	}
	return 1;
}

void idioto_ochrona(float * liczba)
{
	while ((wczytaj_float(liczba) != 1)||(*liczba == 0))
	{
		printf("Wprowadzona wartosc jest niepoprawna. Spronuj ponownie.\n");
	}
}

void idioto_ochrona_dla_D(float * liczba)
{
	while (wczytaj_float(liczba) != 1)
	{
		printf("Wprowadzona wartosc jest niepoprawna. Spronuj ponownie.\n");
	}
}

int wczytaj(float **wyniki)
{
	int i = 0;
	FILE* zapissygnalow;
	zapissygnalow = fopen("C:\\Users\\awilk\\Desktop\\zapissygnalow.CSV", "r");
	float *wyniki_proba = NULL;
	*wyniki = NULL;

	if (zapissygnalow == NULL)
	{
		printf("blad wczytywania");
	}

	else
	{
		for (i = 1;; i++)
		{

			wyniki_proba =(float*) realloc(*wyniki, i * sizeof(float));
			if (wyniki_proba == NULL)
			{
				printf("Relokacja nie powiodla sie.\n");
			}
			else
			{
				*wyniki = wyniki_proba;
			}

			if (fscanf(zapissygnalow, "%f;", *wyniki + i - 1) == EOF) break;
		}
	}

	fclose(zapissygnalow);
	return i - 1;
}
