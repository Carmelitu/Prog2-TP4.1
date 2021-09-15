#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nombre[20];
    int edad;
} Persona;

typedef struct
{
    Persona dato;
    struct nodo*siguiente;
    int numero;
} nodo;

const char file[15] = "archi.txt";
const char file2[15] = "archi2.txt";


void cargarArchivo (char file[]);
void mostrarArchivo (char file[]);
nodo* archivoAlista (char file[], nodo* lista);
nodo* archivoAlistaEnOrden (char file[], nodo* lista);
nodo * insertarOrdenado(nodo* lista, nodo* nuevoNodo);
int buscarElemento(nodo* lista, char nombre[]);
nodo* intercalarListas (nodo* listaA, nodo* listaB, nodo* listaC);
nodo* inicLista (nodo*lista);
Persona cargarPersona();
nodo* crearNodo(Persona dato);
nodo* agregarPpio(nodo* lista, nodo* nuevoNodo);
nodo* cargarListaCompleta (nodo* lista);
void mostrarPersona (Persona aux);
void mostrarLista (nodo* lista);
nodo * borrarNodo (nodo* lista, char nombre[]);
nodo* borrarListaEntera (nodo * lista);
nodo* buscarUltNodo (nodo*lista);
nodo* agregarAlFinal (nodo*lista, nodo*nuevoNodo);

int main()
{

    nodo* lista;
    lista = inicLista(lista);

    /// 1

    cargarArchivo(file);
    mostrarArchivo(file);
    lista = archivoAlista(file,lista);
    mostrarLista(lista);


    /// 2 *!
    /*
    lista = archivoAlistaEnOrden(file,lista);
    mostrarLista(lista);
    */

    /// 3
    /*
    char name[15];
    printf("\n>Ingrese nombre de la persona a buscar: ");
    fflush(stdin);
    gets(name);
    int e = buscarElemento(lista,name);
    if (e == 1)
    {
        printf("\n>Se encontro a %s.", name);
    }
    else if (e == 0)
    {
        printf("\n>No se encontro a %s.", name);
    }
    */


    /// 4 *!
    /*
    nodo* listaA;
    nodo* listaB;
    nodo* listaC;
    listaA = inicLista(listaA);
    listaB = inicLista(listaB);
    listaC = inicLista(listaC);

    printf("\nCargando archivo A...\n");
    cargarArchivo(file);
    printf("\nMostrando archivo A...\n");
    mostrarArchivo(file);
    listaA = archivoAlista(file,listaA);
    printf("\nMostrando lista A...\n");
    mostrarLista(listaA);

    printf("\nCargando archivo B...\n");
    cargarArchivo(file2);
    printf("\nMostrando archivo B...\n");
    mostrarArchivo(file2);
    listaB = archivoAlista(file2,listaB);
    printf("\nMostrando lista B...\n");
    mostrarLista(listaB);


    listaC = intercalarListas(listaA,listaB,listaC);
    printf("\nMostrando lista C...\n");
    mostrarLista(listaC);
    */




    return 0;
}


/// 1.
// Hacer un programa que lea de un archivo datos y los inserte en una lista.
void cargarArchivo (char file[])
{
    Persona aux;
    char control = 's';
    FILE* pBuffer = fopen(file,"ab");

    if (pBuffer)
    {
        while(control == 's')
        {
            aux = cargarPersona();
            fwrite(&aux, sizeof(Persona), 1, pBuffer);
            printf("\n>Continuar? ");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(pBuffer);
    }
    else
    {
        printf("ERROR DE CARGA.");
    }
}

void mostrarArchivo (char file[])
{
    Persona aux;
    FILE* pBuffer = fopen(file, "rb");

    if (pBuffer)
    {
        while(fread(&aux,sizeof(Persona),1,pBuffer) > 0)
        {
            mostrarPersona(aux);
        }
        fclose(pBuffer);
    }
    else
    {
        printf("ERROR AL MOSTRAR.");
    }
}


nodo* archivoAlista (char file[], nodo* lista)
{
    Persona aux;
    nodo* nuevoNodo;
    FILE* pBuffer = fopen(file,"rb");

    if(pBuffer)
    {
        while (fread(&aux,sizeof(Persona), 1, pBuffer) > 0)
        {
            nuevoNodo = crearNodo(aux);
            lista = agregarPpio(lista,nuevoNodo);
        }
        fclose(pBuffer);
    }

    return lista;
}

/// 2.
// Hacer un programa que lea de un archivo datos y los inserte en una lista en forma ordenada.
nodo* archivoAlistaEnOrden (char file[], nodo* lista)
{
    Persona aux;
    nodo* nuevoNodo;
    FILE* pBuffer = fopen(file,"rb");

    if(pBuffer)
    {
        while (fread(&aux,sizeof(Persona), 1, pBuffer) > 0)
        {
            nuevoNodo = crearNodo(aux);
            lista = insertarOrdenado(lista,nuevoNodo);
        }

        fclose(pBuffer);
    }

    return lista;
}

nodo * insertarOrdenado(nodo* lista, nodo* nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;  // lista vacía
    }
    else
    {
        if(nuevoNodo->dato.edad < lista->dato.edad)
        {
            lista = agregarPpio(lista, nuevoNodo);   // inserto al principio porque el nuevo nodo es menor
        }
        else
        {
            nodo * ante = lista;  // inserto al medio o al final
            nodo * seg = lista -> siguiente;
            while(seg != NULL && nuevoNodo->dato.edad >= seg->dato.edad)
            {
                ante = seg;
                seg = seg->siguiente;
            }

            ante->siguiente = nuevoNodo;
            nuevoNodo->siguiente = seg;
        }
    }
    return lista;
}

