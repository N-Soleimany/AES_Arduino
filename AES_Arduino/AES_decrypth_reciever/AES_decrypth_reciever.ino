#include <AES.h>
#include <SoftwareSerial.h>
#include <math.h>

#define blocksize 16

SoftwareSerial mySerial(10, 11); //RX, TX
AES aes;

//16 byte key
uint8_t aes_key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
//IV
uint8_t aes_iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

uint8_t cipherText[blocksize];
uint8_t decryptedText[blocksize];
uint8_t finaldata[blocksize*2]; 
uint8_t i = 0;

void readCipherText(uint8_t* buffer, size_t length);
void decryptAndStore(uint8_t* cipherText, uint8_t* decryptedText, uint8_t* finaldata, size_t offset);
void printFinalDecryptedData(uint8_t* data, size_t length);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available()){
    readCipherText(cipherText, blocksize);

    if (i < 2){
      decryptAndStore(cipherText, decryptedText, finaldata, i*blocksize);
      i++;
    }
  }

  if (i == 2){
    printFinalDecryptedData(finaldata, sizeof(finaldata));
    while (1); //stop after done decrypting
  }
}

void readCipherText(uint8_t* buffer, size_t length){
  for (int i = 0; i < length; i++){
    uint8_t hexData = mySerial.read();
    if(hexData != 0xff) {
      buffer[i] = hexData;
    }
    delay(50);
  }
}

void decryptAndStore(uint8_t* cipherText, uint8_t* decryptedText, uint8_t* finaldata, size_t offset){
  uint8_t iv[blocksize];
  memcpy(iv, aes_iv, blocksize);

  aes.do_aes_decrypt(cipherText, blocksize, decryptedText, aes_key, blocksize*8, iv);

  Serial.print("Decrypted text in stage ");
  Serial.print(offset / blocksize + 1);
  Serial.print(": ");
  for(uint8_t j = 0; j < blocksize; j++){
    Serial.print((char)decryptedText[j]);
    finaldata[offset + j] = decryptedText[j];
  }
  Serial.println();
}

void printFinalDecryptedData(uint8_t* data, size_t length){
  Serial.print("Final decrypted data: ");
  for(uint8_t i = 0; i < length; i++){
    Serial.print((char)data[i]);
  }
  Serial.println();
}
