#pragma once

// Include des Objets et Librairies
#include <SQMLITE_APP_CONFIG.h>
#include <SQMLITE_BME280.h>
#include <SQMLITE_TSL2591.h>
#include <SQMLITE_BLE.h>
#include <SQMLITE_TFT.h>


/// <summary>
/// Objet SQMLITE_APP : Objet applicatif permettant le pilotage complet de l'application SQMLITE_APP
/// </summary>
class SQMLITE_APP : JUANITO_APP
{
  public:
    /// <summary>
    /// Constructeur
    /// </summary>
    SQMLITE_APP();

    /// <summary>
    /// Initialisation de l'application
    /// </summary>
    void Init();

    /// <summary>
    /// Traitements cadencés
    /// </summary>
    void Loop();

  private:
    // Fonctions
    void ReadJoystickState();
    void UpdateCurrentDisplay();

    // Instanciation des objets internes
    SQMLITE_BME280 _bme280 = SQMLITE_BME280();
    SQMLITE_TSL2591 _tsl2591 = SQMLITE_TSL2591();
    SQMLITE_BLE _bluetoothLE = SQMLITE_BLE();
    SQMLITE_TFT _tft = SQMLITE_TFT();

    // Membres internes
    DISPLAY_SCREEN_TYPE _currentDisplayScreenType = DISPLAY_HOME;           // Ecran d'affichage courant
    ACTION_TYPE _currentAction = ACTION_NONE;                               // Action en cours
    DISPLAY_HOME_TYPE _displayHomeType = DISPLAY_HOME_LUX;                  // Mode d'affichage de l'écran Home
    DataSensorEnvironment _dataEnvironment;                                 // Données relatives au capteur d'envitonnement BME280
    DataSensorLuminosity _dataLuminosity;                                   // Données relatives au cateur de luminosité TSL2591
    bool  _bluetoothConnected = false;                                      // Flag de connexion Bluetooth
    bool _joystickPressed;                                                  // Flag de clic sur le switch du Joystick
    bool _joystickMoved;                                                    // Flag de mouvement du Joystick

    // Chronos
    long _chronoReadJoystick;                                               // Chrono pour lecture de l'état du Joystick
    long _chronoJoystickButtonPressed;                                      // Chrono de début de clic sur le switch du Joystick
    long _chronoDisplayTimeout;                                             // Chrono de gestion de la mise en veille de l'affichage
};