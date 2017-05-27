#include <stdio.h>
#include <stdlib.h>

int main (void){
	int dataset;
	scanf("%d",&dataset);
	int *data = (int *)malloc(sizeof(int)*dataset*100);
	int *count_data = (int *)malloc(sizeof(int)*dataset);
	if(data == NULL) exit(0);


	//input >> array
	int i,j;
	char input[100];
	for(i = 0; i < dataset; i++){
		scanf("%s",input);
		for(j = 0; input[j] != '\0'; j++){
			data[i*100+j]= input[j]-48;
			count_data[i] = j+1;
		}
	}

	int b;
	int s,t;

	for(i = 0; i < dataset; i++){
		int ways[count_data[i] - 1][8][count_data[i]];
		for(b = 1; b < count_data[i]; b++){
			s = count_data[i] - b;
			for(j = 0; j < b; j++){
				ways[b-1][0][j] = data[i*100+j];
				ways[b-1][1][j] = data[i*100+j];
				ways[b-1][2][s] = data[i*100+j];
				ways[b-1][6][s] = data[i*100+j];
				s++;
			}

			s = 0;
			t = count_data[i] - b;
			for(j = b - 1; j >= 0; j--){
				ways[b-1][3][t] = data[i*100+j];
				ways[b-1][7][t] = data[i*100+j];
				ways[b-1][4][s] = data[i*100+j];
				ways[b-1][5][s] = data[i*100+j];
				s++;
				t++;
			}
			t = 0;
			for(j = b; j < count_data[i]; j++){
				ways[b-1][0][j] = data[i*100+j];
				ways[b-1][4][j] = data[i*100+j];
				ways[b-1][6][t] = data[i*100+j];
				ways[b-1][7][t] = data[i*100+j];
				t++;
			}
			s = b;
			t = 0;
			for(j = count_data[i] - 1; j >= b;j--){
				ways[b-1][1][s] = data[i*100+j];
				ways[b-1][5][s] = data[i*100+j];
				ways[b-1][2][t] = data[i*100+j];
				ways[b-1][3][t] = data[i*100+j];
				s++;
				t++;
			}
		}
		int unique_flg[count_data[i] - 1][8];
		int unique_tmp_flg[count_data[i] - 1][8];
		int x,y;
		for(x = 0;x < count_data[i] - 1; x++){
			for(y = 0; y < 8; y++){
				unique_flg[x][y] = 0;
				unique_tmp_flg[x][y] = 0;
			}
		}
		int p,q,r;
		int g,h;
		for(x = 0; x < count_data[i] - 1; x++){
			for(y = 0; y < 8; y++){
				if(unique_flg[x][y] == 0){
					for(g = 0; g < count_data[i]-1;g++){
						for(h = 0; h < 8; h++){
							unique_tmp_flg[g][h] = 0;
						}
					}
					for(p = 0; p < count_data[i] - 1; p++){
						for(q = 0; q < 8; q++){
							if(q == y && p == x){
								continue;
							}
							for(r = 0; r < count_data[i]; r++){
								if(ways[x][y][r] != ways[p][q][r]){
									unique_tmp_flg[p][q] = 1;
								}
								if(unique_tmp_flg[p][q] != 0){
									break;
								}
							}
							if(unique_tmp_flg[p][q] == 0){ //unique? -> false

								unique_flg[p][q] = 1; //unique? -> false
							}
						}
					}
				}
			}
		}

		//count
		int result = 0;
		for(x = 0; x < count_data[i] - 1; x++){
			for(y = 0; y < 8; y++){
				if(unique_flg[x][y] == 0){
					result++;
				}
			}
		}
		printf("%d\n",result);
	}


	free(data);
	free(count_data);
	return 0;
}


