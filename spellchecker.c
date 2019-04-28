#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#include <ctype.h>

  
 // Trie node data structure
struct TrieNode 
{ 
	// possible next letters
    struct TrieNode *leafs[26]; 
  
  	// if is end of word
    bool isEnd; 
}; 
  
// allocate memorh for new node
struct TrieNode *createEmptyNode(void) 
{ 
    struct TrieNode *node = NULL; 
  
    node = (struct TrieNode *)malloc(sizeof(struct TrieNode)); 
  
    if (node) 
    { 
    	// set default values
        node->isEnd = false; 
  
        for (int i = 0; i < 26; i++) {
            node->leafs[i] = NULL; 
        }
    } 
  
    return node; 
} 
  
// insert a word to trie tree
void insertWord(struct TrieNode *root, const char *word) 
{ 
    int length = strlen(word); 
    int idx; 
  
    struct TrieNode *current = root; 
  
    for (int i = 0; i < length; i++) 
    { 
    	// insert each letter to the tree
        idx = ((int)word[i] - (int)'a'); 
        if (!current->leafs[idx]) {
            current->leafs[idx] = createEmptyNode(); 
        }
  
        current = current->leafs[idx]; 
    } 
  
    current->isEnd = true; 
} 
  
// search if word exist in trie tree
bool searchWord(struct TrieNode *root, char *word) 
{ 
    int length = strlen(word); 
    int idx; 
    struct TrieNode *current = root; 
  
  	// search letter by letter
    for (int i = 0; i < length; i++) 
    { 
        idx = ((int)word[i] - (int)'a'); 
  
        if (!current->leafs[idx]) {
            return false; 
        }
  
        current = current->leafs[idx]; 
    } 
  
    return (current != NULL && current->isEnd); 
}


int main()
{
	// create root node
	struct TrieNode *root = createEmptyNode();

	// open dictionary file
	static const char filename[] = "dictionary.txt";
	FILE *file = fopen ( filename, "r" );
	if ( file != NULL )
	{
		printf("Loading dictionary...\n");

		char line[128];
		while ( fgets ( line, sizeof line, file ) != NULL )
		{
			// convert to lower case and insert to tree
			strtok(line, "\n");
			for(int k = 0; line[k]; k++){
			  	line[k] = tolower(line[k]);
			}
			insertWord(root, line);
		}
		fclose ( file );
		printf("Successfully loaded dictionary...\n");

		// ask user to type a word and check if in tree
		char keyword[100];
		while(true){
			printf("Type a word to search: \n");
			scanf("%s", keyword);
			for(int k = 0; keyword[k]; k++){
			  	keyword[k] = tolower(keyword[k]);
			}
			if(searchWord(root, keyword)){
				printf("Spelling is correct.\n");
			}else{
				printf("Word not found in dictionary, Maybe spelling is wrong.\n");
			}
		}


	}
	else
	{
	  printf("No dictionary.txt file found, quit...\n");
	  return 0;
	}

		

	return 0;
}