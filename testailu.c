#include <stdio.h>
#include <stdlib.h>
#include "polynomit.h"

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