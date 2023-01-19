#include <stdio.h>
#include <stdlib.h>

int* parents;
int* time;
int* finaltime;
int* colors;
int t = 0;

typedef struct node {
	int value;
	struct node* next;
} node;

typedef struct {
	int n;
	node** list;
} Graph;

enum {
	WHITE, GRAY, BLACK
};

node* createNod(int value)
{
	node* q = (node*)malloc(sizeof(node));
	q->value = value;
	q->next = NULL;
	return q;
}

int marimeLista(node* t)
{
	int n = 0;
	while (t != NULL)
	{
		n++;
		t = t->next;
	}
	return n;
}

void DFS_VISIT(Graph G, int key, int n)
{
	t++;
	time[key] = t;
	colors[key] = GRAY;
	printf("%d\t", key);


	node* q = NULL;
	q = G.list[key];
	int gSize = marimeLista(q);
	for (int i = 0; i < gSize; i++)
	{
		int val = q->value;
		if (colors[val] == WHITE)
		{
			parents[val] = key;
			DFS_VISIT(G, val, gSize);
		}
		q = q->next;
	}
	colors[key] = BLACK;
	t++;
	finaltime[key] = t;
}

void DFS(Graph G, int gSize)
{
	t = 0;
	printf("DFS: ");

	for (int i = 0; i < gSize; i++) {
		parents[i] = -1;
		time[i] = 0;
		finaltime[i] = 0;
		colors[i] = WHITE;
	}

	for (int i = 0; i < gSize; i++)
	{
		if (colors[i] == WHITE)
		{
			DFS_VISIT(G, i, gSize);

		}
	}
	printf("\n");
}


void demo()
{
	Graph G;
	printf("Numar noduri: ");
	scanf_s("%d ", &G.n);

	G.list = (node**)malloc(G.n * sizeof(node*));
	for (int i = 0; i < G.n; i++) {
		G.list[i] = NULL;
	}

	int v, w, ok = 1;
	while (scanf_s("%d %d", &v, &w) == 2 && ok < G.n) {
		if (G.list[v] == NULL) {
			G.list[v] = createNod(v);
			G.list[v]->next = createNod(w);
		}
		else {
			node* p;
			p = G.list[v];
			while (p->next != NULL)
				p = p->next;
			p->next = createNod(w);
		}
		ok++;

	}

	for (int i = 0; i < G.n; i++) {
		if (G.list[i] == NULL)
			G.list[i] = createNod(i);
	}

	colors = (int*)malloc(G.n * sizeof(int));
	time = (int*)malloc(G.n * sizeof(int));
	finaltime = (int*)malloc(G.n * sizeof(int));
	parents = (int*)malloc(G.n * sizeof(int));

	DFS(G, G.n);


	for (int i = 0; i < G.n; i++) {
		printf("%d p: %d ", i, parents[i]);
		printf("t: %d ", time[i]);
		printf("ft: %d \n", finaltime[i]);
	}

}



int main()
{
	demo();

	/*7
		0 1
		1 4
		0 2
		2 5
		0 3
		3 6
		9 9*/
}


