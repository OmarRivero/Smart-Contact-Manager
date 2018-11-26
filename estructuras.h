/**Tabla hash abierta
	Decidi utilizar una función hash propuesta por Brian
	Kerninghan y Dennis Ritchie para procesar tipos de cadenas,
	en la que basicamente se forma un numero muy grande con la
	combinacion de los valores enteros de cada caracter y
	finalmente se aplica un modulo para obtener un valor aceptable en
	alguna celda de la tabla hash.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCEL 10

typedef struct moldec{
  char *nombre;
  struct moldec *next;
}tcelda, *pcelda;

static pcelda hashtable[MAXCEL];

void makenull(void){
	int i;
	for(i = 0; i < MAXCEL; i++){
		hashtable[i]->nombre = "/vacio";
		hashtable[i] = NULL;
	}
}

//Funcion hash
unsigned int stringhash(char *s){
	unsigned int h = 0;
	for(int i = 0; *s; s++){
		h = 131*h + *s;
	}
	return(h % MAXCEL);
}

pcelda search(char *s){
	pcelda cp;
	for(cp = hashtable[stringhash(s)]; cp != NULL; cp = cp->next){
		if (strcmp(s, cp->nombre) == 0)
		{
		    printf("Ya estaba en la tabla, no se agregara\n\n");
			return(cp); //Significa que lo encontró
		}
	}
	printf("Elemento no encontrado, se agregara a la tabla...\n\n");
}

char *strsave(char *s){
	char *p;
	if((p = malloc(strlen(s) + 1)) != NULL)
		strcpy(p, s);
	return(p);
}

pcelda insertar(char *s){
	pcelda cp;
	int hval;
	if((cp = search(s)) == NULL){
		cp = (pcelda) malloc(sizeof(tcelda));
		if(cp == NULL)
            return NULL;
		if((cp->nombre = strsave(s)) == NULL)
			return NULL;
        hval = stringhash(cp->nombre);
		cp->next = hashtable[hval];
		hashtable[hval] = cp;
		display();
		return(cp);
	}
}

int eliminar(char *s){
	pcelda q, cp;
	cp = hashtable[stringhash(s)];
	if(cp != NULL){
		if(strcmp(s, cp->nombre) == 0){ //primero en la lista
			hashtable[stringhash(s)] = cp->next;
			display();
		}
		else
			for(q = cp, cp = cp->next; cp != NULL; q = cp, cp->next){
				if(strcmp(s,cp->nombre) == 0){
					q->next = cp->next;
					display();
					break;
				}
			}
		if (cp != NULL)
		{
			free((char *) cp->nombre);
			free((pcelda) cp);
			return 0;
		}
		else
			return 1; //no lo encontró en la tabla
	}
	else
		return 1; // la tabla esta vacia
}

void display(void){
    pcelda cp;
    printf("==================================\n");
    printf("Tabla hash hasta el momento\n");
	for(int i = 0; i < MAXCEL; i++){
		cp = hashtable[i];
		if(cp == NULL){
            printf("/Vacio");
		}
		while(cp != NULL){
            printf("%s-> ", cp->nombre);
            cp = cp->next;
		}
		printf("\n");
	}
	printf("==================================\n\n");
}
