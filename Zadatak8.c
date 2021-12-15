#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

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

int main(int argc, char* argv[])
{
	Position Root = NULL;
	int element = 1;
	int i = 0;
	int el = 0;
	Position temp = NULL;

	do
	{
		printf("Unesi cijeli broj koji zelis dodati u stablo.\n");
		printf("Za prekid unosa stisni 0.\n");
		scanf(" %d", element);
		Root = Insert(Root, element);
	} while (element != 0);

	do
	{
		printf("Odaberi sto zelis raditi sa stablom:\n");
		printf("1 - Levelorder ispis stabla\n");
		printf("2 - Inorder ispis stabla\n");
		printf("3 - Postorder ispis stabla\n");
		printf("4 - Preorder ispis stabla\n");
		printf("5 - Trazi element stabla\n");
		printf("6 - Brisi element iz stabla\n");
		printf("7 - Izlaz\n");

		scanf(" %d", &i);

		switch (i)
		{
		case 1:
			PrintLevelorder(Root);
			break;
		case 2:
			PrintInorder(Root);
			break;
		case 3:
			PrintPostorder(Root);
			break;
		case 4:
			PrintPreorder(Root);
			break;
		case 5:
			printf("Unesi element koji zelis pronaci:\n");
			scanf(" %d", &el);
			temp = SearchElement(Root, el);
			if (temp)
				printf("Element %d se nalazi na adresi %d\n", temp->element, temp);
			break;
		case 6:
			printf("Unesi element koji zelis izbrisati:\n");
			scanf(" %d", &el);
			Root = Delete(Root, el);
			break;
		case 7:
			break;
		default:
			printf("Pogresan unos!\n");
		}
	} while (i != '7');

	return EXIT_SUCCESS;
}

Position CreateElement(int el)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Tree));
	if (!newElement)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newElement->element = el;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

Position Insert(Position Root, int el)
{
	if (Root == NULL)
		return CreateElement(el);

	else if (Root->element > el)
		Root->left = Insert(Root->left, el);

	else
		Root->right = Insert(Root->right, el);

	return Root;
}

int PrintInorder(Position Root)
{
	if (Root == NULL)
		return EXIT_SUCCESS;

	PrintInorder(Root->left);
	printf(" %d", Root->element);
	PrintInorder(Root->right);

	return EXIT_SUCCESS;
}

int PrintPostorder(Position Root)
{
	if (Root == NULL)
		return EXIT_SUCCESS;

	PrintPostorder(Root->left);
	PrintPostorder(Root->right);
	printf(" %d", Root->element);

	return EXIT_SUCCESS;
}

int PrintPreorder(Position Root)
{
	if (Root == NULL)
		return EXIT_SUCCESS;

	printf(" %d", Root->element);
	PrintPreorder(Root->left);
	PrintPreorder(Root->right);

	return EXIT_SUCCESS;
}

int PrintLevelorder(Position Root)
{
	int h = Height(Root);
	int i = 1;
	
	for (i = 1; i <= h; i++)
		PrintLevel(Root, i);

	return EXIT_SUCCESS;
}

int PrintLevel(Position Root, int level)
{
	if (Root == NULL)
		return EXIT_SUCCESS;

	if (level == 1)
		printf(" %d ", Root->element);

	else if (level > 1)
	{
		PrintLevel(Root->left, level - 1);
		PrintLevel(Root->right, level - 1);
	}

	return EXIT_SUCCESS;
}

int Height(Position Root)
{
	if (Root == NULL)
		return 0;

	else
	{
		int lheight = Height(Root->left);
		int rheight = Height(Root->right);

		if (lheight > rheight)
			return(lheight + 1);

		else
			return(rheight + 1);
	}
}

Position SearchElement(Position Root, int el)
{
	if (Root == NULL)
		return NULL;

	else if (Root->element > el)
		return SearchElement(Root->left, el);

	else if (Root->element < el)
		return SearchElement(Root->right, el);
	
	else 
		return Root;
}

Position Delete(Position Root, int el)
{
	Position temp = NULL;

	if (Root == NULL)
		return Root;

	else if (Root->element > el)
		Root->left = Delete(Root->left, el);

	else if (Root->element < el)
		Root->right = Delete(Root->right, el);
	
	else
	{
		if (Root->left && Root->right)
		{
			temp = SearchMin(Root->right);
			Root->element = temp->element;
			Root->right = Delete(Root->right, temp->element);
		}
		else
		{
			temp = Root;
			if (!Root->left)
				Root = Root->right;
			else if (!Root->right)
				Root = Root->left;
			free(temp);
		}
	}
	return Root;
}

Position SearchMin(Position Root)
{
	if (Root == NULL)
		return Root;
	else
	{
		Root = SearchMin(Root->left);
		return Root;
	}
}