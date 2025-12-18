/**
 * @file variable.c
 * @brief Définition des constantes globales du projet ESP32.
 *
 * Ce fichier contient les seuils et paramètres de temporisation utilisés
 * par l’application principale pour la gestion des capteurs, LEDs et buzzer.
 *
 * - @ref Temp_alarm : seuil de déclenchement d’alarme (°C)
 * - @ref temps_loop_nominal : délai entre mesures en mode normal
 * - @ref loop_alarme_temp : délai entre mesures en mode alarme
 *
 * @date 21 août 2025
 * @author User
 */

/**
 * @brief Seuil de température déclenchant une alarme.
 *
 * Si la température mesurée dépasse cette valeur (°C), la LED rouge clignote
 * et le buzzer est activé.
 */
#define Temp_alarm_C       50     

/**
 * @brief Durée de temporisation en mode nominal (ms).
 *
 * Délai entre deux lectures de température lorsque le système est en état normal.
 */
#define temps_loop_nominal_ms 10000  

/**
 * @brief Durée de temporisation en mode alarme (ms).
 *
 * Délai entre deux lectures de température lorsque le seuil d’alarme est dépassé.
 */
#define temps_loop_alarme_ms  1000   

#define Temps_check_porte_ms 30000

