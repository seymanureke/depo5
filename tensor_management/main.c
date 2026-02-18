#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// --- 1. TANIMLAMALAR (Header kısmı) ---

typedef enum {
    TENSOR_FLOAT32,
    TENSOR_FLOAT16,
    TENSOR_INT8
} TensorType;

typedef struct {
    TensorType type;
    uint16_t rows;
    uint16_t cols;
    float scale;
    int8_t zero_point;

    union {
        float* f32;
        uint16_t* f16;
        int8_t* i8;
    } data;
} Tensor;

// --- 2. FONKSİYONLAR (Logic kısmı) ---

Tensor* create_tensor(uint16_t rows, uint16_t cols) {
    Tensor* t = (Tensor*)malloc(sizeof(Tensor));
    t->type = TENSOR_FLOAT32;
    t->rows = rows;
    t->cols = cols;
    t->data.f32 = (float*)malloc(rows * cols * sizeof(float));
    return t;
}

void quantize_to_int8(Tensor* t) {
    if (t->type != TENSOR_FLOAT32) return;
    size_t size = t->rows * t->cols;

    // Basit dinamik scale hesabı
    float max_val = 0;
    for(size_t i=0; i<size; i++) {
        if(fabs(t->data.f32[i]) > max_val) max_val = fabs(t->data.f32[i]);
    }
    t->scale = (max_val > 0) ? max_val / 127.0f : 1.0f;
    t->zero_point = 0;

    int8_t* new_data = (int8_t*)malloc(size * sizeof(int8_t));
    for (size_t i = 0; i < size; i++) {
        new_data[i] = (int8_t)(t->data.f32[i] / t->scale);
    }

    float* old_ptr = t->data.f32;
    t->data.i8 = new_data;
    t->type = TENSOR_INT8;
    free(old_ptr);
    printf("\n[Agentic AI] Bellek analizi yapildi. Veriler Int8 formatina sikistirildi.\n");
}

void print_tensor(Tensor *t) {
    printf("Tensor Verileri (%s): ", t->type == TENSOR_FLOAT32 ? "Float32" : "Int8");
    for (int i = 0; i < t->rows * t->cols; i++) {
        if (t->type == TENSOR_FLOAT32) printf("%.2f ", t->data.f32[i]);
        else printf("%d ", t->data.i8[i]);
    }
    printf("\n");
}

void free_tensor(Tensor* t) {
    if (t) {
        // Union'da hangi pointer doluysa onu serbest bırakırız
        free(t->data.f32);
        free(t);
    }
}

// --- 3. ANA PROGRAM (Uygulama) ---

int main() {
    printf("= TinyML Dinamik Tensor Yonetimi 2=\n");

    // 1. Tensor Oluştur
    Tensor* my_tensor = create_tensor(2, 2);
    my_tensor->data.f32[0] = 1.5f;
    my_tensor->data.f32[1] = 12.7f;
    my_tensor->data.f32[2] = 0.0f;
    my_tensor->data.f32[3] = -5.2f;

    print_tensor(my_tensor);

    // 2. Optimizasyon Yap
    quantize_to_int8(my_tensor);

    // 3. Sonucu Yazdır
    print_tensor(my_tensor);

    // 4. Belleği Temizle
    free_tensor(my_tensor);

    printf("\nProgram basariyla tamamlandi. Cikis icin bir tusa basin...");
    getchar();
    return 0;
}