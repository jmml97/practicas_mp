#include <iostream>
#include "tablero.hpp"

#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define BOLDGREEN   "\033[1m\033[32m"
#define RESET   "\033[0m"

using namespace std;

Tablero::Tablero() {

  tablero = Matriz(0, 0);
  SetObjetivoFichas(0);
  SetFichasPorTurno(0);
  ResetInsertadasEnTurno();
  SetTurno(0);
  ganador = 0;

}

Tablero::Tablero(int filas, int columnas, int objetivo, int fichas_turno) {

  tablero = Matriz(filas, columnas);
  SetObjetivoFichas(objetivo);
  SetFichasPorTurno(fichas_turno);
  ResetInsertadasEnTurno();
  SetTurno(1);
  ganador = 0;

}

void Tablero::CambiaTurno(){

  turno = turno == 2 ? 1 : 2;
  ResetInsertadasEnTurno();

}

void Tablero::SetGanador() {

  ganador = GetTurno();
  CambiaTurno();

}

int Tablero::GetPuntuacion() {

  return (objetivo_fichas*10 + ((GetFilas()*GetColumnas()/2) - tablero.GetUsadas()));

}

// Métodos que encuentran N fichas en línea ////////////////////////////////////
//
//

bool Tablero::HayNHorizontal(int fil, int col) {

  for (int i = 0; i < GetObjetivoFichas() - 1; i++)
    if (ContenidoCasilla(fil, col + i) != ContenidoCasilla(fil, col + i + 1))
      return false;

  return true;

}

bool Tablero::HayNVertical(int fil, int col) {

  for (int i = 0; i < GetObjetivoFichas() - 1; i++)
    if (ContenidoCasilla(fil + i, col) != ContenidoCasilla(fil + i + 1, col))
      return false;

  return true;

}

bool Tablero::HayNDiagonal(int fil, int col) {

  for (int i = 0; i < GetObjetivoFichas() - 1; i++)
    if (ContenidoCasilla(fil + i, col + i ) != ContenidoCasilla(fil + i + 1, col + i + 1))
      return false;

  return true;

}

bool Tablero::HayNDiagonalInv(int fil, int col) {

  for (int i = 0; i < GetObjetivoFichas() - 1; i++)
    if (ContenidoCasilla(fil - i, col + i ) != ContenidoCasilla(fil - i - 1, col + i + 1))
      return false;

  return true;

}

bool Tablero::HayNEnLinea() {

  int n = GetObjetivoFichas();

  for (int fil = 0; fil < GetFilas(); fil++) {
    for (int col = 0; col < GetColumnas(); col++) {

      if (ContenidoCasilla(fil, col) != 0) {

        if (col <= GetColumnas() - n && HayNHorizontal(fil, col))
          return true;
        if (fil <= GetFilas() - n && HayNVertical(fil, col))
          return true;
        if(col <= GetColumnas() - n&& fil <= GetFilas() - n && HayNDiagonal(fil, col))
          return true;
        if (col <= GetColumnas() - n && fil >= n - 1 && HayNDiagonalInv(fil, col))
          return true;

      }

    }
  }

  return false;
}

// Devuelve si la partida ha finalizado.
// 0: La partida no ha finalizado.
// 1: La partida ha finalizado y hay un ganador.
// 2: La partida ha finalizado y hay empate.
int Tablero::PartidaFinalizada() {

  if (HayNEnLinea())
    return 1;
  if (tablero.GetUsadas() == GetFilas() * GetColumnas())
    return 2;
  else
    return 0;

}

// MÉTODOS QUE MODIFICAN EL TABLERO

// Se encarga de insertar una ficha en el casillero si la columna introducida es // adecuada (existe y tiene espacios vacíos).
bool Tablero::InsertarFicha(int columna) {

  if (columna < 0 || columna >= GetColumnas())
    return false;

  for (int i = 0; i < GetFilas(); i++){

    if (ContenidoCasilla(i, columna) == 0) {
      tablero.Modifica(i, columna, GetTurno());
      return true;
    }

  }

  return false;
}

void Tablero::PrettyPrint(ostream &os){

  os << "\n\n";

  // Imprime las letras de las columnas

  char letra;

  os << " ";

  for (int i = 0; i < GetColumnas(); i++){
    letra = ('a'+i);
    os << letra << " ";
  }
  os << endl;

  // Imprime el casillero

  for (int i = GetFilas() - 1; i >= 0; i--){

    os << "|";
    for (int j = 0; j < GetColumnas(); j++){

      // cout << GetColumnas()*i + j;
      //cout << i << "," << j;


      if (ContenidoCasilla(i,j) == 1)
        os << BLUE << "x";
      else if (ContenidoCasilla(i,j) == 2)
        os << RED << "o";
      else
        os << " ";

      os << RESET;

      os << "|";

    }
    os << endl;
  }

  // Imprime la base

  os << BOLDGREEN;

  for (int i = 0; i < 2*GetColumnas() + 1; i++){
    os << "=";
  }

  os << RESET << "\n\n";
}

// Operadores de E/S

ostream& operator<<(ostream &os, const Tablero &t) {

  os << t.GetObjetivoFichas() << ' ';
  os << t.GetFichasPorTurno() << ' ';
  os << t.GetInsertadasEnTurno() << ' ';
  os << t.GetTurno() << ' ';
  os << t.GetGanador() << '\n';

  t.EscribirMatrizTablero(os);

  return os;

}

istream& operator>>(istream &is, Tablero &t) {

  int o, tu, f, i, g;

  is >> o >> f >> i >> tu >> g;

  t.SetObjetivoFichas(o);
  t.SetFichasPorTurno(f);
  t.SetInsertadasEnturno(i);
  t.SetTurno(tu);

  t.LeerMatrizTablero(is);

  return is;

}
