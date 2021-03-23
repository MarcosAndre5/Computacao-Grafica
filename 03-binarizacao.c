#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int R, G, B;
}pixel;

int main(){
	int i, j, largura, altura, tamanhoEscala;
	char chave[2];

	FILE *imagem, *novaImagem;

	imagem = fopen("Lena.ppm", "r");

	if(imagem == NULL){
		printf("Erro na abertura da Imagem!\n");
		return 0;
	}

	fscanf(imagem, "%s", chave);

	if(strcmp(chave, "P3") != 0){
		printf("Erro! A Imagem não é no formato PPM.\nChave: %s\n", chave);
		fclose(imagem);
		return 0;
	}

	fscanf(imagem, "%d %d\n%d\n", &altura, &largura, &tamanhoEscala);

	printf("Informacoes da Imagem:\nChave = %s\nLargura = %d | Altura = %d\nTamanho da Escala = %d\n", chave, largura, altura, tamanhoEscala);

	novaImagem = fopen("imagemBinarizada.ppm", "w+");

	if(novaImagem == NULL){
		printf("Erro ao abrir Nova Imagem!");
		return 0;
	}

	pixel **RGB = (pixel**) malloc (altura * sizeof(pixel*));

	for(i = 0; i < altura; i++)
		RGB[i] = (pixel*) malloc (largura * sizeof(pixel));

	for(i = 0; i < altura; i++)
		for(j = 0;j < largura; j++){
			fscanf(imagem, "%d", &RGB[i][j].R);
			fscanf(imagem, "%d", &RGB[i][j].G);
			fscanf(imagem, "%d", &RGB[i][j].B);
		}

	fprintf(novaImagem, "P3\n%d %d\n%d\n", altura, largura, tamanhoEscala);

	for(i = 0; i < altura; i++)
		for(j = 0; j < largura; j++){
			if(RGB[i][j].R <= 126){
				RGB[i][j].R = RGB[i][j].G = RGB[i][j].B = 0;
				fprintf(novaImagem, "\n%d ", RGB[i][j].R);
				fprintf(novaImagem, "%d ", RGB[i][j].G);
				fprintf(novaImagem, "%d ", RGB[i][j].B);
			}else if(RGB[i][j].R > 126){
				RGB[i][j].R = RGB[i][j].G = RGB[i][j].B = 255;
				fprintf(novaImagem, "\n%d ", RGB[i][j].R);
				fprintf(novaImagem, "%d ", RGB[i][j].G);
				fprintf(novaImagem, "%d ", RGB[i][j].B);
			}
		}

	printf("\nNova Imagem gerada com Sucesso!\n");
	fclose(imagem);
	fclose(novaImagem);
	return 0;
}