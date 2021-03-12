#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int R, G, B;
}pixel;

int main(){
	int i, j, largura, altura, tamanhoEscala, escalaCinza;
	char chave[5];

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

	printf("Informacoes da Imagem:\nChave = %s\nLargura = %d Altura = %d\nTamanho da Escala = %d\n", chave, largura, altura, tamanhoEscala);

	novaImagem = fopen("imagemMonocromatica.ppm","w+");

	if(novaImagem == NULL){
		printf("Erro ao abrir Nova Imagem!");
		return 0;
	}

	pixel **RGB = (pixel**) malloc (altura * sizeof(pixel*));
	
	for(i = 0; i < altura; i++)
		RGB[i] = (pixel*) malloc (largura * sizeof(pixel));

	for(i = 0; i < altura; i++)
		for(j = 0; j < largura; j++){
			fscanf(imagem, "%d", &RGB[i][j].R);
			fscanf(imagem, "%d", &RGB[i][j].G);
			fscanf(imagem, "%d", &RGB[i][j].B);
		}

	fprintf(novaImagem, "P2\n%d %d\n%d\n", altura, largura, tamanhoEscala);

	for(i = 0; i < altura; i++, fprintf(novaImagem, "\n"))
		for(j = 0; j < largura; j++){
			escalaCinza = (RGB[i][j].R + RGB[i][j].G + RGB[i][j].B) / 3;
			fprintf(novaImagem, "%d ", escalaCinza);
		}

	printf("Nova Imagem gerada com Sucesso!\n");
	fclose(imagem);
	fclose(novaImagem);
	return 0;
}