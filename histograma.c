#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r, g, b;
}pixel;

typedef struct{
	float R[255], G[255], B[255];
}histogram;

int main(){
	FILE *image;
	FILE *newImage;

	char key[5];
	int i, j, larg, alt, max, hist[255], k;
	histogram img;

	image = fopen("AA.ppm", "r");
	
	if(image == NULL){
		printf("Erro na abertura do arquivo\n");
		return 0;
	}

	fscanf(image, "%s", key);

	if(strcmp(key, "P3") != 0){
		printf("Arquivo nao e PPM\n");
		printf("%s\n", key);
		fclose(image);
		return 0;
	}

	fscanf(image, "%d %d\n%d\n", &alt, &larg, &max);

	printf("larg = %d alt = %d key = %s max = %d\n", larg, alt, key, max);

	newImage = fopen("arquivo.ppm", "w+");

	if(newImage == NULL){
		printf("Erro ao abrir nova imagem!");
		return 0;
	}

	pixel **RGB = (pixel**) malloc (alt*sizeof(pixel*));
	
	for(i = 0; i < alt; i++)
		RGB[i] = (pixel*) malloc (larg*sizeof(pixel));

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++){
			fscanf(image, "%d", &RGB[i][j].r);
			fscanf(image, "%d", &RGB[i][j].g);
			fscanf(image, "%d", &RGB[i][j].b);
		}

	for(k = 0; k <= 255; k++){
		img.R[k] = 0;
		img.G[k] = 0;
		img.B[k] = 0;
	}

	fprintf(newImage, "P3\n%d %d\n%d\n", alt, larg, max);

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

	fprintf(newImage, "\nHistograma - RED\n");

	for(k = 0; k <= 255; k++)
		fprintf(newImage, "%.3f\n", img.R[k] / 100);

	fprintf(newImage, "\nHistograma - GREEN\n");

	for(k = 0; k <= 255; k++)
		fprintf(newImage, "%.3f\n", img.G[k] / 100);

	fprintf(newImage, "\nHistograma - BLUE\n");

	for(k = 0; k <= 255; k++)
		fprintf(newImage, "%.3f\n", img.B[k] / 100);

	fclose(image);
	fclose(newImage);

	return 0;
}