#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n);
char** kth_sentence_in_mth_paragraph(char**** document, int k, int m);
char*** kth_paragraph(char**** document, int k);
char **strtoken(char *s, char delim);
char**** get_document(char* text);

// Test functions
char* get_input_text();
void print_word(char* word);
void print_sentence(char** sentence);
void print_paragraph(char*** paragraph);
