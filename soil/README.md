# Soil Sensor

## Use
We have implemented a teensy 2.0 arduino demo of reading the sensor. See soil_arduino. 
Next task is to port that to the NAVQ+.

## RS485 Soil Protocol 
* 8 bit, no parity, 1 stop bit, CRC, 9600 bps
* Address Code 0x01
* Function Code 0x03 

### Inquiry Frame
* 1 byte - Address Code
* 1 byte - Function Code
* 2 byte - Register Start Address 
* 2 byte - Register Length
* 1 byte - CRC L
* 1 byte - CRC H

### Answer Frame
* 1 byte - Address Code
* 1 byte - Function Code
* 2 byte - Effective Number of Bytes
* 2 byte - Data Area
* 2 byte - Second Data area   
* 2 byte - Nth Data Area 
* 2 byte - Check Code

### Register Addresses
* Reg Addr, PLC or Config Addr, Content, Operation
* 0006H, 40007(40007), PH values (unit 0.01pH), RO
* 0012H, 40013(40019), Soil Moisture(unit 0.1% RH), RO
* 0013H, 40014(40020), Soil Temp (unit 0.1 deg C, signed), RO
* 0015H, 40016(40022), Soil Conductivity (unit 1us/cm), RO
* 001EH, 4001F(40031), Soil Nitrogen (unit mg/kg), RO
* 001FH, 40020(40032), Soil Phosphorus (unit mg/kg), RO
* 0020H, 40021(40033), Soil Potassium (unit mg/kg), RO
* 0100H, 40101(40257), Equipment Address (0-255), RW
* 0101H, 40102(40258), Baud Rate (2400/4800/9600), RW

### Example Read Temperature (-10.1C)  and Humidity (RH 65.8%)
#### Inquiry Frame
* 0x01 - 1 byte - Address Code
* 0x03 - 1 byte - Function Code
* 0x00 0x12 - 2 byte - Register Start Address 
* 0x00 0x02 - 2 byte - Register Length - Number of Registers to Read 
* 0x65 - 1 byte - CRC L
* 0xCB - 1 byte - CRC H

#### Answer Frame
* 0x01 - 1 byte - Address Code
* 0x03 - 1 byte - Function Code
* 0x04 - 2 byte - Effective Number of Bytes
* 0x02 0x92 - 2 byte - Data Area - Humidity
* 0xFF 0x9B - 2 byte - Second Data area   
* 0x5A 0x3D - 2 byte - Check Code

