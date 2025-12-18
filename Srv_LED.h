/**
 * @file Srv_LED.h
 * @brief Déclarations et définitions pour le service de gestion des LEDs.
 *
 * Ce fichier contient :
 * - La définition des broches GPIO utilisées pour les LEDs RGB
 * - Les prototypes des fonctions de gestion des LEDs
 *
 * Voir l’implémentation dans @ref Srv_LED.c
 */

#ifndef MAIN_SRV_LED_H_
#define MAIN_SRV_LED_H_

/**
 * @brief Numéro de broche GPIO utilisée pour la LED rouge.
 */
#define LED_R_GPIO 18

/**
 * @brief Numéro de broche GPIO utilisée pour la LED verte.
 */
#define LED_G_GPIO 21

/**
 * @brief Numéro de broche GPIO utilisée pour la LED bleue.
 */
#define LED_B_GPIO 22

/**
 * @brief Initialise les GPIO des LEDs RGB.
 *
 * - Configure les broches en sortie
 * - Éteint les LEDs par défaut
 */
void rgb_led_init(void);

/**
 * @brief Fait clignoter brièvement la LED rouge.
 *
 * - Allume la LED rouge pendant 200 ms
 * - L’éteint ensuite
 */
void red_blink(void);

#endif /* MAIN_SRV_LED_H_ */
