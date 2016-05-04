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
#define NUMCHR 5;
#define KP_VOL 40;

struct cell {
	int ben;
	int vol;

} typedef cell;

struct cell items[4];
int chromossome[5][4][2];

int calcVol(int chrom_num){
	int vol = 0;
	int i;
	for (i = 0; i < 4; i++){
		vol = vol + chromossome[chrom_num][i][0] * items[i].vol;
	}
	return (vol);
}

int calcFit(int chrom_num){
	int fit = 0;
		int i;
		for (i = 0; i < 4; i++){
			fit = fit + chromossome[chrom_num][i][0] * items[i].ben;
		}
		return (fit);
}

//1 point for Crossover
int crossOver(int chrom1, int chrom2){
	//chromossome[0][0][1]
	//chromossome[0][1][1]

}

int knapsack(){

	/**The first dimension (5) represents the number of chromosomes in a population
	*  The second dimension (4) represents the number of items to be placed into the knapsack
	*  The third dimension (2) is used to former the new generation
	**/


	struct cell chroms[5];

	//Initialize item (could be from file):
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
	int j;
	//int u;

	//for (u=0; u<2; u++){
		for (j=0; j<5; j++)
		{
			for (i = 0; i < 4; i++)
			{
				chromossome[j][i][0] = (rand() % 4);
				printf(">> Chromossome %d %d %d = %d\n", j, i, 0, chromossome[j][i][0]);
			}
			chroms[j].vol = calcVol(j);
			chroms[j].ben = calcFit(j);
			printf("Vol chromossome %d = %d\n", j, chroms[j].vol);
			printf("Fit chromossome %d = %d\n", j, chroms[j].ben);
		}
	//}

	return 0;
}


