#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 
#include <time.h>

long mem = 0;

// a node of avl tree
struct AVLNode 
{ 
	char word[30];
	struct AVLNode *left; 
	struct AVLNode *right; 
	int height; 
}; 

// get height of avl tree
int height(struct AVLNode *node) 
{ 
	if (node == NULL) {
		return 0; 
	}

	return node->height; 
} 


// helper function to get max number of two
int max(int num1, int num2) 
{ 
	return (num1 > num2)? num1 : num2; 
} 


// function to create new avl tree node
struct AVLNode* newNode(char *word) 
{ 
	mem += sizeof(struct AVLNode);
	struct AVLNode* node = (struct AVLNode*) malloc(sizeof(struct AVLNode)); 
	strcpy(node->word, word);
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1;
	return(node); 
} 

// right rotate tree
struct AVLNode *rightRotate(struct AVLNode *node) 
{ 
	struct AVLNode *left = node->left; 
	struct AVLNode *child = left->right; 

	left->right = node; 
	node->left = child; 

	node->height = max(height(node->left), height(node->right))+1; 
	left->height = max(height(left->left), height(left->right))+1; 

	return left; 
} 

// left rotate tree
struct AVLNode *leftRotate(struct AVLNode *node) 
{ 
	struct AVLNode *right = node->right; 
	struct AVLNode *child = right->left; 

	right->left = node; 
	node->right = child; 

	node->height = max(height(node->left), height(node->right))+1; 
	right->height = max(height(right->left), height(right->right))+1; 

	return right; 
} 

int getBalanceFactor(struct AVLNode *node) 
{ 
	if (node == NULL) {
		return 0; 
	}
	return height(node->left) - height(node->right); 
} 

// insert new node
struct AVLNode* insertWord(struct AVLNode* node, char *word) 
{ 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) {
		return(newNode(word)); 
	}

	if (strcmp(word, node->word) < 0) {
		node->left = insertWord(node->left, word); 
	}
	else if (strcmp(word, node->word) > 0) {
		node->right = insertWord(node->right, word); 
	}
	else{
		return node; 
	}

	node->height = 1 + max(height(node->left), height(node->right)); 

	int balance = getBalanceFactor(node); 


	if (balance > 1 && strcmp( word, node->left->word) < 0) {
		return rightRotate(node); 
	}

	if (balance < -1 && strcmp(word, node->right->word) > 0) {
		return leftRotate(node); 
	}

	if (balance > 1 && strcmp(word, node->left->word) > 0)
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	if (balance < -1 && strcmp(word, node->right->word) < 0)
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	return node; 
} 


int searchWord(struct AVLNode* node, char * searchWord)
{

	while (node != NULL)
	{
		if (strcmp(searchWord, node->word) > 0)
		{
			if (node->right == NULL)
			{
				return 0;
			}
			else
			{
				node = node->right;
			}
		}
		else if (strcmp(searchWord, node->word) < 0)
		{
			if (node->left == NULL)
			{
				return 0;
			}
			else
			{
				node = node->left;
			}
		}
		else if (strcmp(searchWord, node->word) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int main(int argc, char **argv) 
{ 
	struct AVLNode *root = NULL; 
	double time_spent = 0.0;

	clock_t begin = clock();
	// open dictionary file
	static const char filename[] = "dictionary.txt";
	FILE *file = fopen ( filename, "r" );
	if ( file != NULL )
	{
		printf("Loading dictionary...\n");

		char line[1000];
		while ( fgets ( line, sizeof line, file ) != NULL )
		{
			// convert to lower case and insert to tree
			strtok(line, "\n");
			for(int k = 0; line[k]; k++){
			  	line[k] = tolower(line[k]);
			}
			root = insertWord(root, line);
		}
		fclose ( file );
		printf("Successfully loaded dictionary...\n");

		// ask user to type a word and check if in tree
		char *text_file = *(argv + 1);
		char keyword[100];
		int m = 0;
		int num = 1;
		FILE *file_text = fopen ( text_file, "r" );
		if ( file_text != NULL ){
			printf("Miss spelled words:\n");
			while ( fgets ( line, sizeof line, file ) != NULL )
			{
				// convert to lower case and insert to tree
				strtok(line, "\n");

				for(int k = 0; line[k]; k++){

					if(tolower(line[k]) > 'z' || tolower(line[k]) < 'a'){
						keyword[m] = '\0';
						// check word
						if(strlen(keyword) && !searchWord(root, keyword)){
							printf("On line %d: %s.\n", num, keyword);
						}
						m = 0;
					}else{
				  		keyword[m] = tolower(line[k]);
				  		m++;
					}
				}

				num++;
				
			}
		}

	}
	else
	{
	  printf("No dictionary.txt file found, quit...\n");
	  return 0;
	}

	
  	printf("Memory usage: %ld\n", mem);
  	clock_t end = clock();

	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Runtime %f\n", time_spent);
	return 0; 
} 
