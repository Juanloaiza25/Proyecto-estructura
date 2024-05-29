#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <conio.h>

/*-----------------------------------------MACROS---------------------------------------------------------------------------*/
#define ANIOACTUAL				2024
#define BISIESTO				(((Anio%4 == 0) && (Anio%100 !=0)) || (Anio%400 == 0))
#define LIMPIAPANTALLA 			system("cls")
#define PAUSA 					system("pause")

/*-----------------------------------------ENUMERACIONES--------------------------------------------------------------------*/

enum TipoVuelo{Nacional=1, Internacional};
enum ClaseTiquete{Economica=1, PrimeraClase};
enum Genero{Masculino=1, Femenino, Otro};
enum Meses{Enero=1, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Septiembre, Octubre, Noviembre, Diciembre};
enum OpcionesMenu{ComprarTiquetes=1, Modificar, Listar, Buscar, CambiarSilla, Imprimir, Cancelar, Salir};

/*-----------------------------------------DECLARAR NOMBRE DE LOS NUMERADORES---------------------------------------------*/

const char *NombreTipoVuelo[] = {"Nacional", "Internacional"};
const char *NombreClaseTiquete[] = {"Economica", "Primera Clase"};
const char *NombreGenero[] = {"Masculino", "Femenino", "Otro", "No Especificado"};
const char *NombreMeses[] = {"No permitido", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

/*-----------------------------------------ESTRUCTURAS--------------------------------------------------------------------*/

/*Estructura de la fecha*/

struct Fecha{
    int dia;
    Meses mes;
    int anio;
};

/*Estructura pasajeros*/

typedef struct nodo_pasajero{
    ClaseTiquete tiquete;
    char documento[10];
    char nombre[20];
    char apellido[20];
    int telefono;
    Fecha fecha_nacimiento;
    Genero genero;
    int Silla;

    struct nodo_pasajero *siguiente;
} NodoPas;
typedef NodoPas *Pasajero;


/*Estructura de los vuelos*/

typedef struct nodo_vuelo{
    int tipo_vuelo;
    char *codigo_vuelo;
    Fecha fecha_vuelo;
    int hora_salida;
    Fecha fecha_llegada;
    int hora_llegada;
    struct nodo_vuelo *siguiente;
} NodoVuelo;
typedef NodoVuelo *Vuelo; 

 struct GolondrinaVeloz{
    Pasajero Pasajeros;
    Vuelo Vuelos;
    struct GolondrinaVeloz *siguiente;
    
};

/*-----------------------------------------DECLARACION FUNCIONES VALIDACION--------------------------------------*/

int TipoVueloValido()
{
    int TipoVuelo;
    while(1)
    {
        scanf("%u", &TipoVuelo); fflush(stdin);
        if(TipoVuelo >= Nacional && TipoVuelo <= Internacional)
            return TipoVuelo;
        printf("\7");
        printf("\n\t ERROR: Tipo de vuelo invalido");
        printf("\n\t Ingrese nuevamente el tipo de vuelo => ");
    }

}

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

int LeeAnioNacimientoValido()
{
    int AnioValido;
    while(1)
    {
        scanf ("%u", &AnioValido); fflush(stdin);
        if (AnioValido >= 1900 && AnioValido <= ANIOACTUAL) 
            return AnioValido;
        printf ("\7");
        printf (" ERROR: Anio invalido");
        printf ("\n Ingrese nuevamente el anio => ");
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
        printf ("\7");
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



Fecha LeeFechaValida()
{
    Fecha NuevaFecha;
    printf("\n\t Ingrese Anio => ");
    NuevaFecha.anio = LeeAnioValido();
    printf("\n\t Ingrese Mes => ");
    NuevaFecha.mes = LeeMesValido();
    printf("\n\t Ingrese Dia => ");
    NuevaFecha.dia = LeeDiaValido(NuevaFecha.anio, NuevaFecha.mes);
    return NuevaFecha;
}

int LeeHoraValida()
{
    int HoraValida;
    while(1)
    {
        scanf ("%u", &HoraValida); fflush(stdin);
        if (HoraValida >= 0 && HoraValida <= 23) 
            return HoraValida;
        printf (" ERROR: Hora invalida");
        printf ("\n Ingrese nuevamente la hora => ");
    }
}

enum Genero LeeGeneroValido()
{
    int GeneroValido;
    while(1)
    {   printf("\n\t 1. Masculino");
        printf("\n\t 2. Femenino");
        printf("\n\t 3. Otro");
        scanf ("%u", &GeneroValido); fflush(stdin);
        if (GeneroValido >= Masculino && GeneroValido <= Otro) 
            return (enum Genero)GeneroValido;
        printf (" ERROR: Genero invalido");
        printf ("\n Ingrese nuevamente el genero => ");
    }
}

enum ClaseTiquete LeeClaseTiqueteValido()
{
    int ClaseTiqueteValido;
    while(1)
    {
        scanf ("%u", &ClaseTiqueteValido); fflush(stdin);
        if (ClaseTiqueteValido >= Economica && ClaseTiqueteValido <= PrimeraClase) 
            return (enum ClaseTiquete)ClaseTiqueteValido;
        printf (" ERROR: Clase de tiquete invalida");
        printf ("\n Ingrese nuevamente la clase de tiquete => ");
    }
}

bool sillaYaAsignada(Pasajero ListaPasajeros, int Silla)
{
    Pasajero Temporal = ListaPasajeros;
    while(Temporal != NULL)
    {
        if(Temporal->Silla == Silla)
        printf("\n\t Silla ya asignada");
            return 1;
        Temporal = Temporal->siguiente;
    }
    return 0;
}

int SillaAleatoria(enum ClaseTiquete Clase)
{
    if (Clase == Economica)
        return rand() % 250 + 21;
    else
        return rand() % 20 + 1;   
        
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

/*-----------------------------------------DECLARACION FUNCIONES PASAJEROS--------------------------------------*/

GolondrinaVeloz* CrearPasajero(GolondrinaVeloz *G)
{
    char Continuar = 'S';
    GolondrinaVeloz *PAux=NULL;

    while (toupper(Continuar)=='S'){
        LIMPIAPANTALLA;
    printf("\n\t --------------------------------------------------------------------------------");
       GolondrinaVeloz *PAux = (GolondrinaVeloz*)malloc(sizeof(GolondrinaVeloz));
        if (PAux == NULL) {
            printf("\n\t Memoria insuficiente");
            return G;
        }
        
        PAux->Pasajeros = (Pasajero)malloc(sizeof(NodoPas));
        PAux->Vuelos = (Vuelo)malloc(sizeof(NodoVuelo));
        if (PAux->Pasajeros == NULL || PAux->Vuelos == NULL) {
            printf("\n\t Memoria insuficiente");
            free(PAux);
            return G;
        }
    PAux -> siguiente = G;
    printf("\n\t 1. Nacional (Bogota-Pereira)");
    printf("\n\t 2. Internacional (Bogota-Madrid)");
    printf("\n\t Ingrese Tipo de vuelo =>");
    PAux->Vuelos->tipo_vuelo = TipoVueloValido();
    printf("\n\t Codigo de vuelo: ");
    if (PAux->Vuelos->tipo_vuelo == Nacional)
    {
        printf("\n\t GOPLA01");
        PAux->Vuelos->codigo_vuelo = "GOPLA01";
    }
    else
    {
        printf("\n\t GOPLA02");
        PAux->Vuelos->codigo_vuelo = "GOPLA02";
    }
    printf("\n\t Ingrese Documento => ");
    scanf("%s", &PAux->Pasajeros->documento);
    printf("\n\t Ingrese Nombre => ");
    scanf("%s", &PAux->Pasajeros->nombre);
    printf("\n\t Ingrese Apellido => ");
    scanf("%s", &PAux->Pasajeros->apellido);
    printf("\n\t Ingrese Telefono => ");
    scanf("%d", &PAux->Pasajeros->telefono);
    printf("\n\t Ingrese Fecha de Nacimiento");
    printf("\n\t Ingrese Anio => ");
    PAux->Pasajeros->fecha_nacimiento.anio = LeeAnioNacimientoValido();
    printf("\n\t Ingrese Mes => ");
    PAux->Pasajeros->fecha_nacimiento.mes = LeeMesValido();
    printf("\n\t Ingrese Dia => ");
    PAux->Pasajeros->fecha_nacimiento.dia = LeeDiaValido(PAux->Pasajeros->fecha_nacimiento.anio, PAux->Pasajeros->fecha_nacimiento.mes);
    printf("\n\t Ingrese Genero => ");
    PAux->Pasajeros->genero = LeeGeneroValido();
    printf("\n\t Ingrese Clase de Tiquete => ");
    PAux->Pasajeros->tiquete = LeeClaseTiqueteValido();
    printf("\n\t Ingrese la fecha de vuelo");
    PAux->Vuelos->fecha_vuelo = LeeFechaValida();
    printf("\n\t Ingrese la hora de salida  => ");
    PAux->Vuelos->hora_salida = LeeHoraValida();
    printf("\n\t Fecha de llegada:");
    if (PAux->Vuelos->tipo_vuelo == Nacional)
    {
        printf("\n\t Tiempo de vuelo de 50 minutos");
        PAux->Vuelos->fecha_llegada.dia = PAux->Vuelos->fecha_vuelo.dia;
    }
    else
    {
        printf("\n\t Tiempo de vuelo de 11 horas ");
        if (PAux->Vuelos->fecha_vuelo.dia == 31 && PAux->Vuelos->fecha_vuelo.mes == Diciembre)
        {
            PAux->Vuelos->fecha_llegada.dia = 1;
            PAux->Vuelos->fecha_llegada.mes = Enero;
            PAux->Vuelos->fecha_llegada.anio = PAux->Vuelos->fecha_vuelo.anio + 1;
        }
        else if (PAux->Vuelos->fecha_vuelo.dia == 31)
        {
            PAux->Vuelos->fecha_llegada.dia = 1;
            PAux->Vuelos->fecha_llegada.mes = (Meses)(PAux->Vuelos->fecha_vuelo.mes + 1);
            PAux->Vuelos->fecha_llegada.anio = PAux->Vuelos->fecha_vuelo.anio;
        }
        else if ( PAux->Vuelos->hora_salida >= 0 && PAux->Vuelos->hora_salida <= 12)
        {
           
            PAux->Vuelos->fecha_llegada.dia = PAux->Vuelos->fecha_vuelo.dia;
            PAux->Vuelos->fecha_llegada.mes = PAux->Vuelos->fecha_vuelo.mes;
            PAux->Vuelos->fecha_llegada.anio = PAux->Vuelos->fecha_vuelo.anio;
            
        }
        else
        {
            PAux->Vuelos->fecha_llegada.dia = PAux->Vuelos->fecha_vuelo.dia + 1;
            PAux->Vuelos->fecha_llegada.mes = PAux->Vuelos->fecha_vuelo.mes;
            PAux->Vuelos->fecha_llegada.anio = PAux->Vuelos->fecha_vuelo.anio;
        }
    }
    printf("\n\t Su hora de llegada es => ");
    if (PAux->Vuelos->tipo_vuelo == Nacional)
    {
        printf("\n\t %d:%d", PAux->Vuelos->hora_salida + 1, 00);
        PAux->Vuelos->hora_llegada = PAux->Vuelos->hora_salida + 1;
    }
    else
    {
        printf("\n\t %d:%d", PAux->Vuelos->hora_salida + 7, 00);
        PAux->Vuelos->hora_llegada = PAux->Vuelos->hora_salida + 7;
    }
    if (PAux->Pasajeros->tiquete == Economica)
        {
            printf("\n\t Su silla es =>");
            PAux->Pasajeros->Silla = SillaAleatoria(Economica);
        }
        else
        {
            printf("\n\t Su silla es =>");
            PAux->Pasajeros->Silla = SillaAleatoria(PrimeraClase);
        }




    printf("\n\t Desea continuar ingresando pasajeros? (S/N) => ");
    scanf("%c", &Continuar);
    fflush(stdin);
    G = PAux;
    }

    return G;

}

void modificarPasajero(Pasajero *ListaPasajeros)
{
    char Documento[20];
    printf("\n\t Ingrese Documento del Pasajero a Modificar => ");
    gets(Documento);
    Pasajero Temporal = *ListaPasajeros;
    while(Temporal != NULL)
    {
        if(strcmp(Temporal->documento, Documento) == 0)
        {
            printf("\n\t Ingrese nuevo Documento => ");
            gets(Temporal->documento);
            printf("\n\t Ingrese nuevo Nombre => ");
            gets(Temporal->nombre);
            printf("\n\t Ingrese nuevo Apellido => ");
            gets(Temporal->apellido);
            printf("\n\t Ingrese nuevo Telefono => ");
            scanf("%d", &Temporal->telefono);
            printf("\n\t Ingrese nueva Fecha de Nacimiento");
            printf("\n\t Ingrese nuevo Anio => ");
            Temporal->fecha_nacimiento.anio = LeeAnioNacimientoValido();
            printf("\n\t Ingrese nuevo Mes => ");
            Temporal->fecha_nacimiento.mes = LeeMesValido();
            printf("\n\t Ingrese nuevo Dia => ");
            Temporal->fecha_nacimiento.dia = LeeDiaValido(Temporal->fecha_nacimiento.anio, Temporal->fecha_nacimiento.mes);
            printf("\n\t Ingrese nuevo Genero => ");
            Temporal->genero = LeeGeneroValido();
            printf("\n\t Ingrese nueva Clase de Tiquete => ");
            Temporal->tiquete = LeeClaseTiqueteValido();
            printf("\n\t Pasajero modificado. Presione una tecla para continuar");
            PAUSA;
        }
        Temporal = Temporal->siguiente;
    }
    printf("\n\t Pasajero no encontrado");
    PAUSA;
    return;
}



void ListarPasajeros(GolondrinaVeloz *ListaPasajeros)
{
    LIMPIAPANTALLA;
    if (ListaPasajeros == NULL) {
        printf("\n\t No hay pasajeros en la lista.");
        return;
    }

    Pasajero Temporal;
    while (ListaPasajeros != NULL)
    {   
        Temporal = ListaPasajeros->Pasajeros;
        while (Temporal != NULL)
        {
            printf("\n\t -----------------");
            printf("\n\t Documento => %s", Temporal->documento);
            printf("\n\t Nombre => %s", Temporal->nombre);
            printf("\n\t Apellido => %s", Temporal->apellido);
            printf("\n\t Telefono => %d", Temporal->telefono);
            printf("\n\t Fecha de Nacimiento => %d/%s/%d", Temporal->fecha_nacimiento.dia, NombreMeses[Temporal->fecha_nacimiento.mes], Temporal->fecha_nacimiento.anio);
            printf("\n\t Genero => %s", NombreGenero[Temporal->genero]);
            Temporal = Temporal->siguiente;
        }
        ListaPasajeros = ListaPasajeros->siguiente;
    }
    PAUSA;
}
int buscarPasajero(GolondrinaVeloz ListaPasajeros)
{
    char Documento[20];
    printf("\n\t Ingrese Documento del Pasajero a Buscar => ");
    gets(Documento);
    Pasajero Temporal = ListaPasajeros.Pasajeros;
    while(Temporal != NULL)
    {
        if(strcmp(Temporal->documento, Documento) == 0)
        {   
            printf("\n\t -----------------");
            printf("\n\t Tipo de Vuelo => %s", ListaPasajeros.Vuelos->codigo_vuelo);
            printf("\n\t Documento => %s", Temporal->documento);
            printf("\n\t Nombre => %s", Temporal->nombre);
            printf("\n\t Apellido => %s", Temporal->apellido);
            printf("\n\t Telefono => %d", Temporal->telefono);
            printf("\n\t Fecha de Nacimiento => %d/%s/%d", Temporal->fecha_nacimiento.dia, NombreMeses[Temporal->fecha_nacimiento.mes], Temporal->fecha_nacimiento.anio);
            printf("\n\t Genero => %s", NombreGenero[Temporal->genero]);
            printf("\n\t Clase de Tiquete => %s", NombreClaseTiquete[Temporal->tiquete]);
            printf("\n\t Fecha de salida => %d/%s/%d", ListaPasajeros.Vuelos->fecha_vuelo.dia, NombreMeses[ListaPasajeros.Vuelos->fecha_vuelo.mes], ListaPasajeros.Vuelos->fecha_vuelo.anio);
            printf("\n\t Hora de salida => %d", ListaPasajeros.Vuelos->hora_salida);
            printf("\n\t Fecha de llegada => %d/%s/%d", ListaPasajeros.Vuelos->fecha_llegada.dia, NombreMeses[ListaPasajeros.Vuelos->fecha_llegada.mes], ListaPasajeros.Vuelos->fecha_llegada.anio);
            printf("\n\t Hora de llegada => %d", ListaPasajeros.Vuelos->hora_llegada);
            printf("\n\t Silla => %d", Temporal->Silla);
            return 1;
        }
        Temporal = Temporal->siguiente;
    }
    printf("\n\t Pasajero no encontrado");
    return 0;
}

void cambiarSilla(Pasajero *ListaPasajeros)
{
    char Documento[20];
    printf("\n\t Ingrese Documento del Pasajero a Cambiar Silla => ");
    gets(Documento);
    Pasajero Temporal = *ListaPasajeros;
    while(Temporal != NULL)
    {
        if(strcmp(Temporal->documento, Documento) == 0)
        {
            printf("\n\t Ingrese nueva silla => ");
            Temporal->Silla = SillaAleatoria(Temporal->tiquete);
            while (sillaYaAsignada(*ListaPasajeros, Temporal->Silla))
                Temporal->Silla = SillaAleatoria(Temporal->tiquete);
            printf("\n\t %d", Temporal->Silla);
            printf("\n\t Silla cambiada");
            return;
        }
        Temporal = Temporal->siguiente;
    }
    printf("\n\t Pasajero no encontrado");
}

void imprimirPaseAbordar(GolondrinaVeloz ListaPasajeros)
{
    char Documento[20];
    printf("\n\t Ingrese Documento del Pasajero a Imprimir Pase de Abordar => ");
    gets(Documento);
    Pasajero Temporal = ListaPasajeros.Pasajeros;
    while(Temporal != NULL)
    {
        if(strcmp(Temporal->documento, Documento) == 0)
        {
            printf("\n\t -----------------");
            printf("\n\t Tipo de Vuelo => %s", NombreTipoVuelo[ListaPasajeros.Vuelos->tipo_vuelo]);
            printf("\n\t Codigo de Vuelo => %s", ListaPasajeros.Vuelos->codigo_vuelo);
            printf("\n\t Documento => %s", Temporal->documento);
            printf("\n\t Nombre => %s", Temporal->nombre);
            printf("\n\t Apellido => %s", Temporal->apellido);
            printf("\n\t Telefono => %d", Temporal->telefono);
            printf("\n\t Fecha de Nacimiento => %d/%s/%d", Temporal->fecha_nacimiento.dia, NombreMeses[Temporal->fecha_nacimiento.mes], Temporal->fecha_nacimiento.anio);
            printf("\n\t Genero => %s", NombreGenero[Temporal->genero]);
            printf("\n\t Clase de Tiquete => %s", NombreClaseTiquete[Temporal->tiquete]);
            printf("\n\t Fecha de salida => %d/%s/%d", ListaPasajeros.Vuelos->fecha_vuelo.dia, NombreMeses[ListaPasajeros.Vuelos->fecha_vuelo.mes], ListaPasajeros.Vuelos->fecha_vuelo.anio);
            printf("\n\t Hora de salida => %d", ListaPasajeros.Vuelos->hora_salida);
            printf("\n\t Fecha de llegada => %d/%s/%d", ListaPasajeros.Vuelos->fecha_llegada.dia, NombreMeses[ListaPasajeros.Vuelos->fecha_llegada.mes], ListaPasajeros.Vuelos->fecha_llegada.anio);
            printf("\n\t Hora de llegada => %d", ListaPasajeros.Vuelos->hora_llegada);
            printf("\n\t Silla => %d", Temporal->Silla);

            return; 

        }
        Temporal = Temporal->siguiente;
    }
    printf("\n\t Pasajero no encontrado");
}

void cancelarTiquete(Pasajero *ListaPasajeros)
{
    char Documento[20];
    printf("\n\t Ingrese Documento del Pasajero a Cancelar Tiquete => ");
    gets(Documento);
    Pasajero Temporal = *ListaPasajeros;
    Pasajero Anterior = NULL;
    while(Temporal != NULL)
    LIMPIAPANTALLA;
    {
        if(strcmp(Temporal->documento, Documento) == 0)
        {
            if(Anterior == NULL)
                *ListaPasajeros = Temporal->siguiente;
            else
                Anterior->siguiente = Temporal->siguiente;
            free(Temporal);
            printf("\n\t Tiquete cancelado");
            return;
        }
        Anterior = Temporal;
        Temporal = Temporal->siguiente; 
    }
    printf("\n\t Pasajero no encontrado");
    LIMPIAPANTALLA;
}

int main(){
    GolondrinaVeloz *Golondrina;
    Golondrina = NULL;
    bool exit = false;
    
    while (!exit)
    {
        
        switch (Menu())
        {
            case ComprarTiquetes:
                LIMPIAPANTALLA;
                Golondrina = CrearPasajero(Golondrina);
                break;
            case Modificar:
                LIMPIAPANTALLA;
                modificarPasajero(&Golondrina->Pasajeros);
                break;
            case Listar:
                LIMPIAPANTALLA;
                ListarPasajeros(Golondrina);
                break;
            case Buscar:
                LIMPIAPANTALLA;
                buscarPasajero(*Golondrina);
                break;
            case CambiarSilla:
                LIMPIAPANTALLA;
                cambiarSilla(&Golondrina->Pasajeros);
                break;
            case Imprimir:
                LIMPIAPANTALLA;
                imprimirPaseAbordar(*Golondrina);
                break;
            case Cancelar:
                LIMPIAPANTALLA;
                cancelarTiquete(&Golondrina->Pasajeros);
                break;
            case Salir:
                LIMPIAPANTALLA;
                printf("\n\t Adios");
                PAUSA;
                exit = true;
                break;
            
            default:
                printf("\n\t Opcion invalida");
        }
    }
}

