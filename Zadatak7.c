#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH 256

typedef struct dir* Position;
typedef struct stack* StackPosition;
typedef struct dir {
	char name[MAX_LENGTH];
	Position sibling;
	Position child;
}Dir;

typedef struct stack {
	Position data;
	StackPosition next;
} Stack;

StackPosition AllocateMemoryForStack();
int PushStack(Position, StackPosition);
Position PopStack(StackPosition);
Position MakeDirectory(Position, char*);
Position ChangeDirectory(Position, StackPosition, char*);
Position ChangeToPreviousDirectory(StackPosition);
int PrintDirectory(Position);
int Path(Position, StackPosition);
int CommandPrompt(Position current, StackPosition stackHead);
int Remove(Position);

int main(int argc, char* argv[])
{
	Dir C = { .sibling = NULL, .child = NULL, .name = "C:" };
	Stack stackHead = { .data = NULL, .next = NULL };

	PushStack(&C, &stackHead);
	CommandPrompt(&C, &stackHead);

	return EXIT_SUCCESS;
}

Position PopStack(StackPosition stackHead)
{
	StackPosition tempStackElement = stackHead->next, prev = stackHead->next;
	if (!tempStackElement->next)
		return NULL;
	while (tempStackElement->next)
	{
		prev = tempStackElement;
		tempStackElement = tempStackElement->next;
	}
	Position directory = tempStackElement->data;
	prev->next = tempStackElement->next;
	free(tempStackElement);
	return directory;
}

int PushStack(Position current, StackPosition stackHead)
{
	StackPosition newStackElement;
	StackPosition tempStackElement = stackHead;
	if (newStackElement = AllocateMemoryForStack())
	{
		while (tempStackElement->next)
			tempStackElement = tempStackElement->next;
		newStackElement->next = tempStackElement->next;
		tempStackElement->next = newStackElement;
		newStackElement->data = current;
		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
}

int PrintDirectory(Position current) {

	if (current->child == NULL)
		printf("Empty directory!\n");

	else
	{
		current = current->child;

		printf("DIRECTORIES: \n");
		printf(" %s\n", current->name);
		while (current->sibling != NULL) {
			printf(" %s\n", current->sibling->name);
			current = current->sibling;
		}
	}

	return EXIT_SUCCESS;
}

Position ChangeToPreviousDirectory(StackPosition stackHead)
{
	return PopStack(stackHead);
}

Position ChangeDirectory(Position current, StackPosition stackHead, char* name)
{
	if (!current->child)
	{
		printf("Directory is empty!\n");
		return current;
	}
	else
	{
		Position parent = current;
		Position WantedDirectory = current->child;
		while (WantedDirectory)
		{
			if (!strcmp(WantedDirectory->name, name))
			{
				PushStack(WantedDirectory, stackHead);
				return WantedDirectory;
			}
			WantedDirectory = WantedDirectory->sibling;
		}
		printf("That directory does not exist!\n");

		return parent;
	}
}

Position MakeDirectory(Position current, char* name)
{
	Position newDirectory;
	newDirectory = (Position)malloc(sizeof(Dir));
	if (!newDirectory)
	{
		printf("Can not allocate memory!\n");
	}
	newDirectory->child = NULL;
	newDirectory->sibling = NULL;
	strcpy(newDirectory->name, name);

	if (!current->child)
	{
		current->child = newDirectory;
	}
	else
	{
		while (current->child->sibling)
			current->child = current->child->sibling;
		current->child->sibling = newDirectory;
	}
	return current;
}

StackPosition AllocateMemoryForStack()
{
	StackPosition newStackElement = (StackPosition)malloc(sizeof(Dir));
	if (!newStackElement)
	{
		printf("Can't allocate memory!\n");
	}
	return newStackElement;
}

int Remove(Position current)
{
	if (!current)
		return EXIT_SUCCESS;
	remove(current->sibling);
	remove(current->child);
}

int Path(Position current, StackPosition stackHead)
{
	char stringToPrint[MAX_LENGTH] = "";

	while (stackHead)
	{
		strcat(stringToPrint, stackHead->data->name);
		strcat(stringToPrint, "\\");
		stackHead = stackHead->next;
	}

	strcat(stringToPrint, ">");
	printf("%s ", stringToPrint);

	return EXIT_SUCCESS;
}

int CommandPrompt(Position current, StackPosition stackHead)
{
	Position C = current;
	char Input[MAX_LENGTH];
	char Command[5];
	char Directory[MAX_LENGTH];
	Path(current, stackHead->next);

	do {
		printf("--------------------------\n");
		printf("Choose one option:\n");
		printf("1 - md\n");
		printf("2 - cd\n");
		printf("3 - ..\n");
		printf("4 - dir \n");
		printf("5 - exit\n");
		printf("--------------------------\n");

		fgets(Input, MAX_LENGTH, stdin);
		sscanf(Input, "%s %s", Command, Directory);

		if (!strcmp(Command, "md"))
		{
			current = MakeDirectory(current, Directory);
			Path(current, stackHead->next);
		}

		else if (!strcmp(Command, "cd"))
		{
			current = ChangeDirectory(current, stackHead, Directory);
			Path(current, stackHead->next);
		}

		else if (!strcmp(Command, ".."))
		{
			if (current = ChangeToPreviousDirectory(stackHead) == NULL)
				current = C;
			Path(current, stackHead->next);
		}

		else if (!strcmp(Command, "dir"))
		{
			PrintDirectory(current);
			Path(current, stackHead->next);
		}

		else if (!strcmp(Command, "exit"))
			Remove(current);

		else
			printf("That's not an option!");

	} while (strcmp(Command, "exit"));

	return EXIT_SUCCESS;
}