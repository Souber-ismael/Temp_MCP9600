/**
 * @file Srv_temperature_sensor.h
 * @brief Déclarations pour le service de gestion du capteur MCP9600 (I2C).
 *
 * Ce fichier contient :
 * - Les définitions des registres du MCP9600
 * - L’adresse I2C du capteur
 * - Les prototypes des fonctions pour lire et convertir les données
 *
 * Voir l’implémentation dans @ref Srv_temperature_sensor.c
 */

#ifndef MAIN_SRV_TEMPERATURE_SENSOR_H_     
#define MAIN_SRV_TEMPERATURE_SENSOR_H_     

#include "esp_err.h"   /**< @brief Gestion des erreurs ESP-IDF */
#include <stdbool.h>   /**< @brief Support des booléens (true/false) */

/**
 * @brief Adresse I2C du capteur MCP9600.
 */
#define MCP9600_ADDR               0x60  

/**
 * @name Registres internes du MCP9600
 * @{
 */
#define MCP9600_REG_HOT_JUNCTION   0x00   /**< Température de la jonction chaude */
#define MCP9600_REG_COLD_JUNCTION  0x01   /**< Température de la jonction froide */
#define MCP9600_REG_DEVICE_ID      0x20   /**< Identifiant du périphérique */
/// @}

/**
 * @brief Lecture de 2 octets depuis un registre du MCP9600.
 *
 * @param[in] reg Adresse du registre à lire
 * @param[out] raw_value Pointeur vers la valeur brute (16 bits) reçue
 * @return 
 * - ESP_OK si la lecture réussit  
 * - Code d’erreur ESP-IDF sinon
 */
esp_err_t mcp9600_read16(uint8_t reg , int16_t *raw_value );

/**
 * @brief Convertit une valeur brute en température Celsius.
 *
 * @param[in] raw Valeur brute issue du capteur
 * @return Température en °C
 */
float mcp9600_convert_temp(int16_t raw );

/**
 * @brief Vérifie que le capteur MCP9600 est présent et valide.
 *
 * @return 
 * - true si le capteur est détecté et son identifiant est correct  
 * - false sinon
 */
bool mcp9600_check_id(void);

#endif /* MAIN_SRV_TEMPERATURE_SENSOR_H_ */
