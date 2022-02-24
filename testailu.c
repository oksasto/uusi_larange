#include <stdio.h>
#include <stdlib.h>
#include "polynomit.h"

void testaa_jarjesta_polynomi(void)
{
	//viela testaamatta se etta samanmerkkisten termien summaaminen tapahtuu oikein
	int tulosta_turhaa = 0;//true/false
	int testi_kerrat = 10000;
	int aste_max = 1;
	int kerroin_max = 500;
	int koko = 2000;

	struct polynomi poly1;
	
	poly1.pituus = koko;


	int kerta;
	int i;

	for (kerta = 0; kerta < testi_kerrat; kerta++)
	{
		
		poly1.jasenet = malloc(sizeof(struct monomi) * koko);
		poly1.pituus = koko;
		for (i = 0; i < koko; i++)
		{
			poly1.jasenet[i].aste = rand() % aste_max;
			poly1.jasenet[i].kerroin = (float)(rand() % kerroin_max);
		}
		//lasketaan paljonko polynomissa on eri asteisia monomeja
		int termien_maara = 0;
		int* termien_asteet = malloc(sizeof(int) * koko);
		if(termien_asteet == NULL)
			exit(EXIT_FAILURE);
		for (i = 0; i < koko; i++)
		{
			int i2;
			for (i2 = 0; i2 < termien_maara; i2++)
			{
				if (termien_asteet[i2] == poly1.jasenet[i].aste)
					break;
			}
			//jos astetta ei loytynyt listasta, lisataan se
			if (i2 == termien_maara)
			{
				termien_asteet[i2] = poly1.jasenet[i].aste;
				termien_maara++;
			}
		}
		free(termien_asteet);

		jarjesta_polynomi(&poly1);


		if (tulosta_turhaa)
		{
			printf("asteiden maara ennen jarjestamista: %d ja jalkeen: %d\n", termien_maara, poly1.pituus);
			tulosta_polynomi(&poly1);
			printf("\n");
		}
		//testataan etta samanmerkkiset yhdistettiin niin etta maara tasmaa
		if (termien_maara != poly1.pituus)
		{
			printf("virhe asteiden yhdistamisessa\n");
			printf("asteiden maara ennen jarjestamista: %d ja jalkeen: %d\n", termien_maara, poly1.pituus);
			tulosta_polynomi(&poly1);
		}
			

		//testataan etta polynomi jarjestyi oikein
		int edellisen_aste = poly1.jasenet[0].aste;
		for (i = 1; i < poly1.pituus; i++)
		{
			if (edellisen_aste <= poly1.jasenet[i].aste)
				printf("Virhe polynomin jarjestyksessa i=%d\n", i);
			edellisen_aste = poly1.jasenet[i].aste;
		}
		free(poly1.jasenet);
	}
	

	printf("jarjesta_polynomi testattu %d kertaa\n",testi_kerrat);

}


void kokeilu1(void)
{
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