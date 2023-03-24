#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tnode {
	long long number;
	long long value;
	int height;
	struct tnode* left;
	struct tnode* right;
}tnode;


tnode* balance(tnode* p);
int flag = 0;

tnode* addtree(tnode* p, long long item, long long x) {

	if (p == NULL) {

		p = malloc(sizeof(struct tnode));

		if (p != NULL) {


			p->number = item;
			p->left = NULL;
			p->right = NULL;
			p->height = 1;
			p->value = x;
		}

	}
	else if (item < p->number) {

		p->left = addtree(p->left, item, x);
		if (!flag) {
			p->height++;
		}

	}
	else if (item > p->number) {

		p->right = addtree(p->right, item, x);
		if (!flag) {
			p->height++;
		}

	}
	else {

		flag = 1;
		p->value = x;

	}
	return balance(p);

}


int HeightOfTree(tnode* node)
{
	if (node == NULL)
		return 0;
	int left, right;
	if (node->left != NULL) {
		left = HeightOfTree(node->left);
	}
	else
		left = 0;
	if (node->right != NULL) {
		right = HeightOfTree(node->right);
	}
	else
		right = 0;
	int max = left > right ? left : right;
	node->height = max + 1;
	return node->height;
}

int height(tnode* p) {

	return p ? p->height : 0;

}

int bfactor(tnode* p) {

	return height(p->right) - height(p->left);

}

void fixheight(tnode* p) {

	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;

}

tnode* rotateright(tnode* p)
{
	tnode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

tnode* rotateleft(tnode* q)
{
	tnode* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

tnode* balance(tnode* p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}


tnode* sorting(tnode* p) {

	if (p == NULL) {
		return NULL;
	}

	if (abs(bfactor(p)) <= 1) {
		return p;
	}

	p->left = sorting(p->left);
	p->right = sorting(p->right);

	return balance(p);

}


int searching_it(tnode* p, long long stuff) {

	if (p == NULL) {
		return 0;
	}

	if (stuff < p->number) {

		return searching_it(p->left, stuff);

	}
	else if (stuff > p->number) {

		return searching_it(p->right,stuff);

	}
	else {

		printf("%lld %lld\n", p->number, p->value);

		return 1;
	}

}

tnode* findmin(tnode* p)
{
	return p->left ? findmin(p->left) : p;
}

tnode* removemin(tnode* p)
{
	if (p->left == NULL)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

tnode* remove_it(tnode* p, long long k)
{
	if (!p) return NULL;
	if (k < p->number)
		p->left = remove_it(p->left, k);
	else if (k > p->number)
		p->right = remove_it(p->right, k);
	else
	{
		tnode* q = p->left;
		tnode* r = p->right;
		free(p);
		if (!r) return q;
		tnode* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

int main(int argc, char* argv[]) {

	long long x1, x2;
	long long x3;
	char keys[2];

	tnode* p = NULL;


		//input..
		
		while (1) {
			scanf("%s", keys);
			switch (keys[0]) {

			case 'A':

				scanf("%lld%lld", &x1, &x2);
				p = addtree(p, x1, x2);
				break;

			case 'S':
				scanf("%lld", &x3);
				searching_it(p, x3);
				break;
			case 'D':
				scanf("%lld", &x3);
				p = remove_it(p, x3);
				break;
			default:
				break;
			}
			if (keys[0] == 'F')
				break;
		}


	return 0;
}
