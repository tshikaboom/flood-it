#include <stdio.h>
#include <stdlib.h>
#include "Pile_case.h"

int main(void)
{
	Pile p;
	init_pile(&p);

	empile(&p, 2, 5);
	printf("%d %d\n", (p.e)->i, (p.e)->j);
}
