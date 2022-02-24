#include "testailu.h"
#include <stdlib.h>
#include <stdio.h>

int main() 
{
	time_t t;
	srand((unsigned)time(&t));
	
	testaa_jarjesta_polynomi();
	kokeilu1();

}