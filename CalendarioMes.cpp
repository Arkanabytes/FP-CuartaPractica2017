/*******************************************************************************
* Modulo: CalendarioMes
*
*   Desarrolla los calculos para obtener el calendario necesario para colocar
*   las reservas de acuerdo con los dias de la semana y para validar las fechas.
********************************************************************************/
#include <stdio.h>
#include "CalendarioMes.h"

/*-- Calcular annos bisiestos --*/
int CalcularBisiestos( int mes, int anno ) {
  int bisiestos;
  bisiestos = 0;
  for ( int i = 1601; i<anno; i++) {
    if ( (i%4 == 0) && (i%100 != 0) ) {
      bisiestos++;
    } else {
      if (i%400 == 0) {
        bisiestos++;
      }
    }
  }
  if ( (anno%4 == 0) && (anno%100 != 0) ) {
    if ( mes>2 ) {
      bisiestos++;
    }
  } else {
    if ( (anno%400 == 0) && (mes>2) ) {
      bisiestos++;
    }
  }
  return bisiestos;
}

/*-- Calcular incremento de annos --*/
int CalcularAnnos( int anno ) {
  return( anno - 1601 );
}

/*-- Aumento total de dias de cada mes para el calculo total --*/
int CalcularDiasAumentoMes( int mes ) {
  switch ( mes ) {
  case 1:
  case 10:
    return 0;
    break;
  case 2:
  case 3:
  case 11:
    return 3;
    break;
  case 4:
  case 7:
    return 6;
    break;
  case 5:
    return 1;
    break;
  case 6:
    return 4;
    break;
  case 8:
    return 2;
    break;
  default:
    return 5;
  }
}

/*-- Devolver dia de la semana en funcion
del incremento de dias calculado --*/
int DiadelaSemana( int incrementoDias ) {
  return incrementoDias%7;
}

/*-- Devuelve el dia de la semana en que se inicia el mes  --*/
void CalendarioMes::CalcularDiaSemanaInicioMes() {
  int bisiestos = 0;
  int annos = 0;
  int posicion = 0;
  int incrementoDias = 0;
  int diaSemana = 0;
  bisiestos = CalcularBisiestos( Mes, Anno );
  annos = CalcularAnnos( Anno );
  posicion = CalcularDiasAumentoMes( Mes );
  incrementoDias = bisiestos + annos + posicion;
  diaSemana = DiadelaSemana( incrementoDias );
  DiaSemanaInicioMes = diaSemana;
}

/*-- Dias totales de cada mes --*/
void CalendarioMes::CalcularDiasMes(){
    int diaFinal = 31;
    const int nummeses = 12;
    typedef int TipoDiasMes[nummeses];

    TipoDiasMes DiasCadaMes = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    diaFinal = DiasCadaMes[Mes - 1];

    if (Mes == 2){
      if ( (Anno%4 == 0) && (Anno%100 != 0) ) {
        diaFinal = 29;
      } else {
        if ( Anno%400 == 0) {
          diaFinal = 29;
        } else {
          diaFinal = 28;
        }
      }
    }

    DiasMes = diaFinal;
}

/*-- Calcula los datos del calendario de un mes y un anno de una fecha --*/
void CalendarioMes::calcularCalendarioMes(Fecha fecha){
    Mes = fecha.mes;
    Anno = fecha.anno;
    CalcularDiaSemanaInicioMes();
    CalcularDiasMes();
}
