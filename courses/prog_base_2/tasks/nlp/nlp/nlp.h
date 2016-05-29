#ifndef NLP_H_INCLUDED
#define NLP_H_INCLUDED



#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "list.h"

typedef struct word_s * word_t;
typedef struct sentence_s * sentence_t;
typedef struct text_s * text_t;

word_t word_new(char * value);

void sentence_addWord(sentence_t sentence, word_t word);
void text_addSentence(text_t text, sentence_t sentence);
void text_writeUniqueInFile(list_t * unique);
void sentence_print(sentence_t self);
void text_print(text_t self);

sentence_t sentence_new();
text_t text_parse(char * text);
text_t text_new();
sentence_t sentence_parse(char * text);

char * text_readText(char * filename);

list_t * text_getUnigueWords(text_t text);

#endif // NLP_H_INCLUDED
