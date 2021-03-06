#include <iostream>
#include "imagenES.h"
#include "codificar.h"

using namespace std;

const int MAX_BUFFER = 1000000;
const int MAX_N_IMAGEN = 100;
const int MAX_MENSAJE = MAX_BUFFER / 8;

void ImprimirCadena(char cadena[], int longitud) {

  for (int i = 0; i < longitud; i++)
    cout << cadena[i];

  cout << endl;
}

int main() {

  /*
      Creamos vectores para almacenar el nombre de las imágenes y el mensaje a
      descifrar (antes habiendo definido unas cuantas constantes para su tamaño
      máximo) así como las filas y columnas de la imagen.
  */

  int filas, columnas;
  TipoError error = NO_ERROR;

  unsigned char buffer[MAX_BUFFER];
  char im_entrada[MAX_N_IMAGEN] = {0}, mensaje[MAX_MENSAJE] = {0};

  /*
      Usamos cin.getline para almacenar en los vectores los nombres que les iremos asignando
  */

  cout << "Indique la imagen cuyo mensaje quieres decodificar: ";
  cin.getline(im_entrada, MAX_N_IMAGEN);

  TipoImagen tipo = LeerTipoImagen(im_entrada, filas, columnas);

  if (tipo == IMG_PGM) {

    LeerImagenPGM(im_entrada, filas, columnas, buffer);

  } else if (tipo == IMG_PPM) {

    LeerImagenPPM(im_entrada, filas, columnas, buffer);

  } else {
    cout << "No ha introducido un archivo de imagen correcto." << endl;
  }

  Revelar(buffer, MAX_MENSAJE, mensaje, error);

  ImprimirError(error);

  if (error == NO_ERROR) {
    cout << "El mensaje oculto es: " << endl;
    ImprimirCadena(mensaje, MAX_MENSAJE);
  }




}
