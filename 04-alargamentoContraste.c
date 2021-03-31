#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int tomCinza;
}pixel;

int main(){
	int i, j, largura, altura, tamanhoEscala, maior, menor, cinza, idMin = 50, idMax = 150;
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

	novaImagem = fopen("imagemAlargamentoConstraste.pgm","w+");

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

	maior = menor = CINZA[0][0].tomCinza;

	for(i = 0; i < altura; i++)
		for(j = 0; j < largura; j++)
			if(CINZA[i][j].tomCinza > maior)
				maior = CINZA[i][j].tomCinza;
			else if(CINZA[i][j].tomCinza < menor)
				menor = CINZA[i][j].tomCinza;

	printf("Escala Máxima da Imagem: %d | Escala Minima da Imagem: %d\n", maior, menor);
	printf("Id Máximo: %d | Id Mínimo: %d\n", idMax, idMin);

	if((maior - menor) <= 0){
		printf("\nNão é possível aplicar o modelo nessa Imagem!\n");
		fclose(imagem);
		fclose(novaImagem);
		return 0;
	}

	fprintf(novaImagem, "P2\n%d %d\n%d\n", altura, largura, tamanhoEscala);

	for(i = 0; i < altura; i++, fprintf(novaImagem, "\n"))
		for(j = 0; j < largura; j++){
			cinza = (CINZA[i][j].tomCinza - menor) * (idMax - idMin) / (maior - menor) + idMin;
			fprintf(novaImagem, "%d ", cinza);
		}

	printf("Nova Imagem gerada com Sucesso!\n");
	fclose(imagem);
	fclose(novaImagem);
	return 0;
}