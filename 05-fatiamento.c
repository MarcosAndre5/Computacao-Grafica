#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int tomCinza;
}pixel;

int main(){
	int i, j, largura, altura, tamanhoEscala, cinzaMinimo = 100, cinzaMaximo = 200;
	char chave[2];

	FILE *imagem;
	FILE *novaImagem;
	
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

    novaImagem = fopen("imagemFatiamento.pgm","w+"); //abre o novo arquivo que vai ser criado
	
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
			if(cinzaMinimo >= CINZA[i][j].tomCinza && CINZA[i][j].tomCinza <= cinzaMaximo)
				fprintf(novaImagem, "%d ", CINZA[i][j].tomCinza);
			else
				fprintf(novaImagem, "%d ", 255);
	
	printf("\nNova Imagem gerada com Sucesso!\n");
	fclose(imagem);
	fclose(novaImagem);
	return 0;
}