#include <stdio.h>
#include<math.h>

#define N 300 //何ブロックあるか
#define KETA 4 //　１ブロック何桁あるか
#define C_N 2000  //nCr　の　n
#define C_R 1000 //nCr　の　r


//int型の普通の整数値を多倍長整数形式に変換する
void henkan(int base,int *num){
	for(int i=0;i<N;i++){
		*(num+i)=0;
	}
	for(int i=5;i>=0;i--){
		if(i==0){
			num[i]=base;
		}else{
			num[i]= base/ (pow( 10,KETA*(i) ) );
			base-=num[i]*pow( 10,KETA*(i) );
		}
	}
}

//　ある多倍長整数を別の多倍長整数に代入する
void substitute(int *base,int *new){
	for(int i=0;i<N;i++){
		new[i]=base[i];
	}
}
//多倍長整数を表示する
//なにも値が入っていない（０が入っている）ものを、普通に表示させると000000224とかになる
//また、１ブロックの桁数が四桁のとき、あるブロックに234というすうじが入っているときは、0234と表示させないとブロック全体での桁数がへっちゃう
//ただし、０でない一番先頭のブロックに限っては、０をつけずに表示したい
// num[1]=23,num[0]=346とすると、表示は230346としたいってこと
void print(int *num){
	int start=0;
	for(int s=N-1;s>=0;s--){
		if(num[s]!=0){
			start=s;
			break;
		}
	}
	for(int i=start;i>=0;i--){
		if(i == start){
			printf("%d",num[i]);
		}else{
			for(int s=1;s<KETA;s++){
				if(num[i] < pow(10,s)){
					for(int t=0;t<KETA-s;t++){
						printf("0");
					}
					break;
				}

			}
			printf("%d",num[i]);
		}
	}
	printf("\n");
}
//加法を定義
//足している途中で１ブロックに入っている値がKETAで定義した（今回は４桁）をこえて五桁になったりする
//それを防ぐために、桁数が超えちゃったら、次のブロックに繰り上がらせる
void plus(int *data1,int *data2,int *answer){
	for(int i=0;i<N;i++){
		answer[i]=0;
	}
	int buf;
	for(int i=0;i<N;i++){
		if(data1[i]+data2[i] >= pow(10,KETA)){
			answer[i+1]+= (data1[i]+data2[i]) / pow(10,KETA);
			answer[i]+=(data1[i]+data2[i]) % (int)pow(10,KETA);
			if(answer[i] >= pow(10,KETA)){
				buf = answer[i] / pow(10,KETA);
				answer[i+1]+= buf;
				answer[i]-= buf * pow(10,KETA);
			}
			if(answer[i+1] >= pow(10,KETA)){
				buf = answer[i+1] / pow(10,KETA);
				answer[i+2]+=buf;
				answer[i+1]-= buf * pow(10,KETA);
			}
		}else{
			answer[i]+=data1[i]+data2[i];
			if(answer[i] >= pow(10,KETA)){
				buf = answer[i] / pow(10,KETA);
				answer[i+1]+= buf;
				answer[i]-= buf * pow(10,KETA);
			}
			if(answer[i+1] >= pow(10,KETA)){
				buf = answer[i+1] / pow(10,KETA);
				answer[i+2]+=buf;
				answer[i+1]-= buf * pow(10,KETA);
			}
		}
	}
}

//乗法？掛け算を定義、繰り上がりに関してはplusと同じ
//0になにをかけても０なので、そのときはそのブロックに対する試行をcontinueでスキップしている
void multiplie(int *data1,int *data2,int *answer){
	for(int i=0;i<N;i++){
		answer[i]=0;
	}
	int buf;
	for(int i=0;i<N;i++){
		if(data1[i]==0){
			continue;
		}
		for(int j=0;j<N;j++){
			if(data2[j]==0){
				continue;
			}
			if(data1[i]*data2[j] >= pow(10,KETA)){
				answer[i+j+1]+= data1[i]*data2[j] / pow(10,KETA);
				answer[i+j]+= (data1[i]*data2[j]) % (int)pow(10,KETA);
				if(answer[i+j] >= pow(10,KETA)){
					buf=answer[i+j] / pow(10,KETA);
					answer[i+j+1]+= buf;
							answer[i+j]-= buf * pow(10,KETA);
				}
				if(answer[i+j+1] >= pow(10,KETA)){
					buf=answer[i+j+1] / pow(10,KETA);
					answer[i+j+2]+= buf;
					answer[i+j+1]-= buf * pow(10,KETA);
				}
			}else{
				answer[i+j]+=data1[i]*data2[j];
				if(answer[i+j] >= pow(10,KETA)){
					buf=answer[i+j] / pow(10,KETA);
					answer[i+j+1]+= buf;
					answer[i+j]-= buf * pow(10,KETA);
				}
				if(answer[i+j+1] >= pow(10,KETA)){
					buf=answer[i+j+1] / pow(10,KETA);
					answer[i+j+2]+= buf;
					answer[i+j+1]-= buf * pow(10,KETA);
				}
			}
		}
	}
}

