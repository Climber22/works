#include <stdio.h>
#include <stdlib.h>
#define Num 1000

/* データの型は構造体により定義せよ */
typedef struct{
	int stunum;
	int SubA;
	double SubB;
	double SubC;
	double sum;
	int rank;
}student;

void readDataFile(student *Data){
	FILE *file = fopen("rep data.txt","r"); /* "r"は読み込み専用の意味 */
	if (file == NULL) { /* ファイルを正しく開けなかった場合 */
		fprintf(stderr, "cannot open file\n");
		exit(1);
	}
	int scannum;
	for(int i=0;i<Num;i++){
		scannum = fscanf(file,"%d %d %lf %lf",&Data[i].stunum, &Data[i].SubA,&Data[i].SubB, &Data[i].SubC);

		if(scannum != 4){ //ファイルから期待通りに読み込めなかった場合
			fprintf(stderr,"cannot read file\n");
			exit(1);
		}

		Data[i].sum=Data[i].SubA+Data[i].SubB+Data[i].SubC;
	}

	fclose(file);
}


void swap(student *a,student *b){
	student c;
	c=*a;
	*a=*b;
	*b=c;
}

void QuickSortBase(student *data, int L, int R){
	int l = L;
	int r = R;

	double pivot = data[(L+R)/ 2].sum;
	while (1) {
		while (data[l].sum < pivot){
			l++;
		}
		while (pivot < data[r].sum){
			r--;
		}
		if (l >= r){
			break;
		}

		swap(&data[l],&data[r]);
		l++;
		r--;
	}

	if (L< l - 1)
		QuickSortBase(data, L, l - 1);
	if (r + 1 <  R)
		QuickSortBase(data, r + 1, R);
}

void QuickSort(student *Data, int a) {
	if (a >= 2) {
		/* QuickSortBaseを適切な引数で呼び出す */
		QuickSortBase(Data,0,a-1);
	}
}

int serchsum(double sum,student *Data,int N){
	int l=0;
	int r=N-1;
	int h=(N-1)/2;
	while(1){
		h=(l+r)/2;
		if(sum==Data[h].sum){
			break;
		}else if(sum>Data[h].sum){
			l=h;
		}else if(sum<Data[h].sum){
			r=h;
		}
	}
	return Data[h].rank;

}

student serchNo(int num,student *Data,int N){
	student result;
	int l=0;
	int r=N-1;
	int h=(N-1)/2;
	while(1){
		h=(l+r)/2;
		if(r-l<2){
			result.stunum=-1;
			return result;
		}
		if(num==Data[h].stunum){
			break;
		}else if(num>Data[h].stunum){
			l=h;
		}else if(num<Data[h].stunum){
			r=h;
		}
	}
	result.stunum=num;
	result.SubA=Data[h].SubA;
	result.SubB=Data[h].SubB;
	result.SubC=Data[h].SubC;
	result.sum=Data[h].sum;
	return result;
}

void writerank(student *Data){
	int j=1;
	for(int i=Num-1;i>=0;i--){
		Data[i].rank=j;
		j++;
	}
}

int main(void){
	student Data[Num],Result;
	int No;

	//学籍番号を入力する
	printf("Input A Student Number:");
	scanf("%d",&No);

	/*Dataを読みとる*/
	readDataFile(Data);
	/*入力されたNoを二分探索により探し，結果をResultに入れる*/
	Result = serchNo(No,Data,Num); /*ここではまだ順位は付いていない*/
	if(Result.stunum==-1){
		printf("No data\n");
		return 0;
	}
	/*順位を付けるために，合計点でソートする*/
	QuickSort(Data,Num);
	/*合計点が高い方から順位を付ける*/
	writerank(Data);
	/*Result.sumに入っている合計点を二分探索により探す*/
	Result.rank = serchsum(Result.sum,Data,Num); /*ここで順位が含まれた結果が得られる*/

	printf("Ranking   :  #%d\n",Result.rank);
	printf("Subject A :  %d\n",Result.SubA);
	printf("Subject B :  %.1f\n",Result.SubB);
	printf("Subject C :  %.2f\n",Result.SubC);
	printf("Total     :  %.2f\n",Result.sum);

	return 0;
}



