#pragma once
#include<stdio.h>

struct _Tree;
typedef struct _Tree* Position;
typedef struct _Tree {
	Position left;
	Position right;
	int element;
} Tree;

Position CreateElement(int el);
Position Insert(Position Root, int el);
int PrintInorder(Position Root);
int PrintPostorder(Position Root);
int PrintPreorder(Position Root);
int PrintLevelorder(Position Root);
int PrintLevel(Position Root, int level);
int Height(Position Root);
Position SearchElement(Position Root, int el);
Position Delete(Position Root, int el);
Position SearchMin(Position Root);