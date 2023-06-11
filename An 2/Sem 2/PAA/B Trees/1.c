#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N   2
#define NN (N*2)

typedef struct Persoana
{
    int unix_epoch_time;
    char nume[128];
} Persoana;

typedef struct Nod
{
    Persoana persoana;
	struct Pagina* p;
	int contor;
} Nod;

typedef struct Pagina
{
	int m;
	struct Pagina* p0;
	Nod e[NN + 1];
} Pagina;

Pagina* insereaza(Pagina *pag, Persoana x, Nod *nod);
void afisare(Pagina *arbore, int nivel);
Pagina* suprima(Pagina *pag, Persoana x, Nod *nod);


Pagina *root = NULL;
Nod v;

Pagina* insereaza(Pagina *pag, Persoana x, Nod *nod)
{
	int i, s, d, mij;
	Pagina *q, *r;

	if (!nod)
	{
		v.persoana.unix_epoch_time = x.unix_epoch_time;
        strcpy(v.persoana.nume, x.nume);
		v.contor = 1;
		v.p = NULL;
	}
	else
		v = *nod;

	if (pag == NULL) //daca nu exista radacina
	{
		pag = (Pagina*)calloc(sizeof(Pagina), 1);
		pag->e[++pag->m] = v;

		return pag;
	}

	//se cauta binar pozitia cheii x in pagina curenta
	s = 1;
	d = pag->m;
	while (s <= d)
	{
		mij = (s + d) / 2;
		if (pag->e[mij].persoana.unix_epoch_time == x.unix_epoch_time) //gasit
		{
			pag->e[mij].contor++;
			return pag;
		}
		if (x.unix_epoch_time < pag->e[mij].persoana.unix_epoch_time)
			d = mij - 1;
		else
			s = mij + 1;
	}

	//daca este pagina terminala sau daca se propaga insertia
	if (pag->p0 == NULL || nod)
	{
		if (pag->m < NN) //se poate adauga un nod in pagina curenta
		{
			++pag->m;
			for (i = pag->m; i > d + 1; i--)
				pag->e[i] = pag->e[i - 1];
			pag->e[i] = v;
		}
		//pagina curenta pag este plina => supradepasire => pagina trebuie scindata
		else
		{
			Pagina *a = pag;
			Pagina *b = (Pagina*)calloc(sizeof(Pagina), 1);
			pag = (Pagina*)calloc(sizeof(Pagina), 1);

			//scindarea paginii curente
			for (i = 1; i <= N; i++)
				b->e[i] = a->e[i + N];
			a->m = b->m = N;

			//cheia noudului v e cheia de scindare
			if (v.persoana.unix_epoch_time > a->e[N].persoana.unix_epoch_time && v.persoana.unix_epoch_time < b->e[1].persoana.unix_epoch_time)
				pag->e[++pag->m] = v;
			else
			{
				//ultima cheie a nodului a este folosita la scindare
				if (v.persoana.unix_epoch_time < a->e[N].persoana.unix_epoch_time)
				{
					pag->e[++pag->m] = a->e[N];
					for (i = a->m; i > 1 && a->e[i - 1].persoana.unix_epoch_time > v.persoana.unix_epoch_time; i--)
						a->e[i] = a->e[i - 1];
					a->e[i] = v;
				}
				//prima cheie a nodului a este folosita la scindare
				else
				{
					pag->e[++pag->m] = b->e[1];
					for (i = 1; i < b->m && b->e[i + 1].persoana.unix_epoch_time < v.persoana.unix_epoch_time; i++)
						b->e[i] = b->e[i + 1];
					b->e[i] = v;
				}
			}

			//se refac legaturile intre pagini
			b->p0 = pag->e[1].p; //prima legatura a paginii b devine legatura nodului parinte
			pag->p0 = a;         //prima legatura a nodului parinte devine fostul vecin stanga
			pag->e[1].p = b;     //a doua legatura a nodului parinte devine fostul vecin dreapta
		}
	}
	else
	{
		if (d == 0) //s-a ajuns la cel mai din stanga element => prima legatura
			q = pag->p0;
		else
			q = pag->e[d].p;
		r = insereaza(q, x, NULL);
		if (r != q) //daca pagina in care s-a inserat s-a scindat <=> arborele crescut cu un nivel
		{
			/*se incearca inserarea nodului din pagina scindata in pagina curenta
			in caz de succes, arborele nu va creste in inaltime*/
			pag = insereaza(pag, r->e[1].persoana, &r->e[1]);
			free(r); //se sterge pagina scindata, intrucat nodul a fost inserat intr-o alta pagina
		}
	}

	return pag;
}

void afisare(Pagina *arbore, int unix)
{
	int i;

	if (!arbore)
		return;
	afisare(arbore->p0, unix);
	for (i = 1; i <= arbore->m; i++)
		afisare(arbore->e[i].p, unix);

	for (i = 1; i <= arbore->m; i++) {
        if (arbore->e[i].persoana.unix_epoch_time > unix) {
		    printf("%s\n", arbore->e[i].persoana.nume);
        }
    }
}

int main(void) {
    Persoana records[8];

    strcpy(records[0].nume, "John Doe");
    records[0].unix_epoch_time = 1;

    strcpy(records[1].nume, "Jane Smith");
    records[1].unix_epoch_time = 2;

    strcpy(records[2].nume, "Michael Johnson");
    records[2].unix_epoch_time = 3;

    strcpy(records[3].nume, "Emily Williams");
    records[3].unix_epoch_time = 4;

    strcpy(records[4].nume, "Christopher Brown");
    records[4].unix_epoch_time = 5;

    strcpy(records[5].nume, "Sophia Davis");
    records[5].unix_epoch_time = 6;

    strcpy(records[6].nume, "Daniel Wilson");
    records[6].unix_epoch_time = 7;

    strcpy(records[7].nume, "Olivia Taylor");
    records[7].unix_epoch_time = 8;

    for (int i = 0; i < 8; i++) {
        root = insereaza(root, records[i], NULL);
    }

    afisare(root, 4);
    return 0;
}