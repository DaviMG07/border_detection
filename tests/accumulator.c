#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/matrix.h" // Assuming this library is available

typedef enum {
  NOP,
  CLN,
  IN,
  OUT
} OPCODE;

typedef struct {
  OPCODE op;
  int8_t values[2];
} Instruction;

typedef struct {
  int64_t accumulator;
  uint8_t data;
  uint8_t done;
} MAC;

void mac_status(MAC mac) {
  printf("accumulator: %d | data: %d | done: %d\n", mac.accumulator, mac.data, mac.done);
}

void mac_run(MAC* mac, Instruction instr) {
  if (instr.op == NOP) {
    mac->done = 0;
    return;
  }
  
  if (instr.op == CLN) {
    mac->accumulator = 0;
    mac->data        = 0;
    mac->done        = 1;
  }

  if (instr.op == IN) {
    mac->accumulator += (int64_t)instr.values[0] * (int64_t)instr.values[1];
    mac->done         = 1;
  }

  if (instr.op == OUT) {
    #define saturate(value) (value) > 255 ? 255 : (value) < 0 ? 0 : (value)
    mac->data = (uint8_t)(saturate(mac->accumulator));
    mac->done = 1;
  }
  mac_status(*mac);
}

void mac_clean(MAC* mac) {
  mac_run(mac, (Instruction){.op = CLN});
}

void mac_in(MAC* mac, int8_t a, int8_t b) {
  mac_run(mac, (Instruction){
    .op     = IN,
    .values = {a, b}
  });
}

uint8_t mac_out(MAC* mac) {
  mac_run(mac, (Instruction){
    .op = OUT
  });
  return mac->data;
}

uint8_t frobenius(MAC* mac, Matrix a, Matrix b) {
  mac_clean(mac);
  for (int i = 0; i < a.height; i++) {
    for (int j = 0; j < a.width; j++) {
      mac_in(mac, (int8_t)a.self[i][j], (int8_t)b.self[i][j]);
    }
  }
  return mac_out(mac);
}

int main() {
  MAC mac;
  mac_clean(&mac);
  Matrix *a, *b;
  int ra[5][5] = {
    {5, -17, 23, -8, 42},
    {-11, 3, -9, 31, -50},
    {29, -1, 45, -14, 7},
    {-33, 22, -16, 19, -2},
    {4, -13, 37, -25, 10}
  };
  int rb[5][5] = {
    {-88, 67, -91, 73, -55},
    {62, -99, 70, -58, 81},
    {-78, 52, -95, 66, -93},
    {60, -85, 76, -98, 51},
    {-89, 64, -96, 72, 83}
  };
  a = copy_reference(ra);
  b = copy_reference(rb);

  uint8_t result = frobenius(&mac, *a, *b);

  print_matrix(*a);
  print_matrix(*b);

  printf("%d\n", result);

  free_matrix(a);
  free_matrix(b);
  return 0;
}
