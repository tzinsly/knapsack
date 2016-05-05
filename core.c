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
#define REP_RATE 0,8;

struct cell {
	int ben;
	int vol;

} typedef cell;

struct cell items[4];	  /*Possible itens to be placed into the knapsack and its volume and benefit*/
int chromosome[5][4][2]; /*Chromosome of two populations*/
struct cell chroms[5][2];    /*Volume and benefit of each chromosome from current population*/

int calcVol(int chrom_num, int pop){
	int vol = 0;
	int i;
	for (i = 0; i < 4; i++){
		vol = vol + chromosome[chrom_num][i][pop] * items[i].vol;
	}
	return (vol);
}

int calcFit(int chrom_num, int pop){
	int fit = 0;
	int i;
	for (i = 0; i < 4; i++){
		fit = fit + chromosome[chrom_num][i][pop] * items[i].ben;
	}
	if (chroms[chrom_num][pop].vol > 40){
		return 0;
	} else {
		return (fit);
	}

}

/*
void calcFit(int chrom_num){
	int fitness;
	if (chroms[chrom_num].vol > 40){
		chroms[chrom_num].ben = 0;
	}
}
*/

//1 point for Crossover
int crossOver(int chrom1, int chrom2){
	//chromosome[0][0][1]
	//chromosome[0][1][1]
	return 0;
}

int knapsack(){

	/**The first dimension (5) represents the number of chromosome in a population
	*  The second dimension (4) represents the number of items to be placed into the knapsack
	*  The third dimension (2) is used to former the new generation
	**/

	/*
	 * Initialize benefit and volume for each item:
	 */
	items[0].ben = 5;
	items[0].vol = 6;

	items[1].ben = 8;
	items[1].vol = 7;

	items[2].ben = 3;
	items[2].vol = 8;

	items[3].ben = 9;
	items[3].vol = 5;

	int reprod[5];
	int i; /*Item number*/
	int c; /*Chromosome number*/
	int p = 0;

		for (c=0; c<5; c++)
		{
			for (i = 0; i < 4; i++)
			{
				chromosome[c][i][0] = (rand() % 4);
				printf(">> Chromosome %d %d %d = %d\n", c, i, 0, chromosome[c][i][p]);
			}
			chroms[c][p].vol = calcVol(c, p);
			chroms[c][p].ben = calcFit(c, p);

			printf("Vol chromosome %d = %d\n", c, chroms[c][p].vol);
			printf("Fit chromosome %d = %d\n", c, chroms[c][p].ben);
		}

		/*
		 * Reproduction Rate of 80%
		 * Selection by Tournament
		 */
		int count;
		int cand1, cand2;
		for (count=0; count<(5*0.8); count++ ){
			cand1 = (rand() % 6);
			cand2 = (rand() % 6);
			if( chroms[cand1][p].ben > chroms[cand2][p].ben){
				reprod[count] = cand1;
			} else {
				reprod[count] = cand2;
			}
		}

	return 0;
}


