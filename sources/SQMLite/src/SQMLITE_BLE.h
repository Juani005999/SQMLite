#pragma once

// Include des librairies
#include <SQMLITE_APP_CONFIG.h>

/// <summary>
/// Objet SQMLITE_BLE : Objet applicatif permettant la gestion de la communication via Bluetooth Low Energy (BLE)
/// </summary>
class SQMLITE_BLE
{
  public:
    /// <summary>
    /// Constructeur
    /// </summary>
    SQMLITE_BLE();

    /// <summary>
    /// Initialisation
    /// </summary>
    /// <param name="bluetoothConnected"></param>
    /// <param name="dataEnvironment"></param>
    /// <param name="dataLuminosity"></param>
    /// <param name="dataSkyState"></param>
    void Init(bool* bluetoothConnected, DataSensorEnvironment* dataEnvironment, DataSensorLuminosity* dataLuminosity);

    /// <summary>
    /// Update des caractéristiques BLE et Notification aux clients BLE
    /// </summary>
    void Notify();

  private:
    // Fonctions

    // Instanciation des objets internes
    BLEServer* _bleServer = NULL;
    BLEService* _bleService = NULL;
    BLECharacteristic* _bleCharacteristicTemperature;
    BLECharacteristic* _bleCharacteristicHumidity;
    BLECharacteristic* _bleCharacteristicPressure;
    BLECharacteristic* _bleCharacteristicDewPoint;
    BLECharacteristic* _bleCharacteristicSkyBrightness;
    BLECharacteristic* _bleCharacteristicSkyQuality;

    // Membres internes
    String _deviceName = BLE_DEVICE_NAME;
    DataSensorEnvironment* _dataEnvironment;
    DataSensorLuminosity* _dataLuminosity;
    bool* _bluetoothConnected;
    char characteristicBuffer[128];

    // Chronos
    long _chronoReadBluetoothLE;                                               // Chrono pour lecture de l'état du Bluetooth
};