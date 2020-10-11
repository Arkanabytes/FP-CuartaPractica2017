/****************************************
* Interfaz de modulo: GestionReservaSala
*
*****************************************/
#pragma once
#include "Fecha.h"
#include "constantes.h"
#include "CalendarioMes.h"

typedef char Cadena20[LONGNOMBRE];
const Cadena20 BLANCO = "                    ";

typedef struct TipoReservado{
  Cadena20 nombre;
  Cadena20 apellido;
  bool hayreserva;
};

typedef TipoReservado TipoReserva[NUMMESES+1][NUMDIAS+1][NUMHORAS+1];

typedef struct UnaReserva {
  Cadena20 nombre;
  Cadena20 apellido;
  Fecha f;
  int horacomienzo;
  int duracion;
};
typedef UnaReserva ResumenReservas[HORASDIA+1];

bool compararNombre(Cadena20 n1, Cadena20 a1, Cadena20 n2, Cadena20 a2);

/*-- TAD de las reservas --*/
typedef struct GestionReservaSala{
  Fecha fechaActual; /* Fecha actual */
  Fecha fechaMaxima; /* Fecha maxima de la reserva */
  int numReservas[NUMMESES+1]; /* Numero de reservas del mes */
  TipoReserva reservado; /* Nombre e indicador de reserva de cada hora por dia y mes */

  /*-- Devuelve un entero con el tipo de reserva (0=no hay reserva, 99=reserva parcial, 100=reserva total)
  Necesita recibir un parametro que contenga la hora, el mes y la duracion a comprobar --*/
  int comprobarReserva (UnaReserva rsv);


  /*-- Imprimir calendario de un mes con el tipo de reserva de cada dia --*/
  void ImprimirCalendarioReservas(CalendarioMes calendario);

  /*-- Hacer reserva con los datos metidos de una reserva.
  Rellena la hora correspondiente del mes y del anno de la matriz de reservas:
  mete el nombre y pone a verdadero el campo hayReserva.
  Comprueba que no exista ya una reserva previa (funcion comprobarReserva)
  Comprueba que no sea sabado y domingo (funcion CalcularDiaSemana) --*/
  void HacerReserva(UnaReserva rsv, CalendarioMes calendario);

  /*-- Anula la reserva. Comprueba que existe esa reserva para esa persona y la anula --*/
  void AnularUnaReserva( UnaReserva rsv, CalendarioMes calendario);

  /*-- Imprime las reservas que hay un dia --*/
  void ReservasDia (Fecha fechaRsv);

  /*-- Funcion para obtener la fecha maxima de las reservas --*/
  void ObtenerFechaMaxima();

  /*-- Iniciar con los nombres en blanco y sin reservas la matriz de todas las reservas --*/
  void IniciarReserva ();


};
