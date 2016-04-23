/*
 * core.c
 *
 *  Created on: 19 de abr de 2016
 *      Author: Zinsly
 */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define NUMITEMS 4;
#define KP_VOL 26;

struct cell {
	int ben;
	int vol;

} typedef cell;

int knapsack(){

	/**The first dimension (5) represents the number of chromosomes in a population
	*  The second dimension (4) represents the number of items to be placed into the knapsack
	*  The third dimension (2) is used to former the new generation
	**/

	int chromossome[5][4][2];
	struct cell items[4];

	//Initialize item:
	items[0].ben = 1;
	items[0].vol = 6;

	items[1].ben = 2;
	items[1].vol = 7;

	items[2].ben = 3;
	items[2].vol = 8;

	items[3].ben = 4;
	items[3].vol = 5;

	//Generate random numbers from 0 to 3

	int i;
	for (i = 0; i < 40; i++)
	{
		/* generating random values between 0 and 3 */
		printf("%d ", rand() % 4);
	}

	chromossome[0][0][0] = 2;
	chromossome[0][1][0] = 1;
	chromossome[0][2][0] = 0;
	chromossome[0][3][0] = 5;



	return 0;
}