//累乗？なんか指数的なやつを定義、掛け算自体はmultiplieにまかせてる
//一個前の計算で得られた答えに、底の値をかけていく
//それをループで表現するために、試行回数が奇数が偶数かで、互い違いに試行して行く
void power(int *base,int index,int *answer){
	int buf1[N],buf2[N];
	multiplie(base,base,buf1);
	for(int i=2;i<index;i++){
		if(i%2 == 0){
			multiplie(buf1,base,buf2);
		}else{
			multiplie(buf2,base,buf1);
		}
	}
	if(index%2 == 0){
		substitute(buf1,answer);
	}else{
		substitute(buf2,answer);
	}
}

//ncr_yakubun　で約分したので、分母は１、分子には割り切れずにあまった数が残っている
//それをかけていく関数
void ncr_kakezan(int *bunsi,int *answer){
	for(int i=0;i<N;i++){
		answer[i]=0;
	}
	int count=0;
	int buf[N],buf1[N],buf2[N];
	henkan(1,buf1);
	for(int i=0;i<C_R;i++){
		if( *(bunsi+i) != 1){
			if(count %2 ==0){
				henkan( *(bunsi+i),buf);
				multiplie(buf1,buf,buf2);
				count++;
			}else{
				henkan( *(bunsi+i),buf);
				multiplie(buf2,buf,buf1);
				count++;
			}
		}
	}
	if(count%2 == 0){
		substitute(buf1,answer);
	}else{
		substitute(buf2,answer);
	}

}

//　分子と分母の数に関して、共通の約数を見つけて、約分していく
void ncr_yakubun(int *bunsi,int *bunbo){
	int flg1,flg2,bo_kai,si_kai;
	for(int d=C_R;d>1;d--){
		flg1=0;
		flg2=0;
		while(flg1 != 2 && flg2 !=2){
			for(int index_bo=C_R-1;index_bo>=0;index_bo--){
				if( *(bunbo+index_bo) % d ==0){
					flg1=1;
					bo_kai=index_bo;
					break;
				}
				if(index_bo == 0){
					flg1=2;
				}
			}
			if(flg1 ==1){
				for(int index_si=C_R-1;index_si>=0;index_si--){
					if( *(bunsi+index_si) % d ==0){
						flg2=1;
						si_kai=index_si;
						break;
					}
					if(index_si == 0){
						flg2=2;
					}
				}
				if(flg2 ==1){
					*(bunbo+bo_kai) /=d;
					*(bunsi+si_kai) /=d;
				}
			}
		}
	}
}





int main (void){
	int nCr[N]; //最終的な答えを格納する配列
	int bunbo[C_R]; //分母にある数を一つずつ格納する
	for(int i=0;i<C_R;i++){
		bunbo[i]=i+1;
	}
	int bunsi[C_R]; //分子も同じく
	int r_d=C_N-C_R+1;
	for(int j=0;j<C_R;j++){
		bunsi[j]=r_d;
		r_d++;
	}
	ncr_yakubun(bunsi,bunbo);
	ncr_kakezan(bunsi,nCr);
	printf("2000C1000 =\n");
	print(nCr);

	int num[N];
	int kaizyo[N];
	henkan(29,num);
	power(num,400,kaizyo);
	printf("29^400 =\n");
	print(kaizyo);

	int answer[N];
	plus(nCr,kaizyo,answer);
	printf("2000C1000 + 29^400 =\n");
	print(answer);





	return 0;
}
