#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r, g, b;
}pixel;

int main(){
	FILE *imagem1;
	FILE *imagem2;
	FILE *novaImagem;

	char chave[5], _chave[5];
	int i, j, larg, alt, max, aux, _i, _j, _larg, _alt, _max;

	imagem1 = fopen("AA.ppm", "r");

	if(imagem1 == NULL){
		printf("Erro na abertura da Imagem1!\n");
		return 0;
	}

	fscanf(imagem1, "%s", chave);

	if(strcmp(chave, "P3") != 0){
		printf("Erro! A Imagem1 não é no formato PPM.\n");
		printf("%s\n", chave);
		fclose(imagem1);
		return 0;
	}

	fscanf(imagem1, "%d %d\n%d\n", &alt, &larg, &max);

	printf("Imagem: largura = %d altura = %d chave = %s máxima = %d\n", larg, alt, chave, max);

	pixel **RGB = (pixel**) malloc (alt*sizeof(pixel*));

	for(i = 0; i < alt; i++)
		RGB[i] = (pixel*) malloc (larg*sizeof(pixel));

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++){
			fscanf(imagem1, "%d", &RGB[i][j].r);
			fscanf(imagem1, "%d", &RGB[i][j].g);
			fscanf(imagem1, "%d", &RGB[i][j].b);
		}

	imagem2 = fopen("BB.ppm", "r");

	if(imagem2 == NULL){
		printf("Erro na abertura da Imagem2!\n");
		return 0;
	}

	fscanf(imagem2, "%s", _chave);

	if(strcmp(_chave, "P3") != 0){
		printf("Erro! A Imagem2 não é no formato PPM.\n");
		printf("%s\n", _chave);
		fclose(imagem2);
		return 0;
	}

	fscanf(imagem2, "%d %d\n%d\n", &_alt, &_larg, &_max);

	printf("Imagem2: largura = %d altura = %d chave = %s máximo = %d\n", _larg, _alt, _chave, _max);

	novaImagem = fopen("imagem_naoLogica.ppm", "w+");

	if(novaImagem == NULL){
		printf("Erro ao abrir a Nova Imagem!");
		return 0;
	}

	pixel **RGB2 = (pixel**) malloc (alt*sizeof(pixel*));

	for(i = 0; i < alt; i++)
		RGB2[i] = (pixel*) malloc (larg*sizeof(pixel));

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++){
			fscanf(imagem2, "%d", &RGB2[i][j].r);
			fscanf(imagem2, "%d", &RGB2[i][j].g);
			fscanf(imagem2, "%d", &RGB2[i][j].b);
		}

	fprintf(novaImagem, "P3\n%d %d\n%d\n", alt, larg, max);

	for(i = 0; i < alt; i++){
		for(j = 0; j < larg; j++){
			if((RGB[i][j].r == RGB2[i][j].r) && ((RGB[i][j].g == RGB2[i][j].g)) && (RGB[i][j].b == RGB2[i][j].b)){
				fprintf(novaImagem, "%d ", 255);
				fprintf(novaImagem, "%d ", 255);
				fprintf(novaImagem, "%d ", 255);
			}else{
				fprintf(novaImagem, "%d ", RGB[i][j].r);
				fprintf(novaImagem, "%d ", RGB[i][j].g);
				fprintf(novaImagem, "%d ", RGB[i][j].b);
			}
		}
		fprintf(novaImagem, "\n");
	}
	fclose(imagem1);
	fclose(imagem2);
	fclose(novaImagem);

	return 0;
}