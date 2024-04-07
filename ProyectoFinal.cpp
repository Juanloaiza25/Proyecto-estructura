#include<stdio.h>
#include<stdlib.h>

enum TipoVuelo{Nacional, Internacional};
enum ClaseTiquete{Economica, PrimeraClase};
enum Genero{Masculino, Femenino, Otro, NoEspecificado};
enum Meses{Enero=1, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre};


struct Fecha{
    int dia;
    Meses mes;
    int anio;
};

typedef struct nodo_pasajero{
    char *documento;
    char *nombre;
    char *apellido;
    char *telefono;
    Fecha fecha_nacimiento;
    char genero;

    struct nodo_pasajero *siguiente;
} NodoPas;

typedef struct nodo_vuelo{
    int tipo_vuelo;
    char codigo_vuelo;
    Fecha fecha_vuelo;
    int hora_salida;
    Fecha fecha_llegada;
    int hora_llegada;
    int sillas_disponibles;
    int sillas_ocupadas;
    int sillas_totales;
    struct nodo_vuelo *siguiente;
} NodoVuelo;

typedef struct nodo_tiquete{
    char *clase_tiquete;
    NodoPas pasajero;
    NodoVuelo vuelo;
    struct nodo_tiquete *siguiente;
} NodoTicket;
