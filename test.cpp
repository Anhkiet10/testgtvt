#include<stdio.h>
#define MAX 100
char filename[30] = "KRU_8D.txt";
int daduyet[MAX];
struct DOTHI {
	int sodinh;
	int a[MAX][MAX];//ma tran ke cua do thi
};
struct CANH {
	int v1, v2, ts;
};
void docFile(DOTHI& g) {
	//printf("nhap ten File:"); scanf("%s",&tenFile);
	FILE* f = fopen(filename, "rt");
	if (f == NULL) {
		printf("\nkhong mo duoc file!");
		return;
	}
	// da mo duoc file
	fscanf(f, "%d", &g.sodinh);
	for (int i = 0;i < g.sodinh;i++)
		for (int j = 0;j < g.sodinh;j++)
			fscanf(f, "%d", &g.a[i][j]);
	fclose(f);	//dong file
}
void xuatDT(DOTHI g) {
	printf("%3d\n", g.sodinh);
	for (int i = 0;i < g.sodinh;i++) {
		printf("\n");
	}
}
void duyetDFS(int dinhXP, DOTHI g) {
	daduyet[dinhXP] = 1;
	for (int i = 0;i < g.sodinh;i++)
		if (daduyet[i] == 0 && g.a[i][dinhXP] != 0)
			duyetDFS(i, g);
}
int soTPLT(DOTHI g) {
	for (int i = 0;i < g.sodinh;i++)
		daduyet[i] = 0;// cac dinh deu chua duyet
	int dem = 0;
	for (int i = 0;i < g.sodinh;i++)
		if (daduyet[i] == 0) {
			dem++;
			duyetDFS(i, g);
		}
	return dem;
}
void Prim(DOTHI g) {
	if (soTPLT(g) > 1) {
		printf("\ndo thi khong lien thong");
		return;
	}
	int VT[MAX] = { 0 };//Tap hop cac dinh thuoc cay khung (TREE), dinh i thuoc TREE thi VT[i]=1
	CANH ET[MAX * 2];//Tap hop cac canh thuoc TREE
	int nET = 0;// so canh cua TREE
	VT[0] = 1;//chon dinh 0 cho vao VT
	while (nET < (g.sodinh - 1)) {
		int min = 1000;
		CANH tam;
		for (int v = 0; v < g.sodinh;v++)
			if (VT[v] == 1)// dinh v thuoc TREE
				for (int s = 0;s < g.sodinh;s++)
					if (VT[s] == 0 && g.a[v][s] != 0 && g.a[v][s] < min)//s o ngoai TREE va ts nho nhat
					{
						tam.v1 = v;
						tam.v2 = s;
						tam.ts = g.a[v][s];
						min = g.a[v][s];
					}
		ET[nET++] = tam;//bo canh tam vao tap hop ET
		VT[tam.v2] = 1;//danh dau dinh cuoi cua canh moi dua vao cay khung la dinh thuoc VT
	}
	//in TREE va tong trong so TREE
	int sumts = 0;
	for (int i = 0;i < nET;i++) {
		sumts += ET[i].ts;//sumts=sumts+ET[i].ts
		printf("\n(%d,%d)=%d", ET[i].v1, ET[i].v2, ET[i].ts);
	}
	printf("\nTONG TRONG SO CUA TREE=%d", sumts);
}
int main() {
	DOTHI g;
	docFile(g);
	Prim(g);
}













