/*
 * Proyecto II - Sistemas Operativos
 * Gabriela Garro Abdykerimov
 * 29 Octubre 2017
 *
 * Para compilar: gcc -o star star.c tar.c 
 *
 * Uso del programa:
 * ./tar <opciones> <archivoSalida> <archivo1> <archivo2> ... <archivoN>
 *
 * Opciones:
 * * -c, –create : crea un nuevo archivo
 * * -x, –extract : extraer de un archivo
 * * -t, –list: listar los contenidos de un archivo
 * * --delete: borrar desde un archivo
 * * -u, –update: actualiza el contenido del archivo
 * * -v, –verbose: ver un reporte de las acciones a medida que se van realizando
 * * -f, –file: empaquetar contenidos de archivo, si no está presente asume la entrada estándar.
 * * -r, –append: agrega contenido a un archivo
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tar.h"

#define MAX_NUM_FILES 10

// Variables globales
bool arg_c = false;			// Create
bool arg_x = false;			// Extract
bool arg_t = false;			// List
bool arg_delete = false; 	// Delete
bool arg_u = false;			// Update
bool arg_v = false; 		// Verbose
bool arg_f = false; 		// File
bool arg_r = false; 		// Append
bool arg_d = false;			// Dump
bool arg_h = false;			// Help

char * tar_filename;
char * filenames[MAX_NUM_FILES];

/* Imprimir un error y salir del programa */
void print_error(char * error) {
	printf("ERROR: %s\n", error);
	exit(-1);
}

/* Texto de ayuda */
void print_help() {
	printf("Uso del programa:\n");
	printf("./tar <opciones> <archivoSalida> <archivo1> <archivo2> ... <archivoN>\n");
	printf("\n");
	printf("Opciones:\n");
	printf(" * -c, –create : crea un nuevo archivo\n");
	printf(" * -x, –extract : extraer de un archivo\n");
	printf(" * -t, –list: listar los contenidos de un archivo\n");
	printf(" * --delete: borrar desde un archivo\n");
	printf(" * -u, –update: actualiza el contenido del archivo\n");
	printf(" * -v, –verbose: ver un reporte de las acciones a medida que se van realizando\n");
	printf(" * -f, –file: empaquetar contenidos de archivo, si no está presente asume la entrada estándar\n");
	printf(" * -r, –append: agrega contenido a un archivo\n");
	exit(0);
}

/* Dump */
void print_dump() {
	printf("DUMP\n");
	exit(0);
}

/* Escribir las banderas especificadas por el usuario*/
bool set_flag(char * flag) {
	if ((strcmp(flag, "-c") == 0) || (strcmp(flag, "--create") == 0)) {
		printf("\t-c: Create\n");
		arg_c = true;
		return true;
	}
	else if ((strcmp(flag, "-x") == 0) || (strcmp(flag, "--extract") == 0)) {
		printf("\t-x: Extract\n");
		arg_x = true;
		return true;
	}
	else if ((strcmp(flag, "-t") == 0) || (strcmp(flag, "--list") == 0)) {
		printf("\t-t: List\n");
		arg_t = true;
		return true;
	}
	else if (strcmp(flag, "--delete") == 0) {
		printf("\t--delete: Delete\n");
		arg_delete = true;
		return true;
	}
	else if ((strcmp(flag, "-u") == 0) || (strcmp(flag, "--update") == 0)) {
		printf("\t-u: Update\n");
		arg_u = true;
		return true;
	}
	else if ((strcmp(flag, "-v") == 0) || (strcmp(flag, "--verbose") == 0)) {
		printf("\t-v: Verbose\n");
		arg_v = true;
		return true;
	}
	else if ((strcmp(flag, "-f") == 0) || (strcmp(flag, "--file") == 0)) {
		printf("\t-f: File\n");
		arg_f = true;
		return true;
	}
	else if ((strcmp(flag, "-r") == 0) || (strcmp(flag, "--append") == 0)) {
		printf("\t-r: Append\n");
		arg_r = true;
		return true;
	}
	else if ((strcmp(flag, "-d") == 0) || (strcmp(flag, "--dump") == 0)) {
		printf("\t-d: Dump\n");
		arg_d = true;
		return true;
	}
	else if ((strcmp(flag, "-h") == 0) || (strcmp(flag, "--help") == 0)) {
		/*printf("\t-h: Help\n");
		arg_h = true;
		return true;*/
		print_help();
	}
	return false;
}

/* Analizar los argumentos */
int get_args(int args, char * argv[]) {
	// Revisar cantidad min de argumentos
	if (args < 1) {
		print_error("Cantidad insuficiente de argumentos.");
	}
	//printf("Argumentos:\n");
	int arg_num = 1; // Contador de argumentos
	// Recuperar banderas
	while (arg_num <= 10 && arg_num < args) {
		if (set_flag(argv[arg_num])) {
			arg_num++;
			continue;
		}
		if (argv[arg_num][0] == '-') {
			int i;
			char argument[2] = "-?";
			for (i = 1; argv[arg_num][i] != '\0'; i++) {
				argument[1] = argv[arg_num][i];
				if (!set_flag(argument)) {
					print_error("Argumento erróneo. Use -h para obtener ayuda.");
				}
			}
			arg_num++;
		}
		else {
			//print_error("Argumento erróneo. Use -h para obtener ayuda.");
			break;
		}
	}

	// Guardar el nombre del archivo tar
	tar_filename = argv[arg_num];
	if (arg_v) printf("Archivo destino: %s\n", tar_filename);
	arg_num++;

	// Guardar los archivos a comprimir
	if(arg_v) printf("Archivos a comprimir:\n");
	if (arg_f) { // Si indica que los archivos se obtienen desde los comandos
		int i;
		for (i = 0; i < MAX_NUM_FILES, arg_num < args; i++, arg_num++) {
			filenames[i] = argv[arg_num];
			if (arg_v) printf("\t%s\n", filenames[i]);
		}
	}
	else {
		print_error("No se ha implementado lectura desde entrada estándar. Use -f.");
	}
	return 0;
}

int main(int argc, char * argv[]) {
	// Obtener valores de argumentos
	get_args(argc, argv);
	// Dump
	if (arg_d) {
		print_dump();
	}
	// Create
	else if (arg_c) {
		if (arg_v) printf("Acción: Crear archivo tar.\n");
		exit(0);
	}
	// Extract
	else if (arg_x) {
		if (arg_v) printf("Acción: Extraer archivo tar.\n");
		exit(0);
	}
	// List
	else if (arg_t) {
		if (arg_v) printf("Acción: Listar archivos en tar.\n");
		exit(0);
	}
	// Delete
	else if (arg_delete) {
		if (arg_v) printf("Acción: Borrar archivo en tar.\n");
		exit(0);
	}
	// Update
	else if (arg_u) {
		if (arg_v) printf("Acción: Actualizar archivo en tar.\n");
		exit(0);
	}
	// Append
	else if (arg_r) {
		if (arg_v) printf("Acción: Añadir archivo a tar.\n");
		exit(0);
	}
	else {
		print_error("No se indicó una acción a realizar.");
	}
}