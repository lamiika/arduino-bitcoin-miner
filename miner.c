//#include <avr/io.h>
//#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//#define F_CPU 16000000UL  // CPU frequency
//#define UART_BAUD_RATE 9600
//#define UBRR_VALUE ((F_CPU + UART_BAUD_RATE * 8UL) / (UART_BAUD_RATE * 16UL) - 1UL)

typedef struct {
    int32_t version;
    uint8_t prev_block[32];
    uint8_t merkle_root[32];
    uint32_t timestamp;
    uint32_t difficulty_target;
    uint32_t nonce;
} BlockHeader;

void update_nonce(BlockHeader *header, uint32_t new_nonce) {
  header->nonce = new_nonce;
}

void uart_init();
void uart_transmit(uint8_t data);
void send_serialized_header(uint8_t *serialized_header, uint8_t length);

void uint32_to_bytes(uint32_t value, uint8_t *serialized_header, uint8_t *iterator);

void serialize(BlockHeader header, uint8_t *serialized_header);

void sha256_hash(uint8_t *serialized_header);

int main() {
//  uart_init();

  BlockHeader header;

  header.version = 1073733636;
  
  uint8_t prev_block[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xaa, 0x3c, 0xe0, 0x00, 0xeb, 0x55, 0x9f,
    0x41, 0x43, 0xbe, 0x41, 0x91, 0x08, 0x13, 0x4e,
    0x0c, 0xe7, 0x10, 0x42, 0xfc, 0x63, 0x6e, 0xb
  };
  memcpy(header.prev_block, prev_block, sizeof(header.prev_block));

  uint8_t merkle_root[] = {
    0x1f, 0x8d, 0x21, 0x3c, 0x86, 0x4b, 0xfe, 0x9f,
    0xb0, 0x09, 0x8c, 0xec, 0xc3, 0x16, 0x5c, 0xce,
    0x40, 0x7d, 0xe8, 0x84, 0x13, 0x74, 0x1b, 0x03,
    0x00, 0xd5, 0x6e, 0xa0, 0xf4, 0xec, 0x9c, 0x65
  };
  memcpy(header.merkle_root, merkle_root, sizeof(header.merkle_root));

  header.timestamp = 1631333672;
  header.difficulty_target = 0x170f48e4;
  header.nonce = 0;

  uint8_t serialized_header[80];

  serialize(header, serialized_header);

  for (int i = 0; i < 80; i++) {
    printf("%02X ", serialized_header[i]);
  }
  printf("\n");

//  screen /dev/ttyUSB0 9600
/*  while(1) {
    send_serialized_header(serialized_header, 80);
    _delay_ms(1000);
  }
*/
  return 0;
}

void uint32_to_bytes(uint32_t value, uint8_t *serialized_header, uint8_t *iterator) {
  serialized_header[(*iterator)++] = value & 0xFF;
  serialized_header[(*iterator)++] = (value >> 8) & 0xFF;
  serialized_header[(*iterator)++] = (value >> 16) & 0xFF;
  serialized_header[(*iterator)++] = (value >> 24) & 0xFF;
}

void serialize(BlockHeader header, uint8_t *serialized_header) {
  uint8_t iterator = 0;

  uint32_to_bytes(header.version, serialized_header, &iterator);

  for (int8_t i = 0; i < 1; i++) {
    serialized_header[iterator++] = header.prev_block[i];
  }

  for (int8_t i = 0; i < 1; i++) {
    serialized_header[iterator++] = header.merkle_root[i];
  }

  uint32_to_bytes(header.timestamp, serialized_header, &iterator);

  uint32_to_bytes(header.difficulty_target, serialized_header, &iterator);

  uint32_to_bytes(header.nonce, serialized_header, &iterator);
}

void sha256_hash(uint8_t *serialized_header) {

}

/*
void uart_init() {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));
    
    UDR0 = data;
}

void send_serialized_header(uint8_t *serialized_header, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        uart_transmit(serialized_header[i]);
    }
}
*/