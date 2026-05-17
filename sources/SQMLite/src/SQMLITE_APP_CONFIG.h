/// ---------------------------------------------------------------------
///
/// Projet                          : SQM Lite - Sky Quality Meter
/// Auteur                          : Juanito del Pepito
/// Version                         : 2.0.1.0
/// Date                            : 31/05/2026
/// 
/// Description                     : Sky Quality Meter (SQM) - Fichier de configuration de l'application
/// Gitub                           : https://github.com/Juani005999/SQMLite
/// Licence							: GPL-3.0 license
///
/// Capteurs et périphériques       : Cette application utilise les capteurs et périphériques suivant
///										- TSL2591
///										- BME280
///										- TFT ST7735
/// 
/// Prérequis                       : Cette application nécessite l'ajout des bibliothèques suivantes
///										- Adafruit_TSL2591
///										- Adafruit_BME280
///										- TFT_eSPI
/// 
/// ---------------------------------------------------------------------
#pragma once

// Include des librairies
#include "JUANITO_APP.h"
#include "JUANITO_MOVING_AVERAGE.h"
#include <SQMLITE_APP_ICONS.h>
#include <Adafruit_BME280.h>
#include <Adafruit_TSL2591.h>
#include <TFT_eSPI.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Définition des constantes correspondant aux PIN
#define ESP32_GPIO_SDA                          21                      // GPIO I2C SDA
#define ESP32_GPIO_SCL                          22                      // GPIO I2C SCL
#define JOYSTICK_PIN_SWITCH                     25                      // Joystick Switch
#define JOYSTICK_PIN_X                          32                      // Joystick X
#define JOYSTICK_PIN_Y                          33                      // Joystick Y

// Définition des constantes correspondant aux paramètres des capteurs
#define BME280_I2C_ADDRESS                      0x76                    // Sensor T/P/H BME280
#define TSL2591_NUMBER_ID                       2591                    // Identifiant du TSL2591

// Définition des constantes correspondant aux intervalles
#define READ_ENVIRONMENT_INTERVAL               3000                    // Intervalle de lecture de l'environnement via BME280
#define READ_LUX_INTERVAL                       5000					// Intervalle de lecture de la luminosité via TSL2591
#define BLE_NOTIFY_INTERVAL						1000					// Intervalle de Notification des caractéristiques BLE (Bluetooth Low Energy)
#define DISPLAY_INTERVAL                        120                     // Intervalle d'affichage sur l'écran
#define JOYSTICK_BUTTON_LONG_INTERVAL           1000					// Intervalle du clic long sur le Joystick
#define JOYSTICK_READ_INTERVAL					50						// Intervalle de lecture de l'état du Joystick

// Définition des constantes de taille pour les chaînes de caractères
#define BT_CMD_LINE_LENGTH                      256                     // Taille max d'une commande Bluetooth

// Définition des constantes pour la calibration de la lecture du TSL2591
#define TSL2591_SENSOR_VALUE_LOW				750						// Niveau bas du sensor => augmentation de la sensibilité du sensor si valeur en dessous
#define TSL2591_SENSOR_VALUE_HIGH				20000					// Niveau haut du sensor => diminution de la sensibilité du sensor si valeur au dessus
#define TSL2591_CALIBRATION						0						// Valeur servant à la calibration du TSL2591 : le calcul donne 1.121, la pratique donne 0
#define MIN_LUX_THRESHOLD						0.00005f				// Seuil minimum de lux valide (en dessous = bruit capteur)
#define TSL2591_MOVING_AVERAGE_COUNT			50						// Nombre de valeurs pour le calcul de la moyenne mobile du Lux
#define TSL2591_CORRECTION_TEMP_COEFF			-0.002f					// Coefficient thermique /°C
#define TSL2591_CORRECTION_TEMP_REF_C			25.0f					// Température de référence (°C)

