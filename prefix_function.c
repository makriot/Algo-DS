#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* prefix_function(char* word) {
	
	int n;
	for (n = 0; word[n]; n++)
		;
	n++;
	int* mas = (int*)malloc(sizeof(int) * n);
	if (!mas) return NULL;
	mas[0] = 0;

	int i = 1, j = 0;

	while (word[i]) {

		if (word[i] == word[j]) {
			mas[i] = j + 1;
			i++;
			j++;
		}
		else {
			if (j == 0) {
				mas[i] = 0;
				i++;
			}
			else {
				j = mas[j - 1];
			}
		}

	}

	return mas;

}
