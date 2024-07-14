void setup() {

pinMode(13,OUTPUT);   //left motors forward

pinMode(12,OUTPUT);   //left motors reverse

pinMode(11,OUTPUT);   //right motors forward

pinMode(10,OUTPUT);   //right motors reverse

pinMode(9,OUTPUT);   //Led

Serial.begin(9600);

 

}

 

void loop() {

if(Serial.available()){

  t = Serial.read();

  Serial.println(t);

}

 

if(t == 'F'){            //move forward(all motors rotate in forward direction)

  digitalWrite(13,HIGH);

  digitalWrite(11,HIGH);

}

 

else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)

  digitalWrite(12,HIGH);

  digitalWrite(10,HIGH);

}

 

else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)

  digitalWrite(11,HIGH);

}

 

else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)

  digitalWrite(13,HIGH);

}



else if(t == 'W'){    //turn led on or off)

  digitalWrite(9,HIGH);

}

else if(t == 'w'){

  digitalWrite(9,LOW);

}

 

else if(t == 'S'){      //STOP (all motors stop)

  digitalWrite(13,LOW);

  digitalWrite(12,LOW);

  digitalWrite(11,LOW);

  digitalWrite(10,LOW);

}

delay(100);

}







.................................................................RFID Code...........................................................................





 #include <SPI.h>

#include <MFRC522.h>



#define RST_PIN         9           // Configurable, see typical pin layout above

#define SS_PIN          10          // Configurable, see typical pin layout above



MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.



String read_rfid;                   // Add how many you need and don't forget to include the UID.

String ok_rfid_1="f9a112e8";        // This is for my main RFID Card. aka. The one I will be using to turn on my PC. Can also be used to shut it down if you want to.

String ok_rfid_2="19e3c1b1";        // This is for the RFID Keyfob. aka. Shutdown Keyfob. Not advisable tho. Just shutdown your PC normally.

int lock = 7;                       // For the Card.

int lock2 = 7;                      // For the Keyfob.

/*

 * Initialize.

 */

void setup() {

    Serial.begin(9600);         // Initialize serial communications with the PC

    while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

    SPI.begin();                // Init SPI bus

    mfrc522.PCD_Init();         // Init MFRC522 card



    //Choose which lock below:

    pinMode(lock, OUTPUT);

    pinMode(lock2, OUTPUT);

}

/*

 * Helper routine to dump a byte array as hex values to Serial.

 */

void dump_byte_array(byte *buffer, byte bufferSize) {

    read_rfid="";

    for (byte i = 0; i < bufferSize; i++) {

        read_rfid=read_rfid + String(buffer[i], HEX);

    }

}



void open_lock() {

  //Use this routine when working with Relays and Solenoids etc.

  digitalWrite(lock,HIGH);

  delay(500);

  digitalWrite(lock,HIGH);

}





void close_lock2() {          // You can also just use the card to shutdown your PC. This is just for those moments that you really need to shut it down quickly. 

  //Use this routine when working with Relays and Solenoids etc.

  digitalWrite(lock2, LOW);

  delay(5000);                

  digitalWrite(lock2,LOW);

}





void loop() {



      // Look for new cards

    if ( ! mfrc522.PICC_IsNewCardPresent())

        return;



    // Select one of the cards

    if ( ! mfrc522.PICC_ReadCardSerial())

        return;



    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

    Serial.println(read_rfid);

    if (read_rfid==ok_rfid_1) {

      //ok, open the door.

      open_lock();

    }



    Serial.println(read_rfid);

    if (read_rfid==ok_rfid_2) {

      //ok, open the door.

      close_lock2();

    }

    //Add below as many "keys" as you want

    //if (read_rfid==ok_rfid_2) {

      //also ok, open the door

    //  open_lock();

    //}

    // else not needed. Anything else is not ok, and will not open the door...

}
