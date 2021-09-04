#include <stdio.h>
#include <stdlib.h>

int main()
{
    nodo* lista;
    lista = inicLista(lista);

    /// Prueba
    /*
    lista = cargarListaCompleta(lista);
    mostrarLista(lista);
    */

    /// 1
    /*
    cargarArchivo(file);
    mostrarArchivo(file);
    lista = archivoAlista(file,lista);
    mostrarLista(lista);
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
            lista = agregarAlista(lista,nuevoNodo);
        }
        fclose(pBuffer);
    }

    return lista;
}
