// Include des librairies
#include <SQMLITE_APP_CONFIG.h>

/// <summary>
/// Objet SQMLITE_DISPLAY_HOME : Objet applicatif permettant l'affichage du panneau Home
/// </summary>
class SQMLITE_DISPLAY_HOME
{
public:
    /// <summary>
    /// Constructeur
    /// </summary>
    SQMLITE_DISPLAY_HOME();

    /// <summary>
    /// Initialisation
    /// </summary>
    /// <param name="tft"></param>
    /// <param name="dataEnvironment"></param>
    /// <param name="dataLuminosity"></param>
    void Init(TFT_eSPI* tft,
                DataSensorEnvironment* dataEnvironment,
                DataSensorLuminosity* dataLuminosity);

    /// <summary>
    /// Actualisation de l'affichage
    /// </summary>
    void UpdateDisplay();

    /// <summary>
    /// Met à jour les variables de l'objet
    /// </summary>
    /// <param name="displayHomeType"></param>
    void SetCurrentDisplay(DISPLAY_HOME_TYPE displayHomeType);

    /// <summary>
    /// Force la mise à jour complète de l'affichage
    /// </summary>
    void ForceRedraw();

private:
    // Fonctions
    void ClearDisplay();
    void DisplayLux();
    void DisplayTemperature();
    void DisplayDewPoint();
    void DisplayBortle();
    void DisplaySensorValues();

    // Instanciation des objets internes
    TFT_eSPI* _tft;

    // Membres internes
    DISPLAY_HOME_TYPE _displayHomeType = DISPLAY_HOME_LUX;
    bool _forceRedraw = true;
    DataSensorEnvironment* _dataEnvironment;
    DataSensorLuminosity* _dataLuminosity;
    DEWPOINT_STATE _dewPointStateLast = DEWPOINT_STATE_UNKNOWN;
};