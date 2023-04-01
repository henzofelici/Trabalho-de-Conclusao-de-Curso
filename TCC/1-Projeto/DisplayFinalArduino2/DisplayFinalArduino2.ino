/* -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */
#include <EasyNextionLibrary.h>
#include <trigger.h>
#include <Servo.h>
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurável, veja o layout típico dos pinos acima
#define SS_PIN          10          // Configurável, veja o layout típico dos pinos acima

bool flag = false;
EasyNex d = EasyNex(Serial);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria instância MFRC522.

Servo meuservo; // Cria o objeto servo para programação 
int angulo = 0; // Ajusta o ângulo inicial do Servo 

String read_rfid;                   // Adicione quantos você precisa e não esqueça de incluir o UID.
String ok_rfid_1="339d4616";        // Isto é para o meu cartão RFID principal. também conhecido como O que vou usar para ligar o meu PC. Também pode ser usado para desligá-lo, se você quiser.
String ok_rfid_2="436e1f15";        // Isto é para o chaveiro RFID. também conhecido como Desligue o chaveiro. Não é aconselhável. Basta desligar o PC normalmente.
int lock = 8;                       // Para o cartão.
int lock2 = 8;                      // Para o chaveiro.

void setup() {
   Serial.begin(9600);         // Initialize serial communications with the PC
    while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();                // Init SPI bus
    mfrc522.PCD_Init();         // Init MFRC522 card

    //Escolha qual bloqueio abaixo:
    pinMode(lock, OUTPUT);
    pinMode(lock2, OUTPUT);
    
  d.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  meuservo.attach(4);
}

         //RFID
 /*
* Rotina auxiliar para despejar uma matriz de bytes como valores hexadecimais para Serial.
*/
void dump_byte_array(byte *buffer, byte bufferSize) {
    read_rfid="";
    for (byte i = 0; i < bufferSize; i++) {
        read_rfid=read_rfid + String(buffer[i], HEX);
    }
}

void open_lock() {
  //Use esta rotina ao trabalhar com Relés e Solenóides etc.
  digitalWrite(lock,HIGH);
 
}


void close_lock2() {          
  //Use esta rotina ao trabalhar com Relés e Solenóides etc.          
  digitalWrite(lock2,LOW);
}


void loop() {
d.NextionListen();
      // Procura por novos cartões
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    //Selecione uma das cartas
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    delay(1500);
    Serial.println(read_rfid);
    if(!flag)
    {
      if (read_rfid==ok_rfid_1 || read_rfid==ok_rfid_2) {
        //ok, abra a porta.
        //delay(1000);
        open_lock();
        flag = true;
      }
    }
    else{
          Serial.println(read_rfid);
          if (read_rfid==ok_rfid_2 || read_rfid==ok_rfid_1) {
           //ok, abra a porta.
         // delay(1000);
            close_lock2();
            flag=false;
          }
    }


    //Adicione abaixo quantas "chaves" desejar
    //if (read_rfid==ok_rfid_2) {
      //Também ok, abre a porta
    // open_lock();
    ///}
    // mais não é necessário. Qualquer outra coisa não está bem, e não vai abrir a porta...
}

        //tela
void trigger0(){
  digitalWrite(7,HIGH);
}
void trigger1(){
  digitalWrite(7,LOW);
}

void trigger4(){
  digitalWrite(6,HIGH);
}
void trigger5(){
  digitalWrite(6,LOW);
}

void trigger6(){
  digitalWrite(5,HIGH);

}
void trigger7(){
  digitalWrite(5,LOW);
}

void trigger8(){
  digitalWrite(3,HIGH);

}
void trigger9(){
  digitalWrite(3,LOW);
}

void trigger10(){
  digitalWrite(2,HIGH);

}
void trigger11(){
  digitalWrite(2,LOW);
}


void trigger3(){
 for (angulo = 110; angulo >= 1; angulo -= 5) { // Comando que muda a posição do servo de 180 para 0°
meuservo.write(angulo); // Comando para angulo específico
delay(150);
}
}
void trigger2(){
  meuservo.write(155); 
  delay(500);
}
