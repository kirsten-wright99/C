#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG
// global variable for the alphabet passed in
char alpha[26];

// function prototypes
void sort(int start, int end, char ** names, char ** newNames);
int compareChars(char a, char b);
void printNames(char ** names, int n);

int main(void)
{
	int i, n;
	char ** names; // names passed in by user
	char ** newNames; // names for sorting

	for (i = 0; i < 26; i++)
	{
		scanf(" %c", &alpha[i]);
	}

	scanf(" %d", &n);

	names = (char **) calloc(n, sizeof(char *));
	newNames = (char **) calloc(n, sizeof(char *));

	for (i = 0; i < n; i++)
	{
        names[i] = (char *) calloc(100, sizeof(char));
        newNames[i] = (char *) calloc(100, sizeof(char));
        scanf(" %s", names[i]);     
	}

	sort(0, n - 1, names, newNames);
	printNames(newNames, n);
}

// a version of a merge sort to sort the names
void sort(int start, int end, char ** names, char ** newNames)
{
	int mid = (start + end) / 2;
	int front = start;
	int back = mid + 1;
	int merged = 0;

	if (start == end)
		return;

	sort(start, mid, names, newNames);
	sort(mid + 1, end, names, newNames);

	while (merged <= end - start)
	{
		if (front == mid + 1 || (back != end +1 && compareChars(names[front][0], names[back][0]) ) )
			strcpy(newNames[merged++], names[back++]);
		else 
			strcpy(newNames[merged++], names[front++]);
	}
}

// this function finds which character comes first in the 
// alphabet passed in by the user
int compareChars(char a, char b)
{
	int i;

	for (i = 0; i < 26; i ++)
	{
		if (alpha[i] == a)
			return 1;
		else if (alpha[i] == b)
			return 0;
	}
}

// this function prints the names in sorted order
void printNames(char ** names, int n)
{
	int i;

	for (int i = n - 1; i >= 0; i--)
		printf("%s\n", names[i]);
}