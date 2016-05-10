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
#define NUMCRH 5;
#define KP_VOL 40;
#define REP_RATE 0,8;
#define STOP_LIMIT 500;

struct cell {
	int ben;
	int vol;

}typedef cell;

struct cell items[4]; /*Possible itens to be placed into the knapsack and its volume and benefit*/
int chromosome[5][4][2]; /*Chromosome of two populations*/
struct cell chroms[5][2]; /*Volume and benefit of each chromosome from current population*/
int reprod[5];

int calcVol(int chrom_num, int pop) {
	int vol = 0;
	int i;
	for (i = 0; i < 4; i++) {
		vol = vol + chromosome[chrom_num][i][pop] * items[i].vol;
	}
	return (vol);
}

int calcFit(int chrom_num, int pop) {
	int fit = 0;
	int i;
	for (i = 0; i < 4; i++) {
		fit = fit + chromosome[chrom_num][i][pop] * items[i].ben;
	}
	if (chroms[chrom_num][pop].vol > 40) {
		return 0;
	} else {
		return (fit);
	}

}

void eval(int p) {
	int i; /*Item number*/
	int c; /*Chromosome number*/

	for (c = 0; c < 5; c++) {
		for (i = 0; i < 4; i++) {
			chroms[c][p].vol = calcVol(c, p);
			chroms[c][p].ben = calcFit(c, p);
		}
		printf("Vol chromosome %d = %d\n", c, chroms[c][p].vol);
		printf("Fit chromosome %d = %d\n", c, chroms[c][p].ben);
	}
}



void select_parents(int p) {
	/*
	 * Reproduction Rate of 80%
	 * Selection by Tournament
	 */
	int count;
	int cand1, cand2;
	for (count = 0; count < (5 * 0.8); count++) {
		cand1 = (rand() % 5);
		cand2 = (rand() % 5);
		if (chroms[cand1][p].ben > chroms[cand2][p].ben) {
			reprod[count] = cand1;
		} else {
			reprod[count] = cand2;
		}
		printf("Reprod %d = %d\n", count, reprod[count]);
	}
}
//1 point for Crossover
void crossOver(int limit) {
	int count;
	int cross_point;
	int pop1 = 0;
	int pop2 = 0;
	int i;

	for (count=0; count <= (limit / 2); count=count+2) {

		cross_point = (rand() % 3);
		for (i = 0; i <= cross_point; i++) {
			chromosome[count][i][pop2] = chromosome[reprod[count]][i][pop1];
			chromosome[count + 1][i][pop2] = chromosome[reprod[count + 1]][i][pop1];
			printf(">> Chromosome %d %d 1 = %d\n", count, i,
					chromosome[count][i][pop2]);
			printf(">> Chromosome %d %d 1 = %d\n", count+1, i,
					chromosome[count + 1][i][pop2]);
		}

		for (i = cross_point + 1; i <= (4-1); i++) {
			chromosome[count][i][pop2] = chromosome[reprod[count +1]][i][pop1];
			chromosome[count + 1][i][pop2] =
					chromosome[reprod[count]][i][pop1];

			printf(">> Chromosome %d %d 1 = %d\n", count, i,
					chromosome[count][i][pop2]);
			printf(">> Chromosome %d %d 1 = %d\n", count+1, i,
					chromosome[count + 1][i][pop2]);
		}

		printf("Cross_point = %d \n", cross_point);

	}
}

void next_gen() {

	/*
	 * Selecting next item by Elitism
	 */
	int i, c;
	int crm;

	/*
	 * Verifying what is the best chromosome
	 */
	for (c = 0; c < 5; c++) {
		if (chroms[c][0].ben > chroms[4][1].ben) {
			chroms[4][1].ben = chroms[c][0].ben;
			chroms[4][1].vol = chroms[c][0].vol;
			crm = i;
		}
	}

	/*Replicating the best one for the next generation*/
	for (i = 0; i < 4; i++) {
		chromosome[4][i][1] = chromosome[crm][i][0];
	}

	/*Bringing pop 2 to pop 1*/
	for (c = 0; c < 5; c++) {
		for (i = 0; i < 4; i++) {
			chromosome[c][i][0] = chromosome[c][i][1];
		}
	}
}

int knapsack() {

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

	int i; /*Item number*/
	int c; /*Chromosome number*/
	int p = 0; /*Pop 1*/

	/*
	 * Generating first Population
	 */
	printf("First pop\n");
	for (c = 0; c < 5; c++) {
		for (i = 0; i < 4; i++) {
			chromosome[c][i][p] = (rand() % 4);
			printf("%d  ", chromosome[c][i][p]);
		}
		printf("\n");
	}

	/*
	 * Repeat while less than 80% of population has the same fitnessa value && count less than 500x
	 */
	int iteration;
	for (iteration = 0; iteration <= 0; iteration++) {
		eval(p);
		select_parents(p);
		crossOver(5 * 0.8);

	}

	return 0;
}

