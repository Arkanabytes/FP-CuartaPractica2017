/***********************************
* Interfaz de modulo: CalendarioMes
*
************************************/
#pragma once
#include "Fecha.h"

/*-- Bisiestos desde 1601 --*/
int CalcularBisiestos( int mes, int anno );
/*-- Annos desde 1601 --*/
int CalcularAnnos( int anno );
/*-- Devolver dia de la semana en funcion del incremento de dias calculado --*/
int CalcularDiasAumentoMes( int mes );
/*-- Aumento total de dias de cada mes para el calculo total --*/
int DiadelaSemana( int incrementoDias );

/*-- TAD del calendario --*/
typedef struct CalendarioMes{
  int Mes; /* Mes del calendario */
  int Anno; /* Anno del calendario */
  int DiaSemanaInicioMes; /* Dia de la semana en que comienza el mes */
  int DiasMes; /* Dias totales del mes */

  /*-- Calcula el dia de la semana en que se inicia el mes  --*/
  void CalcularDiaSemanaInicioMes();

  /*-- Calcula Dias totales de cada mes --*/
  void CalcularDiasMes();

  /*-- Calcula los datos del calendario de un mes y un anno de una fecha --*/
  void calcularCalendarioMes(Fecha fecha);
};
