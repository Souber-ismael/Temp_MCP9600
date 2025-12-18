/**
 * @file main.c
 * @brief Application principale pour le projet ESP32 avec capteur MCP9600.
 *
 * Ce fichier initialise les périphériques (capteur de température MCP9600,
 * LED RGB, buzzer) et crée une boucle infinie pour mesurer la température
 * et déclencher des alertes visuelles/sonores selon un seuil.
 *
 * - Capteur MCP9600 : lecture température
 * - LED RGB : indicateur visuel (vert = normal, rouge = alarme)
 * - Buzzer : alarme sonore
 */

#include "Srv_temperature_sensor.h"  /**< @brief Driver pour MCP9600 (I2C) */
#include "Srv_buzzer.h"              /**< @brief Fonctions de contrôle du buzzer */
#include "Srv_LED.h"                 /**< @brief Fonctions de contrôle des LEDs */
#include "variable.c"                /**< @brief Variables globales du projet */
#include "esp_err.h"                 /**< @brief Gestion des codes d’erreur ESP-IDF */
#include "esp_log.h"                 /**< @brief Système de logs (ESP_LOGI, ESP_LOGE, …) */
#include "freertos/FreeRTOS.h"       /**< @brief Kernel temps-réel FreeRTOS */
#include "freertos/task.h"           /**< @brief Gestion des tâches FreeRTOS (vTaskDelay, …) */
#include "driver/gpio.h"             /**< @brief Fonctions bas niveau GPIO */
#include "hal/gpio_types.h"          /**< @brief Définitions des types GPIO */

/** 
 * @brief Tag utilisé pour identifier les logs dans l’application.
 */
static const char *TAG = "MCP9600";

/**
 * @brief Fonction principale lancée au démarrage de l’ESP32.
 *
 * Étapes :
 * - Initialise les périphériques (I2C, LED, buzzer)
 * - Vérifie la présence du capteur MCP9600
 * - Boucle infinie :
 *   - Lit la température
 *   - Affiche la valeur via logs
 *   - Active LED verte si température < seuil
 *   - Active LED rouge clignotante + buzzer si température >= seuil
 */
void app_main(void) {
    ESP_LOGI(TAG, "Initialisation I2C...");   /**< Log : début initialisation I2C */

    rgb_led_init();        /**< Initialise la LED RGB */
    buzzer_set_gpio();     /**< Configure la GPIO du buzzer */

    if (!mcp9600_check_id()) {  /**< Vérifie que le capteur MCP9600 est présent */
        ESP_LOGE(TAG, "MCP9600 non détecté !"); /**< Log d’erreur si capteur absent */
        return;  /**< Stoppe le programme si le capteur n’est pas détecté */
    }
    ESP_LOGI(TAG, "MCP9600 détecté avec succès."); /**< Log si détection réussie */

    while (1) {  /**< Boucle principale infinie */
        int16_t raw_temp;  /**< @brief Variable pour stocker la valeur brute de température */

        if (mcp9600_read16(MCP9600_REG_HOT_JUNCTION, &raw_temp) == ESP_OK) {
            float temp_c = mcp9600_convert_temp(raw_temp);   /**< Conversion brute → °C */
            ESP_LOGI(TAG, "Température : %.2f C", temp_c);   /**< Log de la température */

            if (temp_c < Temp_alarm_C) {  /**< Cas normal : température sous le seuil */
                gpio_set_level(LED_G_GPIO , 1);               /**< Allume LED verte */
                gpio_set_level(LED_R_GPIO , 0);               /**< Éteint LED rouge */
                ESP_LOGI(TAG,"LED GREEN");                    /**< Log état LED */
                vTaskDelay(pdMS_TO_TICKS(temps_loop_nominal_ms));/**< Pause nominale */
            }else{  /**< Cas alarme : température au-dessus du seuil */
                red_blink();                                  /**< Fait clignoter LED rouge */
                gpio_set_level(LED_G_GPIO , 0);               /**< Éteint LED verte */
                buzzer_set_blink();                           /**< Active buzzer */
                ESP_LOGI(TAG,"LED RED");                      /**< Log état LED */
                vTaskDelay(pdMS_TO_TICKS(temps_loop_alarme_ms));  /**< Pause alarme */
            }
        } else {
            ESP_LOGW(TAG, "Erreur de lecture température."); /**< Log si lecture capteur échoue */
        }
    }
}
