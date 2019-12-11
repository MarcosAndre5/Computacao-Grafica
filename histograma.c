#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r, g, b;
}pixel;

typedef struct{
	float R[255], G[255], B[255];
}histograma;

int main(){
	FILE *imagem;
	FILE *novaImagem;

	char chave[5];
	int i, j, larg, alt, max, k;
	histograma img;

	imagem = fopen("AA.ppm", "r");
	
	if(imagem == NULL){
		printf("Erro na abertura da Imagem!\n");
		return 0;
	}

	fscanf(imagem, "%s", chave);

	if(strcmp(chave, "P3") != 0){
		printf("Erro! A Imagem não é no formato PPM.\n");
		printf("%s\n", chave);
		fclose(imagem);
		return 0;
	}

	fscanf(imagem, "%d %d\n%d\n", &alt, &larg, &max);

	printf("Iamgem: largura = %d altura = %d chave = %s máximo = %d\n", larg, alt, chave, max);

	novaImagem = fopen("imagem_histograma.ppm", "w+");

	if(novaImagem == NULL){
		printf("Erro ao abrir Nova Imagem!");
		return 0;
	}

	pixel **RGB = (pixel**) malloc (alt*sizeof(pixel*));
	
	for(i = 0; i < alt; i++)
		RGB[i] = (pixel*) malloc (larg*sizeof(pixel));

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++){
			fscanf(imagem, "%d", &RGB[i][j].r);
			fscanf(imagem, "%d", &RGB[i][j].g);
			fscanf(imagem, "%d", &RGB[i][j].b);
		}

	for(k = 0; k <= 255; k++){
		img.R[k] = 0;
		img.G[k] = 0;
		img.B[k] = 0;
	}

	fprintf(novaImagem, "P3\n%d %d\n%d\n", alt, larg, max);

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++)
			for(k = 0; k <= 255; k++)
				if(RGB[i][j].r == k)
					img.R[k]++;

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++)
			for(k = 0; k <= 255; k++)
				if(RGB[i][j].g == k)
					img.G[k]++;

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++)
			for(k = 0; k <= 255; k++)
				if(RGB[i][j].b == k)
					img.B[k]++;

	fprintf(novaImagem, "\nHistograma - RED\n");

	for(k = 0; k <= 255; k++)
		fprintf(novaImagem, "%.3f\n", img.R[k] / 100);

	fprintf(novaImagem, "\nHistograma - GREEN\n");

	for(k = 0; k <= 255; k++)
		fprintf(novaImagem, "%.3f\n", img.G[k] / 100);

	fprintf(novaImagem, "\nHistograma - BLUE\n");

	for(k = 0; k <= 255; k++)
		fprintf(novaImagem, "%.3f\n", img.B[k] / 100);

	fclose(imagem);
	fclose(novaImagem);

	return 0;
}