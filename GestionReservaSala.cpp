/********************************************************
* Modulo: GestionReservaSala
*
*   Desarrolla las distintas condiciones y restricciones
*   a seguir según la opción de programa elegida.
*********************************************************/
#include <stdio.h>
#include <string.h>
#include "GestionReservaSala.h"

/*-- Devuelve verdadero cuando los dos nombres y los dos apellidos pasados en los parametros son iguales.
El orden de los parametros en la llamada debe ser: nombre1, apellido1, nombre2, apellido2 --*/
bool compararNombre(Cadena20 n1, Cadena20 a1, Cadena20 n2, Cadena20 a2) {
  if (strcmp(n1, n2)==0 && strcmp(a1,a2)==0) {
    return true;
  } else {
    return false;
  }
}

/*-- Devuelve un entero con el tipo de reserva (0=no hay reserva, 99=reserva parcial, 100=reserva total).
Necesita recibir un parametro que contenga la hora, el mes y la duracion a comprobar --*/
int GestionReservaSala::comprobarReserva (UnaReserva rsv) {
  int esReservado = 0;
  bool nada = true;
  bool todo = true;
  for (int i=rsv.horacomienzo; i<rsv.horacomienzo+rsv.duracion; i++) {
    if (reservado[rsv.f.mes][rsv.f.dia][i].hayreserva) {
      nada = false;
    } else {
      todo = false;
    }
  }
  if (nada) {
    esReservado = 0;
  } else if (todo) {
    esReservado = TOTAL;
  } else {
    esReservado = PARCIAL;
  }
  return esReservado;
}

/*-- Imprimir calendario de un mes con el tipo de reserva de cada dia --*/
void GestionReservaSala::ImprimirCalendarioReservas(CalendarioMes calendario) {
  int numSemanas;
  int contdias;
  int contpos;
  int numPosInicial;
  int numPosFinal;
  const int NumPosiciones = 43;
  const int nummeses = 12;
  const int numletras = 24;
  typedef char TipoCadena[numletras];
  typedef TipoCadena TipoNombreMes[nummeses];
  TipoNombreMes NombreMes;

  typedef int TipoDias[NumPosiciones];
  TipoDias posicion;
  int esreserva;
  UnaReserva reservado;

  strcpy( NombreMes[0], "ENERO                  ");
  strcpy( NombreMes[1], "FEBRERO                ");
  strcpy( NombreMes[2], "MARZO                  ");
  strcpy( NombreMes[3], "ABRIL                  ");
  strcpy( NombreMes[4], "MAYO                   ");
  strcpy( NombreMes[5], "JUNIO                  ");
  strcpy( NombreMes[6], "JULIO                  ");
  strcpy( NombreMes[7], "AGOSTO                 ");
  strcpy( NombreMes[8], "SEPTIEMPRE             ");
  strcpy( NombreMes[9], "OCTUBRE                ");
  strcpy( NombreMes[10], "NOVIEMBRE              ");
  strcpy( NombreMes[11], "DICIEMBRE              ");


  for ( int i = 0; i <= 42; i++) {
    posicion[i]=0;
  }

  /*-- Calcula el numero de semanas que se necesitan imprimir del calendario --*/
  numPosInicial = calendario.DiaSemanaInicioMes ;
  numPosFinal = numPosInicial + calendario.DiasMes;
  numSemanas = 4;
  if (numPosFinal > 28) {
    numSemanas = 5;
  }
  if (numPosFinal > 35) {
    numSemanas = 6;
  }

  /*-- Mete en la matriz posicion para cada dia:
  1. Un cero cuando esa posicion del calendario no se corresponde con ningun dia
  2. El numero de dia en la posicion del calendario si no hay reserva
  3. El tipo de reserva (99 o 100) dependiendo de si la reserva es total o parcial
  (que lo calcula la funcion comprobarReserva) --*/
  contdias = 1;
  esreserva = 0;
  reservado.f.mes = calendario.Mes;
  reservado.f.anno = calendario.Anno;
  reservado.horacomienzo = HORAINICIAL;
  reservado.duracion = HORASDIA;
  for ( int i = numPosInicial; i<numPosFinal; i++) {
    reservado.f.dia = contdias;
    esreserva = comprobarReserva(reservado);
    if (esreserva!=0) {
      posicion[i] = esreserva;
    } else {
      posicion[i] = contdias;
    }
    contdias = contdias + 1;
  }

  /*-- Cabecera del calendario del mes --*/
  printf( "\n" );
  printf( "%s", NombreMes[calendario.Mes-1] );
  printf( "%d", calendario.Anno );
  printf( "\n" );
  printf( "===========================\n" );
  printf( "LU  MA  MI  JU  VI | SA  DO\n" );
  printf( "===========================\n" );

  /*-- Imprime los valores de cada dia (que se guardaron en el vector posicion)
  colocados por semanas en forma de calendario --*/
  contpos = 0;
  for ( int i = 0; i<numSemanas; i++) {
    for ( int j = 0; j<=6; j++) {
      switch (posicion[contpos]) {
      case 0:
        printf( " . " );
        break;
      case PARCIAL:
        printf( "PA " );
        break;
      case TOTAL:
        printf( "TO " );
        break;
      default:
        printf( "%2d ", posicion[contpos] );
      }
      contpos = contpos + 1;
      if (j == 4) {
        printf( "| " );
      } else {
        printf( " " );
      }
    }
    printf( "\n" );
  }
  //
  printf( "\n" );
}

