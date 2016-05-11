/*
 * core.c
 *
 *  Created on: 19 de abr de 2016
 *      Author: Zinsly
 */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define NUMCRH 10
#define NUMITENS 4
#define KP_VOL 40
#define REP_RATE 0.8
#define STOP_LIMIT 100
#define POP 2

struct cell {
	int ben;
	int vol;

}typedef cell;

struct cell items[NUMITENS]; /*Possible itens to be placed into the knapsack and its volume and benefit*/
int chromosome[NUMCRH][NUMITENS][POP]; /*Chromosome of two populations*/
struct cell chroms[NUMCRH];
int reprod[NUMCRH];

void BubbleSort(int vetor[], int tamanho);

int calcVol(int chrom_num) {
	int vol = 0;
	int i;
	int pop = 0;
	for (i = 0; i < NUMITENS; i++) {
		vol = vol + chromosome[chrom_num][i][pop] * items[i].vol;
	}
	return (vol);
}

int calcFit(int chrom_num) {
	int fit = 0;
	int i;
	int pop = 0;
	for (i = 0; i < NUMITENS; i++) {
		fit = fit + chromosome[chrom_num][i][pop] * items[i].ben;
	}
	if (chroms[chrom_num].vol > KP_VOL) {
		return 0;
	} else {
		return (fit);
	}

}

void eval() {
	int i; /*Item number*/
	int c; /*Chromosome number*/

	for (c = 0; c < NUMCRH; c++) {
		for (i = 0; i < NUMITENS; i++) {
			chroms[c].vol = calcVol(c);
			chroms[c].ben = calcFit(c);
		}
		printf("Vol chromosome %d = %d\n", c, chroms[c].vol);
		printf("Fit chromosome %d = %d\n", c, chroms[c].ben);
	}
}

void select_parents() {
	/*
	 * Reproduction Rate of 80%
	 * Selection by Tournament
	 */
	int count;
	int cand1, cand2;
	for (count = 0; count < (NUMCRH * REP_RATE); count++) {
		cand1 = (rand() % NUMCRH);
		cand2 = (rand() % NUMCRH);
		if (chroms[cand1].ben > chroms[cand2].ben) {
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
	int pop2 = 1;
	int i;

	for (count = 0; count <= (limit - 2); count = count + 2) {

		cross_point = (rand() % 3);
		for (i = 0; i <= cross_point; i++) {
			chromosome[count][i][pop2] = chromosome[reprod[count]][i][pop1];
			chromosome[count + 1][i][pop2] =
					chromosome[reprod[count + 1]][i][pop1];
			printf(">> Chromosome %d %d 1 = %d\n", count, i,
					chromosome[count][i][pop2]);
			printf(">> Chromosome %d %d 1 = %d\n", count + 1, i,
					chromosome[count + 1][i][pop2]);
		}

		for (i = cross_point + 1; i <= (NUMITENS - 1); i++) {
			chromosome[count][i][pop2] = chromosome[reprod[count + 1]][i][pop1];
			chromosome[count + 1][i][pop2] = chromosome[reprod[count]][i][pop1];

			printf(">> Chromosome %d %d 1 = %d\n", count, i,
					chromosome[count][i][pop2]);
			printf(">> Chromosome %d %d 1 = %d\n", count + 1, i,
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
	int replic = NUMCRH - (NUMCRH * REP_RATE);
	int crm[replic];

	int temp_array[NUMCRH];

	for (c = 0; c < NUMCRH; c++){
		temp_array[c] = chroms[c].ben;
	}
	BubbleSort(temp_array, NUMCRH);

	/*
	 * Verifying what are the bests chromosomes
	 */
	int j = 0;
	for (i=NUMCRH-1; i>=(NUMCRH-replic); i--,j++){
		for (c = 0; c < NUMCRH; c++) {
			if ( (chroms[c].ben == temp_array[i])) {
				if( (j == 0) || (j != 0 && crm[j-1] != c) ){
					crm[j] = c;
					c = NUMCRH;
				}
			}
		}
	}

	/*Replicating the bests for the next generation*/
	int pos = 0;
	for (c = (NUMCRH * REP_RATE); c<NUMCRH; c++,pos++){
		for (i = 0; i < NUMITENS; i++) {
			chromosome[c][i][1] = chromosome[crm[pos]][i][0];
		}
	}

	/*Bringing pop 2 to pop 1*/
	printf("Next Generation\n");
	for (c = 0; c < NUMCRH; c++) {
		for (i = 0; i < NUMITENS; i++) {
			chromosome[c][i][0] = chromosome[c][i][1];
			printf("%d  ", chromosome[c][i][0]);
		}
		printf("\n");
	}
}

/*
 * This function analyzes if more than 80% of the population has the
 */
int converg() {
	int c;
	int conv = 1;
	int conv_aux = 0;
	int temp_array[NUMCRH];

	for (c = 0; c < NUMCRH; c++){
		temp_array[c] = chroms[c].ben;
	}

	BubbleSort(temp_array, NUMCRH);

	for (c = 0; c < NUMCRH; c++) {
		if (temp_array[c] == temp_array[c + 1]) {
			conv++;
		} else if (conv > conv_aux) {
			conv_aux = conv;
			conv = 1;
		}
	}
	return conv_aux;
}
void knapsack() {

	/**The first dimension (NUMCRH) represents the number of chromosome in a population
	 *  The second dimension (NUMITENS) represents the number of items to be placed into the knapsack
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
	for (c = 0; c < NUMCRH; c++) {
		for (i = 0; i < NUMITENS; i++) {
			chromosome[c][i][p] = (rand() % NUMITENS);
			printf("%d  ", chromosome[c][i][p]);
		}
		printf("\n");
	}

	/*
	 * Repeat while less than 80% of population has the same fitness value && count less than 500x
	 */
	int iteration, it;
	for (iteration = 0; iteration <= STOP_LIMIT; iteration++) {
		eval();
		if (converg() >= (NUMCRH * REP_RATE)) {
			it = iteration+1;
			iteration = STOP_LIMIT;
		} else {
			it = iteration+1;
			select_parents();
			crossOver(NUMCRH * REP_RATE);
			next_gen();
		}
	}
	printf(">> Num Iterations: %d\n", it);

}

