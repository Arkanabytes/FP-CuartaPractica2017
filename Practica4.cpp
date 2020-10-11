/*************************************
* NOMBRE: #Yassine#
* PRIMER APELLIDO: #Marroun#
* SEGUNDO APELLIDO: #Nettah#
* DNI: #47587376#
* EMAIL: #ymarroun1@alumno.uned.es#
*************************************/

/***************************************************
* Programa: Practica4
*
* Descripcion:
*   Este programa gestiona las reservas de una sala
*   cumpliendo ciertas condiciones y restricciones
*   indicadas en el enunciado de la cuarta practica.
****************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "CalendarioMes.h"
#include "GestionReservaSala.h"

CalendarioMes Calendario;
GestionReservaSala Reserva;

/*-- Valida la longitud del nombre y el apellido --*/
bool validarNombre(Cadena20 nombre, Cadena20 apellido) {
  if ((strlen(nombre) + strlen(apellido)) < LONGNOMBRE - 1) {
    return true;
  } else {
    printf( "Nombre con mas de 20 letras.\n" );
    printf( "\n" );
    return false;
  }
}
/*-- Valida las fechas: que esta dentro de los limites y que es valida en el mes del calendario --*/
bool validarFecha(Fecha fecha) {
  bool valido = false;
  if ((fecha.anno > Reserva.fechaMaxima.anno) ||
      ((fecha.anno == Reserva.fechaMaxima.anno) && (fecha.mes > Reserva.fechaMaxima.mes))
     ) {
    printf( "Fecha introducida mayor que fecha maxima de reservas.\n" );
    printf( "\n" );
    return false;
  } else {
    valido = true;
  }

  if ((fecha.anno < Reserva.fechaActual.anno) ||
      ((fecha.anno == Reserva.fechaActual.anno) && (fecha.mes < Reserva.fechaActual.mes)) ||
      ((fecha.anno == Reserva.fechaActual.anno) && (fecha.mes == Reserva.fechaActual.mes) && (fecha.dia < Reserva.fechaActual.dia))
     ) {
    printf( "Fecha introducida menor que fecha actual.\n" );
    printf( "\n" );
    return false;
  } else {
    valido = true;
  }

  Calendario.Mes = fecha.mes;
  Calendario.Anno = fecha.anno;
  Calendario.CalcularDiasMes();
  if (fecha.dia>Calendario.DiasMes) {
    printf( "Dia introducido mayor que dias totales del mes.\n" );
    printf( "\n" );
    return false;
  }   else {
    valido = true;
  }
  return true;
}

/*-- Valida la hora: que esta en los limites y la duracion no sobrepasa el final --*/
bool validarHoras(int comienzo, int duracion) {
  int final;
  final = comienzo + duracion;
  if (comienzo>=HORAINICIAL && comienzo<=HORAFINAL &&
      duracion>=1 && duracion<=HORASDIA && final <= HORAFINAL+1) {
    return true;
  } else {
    printf( "Horas o duracion incorrectas.\n" );
    printf( "\n" );
    return false;
  }
}


/*-- Mensaje al salir del programa --*/
void Salir () {
  printf ( "Fin del proceso de reservas.\n" );
}

/*-- Leer datos para Nueva Reserva. Devuelve los valores metidos en una variable de tipo UnaReserva --*/
UnaReserva LeerNuevaReserva() {
  UnaReserva datos;
  printf( "Nueva Reserva:\n" );
  printf( "   Persona que reserva (Maximo 20 caracteres)? " );
  scanf( "%s %s", datos.nombre, datos.apellido);
  printf( "   Dia? " );
  scanf( "%d", &datos.f.dia );
  printf( "   Mes? " );
  scanf( "%d", &datos.f.mes );
  printf( "   Anno? " );
  scanf( "%d", &datos.f.anno );
  printf( "   Hora de comienzo (Hora en punto de 8 a 20)? " );
  scanf( "%d", &datos.horacomienzo );
  printf( "   Duracion (Horas completas)? " );
  scanf( "%d", &datos.duracion );
  return datos;
}

/*-- Leer datos para Anular Reserva. Devuelve los valores metidos en una variable de tipo UnaReserva --*/
UnaReserva LeerAnularReserva() {
  UnaReserva datos;
  printf( "Anular Reserva:\n" );
  printf( "   Persona que reservo? " );
  scanf( "%s %s", datos.nombre, datos.apellido);
  printf( "   Dia? " );
  scanf( "%d", &datos.f.dia );
  printf( "   Mes? " );
  scanf( "%d", &datos.f.mes );
  printf( "   Anno? " );
  scanf( "%d", &datos.f.anno );
  printf( "   Hora de comienzo (Hora en punto de 8 a 20? " );
  scanf( "%d", &datos.horacomienzo );
  return datos;
}

/*-- Leer datos para Reservas del Mes. Devuelve los datos en una estructura de tipo Fecha --*/
Fecha LeerMes() {
  Fecha fecha;
  fecha = Reserva.fechaActual;
  //
  printf ( "Reservas del Mes:\n" );
  printf( "   Mes? " );
  scanf( "%d", &fecha.mes );
  printf( "   Anno? " );
  scanf( "%d", &fecha.anno );
  return fecha;
}

/*-- Devuelve en la estructura Fecha la fecha metida en la pantalla --*/
Fecha LeerDia() {
  Fecha fecha;
  fecha = Reserva.fechaActual;
  //
  printf ( "Reservas del Dia:\n" );
  printf( "   Dia? " );
  scanf( "%d", &fecha.dia );
  printf( "   Mes? " );
  scanf( "%d", &fecha.mes );
  printf( "   Anno? " );
  scanf( "%d", &fecha.anno );
  return fecha;
}

