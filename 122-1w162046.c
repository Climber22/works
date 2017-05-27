#include <stdio.h>
#include <stdlib.h>

typedef struct{
	double *Data;
	int Size;
	int count;
}Stack;

void *mallocx(int size) {
  void *p = malloc(size);
  if (p == NULL) {
    printf("cannot allocate memory\n");
    exit(1);
  }
  return p;
}

Stack *CreateStack(int size){
	Stack *s=(Stack*)mallocx(sizeof(Stack));
	s->Data=(double*)mallocx(size*sizeof(double));
	s->Size=size;
	s->count=0;


	return s;
}

void DisposeStack(Stack *s){

	free(s->Data);
	free(s);
}

void Push(Stack *s,double x){
	if(s->count == s->Size){
		printf("queue overflow\n");
		exit(1);
	}
	s->Data[s->count]=x;
	s->count++;
}

double Pop(Stack *s){
	if(s->count ==0){
		printf("queue underflow\n");
		exit(1);
	}
	s->count--;
	return s->Data[s->count];
}


int main (void){

	int size;
	printf("the size of array =");
	scanf("%d",&size);

	Stack *s=CreateStack(size);
	int sel=1;
	while(sel!=0){
		printf("select (1) Enqueue,, (2) Dequeue,, (0) Exit: ");
		scanf("%d",&sel);
		switch(sel){
		case 0:
			return 0;
		case 1:
			printf("input: ");
			double in;
			scanf("%lf",&in);
			Push(s,in);
			break;
		case 2:
			printf("output: %.1f\n",Pop(s));
			break;
		}
		printf("queue:");
		if(s->count==0){
			printf(" (none)\n");
		}else{
			for(int i=0;i<=s->count-1;i++){
				printf("%.1f,",s->Data[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
