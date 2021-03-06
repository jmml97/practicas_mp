
#ifndef tablero_h
#define tablero_h

/*
  Clase Tablero que se encarga de interactuar con Matriz para almacenar los datos del juego
*/

#include "matriz.hpp"

class Tablero {

  private:

    Matriz tablero;
    int objetivo_fichas, turno, ganador;

  public:

    int GetFilas();
    int GetColumnas();

    inline int GetObjetivoFichas() const {
      return objetivo_fichas;
    }
    void SetObjetivoFichas(int objetivo);

    inline int GetTurno() const {
      return turno;
    }
    void SetTurno(int n);
    void CambiaTurno();

    int GetPuntuacion();

    inline int GetGanador() const {
      return ganador;
    }
    void SetGanador();

    int ContenidoCasilla(int x, int y);
    void PrettyPrint();

    bool HayNHorizontal(int fil, int col);
    bool HayNVertical(int fil, int col);
    bool HayNDiagonal(int fil, int col);
    bool HayNDiagonalInv(int fil, int col);
    bool HayNEnLinea();
    int PartidaFinalizada();

    bool InsertarFicha(int columna);
    void VaciarTablero();

    Tablero(int filas, int columnas, int objetivo);


};

#endif