/*-- Hacer reserva con los datos metidos de una reserva
Rellena la hora correspondiente del mes y del anno de la matriz de reservas:
mete el nombre y pone a verdadero el campo hayReserva.
Comprueba que no exista ya una reserva previa (funcion comprobarReserva)
Comprueba que no sea sabado y domingo (funcion CalcularDiaSemana) --*/
void GestionReservaSala::HacerReserva(UnaReserva rsv, CalendarioMes calendario) {
  int diaSabDom = 0;
  int hayReserva = 0;

  /*-- Comprueba que el dia introducido no es sabado ni domingo --*/
  calendario.Mes = rsv.f.mes;
  calendario.Anno = rsv.f.anno;
  calendario.CalcularDiaSemanaInicioMes();
  diaSabDom = (calendario.DiaSemanaInicioMes + rsv.f.dia)%7;
  if (diaSabDom==0 || diaSabDom==6) {
    printf( "No se puede reservar en Sabado ni Domingo.\n" );
    printf( "\n" );
    return;
  }

  if (numReservas[rsv.f.mes] >= NUMMAXRSVMES) {
    printf( "No se pueden realizar mas de %d reservas.\n", NUMMAXRSVMES );
    printf( "\n" );
    return;
  }

  /*-- Comprueba que no haya reserva previa --*/
  hayReserva = comprobarReserva(rsv);
  /* Si no hay reserva previa entonces guarda el nombre
  y pone a verdadero el campo hayReserva en la matriz de reservas */
  if (hayReserva==0) {
    for (int i=rsv.horacomienzo; i<rsv.horacomienzo+rsv.duracion; i++) {
      strcpy(reservado[rsv.f.mes][rsv.f.dia][i].nombre, rsv.nombre);
      strcpy(reservado[rsv.f.mes][rsv.f.dia][i].apellido, rsv.apellido);
      reservado[rsv.f.mes][rsv.f.dia][i].hayreserva=true;
    }
    numReservas[rsv.f.mes]++;
	/* Una vez guardada la reserva imprime el calendario para comprobar que se hizo correctamente */
	  calendario.calcularCalendarioMes(rsv.f);
    ImprimirCalendarioReservas(calendario);
    printf( "\n" );
  /* Si hay reserva avisa al usuario con el error */
  } else {
    printf( "Ya hay reserva para ese dia y hora.\n" );
    printf( "Cambie los datos o la duracion.\n" );
    printf( "\n" );
  }
}

/*-- Anula la reserva. Comprueba que existe esa reserva para esa persona y la anula --*/
void GestionReservaSala::AnularUnaReserva( UnaReserva rsv, CalendarioMes calendario) {
  int hayReserva = 0;
  char confirmar = ' ';

  rsv.duracion = 1;
  /* Comprueba si hay reserva (devuelve 0 cuando no hay reserva y 99 o 100 cuando hay reserva total o parcial */
  hayReserva = comprobarReserva(rsv);
  /* Si es distinto de cero hay reserva. Se pide confirmacion */
  if (hayReserva!=0) {
    printf ("Confirma anular esta reserva?(S/N):");
    scanf(" %c", &confirmar);
    if (confirmar=='S') {
      /* Se pone a falso el campo hayReserva de la matriz para esa hora
      y las siguientes que tenga reservado con el mismo nombre */
      for (int i=rsv.horacomienzo;i<=HORAFINAL;i++) {
      /* Anula la reserva (la pone a falso) cuando el nombre coincide con el introducido para anular */
        if (compararNombre(rsv.nombre, rsv.apellido, reservado[rsv.f.mes][rsv.f.dia][i].nombre, reservado[rsv.f.mes][rsv.f.dia][i].apellido )) {
          reservado[rsv.f.mes][rsv.f.dia][i].hayreserva=false;
        } else {
          i=HORAFINAL+1; /* se sale del bucle poniendo la variable del bucle con un valor mayor que el final */
        }
      }
      numReservas[rsv.f.mes]--;
      /* Imprime el calendario con las reservas para comprobar que se ha anulado correctamente */
      calendario.calcularCalendarioMes(rsv.f);
      ImprimirCalendarioReservas(calendario);
      printf( "\n" );
    }
  /* Si es cero se avisa de que no hay reserva para esa hora y ese nombre y por tanto no se puede anular */
  } else {
    printf( "No hay reserva para ese dia y hora que se intenta anular.\n" );
    printf( "\n" );
  }

}