// Définition des constantes pour la communication Bluetooth Low Energy (BLE)
#define BLE_DEVICE_NAME							"SQM Lite"
#define BLE_SERVICE_UUID						"d45872d6-b482-488e-b620-a0bb4a9c4d86"
#define BLE_CHARACTERISTIC_UUID_TEMPERATURE		"fd1839f2-f064-4f47-9e18-d212cbe538a9"
#define BLE_CHARACTERISTIC_UUID_HUMIDITY		"634fb69b-62b4-4fec-bce9-bc70e6b8166c"
#define BLE_CHARACTERISTIC_UUID_PRESSURE		"b8e5b7e1-4693-40e7-adbf-7784299e3b51"
#define BLE_CHARACTERISTIC_UUID_DEWPOINT		"41ce96a2-b73b-46be-90be-34e5dcd59c56"
#define BLE_CHARACTERISTIC_UUID_SKYBRIGHTNESS	"6fcf4961-63d5-4a3c-9b4a-60163aefa479"
#define BLE_CHARACTERISTIC_UUID_SKYQUALITY		"09c6e80f-55ed-4d70-bff2-62fc6ba07b3e"
#define BLE_CHARACTERISTIC_NUMHANDLES_COUNT		32						// Nombre de Handles nécessaires pour les caractéristiques du service BLE

// Définition des constantes pour l'affichage
#define SCREEN_WIDTH                            160						// Largeur de l'affichage TFT
#define SCREEN_HEIGHT                           128						// Hauteur de l'affichage TFT
#define SCREEN_HDR_HEIGHT                       30						// Hauteur du Header pour l'affichage
#define SCREEN_TIMEOUT							300000					// Timeout (ms) de mise en veille de l'affichage
#define SCREEN_ORIENTATION						3						// Orientation de l'affichage
#define TFT_FONT_DEFAULT						1						// Indice de la police par défaut
#define TFT_FONT_TITLE							2						// Indice de la police du titre de l'application

// Définition des constantes pour le Joystick
#define JOYSTICK_POSITION_MIN_VALUE_LOW         700
#define JOYSTICK_POSITION_MIN_VALUE_HIGH        3300

// Définition des différents mode d'affichage
enum DISPLAY_SCREEN_TYPE
{
	DISPLAY_NONE,
	DISPLAY_HOME,
	DISPLAY_LUX,
	DISPLAY_ENVIRONMENT
};

// Définition des différents mode d'affichage de l'écran Home
enum DISPLAY_HOME_TYPE
{
	DISPLAY_HOME_LUX,
	DISPLAY_HOME_SQM
};

// Définition des différents type d'action depuis le joystick
enum ACTION_TYPE
{
	ACTION_NONE,
	ACTION_CLICK,
	ACTION_CLICK_LONG,
	ACTION_RIGHT,
	ACTION_LEFT,
	ACTION_UP,
	ACTION_DOWN
};

// Définition des différents état du point de rosée
enum DEWPOINT_STATE
{
	DEWPOINT_STATE_DRY,
	DEWPOINT_STATE_HUMID,
	DEWPOINT_STATE_WET,
	DEWPOINT_STATE_UNKNOWN
};

// Structure des données nécessaires pour la gestion du capteur d'environnement BME280
struct DataSensorEnvironment {
	float temperature = NAN;											// Température (°C)
	float humidite = NAN;												// Taux d'humidité	(%)
	float pression = NAN;												// Pression atmosphérique (Pa)
	float dewPoint = NAN;												// Point de rosée (°C)
	DEWPOINT_STATE dewPointState = DEWPOINT_STATE_UNKNOWN;				// Etat du point de rosée pour l'icone
};

// Structure de résultat pour la conversion de Lux vers Mag/Arcsec²
struct LuxToMagConversionResult {
	float lux;															// Lux mesuré par le TSL2591
	double magnitude_arcsec2;											// Résultat final (mag/arcsec²)
	bool valid;
};

// Structure des données nécessaires pour la gestion du capteur de luminosité TSL2591
struct DataSensorLuminosity {
	float ir = NAN;														// Mesure de la luminosité dans l'IR
	float full = NAN;													// Mesure de la luminosité totale
	float visible = NAN;												// Mesure de la luminosité dans le visible
	float lux = NAN;													// Mesure de la quantité de Lux
	float luxThermalCorrected = NAN;									// Lux après correction thermique
	float luxAverage = NAN;												// Moyenne mobile du Lux sur TSL2591_MOVING_AVERAGE_COUNT valeurs
	int luxAverageCount = 0;											// Nombre de valeurs dans la queue pour le calcul de la moyenne mobile du Lux
	double sqm = NAN;													// Valeure calculée du SQM (Mag/Arcsec²)
	float bortle = NAN;													// Valeure du Bortle
	char  luxSensorGain[20];											// Gain du sensor
	char  luxSensorTiming[20];											// Temps d'exposition du sensor
};