/*-- Imprimir la matriz de reservas (por si fuera necesario para comprobar) --*/
void ImprimirReserva (int mes) {
  int ini, fin;
  if (mes<0) {
    ini = 0;
    fin = NUMMESES+1;
  } else {
    ini = mes;
    fin = mes+1;
  }

  for ( int i = ini; i < fin; i++) {
    printf( "mes: %d \n", i );
    for ( int j = 0; j <= NUMDIAS; j++) {
      printf( "d%d:", j );
      for ( int k = 0; k <= NUMHORAS; k++) {
        printf( " %s ", Reserva.reservado[i][j][k].nombre );
      }
      printf( "\n" );
    }
    printf( "******************\n" );
  }
}


/*-- Lee los datos para hacer la reserva (LeerNuevaReseva)
y llama a la funcion que hace las comprobaciones y la reserva (funcion HacerReserva).
Tambien valida que los datos introducidos son correctos (funciones validarNombre, validarFecha y validarHoras) --*/
void NuevaReserva() {
  UnaReserva datosReserva;
  datosReserva = LeerNuevaReserva();
  if ( validarNombre(datosReserva.nombre, datosReserva.apellido) &&
       validarFecha(datosReserva.f) &&
       validarHoras (datosReserva.horacomienzo, datosReserva.duracion) ) {
               Reserva.HacerReserva( datosReserva, Calendario );
  } else {
    printf( "Introducir datos correctamente.\n" );
    printf( "Nombre, fecha u hora incorrecta.\n" );
    printf( "Solo reservas para tres meses.\n" );
    printf( "\n" );
  }
}

/*-- Lee los datos para anular la reserva (LeerAnularReseva)
y llama a la funcion que hace las comprobaciones y anula la reserva (funcion AnularReserva).
Tambien valida que los datos introducidos son correctos (funciones validarNombre, validarFecha y validarHoras) --*/
void AnularReserva() {
  UnaReserva anulaReserva;
  anulaReserva = LeerAnularReserva();
  if (  validarNombre(anulaReserva.nombre, anulaReserva.apellido) &&
        validarFecha(anulaReserva.f) &&
        validarHoras (anulaReserva.horacomienzo, 1) ) {
             Reserva.AnularUnaReserva(anulaReserva, Calendario);
  } else {
    printf( "No existe reserva con los datos introducidos.\n" );
    printf( "\n" );
  }
}

/*-- Lee los datos para imprimir las reservas de un mes (LeerMes)
y llama a la funcion que imprime el mes: ImprimirCalendario.
Tambien valida que los datos introducidos son correctos (validarFecha) --*/
void ReservasMes () {
  Fecha fecha;
  fecha = LeerMes();
  if ( validarFecha(fecha) ) {
     Calendario.calcularCalendarioMes(fecha);
     Reserva.ImprimirCalendarioReservas(Calendario);
  } else {
     printf( "Fecha introducida incorrecta.\n" );
     printf( "\n" );
  }
}

/*-- Imprime las reservas que hay un dia --*/
void ReservasDia(){
  Fecha fechaRsv;
  fechaRsv = LeerDia();
  Reserva.ReservasDia (fechaRsv);
}

/*-- Textos de la peticion de opcion y lectura de la opcion introducida --*/
char pedirOpcion(){
      char opcion = ' ';
      printf( "Nueva Reserva       (Pulsar N)\n" );
      printf( "Anular Reserva      (Pulsar A)\n" );
      printf( "Reservas de un Dia  (Pulsar D)\n" );
      printf( "Reservas de un Mes  (Pulsar M)\n" );
      printf( "Salir               (Pulsar S)\n" );
      printf( "\n" );
      printf( "Teclear una opcion valida (N|A|D|M|S).\n" );
      scanf( " %c", &opcion );
      return opcion;
}

/*-- Leer Opcion y llamar a la funcion correspondiente --*/
void GestionReservas () {
  char opcion = ' ';
  printf( "\n" );
  printf( "Gestion de Reservas Sala.\n" );
  printf( "\n" );
  opcion = pedirOpcion();
    while ( opcion != 'S' ) {
      //
      switch (opcion){
          case 'N':
             NuevaReserva ();
             break;
          case 'A':
             AnularReserva ();
             break;
          case 'D':
             ReservasDia ();
             break;
          case 'M':
             ReservasMes ();
             break;
          case 'S':
             Salir();
             break;
          default:
             printf ("Opcion invalida\n");
      }
       opcion = pedirOpcion();
    }

}

/*-- Obtiene la fecha actual para poder establecer los limites de la peticion (no superior a tres meses despues) --*/
Fecha obtenerFechaActual() {
  Fecha fecact;
  typedef  tm *tiempo;
  time_t t = time(0);
  tiempo ahora=localtime(&t);

  fecact.dia = ahora->tm_mday;
  fecact.mes = (ahora->tm_mon) + 1;
  fecact.anno = (ahora->tm_year) + 1900;
  printf( "Fecha actual: %2d %2d %2d \n", fecact.dia, fecact.mes, fecact.anno );
  return fecact;
}

/*-- Funcion main inicio del programa. Declara la matriz de reservas y la inicia,
y llama a la funcion que va a tener el bucle con el menu de opciones posibles: GestionReservas --*/
int main() {
  Reserva.IniciarReserva ();
  Reserva.fechaActual = obtenerFechaActual();
  Reserva.ObtenerFechaMaxima();
  GestionReservas();
  printf( "Fin del programa.\n" );
  return(0);
}
