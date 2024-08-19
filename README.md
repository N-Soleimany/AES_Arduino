# Arduino AES Encryption and Decryption

This project demonstrates AES encryption and decryption using two Arduino boards. One Arduino encrypts and sends a message, while the other receives and decrypts it.

## Requirements

- Hardware: 2 Arduino boards, jumper wires, breadboard (optional)
- Software: Arduino IDE, AES library

## Setup

1. Connections:  
   - Sender: Pin 10 (TX) to Receiver Pin 11 (RX)
   - Receiver: Pin 10 (TX) to Sender Pin 11 (RX)
   - Common ground between both Arduinos

2. Code:
   - Upload the Encryption code to the sender Arduino.
   - Upload the Decryption code to the receiver Arduino.

## Usage

- Sender: Encrypts and transmits a text message.
- Receiver: Decrypts the message and displays it.

## Library

AESLib

