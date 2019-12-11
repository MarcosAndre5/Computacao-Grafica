#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int r, g, b;
}pixel;

int main(){
	FILE *image;
	FILE *image2;
	FILE *newImage;

	char key[5], _key[5];
	int i, j, larg, alt, max, aux, _i,_j, _larg, _alt, _max;

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

	printf("Image larg = %d alt = %d key = %s max = %d\n", larg, alt, key, max);

	pixel **RGB = (pixel**) malloc (alt*sizeof(pixel*));

	for(i = 0; i < alt; i++)
		RGB[i] = (pixel*) malloc (larg*sizeof(pixel));

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++){
			fscanf(image, "%d", &RGB[i][j].r);
			fscanf(image, "%d", &RGB[i][j].g);
			fscanf(image, "%d", &RGB[i][j].b);
		}

	image2 = fopen("BB.ppm", "r");

	if(image2 == NULL){
		printf("Erro na abertura do arquivo\n");
		return 0;
	}

	fscanf(image2, "%s", _key);

	if(strcmp(_key, "P3") != 0){
		printf("Arquivo n eh PPM\n");
		printf("%s\n",_key);
		fclose(image2);
		return 0;
	}

	fscanf(image2, "%d %d\n%d\n", &_alt, &_larg, &_max);

	printf("Image2 larg = %d alt = %d key = %s max = %d\n", _larg, _alt, _key, _max);

	newImage = fopen("arquivo.ppm", "w+");

	if(newImage == NULL){
		printf("Erro ao abrir a nova imagem!");
		return 0;
	}

	pixel **RGB2 = (pixel**) malloc (alt*sizeof(pixel*));

	for(i = 0; i < alt; i++)
		RGB2[i] = (pixel*) malloc (larg*sizeof(pixel));

	for(i = 0; i < alt; i++)
		for(j = 0; j < larg; j++){
			fscanf(image2, "%d", &RGB2[i][j].r);
			fscanf(image2, "%d", &RGB2[i][j].g);
			fscanf(image2, "%d", &RGB2[i][j].b);
		}

	fprintf(newImage, "P3\n%d %d\n%d\n", alt, larg, max);

	for(i = 0; i < alt; i++){
		for(j = 0; j < larg; j++){
			if((RGB[i][j].r / RGB2[i][j].r) > 255){
				aux = 255;
				fprintf(newImage, "%d ", aux);
			}else if((RGB[i][j].r / RGB2[i][j].r) < 0){
				aux = 0;
				fprintf(newImage, "%d ", aux);
			}else
				fprintf(newImage, "%d ", (RGB[i][j].r / RGB2[i][j].r));

			if((RGB[i][j].g / RGB2[i][j].g) > 255){
				aux = 255;
				fprintf(newImage, "%d ", aux);
			}else if((RGB[i][j].g / RGB2[i][j].g) < 0){
				aux = 0;
				fprintf(newImage, "%d ", aux);
			}else
				fprintf(newImage, "%d ", (RGB[i][j].g / RGB2[i][j].g));

			if((RGB[i][j].b / RGB2[i][j].b) > 255){
				aux = 255;
				fprintf(newImage, "%d ", aux);
			}else if((RGB[i][j].b / RGB2[i][j].b) < 0){
				aux = 0;
				fprintf(newImage, "%d ", aux);
			}else
				fprintf(newImage, "%d ", (RGB[i][j].b / RGB2[i][j].b));
		}
		fprintf(newImage, "\n");
	}

	fclose(image);
	fclose(image2);
	fclose(newImage);

	return 0;
}