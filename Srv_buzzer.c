/**
 * @file Srv_buzzer.c
 * @brief Service pour la gestion du buzzer sur ESP32.
 *
 * Ce module fournit des fonctions pour initialiser et activer
 * le buzzer en sortie GPIO. 
 * 
 * Fonctions disponibles :
 * - @ref buzzer_set_gpio() : configure la broche du buzzer.
 * - @ref buzzer_set_blink() : fait sonner brièvement le buzzer.
 */

#include "Srv_buzzer.h"          /**< @brief Header : définition des pins et prototypes */
#include "driver/gpio.h"         /**< @brief Driver ESP-IDF pour manipuler les GPIO */
#include "freertos/FreeRTOS.h"   /**< @brief Kernel FreeRTOS */
#include "freertos/task.h"       /**< @brief Gestion des temporisations (vTaskDelay) */

/**
 * @brief Initialise la broche du buzzer en sortie.
 *
 * Cette fonction :
 * - Réinitialise la broche définie dans @ref Buzzer
 * - Configure la broche en sortie
 * - Place le buzzer à l’état bas (désactivé)
 */
void buzzer_set_gpio(void) {
    gpio_reset_pin(Buzzer);                      /**< Réinitialise la broche */
    gpio_set_direction(Buzzer, GPIO_MODE_OUTPUT);/**< Configure en sortie */
    gpio_set_level(Buzzer, 0);                   /**< Buzzer OFF par défaut */
}

/**
 * @brief Fait sonner le buzzer brièvement (blink).
 *
 * Cette fonction :
 * - Active le buzzer pendant 50 ms
 * - Le désactive ensuite
 * - Attend 300 ms avant de rendre la main
 *
 * Utilisation typique : signaler une alarme ou un événement.
 */
void buzzer_set_blink(void) {
    gpio_set_level(Buzzer, 1);   /**< Active le buzzer */
    vTaskDelay(pdMS_TO_TICKS(50));  /**< Attente 50 ms */

    gpio_set_level(Buzzer, 0);   /**< Désactive le buzzer */
    vTaskDelay(pdMS_TO_TICKS(300)); /**< Attente 300 ms */
}
