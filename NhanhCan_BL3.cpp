#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char TenDV[20];
	float TL, GT, DG;
	int PA;
} DoVat;


DoVat * ReadFromFile(float *W, int *n) {
	FILE *f;
	f = fopen("CaiBalo3.INP", "r");
	fscanf(f, "%f", W);
	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f)) {
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
		dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}

void swap(DoVat* x, DoVat* y) {
	DoVat temp = *x;
	*x = *y;
	*y = temp;
}
void BubbleSort(DoVat * dsdv, int n) {
	int i, j;
	for(i = 0; i <= n-2; i++) 
		for(j=n-1; j>=i+1; j--) 
			if(dsdv[j].DG > dsdv[j-1].DG)
				swap(&dsdv[j], &dsdv[j-1]);
}

void InDSDV(DoVat *dsdv ,int n, float W){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhuong an Cai Ba lo 3 dung thuat toan NHANH CAN nhu sau:\n");
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     |T. Luong | Gia Tri | Don gia | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d     |\n",
		i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG, dsdv[i].PA);
		TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
		TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|--------------------|---------|---------|---------|-----------|\n");	
	printf("Trong luong cua ba lo = %-9.2f\n",W);
	printf("Tong trong luong = %-9.2f\n",TongTL);
	printf("Tong gia tri = %-9.2f\n",TongGT);
	printf("Phuong an X = (");
	for(int i = 0 ; i< n; i++) {
		if(i!= n-1) {
			printf("%d, ", dsdv[i].PA);
		}
		else{
			printf("%d", dsdv[i].PA);
		}
	}
	printf(")");
}

void Tao_Nut_Goc(float W, float *v, float *CT, float *GLNTT, float *TGT, float DG_Max) {
	*TGT = 0.0;
	*v = W;
	*CT = *v * DG_Max;	
	*GLNTT = 0.0;
}

void Cap_Nhat_GLNTT(float TGT, float *GLNTT, int x[], DoVat *dsdv, int n) {
	int i;
	if(*GLNTT < TGT) {
		*GLNTT = TGT;
		for(i=0;i<n;i++) 
			dsdv[i].PA = x[i];
	}
}

int min(int a, int b) {
	return a<b?a:b;
}

void Nhanh_Can(int i,float *TGT ,float *CT, float *v, float *GLNTT, int x[], DoVat* dsdv, int n) {
	int j;
	int yk;
	yk = min(1,*v/dsdv[i].TL);
	for(j = yk; j>=0; j--) {
		*TGT = *TGT + j*dsdv[i].GT;
		*v = *v - j*dsdv[i].TL;
		*CT = *TGT + *v * dsdv[i+1].DG;
		if(*CT > *GLNTT) {
			x[i] = j;
			if( i == n-1 || *v == 0) {
				Cap_Nhat_GLNTT(*TGT, GLNTT, x, dsdv, n);
			}
			else Nhanh_Can(i+1, TGT, CT, v, GLNTT, x, dsdv, n);
		}
		x[i] = 0;
		*TGT = *TGT - j*dsdv[i].GT;
		*v = *v + j*dsdv[i].TL;
	}	
}
int main(){
	DoVat * dsdv;	// Danh sach cac do vat (mang dong cua cac do vat)
	int n; 			// luu so luong do vat
	float W; 		// Luu trong luong cua Ba lo
	
	float CT; 		// Luu can tren
	float TGT; 		// Luu Tong gia tri cua cac vat da duoc chon tai moi nut
	float V; 		// Luu Trong luong con lai cua Ba lo tai moi nut
	float GLNTT; 	// Luu Gia lon nhat tam thoi 
	
	dsdv = ReadFromFile(&W, &n);
	
	int x[n];		// Luu phuong an tot nhat tam thoi
	
	BubbleSort(dsdv,n);
	Tao_Nut_Goc(W, &V, &CT, &GLNTT, &TGT, dsdv[0].DG);
	Nhanh_Can(0, &TGT, &CT, &V, &GLNTT, x, dsdv, n);
	InDSDV(dsdv,n,W);
	
	free(dsdv);
	return 0;
}













