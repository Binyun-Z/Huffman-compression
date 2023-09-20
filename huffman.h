#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LineCountNum 100
#define LIST_INIT_SIZE 100

typedef struct CharacterNode {
    char Character;
    int freq;
    char *HuffmanCode;
}CharacterNode;
typedef CharacterNode ElemType;
typedef struct{
    ElemType *elem;
    int length;
	int listsize;
}CharacterList;
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode,*HuffmanTree;
typedef struct{
    unsigned int a:1;
}Bite;
void InitList(CharacterList &L);
void ReadFile(CharacterList &L);
void Select(HuffmanTree HT, int i, int &s1, int &s2);
void HuffamnCoding(HuffmanTree &HT,CharacterList &L);
void Codedocument(CharacterList L);
void PrintCharactorList(CharacterList L);
void Getch(char* str,char& ch,CharacterList L);
void Coded_File(CharacterList L);


#endif // HUFFMAN_H_INCLUDED
