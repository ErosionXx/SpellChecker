#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#include <ctype.h>
#include <time.h>
 
long mem = 0;
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
  	mem += sizeof(struct TrieNode);
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


int main(int argc, char **argv)
{
	// create root node
	struct TrieNode *root = createEmptyNode();
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
			insertWord(root, line);
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