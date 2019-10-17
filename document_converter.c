#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k - 1];
}

// This function returns an array of strings reparated by the separator 'delim'.
char **strtoken(char *s, char delim) {
    char **string_array = NULL;
    char *p_delim = NULL;
    int size = 0;

    if(s != NULL) {
        string_array = malloc(sizeof(char *));
        
        // As the string exists, it obviously has a size of at least 1.
        size = 1;
        p_delim = strtok(s, &delim);
        // Let the array of strings points to the 1st element of the string s
        *string_array = p_delim;
        while(p_delim != NULL) {
            // Increase the size of the array by 1 to be able to store another string
            size++;
            string_array = realloc(string_array, sizeof(char*) * size);
            p_delim = strtok(NULL, &delim);
            // Let the last element of the array points to the tokenized string pointer
            string_array[size - 1] = p_delim;
        }
    }

    return string_array;
}

char**** get_document(char* text) {
    char ****document = NULL; 

    char **paragraphs = NULL;
    int it_paragraph = 0;
    int n_paragraphs = 0;

    char **sentences = NULL;
    int it_sentence = 0;
    int n_sentences = 0;

    // Split the text into n paragraphs
    paragraphs = strtoken(text, '\n');
    
    // Get the number of paragraphs in the document
    while(paragraphs[n_paragraphs] != NULL)
        n_paragraphs++;

    // Allocate memory for the document to create an array of paragraphs. 
    // Allocate another memory block to store an "end of array" value (= NULL)
    document = malloc(sizeof(char ***) * (n_paragraphs + 1));
    document[n_paragraphs] = NULL;

    while(paragraphs[it_paragraph] != NULL) {
        // Need to reset these variables for each paragraph
        n_sentences = 0;
        it_sentence = 0;

        // Split the current paragraph into n sentences
        sentences = strtoken(paragraphs[it_paragraph], '.');
        
        // Get the number of sentences in the current paragraph
        while(sentences[n_sentences] != NULL)
            n_sentences++;

        // Allocate memory for the current paragraph to create an array of sentences
        document[it_paragraph] = malloc(sizeof(char **) * (n_sentences + 1));
        document[it_paragraph][n_sentences] = NULL;

        while(sentences[it_sentence] != NULL) {
            // As the strtoken function returns an array of strings reparated by a separator 'delim', if the delim is a space, then the function called here will return an array of words in the current sentence. It can be directly stored inside the document pointer.
            document[it_paragraph][it_sentence] = strtoken(sentences[it_sentence], ' ');
            it_sentence++;
        }

        it_paragraph++;
    }

    return document;
}



char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}
