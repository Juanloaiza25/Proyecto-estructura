#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*-----------------------------------------MACROS---------------------------------------------------------------------------*/
#define ANIOACTUAL				2024
#define BISIESTO				(((Anio%4 == 0) && (Anio%100 !=0)) || (Anio%400 == 0))
#define LIMPIAPANTALLA 			system("cls")

/*-----------------------------------------ENUMERACIONES--------------------------------------------------------------------*/

enum TipoVuelo{Nacional, Internacional};
enum ClaseTiquete{Economica, PrimeraClase};
enum Genero{Masculino, Femenino, Otro, NoEspecificado};
enum Meses{Enero=1, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre};
enum OpcionesMenu{ComprarTiquetes=1, Modificar, Listar, Buscar, CambiarSilla, Imprimir, Cancelar, Salir};

/*-----------------------------------------DECLARAR NOMBRE DE LOS NUMERADORES---------------------------------------------*/

const char *NombreTipoVuelo[] = {"Nacional", "Internacional"};
const char *NombreClaseTiquete[] = {"Economica", "Primera Clase"};
const char *NombreGenero[] = {"Masculino", "Femenino", "Otro", "No Especificado"};
const char *NombreMeses[] = {"No permitido", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

/*-----------------------------------------ESTRUCTURAS--------------------------------------------------------------------*/

/*Estructura de la fecha*/

typedef struct Fecha{
    int dia;
    Meses mes;
    int anio;
};

/*Estructura pasajeros*/

typedef struct nodo_pasajero{
    ClaseTiquete tiquete;
    char *documento;
    char *nombre;
    char *apellido;
    char *telefono;
    Fecha fecha_nacimiento;
    Genero genero;
    int Silla;

    struct nodo_pasajero *siguiente;
} NodoPas;
typedef NodoPas *Pasajero;


/*Estructura de los vuelos*/

typedef struct nodo_vuelo{
    int tipo_vuelo;
    char codigo_vuelo;
    Fecha fecha_vuelo;
    int hora_salida;
    Fecha fecha_llegada;
    int hora_llegada;
    struct nodo_vuelo *siguiente;
} NodoVuelo;
typedef NodoVuelo *Vuelo; 

/*-----------------------------------------DECLARACION FUNCIONES VALIDACION--------------------------------------*/

int DiaMaxMes(int Anio, Meses Mes)
{
    int DiaMax;
    switch(Mes)
    {
        case Enero:
        case Marzo:
        case Mayo:
        case Julio:
        case Agosto:
        case Octubre:
        case Diciembre:
            DiaMax = 31;
            break;

        case Abril:
        case Junio:
        case Septiembre:
        case Noviembre:
            DiaMax = 30;
            break;

        case Febrero:
            if (BISIESTO) DiaMax = 29;
            else DiaMax = 28;
            break;
    }
    return DiaMax;
}



int LeeAnioValido()
{
    int AnioValido;
    
    while(1)
    {
        scanf ("%u", &AnioValido); fflush(stdin);     
		if(AnioValido >= ANIOACTUAL && AnioValido <= ANIOACTUAL+5)
			return AnioValido;
        else{		
        	printf ("\7");
        	printf ("\n ERROR: Anio invalido");
        	printf ("\n Ingrese nuevamente el anio => ");
    	}
    }
}


enum Meses LeeMesValido()
{
    int MesValido;
    while(1)
    {
        scanf ("%u", &MesValido); fflush(stdin);
        if (MesValido >= Enero && MesValido <= Diciembre) 
            return (enum Meses)MesValido;
        printf (" ERROR: Mes invalido");
        printf ("\n Ingrese nuevamente el mes => ");
    }
}

int LeeDiaValido (int Anio, enum Meses Mes)
{
    int DiaValido;
    while(1)
    {
        scanf ("%u", &DiaValido); fflush(stdin);
        if (DiaValido >= 1 && DiaValido <= DiaMaxMes(Anio, Mes)) 
			return DiaValido;
        printf (" ERROR: Dia invalido para el mes %s", NombreMeses[Mes]);
        printf ("\n Ingrese nuevamente el dia => ");
    }
}

enum Genero LeeGeneroValido()
{
    int GeneroValido;
    while(1)
    {
        scanf ("%u", &GeneroValido); fflush(stdin);
        if (GeneroValido >= Masculino && GeneroValido <= NoEspecificado) 
            return (enum Genero)GeneroValido;
        printf (" ERROR: Genero invalido");
        printf ("\n Ingrese nuevamente el genero => ");
    }
}


/*-----------------------------------------DECLARACION FUNCIONES PASAJEROS--------------------------------------*/

Pasajero CrearPasajero()
{
    Pasajero NuevoPasajero = (Pasajero)malloc(sizeof(NodoPas));
    if(NuevoPasajero == NULL)
    {
        printf("\n\t Memoria insuficiente");
        return NULL;
    }
    printf("\n\t Ingrese Clase de Tiquete => ");
    scanf("%d", &NuevoPasajero->tiquete);
    printf("\n\t Ingrese Documento => ");
    gets(NuevoPasajero->documento);
    printf("\n\t Ingrese Nombre => ");
    gets(NuevoPasajero->nombre);
    printf("\n\t Ingrese Apellido => ");
    gets(NuevoPasajero->apellido);
    printf("\n\t Ingrese Telefono => ");
    gets(NuevoPasajero->telefono);
    printf("\n\t Ingrese Fecha de Nacimiento");
    printf("\n\t Ingrese Anio => ");
    NuevoPasajero->fecha_nacimiento.anio = LeeAnioValido();
    printf("\n\t Ingrese Mes => ");
    NuevoPasajero->fecha_nacimiento.mes = LeeMesValido();
    printf("\n\t Ingrese Dia => ");
    NuevoPasajero->fecha_nacimiento.dia = LeeDiaValido(NuevoPasajero->fecha_nacimiento.anio, NuevoPasajero->fecha_nacimiento.mes);
    printf("\n\t Ingrese Genero => ");
    NuevoPasajero->genero = LeeGeneroValido();
    NuevoPasajero->siguiente = NULL;
    return NuevoPasajero;
}

void InsertarPasajero(Pasajero *ListaPasajeros, Pasajero NuevoPasajero)
{
    if(*ListaPasajeros == NULL)
    {
        *ListaPasajeros = NuevoPasajero;
        return;
    }

    Pasajero Temporal = *ListaPasajeros;
    while(Temporal->siguiente != NULL)
        Temporal = Temporal->siguiente;
    Temporal->siguiente = NuevoPasajero;
}

void ListarPasajeros(Pasajero ListaPasajeros)
{
    Pasajero Temporal = ListaPasajeros;
    while(Temporal != NULL)
    {
        printf("\n\t Documento => %s", Temporal->documento);
        printf("\n\t Nombre => %s", Temporal->nombre);
        printf("\n\t Apellido => %s", Temporal->apellido);
        printf("\n\t Telefono => %s", Temporal->telefono);
        printf("\n\t Fecha de Nacimiento => %d/%s/%d", Temporal->fecha_nacimiento.dia, NombreMeses[Temporal->fecha_nacimiento.mes], Temporal->fecha_nacimiento.anio);
        printf("\n\t Genero => %s", NombreGenero[Temporal->genero]);
        Temporal = Temporal->siguiente;
    }
}



/*------------------------------------------Menu-------------------------------------*/

OpcionesMenu Menu()
{
    OpcionesMenu Opcion;
    LIMPIAPANTALLA;
    printf("\n\t -------------GOLONDRINA VELOZ--------");
    printf("\n\t =====================================");
    printf("\n\t MENU PRINCIPAL\n");

    printf("\n\t 1. Comprar Tiquetes");
    printf("\n\t 2. Modificar Pasajero");
    printf("\n\t 3. Listar Pasajeros");
    printf("\n\t 4. Buscar Pasajero");
    printf("\n\t 5. Cambiar Silla");
    printf("\n\t 6. Imprimir pase de abordar");
    printf("\n\t 7. Cancelar Tiquete");
    printf("\n\t 8. Salir");

    printf("\n\t Ingrese Opcion => ");
    scanf("%d", &Opcion);
    fflush(stdin);
    return Opcion;
}

