#include "../lib/includes.h"

// Armazena um valor em um registrador do coprocessador.
void store(int id, int row, int col, int value, Mpu* mpu) {
    *(mpu->data_in) = 2 | id << 3 | col << 4 | row << 7 | value << 10 | 1  << 18;
    while (!(*(mpu->data_out) & 0b10000000000)) {}
    *(mpu->data_in) = 0;
}

// Carrega um valor de um registrador do coprocessador.
int load(int row, int col, Mpu* mpu) {
    *(mpu->data_in) = 1 | col << 3 | row << 6;
    int done = 0;
    int data_out;
    while (!done) {
        data_out = *(mpu->data_out);
        done     = data_out & 1024;
        data_out &= 1023;
    }
    *(mpu->data_in) = 0;
    return data_out;
}

// Inicia a operação de convolução no coprocessador.
void conv(Mpu* mpu) {
    *(mpu->data_in) = 3;
    while (!(*(mpu->data_out) & 0b10000000000)) {}
    *(mpu->data_in) = 0;
}

// Inicializa a comunicação com o coprocessador.
Mpu* init_mpu() {
    Mpu* mpu = malloc(sizeof(Mpu));
    if (!mpu) {
        perror("ERROR: malloc for Mpu failed");
        return NULL;
    }

    if ((mpu->fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        free(mpu);
        return NULL;
    }

    mpu->lw_virtual_base = mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, mpu->fd, LW_BRIDGE_BASE);
    if (mpu->lw_virtual_base == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(mpu->fd);
        free(mpu);
        return NULL;
    }

    mpu->data_in  = (int*) (mpu->lw_virtual_base + DATA_IN_BASE);
    mpu->data_out = (int*) (mpu->lw_virtual_base + DATA_OUT_BASE);

    return mpu;
}

// Libera os recursos utilizados pelo coprocessador.
void cleanup_mpu(Mpu* mpu) {
    if (mpu) {
        munmap(mpu->lw_virtual_base, LW_BRIDGE_SPAN);
        close(mpu->fd);
        free(mpu);
    }
}

// Envia uma matriz para o coprocessador.
void send_matrix(int id, Matrix matrix, Mpu* mpu) {
    if (matrix.height != matrix.width || matrix.height != 5 || matrix.width != 5) return;
    for (int i = 4; i >= 0; i--) {
        for (int j = 4; j >= 0; j--) {
            store(id, i, j, (int)(unsigned char)matrix.self[i][j], mpu);
        }
    }
}

// Obtém um valor do coprocessador.
int get_value(int row, int col, Mpu* mpu) {
    return load(row, col, mpu);
}
