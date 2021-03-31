#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r, g, b;
}pixel;

int main(){
	FILE *imagem;
	FILE *novaImagem;

	char chave[5];
	int i, j, larg, alt, max;

	imagem = fopen("imagem_binarizada.ppm", "r");

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

	printf("Imagem: largura = %d altura = %d chave = %s máximo = %d\n", larg, alt, chave, max);

	novaImagem = fopen("imagem_negada.ppm", "w+");

	if(novaImagem == NULL){
		printf("Erro ao abrir Nova Imagem!");
		return 0;
	}

	pixel **RGB = (pixel**) malloc (alt*sizeof(pixel*));

	for(i = 0; i < alt; i++)
		RGB[i] = (pixel*) malloc (larg*sizeof(pixel));

	for(i = 0; i < alt; i++)
		for(j = 0;j < larg; j++){
			fscanf(imagem, "%d", &RGB[i][j].r);
			fscanf(imagem, "%d", &RGB[i][j].g);
			fscanf(imagem, "%d", &RGB[i][j].b);
		}

	fprintf(novaImagem, "P3\n%d %d\n%d\n", alt, larg, max);

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++){
			if(RGB[i][j].r == 255){
				RGB[i][j].r = 0;
				RGB[i][j].g = 0;
				RGB[i][j].b = 0;
				fprintf(novaImagem, "\n%d ", RGB[i][j].r);
				fprintf(novaImagem, "%d ", RGB[i][j].g);
				fprintf(novaImagem, "%d ", RGB[i][j].b);
			}else if(RGB[i][j].r == 0){
				RGB[i][j].r = 255;
				RGB[i][j].g = 255;
				RGB[i][j].b = 255;
				fprintf(novaImagem, "\n%d ", RGB[i][j].r);
				fprintf(novaImagem, "%d ", RGB[i][j].g);
				fprintf(novaImagem, "%d ", RGB[i][j].b);
			}
		}

	fclose(imagem);
	fclose(novaImagem);

	return 0;
}