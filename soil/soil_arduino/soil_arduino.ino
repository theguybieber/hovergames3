#define SOFT_SERIAL 1
#define MOD_BUS 2
#define NEW_SOFT_SERIAL 3
#define HARDWARE_SERIAL 4
#define MODE HARDWARE_SERIAL
#include <CRCx.h>
//using namespace crcx;
#if MODE == MOD_BUS // haven't tested
  #include <ArduinoRS485.h>
  #include <ArduinoModbus.h>
#elif MODE == SOFT_SERIAL // available does not work
  #include <SoftwareSerial.h>
#elif MODE == NEW_SOFT_SERIAL // consumes lotso resources
  #include <NewSoftSerial.h>
#elif MODE == HARDWARE_SERIAL
  #include <HardwareSerial.h>
#endif

//#define RS485_DE 2     // RS485 driver enable pin
//#define RS485_RE_NEG 3 // RS485 receiver enable pin

// Teensy 2.0 D2 and D3
// PD2 is RXD1
// PD3 is TXD1
//SoftwareSerial RS485Serial(10, 11); // RX, TX
//#define HWSERIAL Serial1 
#if MODE == SOFT_SERIAL
  SoftwareSerial mySerial(8,7); // 7. 8 default
#elif MODE == NEW_SOFT_SERIAL
  NewSoftSerial mySerial(8,7);
#elif MODE == HARDWARE_SERIAL
  HardwareSerial mySerial = Serial1;
#endif

const int BAUDRATE = 9600;
const uint8_t ADDRESS = 0x01;
const uint8_t FUNCTION = 0x03;
//TODO make this an array of structs so we can parse through it
//Reg Addr, PLC or Config Addr, Content, Operation
//0006H, 40007(40007), PH values (unit 0.01pH), RO
const uint16_t SOIL_PH_REG = 0x0006;
const float SOIL_PH_MULT = 0.01;
const char *SOIL_PH_UNIT = "pH";
float soilPH = 0.0;
//0012H, 40013(40019), Soil Moisture(unit 0.1% RH), RO
const uint16_t SOIL_MOISTURE_REG = 0x0012;
const float SOIL_MOISTURE_MULT = 0.1;
const char *SOIL_MOISTURE_UNIT = "RH";
float soilMoisture = 0.0;
//0013H, 40014(40020), Soil Temp (unit 0.1 deg C, signed), RO
const uint16_t SOIL_TEMP_REG = 0x0013;
const float SOIL_TEMP_MULT = 0.1;
const char *SOIL_TEMP_UNIT = "deg C";
float soilTemp = 0.0;
//0015H, 40016(40022), Soil Conductivity (unit 1us/cm), RO
const uint16_t SOIL_CONDUCTIVITY_REG = 0x0015;
const float SOIL_CONDUCTIVITY_MULT = 1.0;
const char *SOIL_CONDUCTIVITY_UNIT = "1us/cm";
float soilConductivity = 0.0;
//001EH, 4001F(40031), Soil Nitrogen (unit mg/kg), RO
const uint16_t SOIL_NITROGEN_REG = 0x001E;
const float SOIL_NITROGEN_MULT = 1.0;
const char *SOIL_NITROGEN_UNIT = "mg/kg";
float soilNitrogen = 0.0;
//001FH, 40020(40032), Soil Phosphorus (unit mg/kg), RO
const uint16_t SOIL_PHOSPHORUS_REG = 0x001F;
const float SOIL_PHOSPHORUS_MULT = 1.0;
const char *SOIL_PHOSPHORUS_UNIT = "mg/kg";
float soilPhosphorus = 0.0;
//0020H, 40021(40033), Soil Potassium (unit mg/kg), RO
const uint16_t SOIL_POTASSIUM_REG = 0x0020;
const float SOIL_POTASSIUM_MULT = 1.0;
const char *SOIL_POTASSIUM_UNIT = "mg/kg";
float soilPotassium = 0.0;
//0100H, 40101(40257), Equipment Address (0-255), RW
//0101H, 40102(40258), Baud Rate (2400/4800/9600), RW

// REQUEST
const int REQ_LENGTH = 8;
const int REQ_REG_START = 2;
const int REQ_SIZE_START = 4;
const int REQ_CHECKSUM_START = 6; 
//uint8_t request[REQ_LENGTH] = { ADDRESS, FUNCTION, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 }; 
uint8_t request[REQ_LENGTH] = { ADDRESS, FUNCTION, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 }; 
//uint8_t request[REQ_LENGTH] = { ADDRESS, FUNCTION, 0x00, 0x1c, 0x00, 0x01, 0xB5, 0xCC }; 

// RESPONSE
const int RESP_LENGTH = 7;
const int RESP_BYTES = 2;
const int RESP_DATA = 3;
const int RESP_CHECKSUM = 5;
uint8_t response[RESP_LENGTH] = { ADDRESS, FUNCTION, 0x02, 0x00, 0x00, 0x00, 0x00 }; 

