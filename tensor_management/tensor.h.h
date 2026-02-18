#ifndef TENSOR_H
#define TENSOR_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// 1. Veri Tipleri (Float16 simülasyonu için uint16_t kullanılır)
typedef enum {
    TENSOR_FLOAT32,
    TENSOR_FLOAT16,
    TENSOR_INT8
} TensorType;

// 2. Dinamik Tensör Yapısı
typedef struct {
    TensorType type;
    uint16_t rows;
    uint16_t cols;
    float scale;
    int8_t zero_point;

    union {
        float* f32;     // 4 Byte per element
        uint16_t* f16;  // 2 Byte per element (Half-precision)
        int8_t* i8;     // 1 Byte per element (Quantized)
    } data;
} Tensor;

// 3. Fonksiyon Prototipleri
Tensor* create_tensor(uint16_t rows, uint16_t cols);
void convert_to_float16(Tensor* t); // Yeni: Hassasiyeti azalt, belleği %50 koru
void quantize_to_int8(Tensor* t);   // Yeni: Max-Min tabanlı dinamik quantization
void agentic_optimize(Tensor* t);   // Yeni: Agentic karar mekanizması
void print_tensor(Tensor* t);
void free_tensor(Tensor* t);        // Yeni: Bellek sızıntısını önlemek için

#endif