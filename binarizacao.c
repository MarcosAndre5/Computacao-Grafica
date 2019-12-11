#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r, g, b;
}pixel;

int main(){
	FILE *image;
	FILE *newImage;

	char key[5];
	int i, j, larg, alt, max;

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
		for(j = 0;j < larg; j++){
			fscanf(image, "%d", &RGB[i][j].r);
			fscanf(image, "%d", &RGB[i][j].g);
			fscanf(image, "%d", &RGB[i][j].b);
		}

	fprintf(newImage, "P3\n%d %d\n%d\n", alt, larg, max);
	
	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++){
			if(RGB[i][j].r <= 126){
				RGB[i][j].r = 0;
				RGB[i][j].g = 0;
				RGB[i][j].b = 0;
				fprintf(newImage, "\n%d ", RGB[i][j].r);
				fprintf(newImage, "%d ", RGB[i][j].g);
				fprintf(newImage, "%d ", RGB[i][j].b);
			}
			if(RGB[i][j].r >= 126){
				RGB[i][j].r = 255;
				RGB[i][j].g = 255;
				RGB[i][j].b = 255;
				fprintf(newImage, "\n%d ", RGB[i][j].r);
				fprintf(newImage, "%d ", RGB[i][j].g);
				fprintf(newImage, "%d ", RGB[i][j].b);
			}
		}

	fclose(image);
	fclose(newImage);

	return 0;
}