/// 3.
// Hacer una función que retorne un 1 (uno) o 0 (cero) si existe un determinado elemento en una lista dada.
int buscarElemento(nodo* lista, char nombre[])
{
    int flag = 0;

    while (lista != NULL)
    {
        if(strcmpi(lista->dato.nombre, nombre) == 0)
        {
            flag = 1;
        }
        lista= lista->siguiente;
    }

    return flag;
}

/// 4.
// Función que intercale en orden los elementos de dos listas ordenadas generando una nueva lista.
// Se deben redireccionar los punteros, no se deben crear nuevos nodos.
nodo* intercalarListas (nodo* listaA, nodo* listaB, nodo* listaC)
{
    nodo* indicador;

    while (listaA != NULL && listaB != NULL)
    {
        if(listaA->dato.edad < listaB->dato.edad)
        {
            indicador = listaA;
            listaA = listaA -> siguiente;
            indicador -> siguiente = NULL; // Para que no apunte al siguiente nodo
            listaC = agregarAlFinal(listaC, indicador);
        }
        else
        {
            indicador = listaB;
            listaA = listaA -> siguiente;
            indicador -> siguiente = NULL;
            listaC = agregarAlFinal(listaC, indicador);
        }
    }

    // Una lista va a quedar vacía antes (corta el while por NULL), sigo evaluando acá...
    if (listaA != NULL)
    {
        listaC = agregarAlFinal(listaC, listaA);
    }
    else if (listaB != NULL)
    {
        listaC = agregarAlFinal(listaC, listaB);
    }

    return listaC;
}

// -------------------------------------- FUNCIONES BÁSICAS ----------------------------------------------------------
nodo* inicLista (nodo*lista)
{
    return NULL;
}

Persona cargarPersona()
{
    Persona aux;
    printf("\n>Ingrese nombre: ");
    fflush(stdin);
    gets(aux.nombre);
    printf(">Ingrese edad: ");
    scanf("%i", &aux.edad);
    return aux;
}

nodo* crearNodo(Persona dato)
{
    nodo* aux= (nodo*) malloc(sizeof(nodo));
    aux -> dato = dato;
    aux -> siguiente = NULL;

    return aux;
}

nodo* agregarPpio(nodo* lista, nodo* nuevoNodo)
{
    if(lista==NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo -> siguiente = lista;
        lista = nuevoNodo;
    }

    return lista;
}

nodo* cargarListaCompleta (nodo* lista)
{
    Persona aux;
    char control = 's';
    nodo* nuevoNodo;

    while (control == 's')
    {
        aux = cargarPersona();
        nuevoNodo = crearNodo(aux);
        lista = agregarPpio(lista,nuevoNodo);

        printf("\n>Continuar? ");
        fflush(stdin);
        scanf("%c", &control);
    }

    return lista;
}

void mostrarPersona (Persona aux)
{
    printf("---------------------------\n");
    printf(">Nombre: %s\n", aux.nombre);
    printf(">Edad: %i\n", aux.edad);
    printf("---------------------------\n");
}

void mostrarLista (nodo* lista)
{
    nodo* seguidora = lista;
    while (seguidora != NULL)
    {
        mostrarPersona(seguidora->dato);
        seguidora = seguidora->siguiente;
    }
}

nodo * borrarNodo (nodo* lista, char nombre[])
{
    if (lista != NULL)
    {
        if(strcmpi (nombre, lista->dato.nombre) == 0) // En primer lugar
        {
            nodo* aEliminar = lista;
            lista = lista->siguiente;
            free(aEliminar); // Borra la dir de memoria del nodo de la memoria
        }
        else
        {
            nodo* ante = lista;
            nodo* seg = lista->siguiente;
            while (seg != NULL && strcmpi (nombre, lista->dato.nombre) != 0)
            {
                ante = seg;
                seg = seg -> siguiente; // Hago un puenteo con estas variables
            }

            if (seg != NULL) // Encontró algo
            {
                ante->siguiente = seg->siguiente; // Ante queda apuntando al sig de seguidora para no perder conexión
                free(seg); // Se elimina seg
            }

        }

    }

    return lista;
}

nodo* borrarListaEntera (nodo * lista)
{
    nodo* aEliminar;

    while (lista != NULL)
    {
        aEliminar = lista;
        lista = lista->siguiente;
        free(aEliminar);
    }

    return lista;

}

nodo* buscarNodo (char nombre[], nodo* lista)
{
    nodo*indicador = lista;

    while (indicador != NULL && strcmpi(nombre,indicador->dato.nombre) != 0)
    {
        indicador = indicador->siguiente;
    }

    return indicador; // Retorna dir del nodo o NULL si llegó al final y no lo encontró
}

nodo* buscarUltNodo (nodo*lista)
{
    nodo*indicador = lista;
    while (indicador -> siguiente != NULL)
    {
        indicador = indicador -> siguiente;
    }
    return indicador;
}

nodo* agregarAlFinal (nodo*lista, nodo*nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodo*ultimo = buscarUltNodo(lista);
        ultimo -> siguiente = nuevoNodo;
    }
    return lista;
}
