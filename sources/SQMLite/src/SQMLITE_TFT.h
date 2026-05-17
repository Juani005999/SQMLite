#pragma once

// Include des librairies
#include <SQMLITE_DISPLAY_HEADER.h>
#include <SQMLITE_DISPLAY_HOME.h>
#include <SQMLITE_DISPLAY_LUX.h>
#include <SQMLITE_DISPLAY_ENVIRONMENT.h>

/// <summary>
/// Objet SQMLITE_TFT : Objet applicatif permettant le pilotage de l'écran TFT
/// </summary>
class SQMLITE_TFT
{
  public:
    /// <summary>
    /// Constructeur
    /// </summary>
    SQMLITE_TFT();

    /// <summary>
    /// Initialisation
    /// </summary>
    /// <param name="dataEnvironment"></param>
    /// <param name="dataLuminosity"></param>
    /// <param name="bluetoothConnected"></param>
    void Init(DataSensorEnvironment* dataEnvironment,
                DataSensorLuminosity* dataLuminosity,
                bool* bluetoothConnected);

    /// <summary>
    /// Affichage de l'écran d'initialisation de l'application
    /// </summary>
    void DisplaySplashApp();

    /// <summary>
    /// Actualisation de l'affichage
    /// </summary>
    void UpdateDisplay();

    /// <summary>
    /// Force la mise à jour complète de l'affichage
    /// </summary>
    void ForceRedraw();

    /// <summary>
    /// Met à jour l'affichage en cours
    /// </summary>
    /// <param name="currentDisplayScreenType"></param>
    /// <param name="displayHomeType"></param>
    void SetCurrentDisplay(DISPLAY_SCREEN_TYPE currentDisplayScreenType, DISPLAY_HOME_TYPE displayHomeType);

    /// <summary>
    /// Affiche l'icone d'état de lecture de la luminosité
    /// </summary>
    void SetLuminosityIcon(bool on = false);

  private:
    // Fonctions

    // Instanciation des objets internes
    TFT_eSPI _tft = TFT_eSPI();                                                         // Ecran TFT SD7735
    SQMLITE_DISPLAY_HEADER _displayHeader = SQMLITE_DISPLAY_HEADER();                   // Objet pour l'affichage du Header
    SQMLITE_DISPLAY_HOME _displayHome = SQMLITE_DISPLAY_HOME();                         // Objet pour l'affichage du panneau Home
    SQMLITE_DISPLAY_LUX _displayLux = SQMLITE_DISPLAY_LUX();                            // Objet pour l'affichage du panneau Lux
    SQMLITE_DISPLAY_ENVIRONMENT _displayEnvironment = SQMLITE_DISPLAY_ENVIRONMENT();    // Objet pour l'affichage du panneau Environnement

    // Membres internes
    DISPLAY_SCREEN_TYPE _currentDisplayScreenType = DISPLAY_HOME;
    DISPLAY_SCREEN_TYPE _lastDisplayScreenType = DISPLAY_HOME;
    DISPLAY_HOME_TYPE _displayHomeType = DISPLAY_HOME_LUX;
    DataSensorEnvironment* _dataEnvironment;
    DataSensorLuminosity* _dataLuminosity;
    bool* _bluetoothConnected;

    // Chronos
    long _chronoDisplay;
};