#include "nlp.h"

struct word_s{
    char * word;
};

struct sentence_s{
    list_t * words;
};

struct text_s{
    list_t * sentences;
};

word_t word_new(char * value){
    if(value != NULL){
        word_t self = malloc(sizeof(struct word_s));
        self->word = malloc(sizeof(char)*strlen(value));
        strcpy(self->word, value);
        return self;
    } else
        return NULL;
}

sentence_t sentence_new(){
    sentence_t self = malloc(sizeof(struct sentence_s));
    self->words = list_new();
    return self;
}

text_t text_new(){
    text_t self = malloc(sizeof(struct text_s));
    self->sentences = list_new();
    return self;
}

void sentence_addWord(sentence_t sentence, word_t word){
    if(word != NULL && sentence != NULL && word->word != NULL)
        list_push_back(sentence->words, word);
}

void text_addSentence(text_t text, sentence_t sentence){
    if(text != NULL && sentence != NULL)
        list_push_back(text->sentences, sentence);
}

void sentence_print(sentence_t self){
    for(int i = 0; i < list_getSize(self->words); i++){
        printf("%s ", ((word_t)list_get(self->words, i))->word);
    }
}

void text_print(text_t self){
    for(int i = 0; i < list_getSize(self->sentences); i++){
        sentence_print(list_get(self->sentences, i));
        puts(" ");
    }
}

sentence_t sentence_parse(char * text){
    if(strlen(text) == 0 || text == NULL)
        return NULL;
    char buff[1000];
    strcpy(buff, text);
    sentence_t res = sentence_new();
    char * word = strtok(buff, " ,.;:");
    list_push_back(res->words, word_new(word));
    while(word != NULL){
        word = strtok(NULL, " ,.;:");
        if(word != NULL && strlen(word) != 0){
            list_push_back(res->words, word_new(word));
        }
    }
    if(list_getSize(res->words) != 0)
        return res;
    else
        return NULL;
}

text_t text_parse(char * text){
    char buff[1000000];

    strcpy(buff, text);
    for(int i = 0; i < strlen(buff); i++){
        if(buff[i] == '\n' || buff[i] == '\"'){
            buff[i] = ' ';
        } else if(buff[i] == '.' || buff[i] == '?' || buff[i] == '!'){
            buff[i] = ' ';
            for(int j = strlen(buff); j > i && j < 1000000; j--){
                    buff[j+1] = buff[j];
            }
            buff[i+1] = '/';
            i+=2;
        }
    }
    text_t txt = text_new();
    list_t * sentences = list_new();
    char * sent = strtok(buff, "/");
    while(sent != NULL){
        list_push_back(sentences, sent);
        sent = strtok(NULL, "/");
    }

    for(int i = 0; i < list_getSize(sentences); i++){
        sentence_t sentence = sentence_parse(list_get(sentences, i));
        if(sentence != NULL){
            list_push_back(txt->sentences, sentence);
        }
    }
    return txt;
}

list_t * text_getUnigueWords(text_t text){
    list_t * unique = list_new();
    list_t * list = text->sentences;
    int flag = 1;
    for(int i = 0; i < list_getSize(list); i++){
        sentence_t sent = list_get(list, i);
        for(int k = 0; k < list_getSize(sent->words); k++){
            flag = 1;
            word_t word = list_get(sent->words, k);
            for(int x = 0; x < list_getSize(list); x++){
                sentence_t cmpSent = list_get(list, x);
                if(flag == 0) break;
                for(int y = 0; y < list_getSize(cmpSent->words); y++){
                    if(i == x && k == y) continue;
                        word_t cmpWord = list_get(cmpSent->words, y);
                        if(strcmp(word->word, cmpWord->word) == 0){
                            flag = 0;
                            break;
                        }
                    }
                }
            if(flag == 1)
                list_push_back(unique, word->word);
        }
    }
    return unique;
}

void text_writeUniqueInFile(list_t * unique){
    FILE * result;
    result = fopen("result.txt", "w+b");
    if(result == NULL){
        printf("Can't create file");
        return;
    }
    for(int i = 0; i < list_getSize(unique); i++){
        fprintf(result, "%s\n", list_get(unique, i));
    }
    fclose(result);

}

char * text_readText(char * filename){
         char text [1000000];
         FILE* finput = fopen(filename, "r");
         int len = fread(text, sizeof(char), sizeof(text)/sizeof(char), finput);
         text[len] = '\0';
         fclose(finput);
         return text;
}

