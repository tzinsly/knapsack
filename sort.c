/*
 * sort.c
 *
 *  Created on: 10 de mai de 2016
 *      Author: Zinsly
 */

void BubbleSort(int vet[], int tamanho) {
	int aux, i, j;

	for (i = 0; i < tamanho; i++) {
		for (j = 0; j < (tamanho - 1); j++) {
			if (vet[j] > vet[j + 1]) {
				aux = vet[j];
				vet[j] = vet[j + 1];
				vet[j + 1] = aux;
			}
		}
	}
}
