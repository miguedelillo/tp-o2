#include "ej1.h"

/**
 * Marca el ejercicio 1 como hecho (`true`) o pendiente (`false`).
 *
 * Funciones a implementar:
 *   - ej1
 */
bool EJERCICIO_1_HECHO = true;

/**
 * Convierte una imagen dada (`src`) a escala de grises y la escribe en el
 * canvas proporcionado (`dst`).
 *
 * Para convertir un píxel a escala de grises alcanza con realizar el
 * siguiente cálculo:
 * ```
 * luminosidad = 0.2126 * rojo + 0.7152 * verde + 0.0722 * azul 
 * ```
 *
 * Como los píxeles de las imágenes son RGB entonces el píxel destino será
 * ```
 * rojo  = luminosidad
 * verde = luminosidad
 * azul  = luminosidad
 * alfa  = 255
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


void ej1(
	rgba_t* dst,
	rgba_t* src,
	uint32_t width, uint32_t height
) {

    // Itero sobre cada píxel de la imagen
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            // Calcula la posición lineal del píxel en la matriz 1D
            uint32_t pixel = y * width + x;
            
			uint8_t rojo,verde,azul,alfa,luminosidad;
			rojo = src[pixel].r;
			azul = src[pixel].b;
			verde = src[pixel].g;
			alfa = src[pixel].a;

			rgba_t pixel_gris;
			luminosidad = 0.2126 * rojo + 0.7152 * verde + 0.0722 * azul;
			pixel_gris.a = 255;
			pixel_gris.b = pixel_gris.g = pixel_gris.r = luminosidad;
            // Copia el píxel de src a dst
            dst[pixel] = pixel_gris;
        }
    }



}
