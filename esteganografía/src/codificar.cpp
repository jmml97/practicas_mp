
/**
  * @file imagenES.cpp
  * @brief Moódulo que contiene las funciones "ocultar" y "revelar" usadas para codificar un mensaje en una imagen
  *
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */

#include <iostream>
#include "imagenES.h"

using namespace std;

void Ocultar (unsigned char imagen[], int longitud_imagen, char mensaje[]) {

  // Vamos iterando por los valores de la cadena char.
  for(int i = 0; mensaje[i] != '\0' && i < longitud_imagen  ; i++) {

    // Cada caracter está formado por 8 bits. Tenemos que ir insertando cada bit
    // del carácter en el bit menos significativo de cada byte de la imagen.
    // Empezamos en el último bit porque así es como lo indica el ejercicio
    // (de izquierda a derecha).
    for(int j = 7; j >= 0; j--) {

      // Con esta fórmula, podemos calcular en qué byte de la imagen Tenemos
      // que guardar el bit correspondiente.
      int byte_imagen = i*8 + (7 - j);

      // Consultamos el valor del bit del carácter i en la posición j-ésima.
      // Si ese bit es 0, mensaje[i] & 1<<j nos devuelve 0. Si es 1, nos
      // devolverá otro valor.
      if ((mensaje[i] & (1<<j)) == 0) { // el bit es 0

        // Como el bit es 0, tenemos que desactivar el bit menos significativo.
        imagen[byte_imagen] = imagen[byte_imagen]&(~1);

      } else { // el bit es 1

        // Como el bit es 1, tenemos que activar el bit menos significativo.
        imagen[byte_imagen] = imagen[byte_imagen]|1;

      }

    }

  }

}


void Revelar (unsigned char im_cifrada[], int longitud_mensaje, char revelacion[]){

  char caracter = 0; // el caracter que está oculto con el que trabajamos.
  int num_caracter = 1; // numero del caracter en la cadena (empezamos por 1)
  int pos_bit; // posicion del bit del caracter que estamos insertando en cada
               // iteración.
  bool finalizado = false;

  for (int i = 0; i < longitud_mensaje && !finalizado; i++) {

    // Comprobamos el valor del bit menos significativo del byte de la imagen
    // de la iteración actual
    int bit_menos_significativo = (im_cifrada[i]&1);

    // Si es 0, tenemos que poner un 0 en el bit que corresponda del caracter
    // empezando de izquierda a derecha.
    // Si es distinto de 0, es 1 y por tanto, tenemos que poner un 1 de la misma
    // forma.

    pos_bit = 8*(num_caracter) - i - 1;

    // Solo si el bit es un 1 tendremos que cambiarlo (ya que por defecto
    // nuestro carácter es 0)
    if (bit_menos_significativo == 1) {
      caracter = caracter|1<<pos_bit;
    }

    // Si llegamos a un byte múltiplo de 7, ya tenemos los 8 bits del carácter
    // por tanto, pasamos al siguiente carácter y guardamos el carácter que
    // hemos descubierto en nuestra cadena char.

    // Si hemos llegado al final del bit (y ya hemos obtenido el caracter)
    if (pos_bit == 0) {

      if (caracter == '\0') {
        // Si el carácter que hemos obtenido es el '\0', hemos acabado.
        finalizado = true;
      } else {
        // Guardamos el caracter que hemos obtenido.
        revelacion[num_caracter - 1] = caracter;
        num_caracter++; // Pasamos al caracter siguiente.
        caracter = 0; // Borramos de nuevo el caracter.
      }

    }

  }

}
