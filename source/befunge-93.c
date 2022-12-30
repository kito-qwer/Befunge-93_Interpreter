#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

long int* stackTopAddress;
long int stackPointer=0;
int stack100=0;

typedef struct{
	int X;
	int Y;
}position;

typedef enum direc{
	up,
	right,
	down,
	left,
}direc;

typedef enum bool{
	false,
	true,
}bool;

void push(int);
int pop();

void outputC(int);
void outputN(int);


int main(int argc,char** argv){
	position ps; // 位置
	ps.X=0;
	ps.Y=0;
	bool run_flg=true;
	bool literal_flg=true;
	FILE* fp;
	char table[25][81]={0};
	direc direction=right;
	long int x,y,z;
	srand((unsigned int)time(NULL));
	if(argc<=1){
		printf("error : No arguments are set. ");
		return 1;
	}
	fp=fopen(argv[1],"r");
	if(fp==NULL){
		printf("error : File not found.");
		return 1;
	}
	stackTopAddress=(long int*)malloc(sizeof(long int)*100);
	stack100=1;
	*stackTopAddress=0;
	if(stackTopAddress==NULL){
		printf("error : Failed to allocate memory.");
		return 2;
	}
	for(int i=0;i<25;i++){
		fgets(table[i],80,fp);
	}
	fclose(fp);
	int microsecond = 0.5 * 1000000;
	while(run_flg){
		if(literal_flg){
			switch(table[ps.Y][ps.X]){
				case '<':
					direction=left;
					break;
				case '>':
					direction=right;
					break;
				case '^':
					direction=up;
					break;
				case 'v':
					direction=down;
					break;
				case '_':
					x=pop();
					if(x==0)direction=right;
					else direction=left;
					break;
				case '|':
					x=pop();
					if(x==0)direction=down;
					else direction=up;
					break;
				case '#':
					if(direction==up)ps.Y--;
					else if(direction==right)ps.X++;
					else if(direction==down)ps.Y++;
					else if(direction==left)ps.X--;
					break;
				case '@':
					free(stackTopAddress);
					return 0;
				case '"':
					literal_flg=false;
					break;
				case ':':
					x=pop();
					push(x);
					push(x);
					break;
				case '\\':
					y=pop();
					x=pop();
					push(y);
					push(x);
					break;
				case '$':
					x=pop();
					break;
				case '&':
					printf("value:");
					scanf("%d",&x);
					push(x);
					break;
				case '~':
					printf("charcter");
					x=getchar();
					push(x);
					break;
				case '.':
					x=pop();
					outputN(x);
					break;
				case ',':
					x=pop();
					outputC(x);
					break;
				case '!':
					x=pop();
					if(x==0)push(1);
					else push(0);
					break;
				case '+':
					y=pop();
					x=pop();
					push(x+y);
					break;
				case '-':
					y=pop();
					x=pop();
					push(x-y);
					break;
				case '*':
					y=pop();
					x=pop();
					push(x*y);
					break;
				case '/':
					y=pop();
					x=pop();
					push(x/y);
					break;
				case '\'':
					y=pop();
					x=pop();
					if(x>y)push(1);
					else push(0);
					break;
				case 'g':
					y=pop();
					x=pop();
					push(table[y][x]);
					break;
				case 'p':
					y=pop();
					x=pop();
					z=pop();
					table[y][x]=z;
					break;
				case '?':
					direction=rand()%4;
					break;
			}
			if(table[ps.Y][ps.X]<=57&&table[ps.Y][ps.X]>=48){
				push(table[ps.Y][ps.X]-48);
			}
		}else{
			if(table[ps.Y][ps.X]=='"')literal_flg=true;
			else push(table[ps.Y][ps.X]);
		}
		if(direction==up)ps.Y--;
		else if(direction==right)ps.X++;
		else if(direction==down)ps.Y++;
		else if(direction==left)ps.X--;
		ps.X=(ps.X+80)%80;
		ps.Y=(ps.Y+25)%25;
	}
}

void push(int a){
	long int* b=stackTopAddress;
	if(stackPointer>=100*stack100){
		b=(long int*)realloc(b,sizeof(long int)*100);
		if(b==NULL){
			printf("error : failed to reallocate memory.");
			free(stackTopAddress);
			exit(1);
		}
		else {
			stack100++;
			stackTopAddress=b;
		}
	}
	stackPointer++;
	*(stackTopAddress+stackPointer)=a;
}

int pop(){
	long int a;
	if(stackPointer<0){
		printf("error : Buffer overrun.");
		free(stackTopAddress);
		exit(1);
	}
	a=*(stackTopAddress+stackPointer);
	stackPointer--;
	return a;
}

void outputC(int a){
	printf("%c",a);
}
void outputN(int a){
	printf("%d ",a);
}
