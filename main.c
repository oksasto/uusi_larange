#include <stdio.h>
#include <stdlib.h>

struct monomi {
	int aste;
	float kerroin;
};

struct polynomi {
	int pituus;
	struct monomi* jasenet;
};

enum tyypit {
	POLYNOMI,
	VAKIO,
	KERTAA,
	JAKO,
	PLUS,
	S_AUKI,
	S_KIINNI
};

struct termi {
	enum tyypit tyyppi;
	struct polynomi* osoite;
};

struct lause {
	int pituus;
	struct termi* jasenet;
};

//EI TESTATTU
int vertaa_monomien_aste(const void* mono1, const void* mono2)
{
	int aste1 = ((struct monomi*)mono1)->aste;
	int aste2 = ((struct monomi*)mono2)->aste;
	//haluamme positiivisen jos ensimmainen pienempi koska lajittelemme laskevaan jarjestykseen
	if (aste1 > aste2) return -1;
	if (aste1 < aste2) return 1;
	return 0;

	//tama on parempi ainoastaan jos ehtolauseet ovat hitaita.
	//return (aste1 < aste2) - (aste1 > aste2);
}
//ei testattu
void jarjesta_polynomi(struct polynomi* kohde)
{
	//monomien jarjestaminen laskevaan jarjestykseen asteen mukaan.
	qsort(kohde->jasenet, kohde->pituus, sizeof(struct monomi), &vertaa_monomien_aste);
	
	//samojen termien yhdistaminen.

	int i1 = 0;
	int i2 = 1;
	while (i2 < kohde->pituus)
	{
		if (kohde->jasenet[i1].aste == kohde->jasenet[i2].aste)
		{
			kohde->jasenet[i1].kerroin += kohde->jasenet[i2].kerroin;
			i2++;

		}
		else
		{
			i1++;
			kohde->jasenet[i1].aste = kohde->jasenet[i2].aste;
			kohde->jasenet[i1].kerroin = kohde->jasenet[i2].kerroin;
			i2++;
		}
	}
	kohde->pituus = i1;
}

void alusta_polynomi(struct polynomi* uusi){
	uusi->pituus = 0;
	uusi->jasenet = NULL;
}

//MUOKKAA JÄRJESTYKSEN YLLÄPITÄVÄKSI!!
void lisaa_polynomiin(struct polynomi* kohde, struct monomi* lisattava) {
	int indeksi = kohde->pituus;
	kohde->pituus++;
	kohde->jasenet = realloc(kohde->jasenet, kohde->pituus * sizeof(struct monomi));
	if (kohde->jasenet == NULL)
		exit(EXIT_FAILURE);
	kohde->jasenet[indeksi].aste = lisattava->aste;
	kohde->jasenet[indeksi].kerroin = lisattava->kerroin;
}

void tulosta_polynomi(struct polynomi* tulostettava) {
	for (int i = 0; i < tulostettava->pituus; i++) {
		printf("%+.2f", tulostettava->jasenet[i].kerroin);
		if (tulostettava->jasenet[i].aste != 0) {
			printf("*x^%d", tulostettava->jasenet[i].aste);
		}
	}
}

void alusta_lause(struct lause* uusi) {
	uusi->pituus = 0;
	uusi->jasenet = NULL;
}

void lisaa_lauseeseen(struct lause* kohde, struct termi* lisattava) {
	int indeksi = kohde->pituus;
	kohde->pituus++;
	kohde->jasenet = realloc(kohde->jasenet, kohde->pituus * sizeof(struct monomi));
	if(kohde->jasenet == NULL)
		exit(EXIT_FAILURE);
	kohde->jasenet[indeksi].tyyppi = lisattava->tyyppi;
	kohde->jasenet[indeksi].osoite = lisattava->osoite;
}

void tulosta_lause(struct lause* tulostettava) {
	for (int i = 0; i < tulostettava->pituus; i++) {
		switch (tulostettava->jasenet[i].tyyppi)
		{
		case POLYNOMI:
			tulosta_polynomi(tulostettava->jasenet[i].osoite);
			break;
		default:
			printf("\nTuntematon termi-tyyppi lausetta tulostaessa!");
			break;
		}
	}
}