/*-- Imprime las reservas que hay un dia --*/
void GestionReservaSala::ReservasDia (Fecha fechaRsv) {
  ResumenReservas rsmrsv;
  int contreservas = 0;
  Cadena20 naux;
  Cadena20 aaux;
  strcpy(naux, "*");
  strcpy(aaux, "*");

  /* Inicia la matriz donde se va a guardar la persona que reserva y las horas que reserva */
  for (int i=0; i<=HORASDIA; i++) {
    strcpy(rsmrsv[i].nombre, " ");
    strcpy(rsmrsv[i].apellido, " ");
    rsmrsv[i].horacomienzo=0;
    rsmrsv[i].duracion=0;
  }

  /* Imprime la cabecera de la reserva del dia */
  printf( "Reservas del dia: %2d/%2d/%4d\n", fechaRsv.dia, fechaRsv.mes, fechaRsv.anno );
  printf( "I-------------I--------------------------I\n" );
  printf( "I Horas:      I08  10  12  14  16  18  20I\n" );
  printf( "I-------------I--------------------------I\n" );
  printf( "I Reservadas: I" );

  /* Para cada hora comprueba si esta reservada en la matriz de reservas y le mete RR a cada hora reservada,
  si el nombre de cada hora reservada coincide con el anterior va sumando las horas y guardando el nombre
  en la matriz rsmrsv (ResumenReservas) para imprimir los nombres al final del resumen del dia */
  for (int i = HORAINICIAL; i<=HORAFINAL; i++) {
    if (reservado[fechaRsv.mes][fechaRsv.dia][i].hayreserva) {
      printf( "RR" );
      if (compararNombre(naux, aaux,reservado[fechaRsv.mes][fechaRsv.dia][i].nombre, reservado[fechaRsv.mes][fechaRsv.dia][i].apellido)) {
        rsmrsv[contreservas].duracion = rsmrsv[contreservas].duracion + 1;
      } else {
        contreservas = contreservas + 1;
        strcpy(naux, reservado[fechaRsv.mes][fechaRsv.dia][i].nombre);
        strcpy(aaux, reservado[fechaRsv.mes][fechaRsv.dia][i].apellido);
        strcpy(rsmrsv[contreservas].nombre, reservado[fechaRsv.mes][fechaRsv.dia][i].nombre);
        strcpy(rsmrsv[contreservas].apellido, reservado[fechaRsv.mes][fechaRsv.dia][i].apellido);
        rsmrsv[contreservas].horacomienzo = i;
        rsmrsv[contreservas].duracion = 1;
      }
    } else {
      printf( "  " );
    }
  }
  printf( "I\nI-------------I--------------------------I\n" );
  printf( "\n" );

  /* Imprime los nombres y la duracion de las reservas del dia (vector rsmrsv) */
  for (int i=1; i<=contreservas; i++) {
    printf( "De %2d a %2d reservado por: %s %s \n", rsmrsv[i].horacomienzo, rsmrsv[i].horacomienzo + rsmrsv[i].duracion, rsmrsv[i].nombre, rsmrsv[i].apellido );
    printf( "\n" );
  }
}

/*-- Funcion para obtener la fecha maxima de las reservas --*/
void GestionReservaSala::ObtenerFechaMaxima() {
  Fecha fecmax;
  fecmax.dia = 31;
  fecmax.mes = fechaActual.mes + 3;
  if (fecmax.mes > 12) {
    fecmax.mes = fecmax.mes - 12;
    fecmax.anno = fechaActual.anno + 1;
  } else {
    fecmax.anno = fechaActual.anno;
  }
  printf( "Fecha maxima: %2d %2d %2d \n", fecmax.dia, fecmax.mes, fecmax.anno );
  fechaMaxima = fecmax;
}

/*-- Iniciar con los nombres en blanco y sin reservas la matriz de todas las reservas --*/
void GestionReservaSala::IniciarReserva () {
  /* Iniciamos los valores de la matriz a 0 */
  for ( int i = 0; i <= NUMMESES; i++) {
    for ( int j = 0; j <= NUMDIAS; j++) {
      for ( int k = 0; k <= NUMHORAS; k++) {
        strcpy(reservado[i][j][k].nombre, BLANCO);
        strcpy(reservado[i][j][k].apellido, BLANCO);
        reservado[i][j][k].hayreserva=false;
      }
    }
  }

  for ( int i = 0; i <= NUMMESES; i++) {
    numReservas[i] = 0;
  }
}
