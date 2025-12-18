/**
 * @file Srv_LED.c
 * @brief Service pour la gestion des LEDs sur ESP32.
 *
 * Ce module fournit des fonctions pour initialiser les LEDs
 * et contrôler leur état (allumage, clignotement).
 *
 * Fonctions disponibles :
 * - @ref rgb_led_init() : configure les GPIOs des LEDs
 * - @ref red_blink() : fait clignoter la LED rouge
 */

#include "Srv_LED.h"            /**< @brief Header : définition des pins et prototypes */
#include "driver/gpio.h"        /**< @brief Driver ESP-IDF pour manipuler les GPIO */
#include "freertos/FreeRTOS.h"  /**< @brief Kernel FreeRTOS */
#include "freertos/task.h"      /**< @brief Gestion des temporisations (vTaskDelay) */

/**
 * @brief Initialise les LEDs RGB (rouge et verte).
 *
 * Cette fonction :
 * - Réinitialise les broches @ref LED_R_GPIO et @ref LED_G_GPIO
 * - Configure ces broches en sortie
 * - Éteint les LEDs par défaut (niveau bas)
 */
void rgb_led_init(void) {
    gpio_reset_pin(LED_R_GPIO);                      /**< Réinitialise la LED rouge */
    gpio_set_direction(LED_R_GPIO, GPIO_MODE_OUTPUT);/**< Configure en sortie */
    gpio_set_level(LED_R_GPIO, 0);                   /**< LED rouge OFF */

    gpio_reset_pin(LED_G_GPIO);                      /**< Réinitialise la LED verte */
    gpio_set_direction(LED_G_GPIO, GPIO_MODE_OUTPUT);/**< Configure en sortie */
    gpio_set_level(LED_G_GPIO, 0);                   /**< LED verte OFF */
}

/**
 * @brief Fait clignoter brièvement la LED rouge.
 *
 * Cette fonction :
 * - Allume la LED rouge pendant 200 ms
 * - L’éteint ensuite
 *
 * Utilisation typique : signaler une alarme ou un état d’erreur.
 */
void red_blink(void) {
    gpio_set_level(LED_R_GPIO, 1);   /**< Allume la LED rouge */
    vTaskDelay(pdMS_TO_TICKS(200));  /**< Attente 200 ms */
    gpio_set_level(LED_R_GPIO, 0);   /**< Éteint la LED rouge */
}
