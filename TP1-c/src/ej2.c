#include <stdlib.h>

#include "ej1.h"

/**
 * Marca el ejercicio 2 como hecho (`true`) o pendiente (`false`).
 *
 * Funciones a implementar:
 *   - ej1
 */
bool EJERCICIO_2_HECHO = true;


/**
 * Aplica un efecto de "mapa de calor" sobre una imagen dada (`src`). Escribe
 * la imagen resultante en el canvas proporcionado (`dst`).
 *
 * Para calcular el mapa de calor lo primero que hay que hacer es computar la
 * "temperatura" del pixel en cuestión:
 * ```
 * temperatura = (rojo + verde + azul) / 3
 * ```
 *
 * Cada canal del resultado tiene la siguiente forma:
 * ```
 * |          ____________________
 * |         /                    \
 * |        /                      \        Y = intensidad
 * | ______/                        \______
 * |
 * +---------------------------------------
 *              X = temperatura
 * ```
 *
 * Para calcular esta función se utiliza la siguiente expresión:
 * ```
 * f(x) = min(255, max(0, 384 - 4 * |x - 192|))
 * ```
 *
 * Cada canal esta offseteado de distinta forma sobre el eje X, por lo que los
 * píxeles resultantes son:
 * ```
 * temperatura  = (rojo + verde + azul) / 3
 * salida.rojo  = f(temperatura)
 * salida.verde = f(temperatura + 64)
 * salida.azul  = f(temperatura + 128)
 * salida.alfa  = 255
 * ```
 *
 * Parámetros:
 *   - dst:    La imagen destino. Está a color (RGBA) en 8 bits sin signo por
 *             canal.
 *   - src:    La imagen origen A. Está a color (RGBA) en 8 bits sin signo por
 *             canal.
 *   - width:  El ancho en píxeles de `src` y `dst`.
 *   - height: El alto en píxeles de `src` y `dst`.
 */

uint8_t f(int16_t x) {
	/*
	f(x) = min(255,temp)
	temp = max(0, 384 -4 |x-192|)
	*/
    int16_t abs, temp; 
	abs = x - 192;
	abs = (abs > 0) ? abs : (- abs);
	temp = 384 - 4*(abs);
	temp = (0 > temp) ? 0 : temp;
	x = (uint8_t) ((255 < temp) ? 255 : temp);
	return x;

}

void ej2(
	rgba_t* dst,
	rgba_t* src,
	uint32_t width, uint32_t height
) {


// Itero sobre cada píxel de la imagen
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            // Calcula la posición lineal del píxel en la matriz 1D
            uint32_t pixel = y * width + x;
            
			int16_t rojo,verde,azul,alfa,temperatura;
			rojo = (int16_t) src[pixel].r;
			azul = (int16_t) src[pixel].b;
			verde = (int16_t) src[pixel].g;
			alfa = (int16_t) src[pixel].a;

			rgba_t pixel_calor;
			temperatura = (rojo +  verde + azul) / 3;
			pixel_calor.a = 255;
			pixel_calor.r = f(temperatura);
			pixel_calor.g = f(temperatura + 64);
			pixel_calor.b = f(temperatura + 128);
			
			
            // Copia el píxel de src a dst
            dst[pixel] = pixel_calor;
        }
    }

}
