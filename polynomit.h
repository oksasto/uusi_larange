#ifndef	POLYNOMIT_H
#define	POLYNOMIT_H

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

int vertaa_monomien_aste(const void* mono1, const void* mono2);

void jarjesta_polynomi(struct polynomi* kohde);

void alusta_polynomi(struct polynomi* uusi);

void lisaa_polynomiin(struct polynomi* kohde, struct monomi* lisattava);

void tulosta_polynomi(struct polynomi* tulostettava);

void alusta_lause(struct lause* uusi);

void lisaa_lauseeseen(struct lause* kohde, struct termi* lisattava);

void tulosta_lause(struct lause* tulostettava);

struct polynomi* summaa_polynomit(struct polynomi* nomi1, struct polynomi* nomi2);


#endif //POLYNOMIT_H
