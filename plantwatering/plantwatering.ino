#include <bluefruit.h>

/* https://www.bluetooth.com/wp-content/uploads/Sitecore-Media-Library/Gatt/Xml/Services/org.bluetooth.service.automation_io.xml */
BLEService        ioservice = BLEService(0x1815);
/* https://www.bluetooth.com/xml-viewer/?src=https://www.bluetooth.com/wp-content/uploads/Sitecore-Media-Library/Gatt/Xml/Characteristics/org.bluetooth.characteristic.digital.xml */
BLECharacteristic iovalve = BLECharacteristic(0x2A56);

BLEDis bledis;    // DIS (Device Information Service) helper class instance

/* As defined by the standart this two bits values can take:
 *  0x0 -> Inactive
 *  0x1 -> Active
 *  0x2 -> Tri-state
 *  0x3 -> Output-state
 * In our case we will only use the two first states.
 */
static uint8_t output_ble_value = 0x0;

/* Pin to control
 *  https://cdn-learn.adafruit.com/assets/assets/000/046/248/original/microcontrollers_Feather_NRF52_Pinout_v1.2-1.png?1504885794
 * 7: connected to nothing else
 * LED_BUILTIN: onboard led
 */
uint16_t valve_pin = LED_BUILTIN;

void setup()
{
  Serial.begin(115200);

  Bluefruit.begin();

  Bluefruit.setName("Plantwatering");

  // Set the connect/disconnect callback handlers
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  bledis.setManufacturer("Plantwatering organization");
  bledis.begin();

  setupBLE();
  startAdv();
}

void startAdv(void)
{
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(ioservice);
  Bluefruit.Advertising.addName();

  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   *
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

void setupBLE(void)
{
  ioservice.begin();

  iovalve.setProperties(CHR_PROPS_READ |CHR_PROPS_WRITE | CHR_PROPS_NOTIFY);
  iovalve.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  iovalve.setFixedLen(1);
  iovalve.setWriteCallback(write_callback, false);
  iovalve.begin();

  // TODO (alex): get valve state and provide it to the bluetooth lib
  iovalve.write8(output_ble_value);
}

void connect_callback(uint16_t conn_handle)
{
  // Get the reference to current connection
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char central_name[32] = { 0 };
  connection->getPeerName(central_name, sizeof(central_name));

  Serial.print("Connected to ");
  Serial.println(central_name);
}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle connection where this event happens
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}

void write_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len)
{
  if (chr->uuid == iovalve.uuid) {
    Serial.print("Write callback: ");
    Serial.println(*data); // FIXME (aguyon): unsafe access
    iovalve.notify(data, len);
  }
}

void loop()
{
  digitalToggle(LED_RED);
  if ( Bluefruit.connected() ) {
    // Toggle last bit (0, 1) each seconds
    output_ble_value = (output_ble_value + 1) & 0x1;
    iovalve.notify(&output_ble_value, sizeof(output_ble_value));
    Serial.print("New valve value: ");
    Serial.println(output_ble_value);
  }
  delay(10000);
}
