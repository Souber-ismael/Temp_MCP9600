/**
 * @file Srv_buzzer.h
 * @brief Déclarations et définitions pour le service de gestion du buzzer.
 *
 * Ce fichier contient :
 * - La définition de la broche GPIO du buzzer
 * - Les prototypes des fonctions pour initialiser et activer le buzzer
 *
 * Voir l’implémentation dans @ref Srv_buzzer.c
 */

#ifndef MAIN_SRV_BUZZER_H_
#define MAIN_SRV_BUZZER_H_

/**
 * @brief Numéro de broche GPIO utilisée pour le buzzer.
 *
 * Cette valeur correspond à la GPIO19 de l’ESP32.
 */
#define Buzzer    19   

/**
 * @brief Initialise la GPIO associée au buzzer.
 *
 * - Configure la broche en sortie
 * - Place le buzzer à l’état désactivé (niveau bas)
 */
void buzzer_set_gpio(void);

/**
 * @brief Active brièvement le buzzer (bip).
 *
 * - Active le buzzer pendant 50 ms
 * - Le désactive
 * - Attend 300 ms
 */
void buzzer_set_blink(void);

#endif /* MAIN_SRV_BUZZER_H_ */
