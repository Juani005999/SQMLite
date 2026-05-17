#include <SQMLITE_DISPLAY_HEADER.h>

/// <summary>
/// Constructeur
/// </summary>
SQMLITE_DISPLAY_HEADER::SQMLITE_DISPLAY_HEADER()
{
}

/// <summary>
/// Initialisation
/// </summary>
/// <param name="tft"></param>
/// <param name="dataEnvironment"></param>
/// <param name="bluetoothConnected"></param>
void SQMLITE_DISPLAY_HEADER::Init(TFT_eSPI* tft, DataSensorEnvironment* dataEnvironment, bool* bluetoothConnected)
{
	// Valorisation des objets internes
	_tft = tft;
	_dataEnvironment = dataEnvironment;
	_bluetoothConnected = bluetoothConnected;
}

/// <summary>
/// Met à jour les variables de l'objet
/// </summary>
/// <param name="currentDisplayScreenType"></param>
void SQMLITE_DISPLAY_HEADER::SetCurrentDisplay(DISPLAY_SCREEN_TYPE currentDisplayScreenType)
{
	// Actualisation des membres internes
	_currentDisplayScreenType = currentDisplayScreenType;
}

/// <summary>
/// Force la mise à jour complète de l'affichage
/// </summary>
/// <param name="forceRedraw"></param>
void SQMLITE_DISPLAY_HEADER::ForceRedraw()
{
	// Actualisation des membres internes
	_forceRedraw = true;
}

/// <summary>
/// Actualisation de l'affichage
/// </summary>
void SQMLITE_DISPLAY_HEADER::UpdateDisplay()
{
	// On clear l'affichage
	ClearDisplay();

	// Affichage des données
	DisplayMainIcon();
	DisplayTitle();
	DisplayBluetoothIcon();

	// Reset de la mise à jour complète de l'affichage
	_forceRedraw = false;
}

/// <summary>
/// Clear de l'affichage du Header
/// </summary>
void SQMLITE_DISPLAY_HEADER::ClearDisplay()
{
	if (_forceRedraw)
	{
		// Background et cadre
		_tft->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HDR_HEIGHT, TFT_WHITE);
		_tft->drawRect(0, 0, SCREEN_WIDTH, SCREEN_HDR_HEIGHT, TFT_SILVER);

		// Contour de l'icone de luminosité
		_tft->drawCircle(130, 16, 8, TFT_MAROON);
		SetLuminosityIcon(lastLuminosityIconState);
	}
}

/// <summary>
/// Affichage de l'icone principal
/// </summary>
void SQMLITE_DISPLAY_HEADER::DisplayMainIcon()
{
	if (_forceRedraw)
	{
		_tft->setSwapBytes(true);
		switch (_currentDisplayScreenType)
		{
		case DISPLAY_LUX:
			_tft->pushImage(5, 5, 20, 20, icon_ampoule);
			break;

		case DISPLAY_ENVIRONMENT:
			_tft->pushImage(5, 5, 20, 20, icon_thermometre);
			break;

		case DISPLAY_HOME:
		default:
			_tft->pushImage(5, 5, 20, 20, icon_home);
			break;
		}
	}
}

/// <summary>
/// Affichage le titre de l'application
/// </summary>
void SQMLITE_DISPLAY_HEADER::DisplayTitle()
{
	if (_forceRedraw)
	{
		// Mise en forme de l'affichage
		_tft->setTextColor(TFT_BLACK, TFT_WHITE);
		_tft->setTextSize(1);
		_tft->setTextFont(TFT_FONT_TITLE);

		// Affichage du titre
		_tft->setCursor(40, 8);
		_tft->print(F("SQM Lite"));

		// On repositionne la Font initiale
		_tft->setTextFont(TFT_FONT_DEFAULT);
	}
}

/// <summary>
/// Affichage de l'icone Bluetooth
/// </summary>
void SQMLITE_DISPLAY_HEADER::DisplayBluetoothIcon()
{
	// On vérifie l'état de l'icone a afficher
	bool iconState = *_bluetoothConnected;

	if (_forceRedraw
		|| iconState != _iconBluetoothLastState)
	{
		_tft->setSwapBytes(true);
		_tft->pushImage(140, 8, 16, 16, *_bluetoothConnected ? icon_bluetooth_green : icon_bluetooth_red);
	}
	_iconBluetoothLastState = iconState;
}

/// <summary>
/// Affiche l'icone d'état de lecture de la luminosité
/// </summary>
/// <param name="on"></param>
void SQMLITE_DISPLAY_HEADER::SetLuminosityIcon(bool on)
{
	if (!firstLuminosityIcon && _currentDisplayScreenType != DISPLAY_NONE)
	{
		_tft->drawCircle(130, 16, 8, TFT_MAROON);
		_tft->fillCircle(130, 16, 6, on ? TFT_ORANGE : TFT_WHITE);
	}
	lastLuminosityIconState = on;
	firstLuminosityIcon = false;
}
