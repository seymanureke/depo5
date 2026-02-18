#include "tensor.h"
#include <stdio.h>
#include <math.h>

Tensor* create_tensor(uint16_t rows, uint16_t cols) {
    Tensor* t = (Tensor*)malloc(sizeof(Tensor));
    t->type = TENSOR_FLOAT32;
    t->rows = rows;
    t->cols = cols;
    t->data.f32 = (float*)malloc(rows * cols * sizeof(float));
    return t;
}

// Float32 -> Float16 Dönüşümü (Basit cast simülasyonu)
void convert_to_float16(Tensor* t) {
    if (t->type != TENSOR_FLOAT32) return;
    size_t size = t->rows * t->cols;
    float* old_data = t->data.f32;
    uint16_t* new_data = (uint16_t*)malloc(size * sizeof(uint16_t));

    for (size_t i = 0; i < size; i++) {
        // Normalde bit kaydırma gerekir, burada temsili dönüşüm yapıyoruz
        new_data[i] = (uint16_t)(old_data[i]);
    }

    free(old_data);
    t->data.f16 = new_data;
    t->type = TENSOR_FLOAT16;
    printf("[System] Float16'ya donusturuldu. Bellek %%50 optimize edildi.\n");
}

// Gelişmiş Quantization (Dinamik Scale Hesabı)
void quantize_to_int8(Tensor* t) {
    if (t->type != TENSOR_FLOAT32) return;
    size_t size = t->rows * t->cols;
    float max_val = 0;
    for(size_t i=0; i<size; i++) if(fabs(t->data.f32[i]) > max_val) max_val = fabs(t->data.f32[i]);

    t->scale = max_val / 127.0f; // Dinamik scale
    t->zero_point = 0;
    int8_t* new_data = (int8_t*)malloc(size * sizeof(int8_t));

    for (size_t i = 0; i < size; i++) {
        new_data[i] = (int8_t)(t->data.f32[i] / t->scale);
    }

    free(t->data.f32);
    t->data.i8 = new_data;
    t->type = TENSOR_INT8;
    printf("[System] Int8 Quantization tamamlandi. Bellek %%75 optimize edildi.\n");
}

// AGENTIC KARAR MEKANIZMASI
void agentic_optimize(Tensor* t) {
    printf("[Agentic-AI] Veri yapisi ve bellek kısıtları analiz ediliyor...\n");
    size_t current_size = t->rows * t->cols * sizeof(float);

    // Senaryo: Eğer veri boyutu "kritik" ise otomatik sıkıştır
    if (current_size > 8) { // 8 byte'tan büyükse (Örnek eşik)
        printf("[Agentic-AI] Kritik bellek kullanimi tespit edildi! Otomatik Quantization uygulaniyor.\n");
        quantize_to_int8(t);
    } else {
        convert_to_float16(t);
    }
}

void print_tensor(Tensor* t) {
    printf("Veriler: ");
    for (int i = 0; i < t->rows * t->cols; i++) {
        if (t->type == TENSOR_FLOAT32) printf("%.2f ", t->data.f32[i]);
        else if (t->type == TENSOR_FLOAT16) printf("%u ", t->data.f16[i]);
        else printf("%d ", t->data.i8[i]);
    }
    printf("\n");
}

void free_tensor(Tensor* t) {
    if (t) {
        free(t->data.f32); // Union olduğu için herhangi birini free etmek yeterlidir
        free(t);
    }
}