uint16_t calcCRC(uint8_t body[], int len)
{
    uint16_t crc=crcx::crc16(body,len,crcx::Crc16::MODBUS);
    return crc;
}

void buildRequest (uint16_t reg) {
    request[REQ_REG_START] = uint8_t(reg >> 8);
    request[REQ_REG_START+1] = uint8_t(reg & 0x00FF);
    uint16_t crc = calcCRC(request, 6); 
    request[REQ_CHECKSUM_START] = uint8_t(crc & 0x00FF);
    request[REQ_CHECKSUM_START+1] = uint8_t(crc >> 8);
}

void txRequest() {
    Serial.print("txRequest:  ");
    for (int i = 0 ; i < REQ_LENGTH ; i++) {
        #if MODE == SOFT_SERIAL 
          mySerial.write(request[i]);
        #elif MODE == HARDWARE_SERIAL
          mySerial.write(request[i]);
        #endif 
        Serial.printf("%02X ", request[i]);
        //while (HWSERIAL.availableForWrite() == 0) ; 
        //HWSERIAL.write(request[i]); 
    }
    Serial.println("");    
}

void rxResponse() {
    Serial.print("rxResponse: ");
    //mySerial.listen();
    for (int i = 0 ; i < RESP_LENGTH ; i++) {
        #if MODE == SOFT_SERIAL
          while (mySerial.available() == 0 ) ;
          response[i] = (uint8_t)mySerial.read();
        #elif MODE == HARDWARE_SERIAL
          while (mySerial.available() == 0 ) ;
          response[i] = (uint8_t)mySerial.read();
        #elif MODE == MODBUS
 
        #endif  
        Serial.printf("%02X ", response[i]);
        //while (HWSERIAL.available() == 0) ; 
        //response[i] = (uint8_t)HWSERIAL.read(); 
    }
    Serial.println("");
}

uint16_t makeRequest (uint16_t reg) {
    // make the serial request and return the register
    buildRequest(reg);
    txRequest();
    rxResponse();
    uint16_t val = (response[RESP_DATA] << 8) + response[RESP_DATA+1];
    delay (50);
    return val;
}

void sampleSoil() {

    soilPH = (float) makeRequest(SOIL_PH_REG) * SOIL_PH_MULT; 

    soilMoisture = (float) makeRequest(SOIL_MOISTURE_REG) * SOIL_MOISTURE_MULT; 

    soilTemp = (float) ((int16_t) makeRequest(SOIL_TEMP_REG)) * SOIL_TEMP_MULT; 

    soilConductivity = (float) makeRequest(SOIL_CONDUCTIVITY_REG) * SOIL_CONDUCTIVITY_MULT; 

    soilNitrogen = (float) makeRequest(SOIL_NITROGEN_REG) * SOIL_NITROGEN_MULT;

    soilPhosphorus = (float) makeRequest(SOIL_PHOSPHORUS_REG ) * SOIL_PHOSPHORUS_MULT;
    
    soilPotassium = (float) makeRequest(SOIL_POTASSIUM_REG ) * SOIL_POTASSIUM_MULT;

}

void printSoilSample() {
    Serial.print("Soil pH: ");
    Serial.print(soilPH);
    Serial.print(" ");
    Serial.println(SOIL_PH_UNIT);
    Serial.print("Soil Moisture: ");
    Serial.print(soilMoisture);
    Serial.print(" ");
    Serial.println(SOIL_MOISTURE_UNIT);
    Serial.print("Soil Temperature: ");
    Serial.print(soilTemp);
    Serial.print(" ");
    Serial.println(SOIL_TEMP_UNIT);
    Serial.print("Soil Conductivity: ");
    Serial.print(soilConductivity);
    Serial.print(" ");
    Serial.println(SOIL_CONDUCTIVITY_UNIT);
    Serial.print("Soil Nitrogen: ");
    Serial.print(soilNitrogen);
    Serial.print(" ");
    Serial.println(SOIL_NITROGEN_UNIT);
    Serial.print("Soil Phosphorus: ");
    Serial.print(soilPhosphorus);
    Serial.print(" ");
    Serial.println(SOIL_PHOSPHORUS_UNIT);
    Serial.print("Soil Potassium: ");
    Serial.print(soilPotassium);
    Serial.print(" ");
    Serial.println(SOIL_POTASSIUM_UNIT);
}

void setup() {
    Serial.begin(BAUDRATE);
    while (!Serial);

    // start the Modbus RTU client
    //HWSERIAL.begin(BAUDRATE);
    #if MODE == SOFT_SERIAL
      mySerial.begin(BAUDRATE);
    #elif MODE == HARDWARE_SERIAL
      mySerial.begin(BAUDRATE,7);
    #elif MODE == MOD_BUS 
      if (!ModbusRTUClient.begin(BAUDRATE)) {
        Serial.println("Failed to start Modbus RTU Client!");
        while (1);
      }
    #endif 
    //HWSERIAL.begin(BAUDRATE);
    //RS485Serial.begin(BAUDRATE);
}

void loop() {
  sampleSoil();
  printSoilSample();

  delay(2000); // wait for next reading
}