//EI TESTATTU!!!
struct polynomi* summaa_polynomit(struct polynomi* nomi1, struct polynomi* nomi2) {
	//luodaan lista, johon tallennetaan summauksen tulos
	int pituus0;
	pituus0 = nomi1->pituus + nomi2->pituus;
	if (pituus0 == 0)
		exit(EXIT_FAILURE);
	struct monomi* jasenet0;
	jasenet0 = malloc(pituus0 * sizeof(struct monomi));
	if (jasenet0 == NULL)
		exit(EXIT_FAILURE);

	//summataan tarkasteltavat polynomit luotuun listaan
	int i0 = 0;
	int i1 = 0;
	int i2 = 0;
	while (i0 < pituus0 && (i1 < nomi1->pituus || i2 < nomi2->pituus))
	{
		//tarkastetaan ettei kasiteltavat polynomit ole loppuneet
		if (i0 < pituus0 && i1 < nomi1->pituus && i2 < nomi1->pituus)
		{
			//jos tarkasteltavien monomien aste on sama, summataan ne
			if (nomi1->jasenet[i1].aste == nomi2->jasenet[i2].aste)
			{
				jasenet0[i0].aste = nomi1->jasenet[i1].aste;
				jasenet0[i0].kerroin = nomi1->jasenet[i1].kerroin + nomi2->jasenet[i2].kerroin;
				i0++;
				i1++;
				i2++;
			}
		}
		//tarkastetaan ettei kasiteltavat polynomit ole loppuneet
		if (i0 < pituus0 && i1 < nomi1->pituus)
		{
			//jos ensimmäisen polynomin monomin aste on suurempi, lisataan se listaan
			if (nomi1->jasenet[i1].aste > nomi2->jasenet[i2].aste)
			{
				jasenet0[i0].aste = nomi1->jasenet[i1].aste;
				jasenet0[i0].kerroin = nomi1->jasenet[i1].kerroin;
				i0++;
				i1++;
			}
		}
		//tarkastetaan ettei kasiteltavat polynomit ole loppuneet
		if (i0 < pituus0 && i2 < nomi2->pituus)
		{
			//jos toisen polynomin monomin aste on suurempi, lisataan se listaan
			if (nomi1->jasenet[i1].aste < nomi2->jasenet[i2].aste)
			{
				jasenet0[i0].aste = nomi2->jasenet[i2].aste;
				jasenet0[i0].kerroin = nomi2->jasenet[i2].kerroin;
				i0++;
				i2++;
			}
		}
	}//while paattyy
	//varmistetaan etta molemmat summattavat polynomit tulivat taysin kasitellyiksi DEBUG?
	if (i1 < nomi1->pituus || i2 < nomi2->pituus)
		exit(EXIT_FAILURE);

	struct polynomi* nomi0 = malloc(sizeof(struct polynomi));
	if (nomi0 == NULL)
		exit(EXIT_FAILURE);
	nomi0->jasenet = jasenet0;
	nomi0->pituus = i0;
	return nomi0;
}


int main() {

	struct monomi monomi1;
	monomi1.aste = 0;
	monomi1.kerroin = 2;

	struct monomi monomi2 = { .aste = 2,.kerroin = 3 };


	struct polynomi polynomi1;
	alusta_polynomi(&polynomi1);
	lisaa_polynomiin(&polynomi1, &monomi1);
	printf("polynomi1 sisaltaa: %d jasentan\n", polynomi1.pituus);
	lisaa_polynomiin(&polynomi1, &monomi2);
	printf("polynomi1 sisaltaa: %d jasenta\n", polynomi1.pituus);
	tulosta_polynomi(&polynomi1);
	printf("\n");

	struct termi termi1;
	termi1.tyyppi = POLYNOMI;
	termi1.osoite = &polynomi1;

	struct lause lause1;
	alusta_lause(&lause1);
	lisaa_lauseeseen(&lause1, &termi1);
	tulosta_lause(&lause1);
	printf("\n");
	lisaa_lauseeseen(&lause1, &termi1);//TAMA ON PAHA JA PITAISI ESTAA!!!
	tulosta_lause(&lause1);


	printf("\n");
}