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

uint8_t plainText[blocksize]; 
uint8_t cipherText[blocksize];
uint8_t unpacked[] = "HELLO its a test!";
const uint8_t dataPack = (uint8_t) ceil((double) (sizeof(unpacked)-1) / blocksize);
uint8_t i = 0;

void encryptAndSend(uint8_t* plainText, uint8_t* cipherText, const uint8_t* key, const uint8_t* iv);
void processEncryption();


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.print("Original text: ");
  for(uint8_t i = 0; i < sizeof(unpacked) - 1; i++){ 
    Serial.print((char)unpacked[i]);
  }
  Serial.println();
}

void loop() {
  processEncryption();
}

void encryptAndSend(uint8_t* plainText, uint8_t* cipherText, const uint8_t* key, const uint8_t* iv){
  uint8_t iv_copy[blocksize];
  memcpy(iv_copy, iv, blocksize);
  
  aes.do_aes_encrypt(plainText, blocksize, cipherText, key, blocksize*8, iv_copy);

  Serial.print("Cipher text stage ");
  Serial.print(i + 1);
  Serial.print(": ");
  for (uint8_t i = 0; i < blocksize; i++){  
    Serial.print(" 0x");
    Serial.print(cipherText[i], HEX); 
  }
  Serial.println();

  mySerial.write(cipherText, blocksize);
}

void processEncryption(){
  if(i < dataPack){
    memcpy(plainText, &unpacked[i*blocksize], blocksize*sizeof(uint8_t));
    encryptAndSend(plainText, cipherText, aes_key, aes_iv);
    delay(3000);
    i++;
  }
}
