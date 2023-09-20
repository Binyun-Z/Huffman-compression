#include"huffman.h"

int main()
{
    CharacterList L;
    HuffmanTree HT;

    InitList(L);
    ReadFile(L);

    HuffamnCoding(HT,L);
    PrintCharactorList(L);
    Codedocument(L);
    Coded_File(L);
    return 0;
}
void InitList(CharacterList &L)
{
    int i;

	L.listsize = LIST_INIT_SIZE;
	L.elem = ( ElemType* )malloc( LIST_INIT_SIZE * sizeof(ElemType));
	L.length = 0;

	for(i = 0;i<LIST_INIT_SIZE;i++)
    {
        L.elem[i].freq = 0;
	}
}
void ReadFile(CharacterList &L)
{
    int n;
    FILE *fp;
    int i;
    int t;
    int j;
    char ch;
    n=0;
    t=1;
    if( (fp = fopen("hufff.txt","r")) == NULL)
    {
        printf("out of space");
        exit(0);
    }

    while(!feof(fp))
    {
        t++;
        ch = fgetc(fp);
        printf("%c",ch);

        for(j = 0;j<L.length;j++)
        {
            if(ch == L.elem[j].Character)
            {
                 L.elem[j].freq++;
                 n = 1;
                 break;
            }
        }
        if(n == 0)
        {
                L.length++;
                L.elem[j].Character = ch;
                L.elem[j].freq = 1;
        }
        n=0;
    }
    printf("%d\n",t);
    printf("\n");
    fclose(fp);
}
void HuffamnCoding(HuffmanTree &HT,CharacterList &L) {
	int n;
    FILE *fp;
    int i;
	int s1;
	int s2;
	int m;
	int j;
	int start;
	int c;
	int f;

	if( (fp = fopen("code_list.txt","w")) == NULL)
    {
        printf("out of space");
        exit(0);
    }
    n=L.length;

    if (n <= 1)
     exit(0);

    m=2*n-1;

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));

	for (i=0 ; i < n;i++)
	{
	    HT[i].weight = L.elem[i].freq;
	    HT[i].lchild = 0;
	    HT[i].rchild = 0;
	    HT[i].parent = 0;
	}
	for (; i <m; ++i)
    {
        HT[i].weight = 0;
	    HT[i].lchild = 0;
	    HT[i].rchild = 0;
	    HT[i].parent = 0;
    }

    for (i = n ; i < m; ++i)
    {
		Select(HT,i,s1,s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';

	for (i = 0; i < n; ++i)
    {
		start = n-1 ;

		for (c = i,f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		L.elem[i].HuffmanCode = (char*)malloc((n-start)* sizeof(char));

		strcpy(L.elem[i].HuffmanCode, &cd[start]);
	}

    for(int i = 0;i<L.length;i++)
    {
       fprintf(fp,"%s\n",L.elem[i].HuffmanCode);
    }
    fclose(fp);
	free(cd);

}
void Select(HuffmanTree HT,int i,int &s1,int &s2)
{
    int j,
    k=10000;

	for(j=0; j<i;  j++)
    {
		if(HT[j].weight<k&&HT[j].parent==0)
		{
			k=HT[j].weight;
			s1=j;
		}
	}

	HT[s1].parent=1;
	k=10000;
	for(j=0; j<i;  j++)
    {
		if(HT[j].weight<k&&HT[j].parent==0)
		{
			k=HT[j].weight;
			s2=j;
		}
	}
	HT[s2].parent=1;

	if(s1>s2)
    {
		k=s1;   s1=s2;	s2=k;
	}
}
void Codedocument(CharacterList L){
    FILE *rp,*wbp,*wp;
    if(!(rp = fopen("hufff.txt","r"))){
        printf("open file error!\n");
        exit(0);
    }
    if(!(wbp = fopen("Code_File.dat","wb"))){
        printf("open file error!\n");
        exit(0);
    }
    if(!(wp = fopen("Code_File.txt","wb"))){
        printf("open file error!\n");
        exit(0);
    }
    int bl = 0;
    unsigned char buffer = 0x00;
    while(!feof(rp)){
        char ch;
        fscanf(rp,"%c",&ch);
        for(int i = 0;i<L.length;++i){
            if(ch == L.elem[i].Character){
                for(int j = 0;L.elem[i].HuffmanCode[j]!='\0';++j)
                {
                    buffer = buffer << 1;
                    if(L.elem[i].HuffmanCode[j] == '1')
                    {
                            buffer = buffer | 0x01;
                            bl++;
                            fputc('1',wp);
                    }
                    else
                    {
                            buffer = buffer | 0x00;
                            bl++;
                            fputc('0',wp);
                    }
                    if(bl == 8){
                        fwrite((char *)&buffer,sizeof(buffer),1,wbp);
                        bl = 0;
                    }
                }
                break;
            }
        }
    }
    while(bl && bl<8){
        buffer = buffer << 1;
        bl++;
    }
    if(bl){
        fwrite((char *)&buffer,sizeof(buffer),1,wbp);
    }
    fclose(rp);
    fclose(wbp);
    fclose(wp);
}
void PrintCharactorList(CharacterList L){
    for(int i = 0;i<L.length;i++){
        printf("%c  fre:%d code:%s \n",L.elem[i].Character,L.elem[i].freq,L.elem[i].HuffmanCode);
    }
}
void Getch(char* str,char& ch,CharacterList L){
    for(int i = 0;i<L.length;i++){
        if(strcmp(str,L.elem[i].HuffmanCode) == 0){
            ch = L.elem[i].Character;
        }

    }
}
void Coded_File(CharacterList L){
    FILE *rp,*wp;
    int bl=0;
    int i=0;
    int t=1;
    char str[20];
    char ch;

    if((rp = fopen("Code_File.dat","rb")) == NULL )
    {
        printf("out of space!\n");
        exit(0);
    }
    if((wp = fopen("code_file.txt","w"))==NULL)
    {
        printf("out of space!\n");
        exit(0);
    }
    unsigned char buffer = 0x00,get = 0x00;
    fread(&buffer,sizeof(buffer),1,rp);

    while(1)
    {

        get = buffer & 0x80;

        if (get == 0x80)
		{
			str[i] = '1';
			str[i + 1] = '\0';
			i++;
		}
		else if (get == 0x00)
		{
			str[i] = '0';
			str[i + 1] = '\0';
			i++;
		}
		bl++;
		buffer = buffer << 1;
		if (bl == 8)
		{
			bl = 0;
			fread(&buffer,sizeof(buffer),1,rp);
			if (feof(rp))
			{
				break;
			}
		}
		Getch(str,ch,L);

		if(ch != 0)
        {
          printf("%c",ch);
         fprintf(wp,"%c",ch);
            ch = 0;
            i = 0;
		}
    }
}
