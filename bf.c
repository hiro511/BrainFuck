#include <stdio.h>
void init(char ary[]);
int parse(char *ptr, FILE *fp);
char* checkChar(int c, char *ptr, FILE *fp);
void goEnd(FILE *fp);

int main(int argc, char *argv[]){
    char ary[1000];
    FILE *fp;
    
    init(ary);
    if(argc>1){
        fp = fopen(argv[1], "r");
        if(fp==NULL){
            printf("failed to open \"%s\"\n", argv[1]);
	    exit(1);
	}
        parse(ary, fp);
    }else
        printf("ファイル名を指定してください\n");
    fclose(fp);
    return 0;
}

void init(char ary[]){
    int arySize = sizeof(*ary)/sizeof(ary[0]);
    for(int i=0; i<arySize; i++)
        ary[i] = 0;
}

int parse(char *ptr, FILE *fp){
    int c;
    while((c=fgetc(fp)) != EOF){
        ptr = checkChar(c, ptr, fp);
    }
    return 1;
}

char* checkChar(int c, char *ptr, FILE *fp){
    switch(c){
        case '+' : (*ptr)++; ;break; //+
        case '-' : (*ptr)--;  ;break; //-
        case '<' : ptr--;  ;break; //<
        case '>' : ptr++;  ;break; //>
        case '[' :
            while(*ptr){
                FILE lfp = *fp;
                while((c=fgetc(&lfp)) != 93){
                    ptr =  checkChar(c, ptr, &lfp);
                }
            }
            goEnd(fp);  //カッコの次の文字まで移動
            break; //[
        case ']' : break; //]
        case ',': *ptr=getchar(); break;
        case '.' : printf("%c", *ptr); break; //.
    }
    return ptr;
}

void goEnd(FILE *fp){
    int n = 1;
    while(n){
        int c = fgetc(fp);
        switch (c) {
            case '[' : n++; break;
            case ']' : n--; break;
        }
    }
}

