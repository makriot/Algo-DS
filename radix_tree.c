#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 27

typedef enum { word, node } tag_t;

typedef struct tree {

	tag_t tag;

	char* key;
	struct tree* nodes[M + 1];

}tree;

static inline int ord(char c){
	return c ? (int)(c - 'a' + 1) : 0;
};

tree* insert(tree* t, char* string) {

	if (!t) {
		int prom;
		t = (tree*)malloc(sizeof(tree));
		if (!t) return NULL;
		t->tag = node;

		for (int p = 0; p < M + 1; p++) {
			t->nodes[p] = NULL;
		}

		t->nodes[prom = ord(string[0])] = (tree*)malloc(sizeof(tree));
		if (!t->nodes[prom]) return NULL;
		t->nodes[prom]->key = _strdup(string);
		t->nodes[prom]->tag = word;
		for (int p = 0; p < M + 1; p++) {
			t->nodes[prom]->nodes[p] = NULL;
		}

		return t;

	}

	tree* trav = t;
	int i = 0;

	int index;
	while (string[i] && trav->nodes[(index = ord(string[i]))]) {
		
		int j = 0;
		char* str_in = trav->nodes[index]->key;

		while (str_in[j] && string[i] && str_in[j] == string[i]) {
			i++;
			j++;
		}
		if (!str_in[j]) {
			trav = trav->nodes[index];
		}
		else {

			if (!string[i]) {

				tree* new_child = (tree*)malloc(sizeof(tree));
				if (!new_child) return NULL;
				for (int p = 0; p < M + 1; p++) {
					new_child->nodes[p] = NULL;
				}
				new_child->key = _strdup(trav->nodes[index]->key);
				new_child->key[j] = '\0';
				for (int p = 0; p < M + 1; p++) {
					new_child->nodes[p] = NULL;
				}
				new_child->tag = word;
				
				trav->nodes[index]->key = &str_in[j];
				new_child->nodes[ord(trav->nodes[index]->key[0])] = trav->nodes[index];
				trav->nodes[index] = new_child;

			}
			else {

				tree* new_main = (tree*)malloc(sizeof(tree));
				tree* new_child = (tree*)malloc(sizeof(tree));
				if (!new_main || !new_child) return NULL;
				for (int p = 0; p < M + 1; p++) {
					new_main->nodes[p] = NULL;
					new_child->nodes[p] = NULL;
				}

				new_main->key = _strdup(trav->nodes[index]->key);
				new_main->key[j] = '\0';
				new_main->tag = node;

				new_child->key = _strdup(&string[i]);
				new_child->tag = word;

				trav->nodes[index]->key = &str_in[j];

				new_main->nodes[ord(trav->nodes[index]->key[0])] = trav->nodes[index];
				new_main->nodes[ord(new_child->key[0])] = new_child;
				trav->nodes[index] = new_main;

			}
			return t;

		}

	}

	if (string[i]) {
		trav->nodes[index = ord(string[i])] = (tree*)malloc(sizeof(tree));
		if (!trav->nodes[index]) return NULL;
		trav->nodes[index]->key = _strdup(&string[i]);
		trav->nodes[index]->tag = word;
		for (int p = 0; p < M + 1; p++) {
			trav->nodes[index]->nodes[p] = NULL;
		}

	}
	else {
		trav->tag = word;
	}

	return t;

}

int searching(tree* t, char* string) {

	int i = 0;
	tree* trav = t;
	int index;

	while (string[i] && trav->nodes[index = ord(string[i])]) {
		int j = 0;
		char* str_in = trav->nodes[index]->key;
		while (str_in[j] && string[i] && string[i] == str_in[j]) {
			i++;
			j++;
		}
		if (!str_in[j] && !string[i] && trav->nodes[index]->tag == word) {
			return 1;
		}
		if (!str_in[j] && !string[i] && trav->nodes[index]->tag == node) {
			return 0;
		}
		if (!str_in[j] && string[i]) {
			trav = trav->nodes[index];
		}
		else {
			return 0;
		}
	}
	return 0;

}

int main(void) {
	tree* head = NULL;
	/*head = insert(head, "haha");
	if (head == NULL) return 1;
	head = insert(head, "hoho");
	if (head == NULL) return 1;
	head = insert(head, "hehe");
	if (head == NULL) return 1;
	head = insert(head, "word");
	if (head == NULL) return 1;*/

	/*head = insert(head, "zhereafter");
	head = insert(head, "zherein");*/
	head = insert(head, "zhis");
	head = insert(head, "zhis");

	//printf("%s", head->nodes[ord('t')]->nodes[ord('e')]->nodes[ord('i')]->key);
	if (searching(head, "zhis")) printf("yea");
	for (int i = 0; i < M + 1; i++) {
		if (head->nodes[i]) {
			for (int j = 0; j < M + 1; j++) {
				if (head->nodes[i]->nodes[j]) {
					printf("ha");
				}
			}
		}
	}
	
	return 0;
}
