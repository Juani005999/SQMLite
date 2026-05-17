// Include des librairies
#include <SQMLITE_APP_CONFIG.h>

/// <summary>
/// Objet SQMLITE_DISPLAY_HEADER : Objet applicatif permettant l'affichage du header
/// </summary>
class SQMLITE_DISPLAY_HEADER
{
  public:
    /// <summary>
    /// Constructeur
    /// </summary>
    SQMLITE_DISPLAY_HEADER();

    /// <summary>
    /// Initialisation
    /// </summary>
    /// <param name="tft"></param>
    /// <param name="dataEnvironment"></param>
    /// <param name="bluetoothConnected"></param>
    void Init(TFT_eSPI * tft, DataSensorEnvironment* dataEnvironment, bool* bluetoothConnected);

    /// <summary>
    /// Actualisation de l'affichage
    /// </summary>
    void UpdateDisplay();

    /// <summary>
    /// Met à jour l'affichage en cours
    /// </summary>
    /// <param name="currentDisplayScreenType"></param>
    void SetCurrentDisplay(DISPLAY_SCREEN_TYPE currentDisplayScreenType);

    /// <summary>
    /// Force la mise à jour complète de l'affichage
    /// </summary>
    void ForceRedraw();

    /// <summary>
    /// Affiche l'icone d'état de lecture de la luminosité
    /// </summary>
    /// <param name="on"></param>
    void SetLuminosityIcon(bool on = false);

  private:
    // Fonctions
    void ClearDisplay();
    void DisplayMainIcon();
    void DisplayTitle();
    void DisplayBluetoothIcon();

    // Instanciation des objets internes
    TFT_eSPI * _tft;

    // Membres internes
    DISPLAY_SCREEN_TYPE _currentDisplayScreenType = DISPLAY_HOME;
    bool _forceRedraw = true;
    DataSensorEnvironment* _dataEnvironment;
    bool* _bluetoothConnected;
    bool _iconBluetoothLastState = false;
    bool firstLuminosityIcon = true;
    bool lastLuminosityIconState = false;
};