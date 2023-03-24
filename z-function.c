#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* z_function(char* s) {
	int n;
	for (n = 0; s[n] != '\0'; n++) {
		;
	}
	n++;
	int* z = (int*)malloc(sizeof(int) * n);
	if (!z) return NULL;
	for (int j = 0; j < n; j++) {
		z[j] = 0;
	}
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r) {
			l = i, r = i + z[i] - 1;
		}
	}
	return z;
}
