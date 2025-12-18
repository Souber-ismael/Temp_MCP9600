/**
 * @file Srv_temperature_sensor.c
 * @brief Service pour la gestion du capteur de température MCP9600 via I2C.
 *
 * Ce module gère la communication avec le capteur MCP9600 :
 * - Initialisation du bus I2C
 * - Lecture des registres internes
 * - Conversion des données brutes en température (°C)
 * - Vérification de l'identifiant du capteur
 *
 * Fonctions principales :
 * - @ref mcp9600_read16()
 * - @ref mcp9600_convert_temp()
 * - @ref mcp9600_check_id()
 */

#include "Srv_temperature_sensor.h"   /**< @brief Header du capteur (macros + prototypes) */
#include "driver/i2c.h"               /**< @brief Driver officiel ESP-IDF pour I2C */
#include "esp_err.h"                  /**< @brief Gestion des erreurs ESP-IDF */
#include "esp_log.h"                  /**< @brief Système de log (console) */

/** @brief Broche SCL utilisée pour le bus I2C */
#define I2C_MASTER_SCL_IO          7
/** @brief Broche SDA utilisée pour le bus I2C */
#define I2C_MASTER_SDA_IO          6
/** @brief Numéro du contrôleur I2C utilisé (ici I2C0) */
#define I2C_MASTER_NUM             I2C_NUM_0
/** @brief Fréquence du bus I2C (100 kHz) */
#define I2C_MASTER_FREQ_HZ         100000
/** @brief Timeout pour les opérations I2C en millisecondes */
#define I2C_MASTER_TIMEOUT_MS      1000

/** 
 * @brief Tag utilisé pour les logs (identification).
 */
static const char *TAG = "MCP9600";

/**
 * @brief Initialise le bus I2C en mode maître.
 *
 * Cette fonction configure :
 * - Les broches SDA et SCL
 * - Les résistances de pull-up
 * - La vitesse du bus
 *
 * @return
 * - ESP_OK si l'initialisation réussit
 * - Code d’erreur ESP-IDF sinon
 */
static esp_err_t i2c_master_init(void) {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
    return i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

/**
 * @brief Lecture de 2 octets dans un registre du MCP9600.
 *
 * @param[in] reg Adresse du registre à lire
 * @param[out] raw_value Pointeur vers la variable qui contiendra la valeur brute
 *
 * @return
 * - ESP_OK si la lecture est réussie
 * - Code d’erreur ESP-IDF sinon
 */
esp_err_t mcp9600_read16(uint8_t reg, int16_t *raw_value) {
    uint8_t data[2];
    esp_err_t ret = i2c_master_write_read_device(
        I2C_MASTER_NUM, MCP9600_ADDR,
        &reg, 1, data, 2,
        I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS
    );
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "data[0] = 0x%02X, data[1] = 0x%02X", data[0], data[1]);
        *raw_value = (int16_t)((data[0] << 8) | data[1]);
    }
    return ret;
}

/**
 * @brief Conversion d’une valeur brute en température en °C.
 *
 * @param[in] raw Valeur brute (16 bits) lue depuis le capteur
 * @return Température en degrés Celsius
 */
float mcp9600_convert_temp(int16_t raw) {
    return raw * 0.0625f;  /**< Résolution : 0,0625 °C/LSB */
}

/**
 * @brief Vérifie si le capteur MCP9600 est présent et valide.
 *
 * Cette fonction :
 * - Initialise le bus I2C
 * - Lit le registre ID du MCP9600
 * - Vérifie que la valeur lue correspond à l’ID attendu (0x40)
 *
 * @return
 * - true si le capteur est détecté
 * - false sinon
 */
bool mcp9600_check_id(void) {
    i2c_master_init();

    uint8_t reg = MCP9600_REG_DEVICE_ID;
    uint8_t id = 0;
    esp_err_t ret = i2c_master_write_read_device(
        I2C_MASTER_NUM, MCP9600_ADDR,
        &reg, 1, &id, 1,
        I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS
    );
    if (ret != ESP_OK) return false;
    return id == 0x40;
}
