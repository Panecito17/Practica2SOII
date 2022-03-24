#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

/**********************************************************************************
Integrantes del equipo:
	Raul Francisco Pallas Talavera
	Diego Jair Hernández Monter
	Montserrat Valencia Garaicochea
	Alejandro Velázquez Peña
**********************************************************************************/

int main(int argc, char *argv[]){
	DIR *apdir;
	FILE *archie;
	char archv[30], path[100];
	int band=0;
	int fildes;
	struct stat info;
	struct dirent *infodir;
	strcpy(archv, argv[1]);
	if(argc>1 && argc<4){
		apdir=opendir(("./%s", archv));
		if(apdir != NULL){
			closedir(apdir);
			do{
				band=0;
				printf("Esta ya existe, haz otra porfa: ");
				fflush(stdin);
				scanf("%s", archv);
				apdir=opendir(("./%s", archv));
				if(apdir != NULL){
					band=1;
					closedir(apdir);
					printf("Apuntador cerrado");
				}else{
					band=0;
					band=mkdir(("./%s", archv), 0664);
					if(band==0){
						printf("El directorio si se creo \n");
					}else{
						printf("El directorio no se creo:c\n");
						exit(0);
					}
				}
			}while(band);
		}else{
			band=mkdir(("./%s", archv), 0664);
			if(band==0){
				printf("El directorio si se creo \n");
			}else{
				printf("El directorio no se creo\n");
				exit(0);
			}
		}
		strcat(path, "./");
		strcat(path, archv);
		strcat(path, "/");
		strcat(path, argv[2]);
		fildes = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if(fildes != -1){
			printf("Se abrio y creo su archivo \n");
			write(fildes, "Raul Francisco Pallas Talavera\n", 32);
			write(fildes, "Diego Jair Hernández Monter\n", 29);
			write(fildes, "Montserrat Valencia Garaicochea\n", 33);
			write(fildes, "Alejandro Velázquez Peña\n", 26);
			close(fildes);
			band=1;
		}else{
			band=0;
			printf("Donde esta el archivo\n");
		}

		if (band==1){
			link(path, "hardlink");
			printf("Enlace duro creado\n");
			symlink(path, "symlink");
			printf("Enlace simbolico creado\n\n");
		}

		fildes = open(path, O_RDONLY);
		if (fildes != -1){
			fstat(fildes, &info);
			printf("Info del archivo que se creo.\nNombre: %s\ninodo: %ld\ntamano: %ld\n#enlaces: %ld\n\n\n", argv[2], info.st_ino, info.st_size, info.st_nlink);
		}else{
			printf("Donde esta el archivo?");
}
		printf("Directorio de trabajo y sus entradas\n");
		apdir=opendir("./");
		if(apdir){
			do{
				infodir=readdir(apdir);
				if(infodir){
					fildes=open(infodir->d_name, O_RDONLY);
					if(fildes != -1){
						fstat(fildes, &info);
						printf("%s\nI-nodo: %ld\n\n", infodir->d_name, info.st_ino);
					}
				}
			}while(infodir!=NULL);
		} else{
		}
	}else{
		printf("Se necesita tener solo 2 argumentos\n");
	}
return 1;
}
