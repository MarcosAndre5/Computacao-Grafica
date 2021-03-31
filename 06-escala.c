#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int tomCinza;
}pixel;

int main(){
	int i, j, largura, altura, tamanhoEscala, Sx = 2, Sy = 2;
	char chave[2];

	FILE *imagem, *novaImagem;

	imagem = fopen("Lena.pgm", "r");
	
	if(imagem == NULL){
		printf("Erro na abertura da Imagem!\n");
		return 0;
	}

	fscanf(imagem, "%s", chave);
	
	if(strcmp(chave, "P2") != 0){
		printf("Erro! A Imagem não é no formato PGM.\nChave: %s\n", chave);
		fclose(imagem);
		return 0;
	}

	fscanf(imagem, "%d %d\n%d\n", &altura, &largura, &tamanhoEscala);
	
	printf("Informacoes da Imagem:\nChave = %s\nLargura = %d | Altura = %d\nTamanho da Escala = %d\n\n", chave, largura, altura, tamanhoEscala);

	novaImagem = fopen("imagemEscala.pgm","w+");
	
	if(novaImagem == NULL){
		printf("Erro ao abrir Nova Imagem!");
		return 0;
	}

	pixel **CINZA = (pixel**) malloc (altura * sizeof(pixel*));

	for(i = 0; i < altura; i++)
		CINZA[i] = (pixel*) malloc (largura * sizeof(pixel));

	for(i = 0; i < altura; i++)
		for(j = 0; j < largura; j++)
			fscanf(imagem, "%d", &CINZA[i][j].tomCinza);

	fprintf(novaImagem, "P2\n%d %d\n%d\n", altura, largura, tamanhoEscala);
	
	for(i = 0; i < altura; i++, fprintf(novaImagem, "\n"))
		for(j = 0; j < largura; j++)
			if((i * Sy < altura) && (j * Sx < largura) && (i * Sy >= 0) && (j * Sx >= 0))
				fprintf(novaImagem, "%d ", CINZA[i * Sy][j * Sx].tomCinza);
			else
				fprintf(novaImagem, "%d ", CINZA[i][j].tomCinza);

	printf("Nova Imagem gerada com Sucesso!\n");
	fclose(imagem);
	fclose(novaImagem);
	return 0;
}