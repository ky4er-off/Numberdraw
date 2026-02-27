#include <string.h>

#include "draw_number.h"

// Константы паттерна
#define PATTERN_WIDTH 3
#define PATTERN_HEIGHT 5

// Инициализация паттерна(текстур) цифр размером 3х5 битами
const unsigned char digit_patterns[10][PATTERN_HEIGHT] = {
    {0b111,  // 0: 111
     0b101,  //    101
     0b101,  //    101
     0b101,  //    101
     0b111}, //    111
     
    {0b010, 0b110, 0b010, 0b010, 0b111}, // 1
    {0b111, 0b001, 0b111, 0b100, 0b111}, // 2
    {0b111, 0b001, 0b111, 0b001, 0b111}, // 3
    {0b101, 0b101, 0b111, 0b001, 0b001}, // 4
    {0b111, 0b100, 0b111, 0b001, 0b111}, // 5
    {0b111, 0b100, 0b111, 0b101, 0b111}, // 6
    {0b111, 0b001, 0b001, 0b001, 0b001}, // 7
    {0b111, 0b101, 0b111, 0b101, 0b111}, // 8
    {0b111, 0b101, 0b111, 0b001, 0b111}  // 9
};

// Функция отрисовки цифры с масштабированием
STATUS draw_digit_scaled(unsigned char *frame, int digit, int start_x, int start_y, 
                         int scale, int frame_width, int frame_height) {
    if (!frame || digit < 0 || digit > 9 || scale < 1) return ERROR;
    
    // Проходим по паттерну 3x5
    for (int py = 0; py < PATTERN_HEIGHT; py++) {
        unsigned char row_pattern = digit_patterns[digit][py];
        
        for (int px = 0; px < PATTERN_WIDTH; px++) {
            // Проверяем бит
            if (row_pattern & (1 << (2 - px))) {
                // Масштабируем пиксель в scale x scale блок
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        int fx = start_x + px * scale + sx;
                        int fy = start_y + py * scale + sy;
                        
                        if (fx >= 0 && fx < frame_width && 
                            fy >= 0 && fy < frame_height) {
                            frame[fy * frame_width + fx] = 180;
                        }
                    }
                }
            }
        }
    }
    return OK;
}

// Функция отрисовки числа (0-99)
STATUS draw_number_scaled(unsigned char *frame, int start_x, int start_y, 
                        int number, int scale, int spacing, 
                        int frame_width, int frame_height) {
    if (!frame || number < 0 || number > 99 || scale < 1) return ERROR;
    
    int digit_width = PATTERN_WIDTH * scale;
    
    if (number >= 10) {
        // Рисуем десятки
        draw_digit_scaled(frame, number / 10, start_x, start_y, 
                         scale, frame_width, frame_height);
        // Рисуем единицы
        draw_digit_scaled(frame, number % 10, 
                         start_x + digit_width + spacing, start_y, 
                         scale, frame_width, frame_height);
    } else {
        // Однозначное число (центрируем для двузначной позиции)
        int offset = (digit_width + spacing) / 2;
        draw_digit_scaled(frame, number, start_x + offset, start_y, 
                         scale, frame_width, frame_height);
    }

    return OK;
}

// Специализированная функция для индикатора скорости
STATUS draw_speed_indicator(unsigned char *frame, int speed, int pos_x, int pos_y, 
                                    int scale, int frame_width, int frame_height) {
    if (!frame) return ERROR;
    
    // Ограничиваем скорость
    if (speed < 0) speed = 0;
    if (speed > 99) speed = 99;
    
    // Рисуем скорость (без фона и рамки)
    draw_number_scaled(frame, pos_x, pos_y, speed, scale, 5, frame_width, frame_height);

    return OK;
}

// Функция очистки области для индикатора скорости
STATUS clear_digit_area(unsigned char *frame, const int pos_x, const int pos_y, 
                      const int scale, const int spacing,  const int frame_width, const int frame_height) {
    if (!frame) return ERROR;
    
    // Рассчитываем размер области, которую занимает индикатор(учитывая отступ)
    int digit_width = PATTERN_WIDTH * scale;
    int total_width = (digit_width * 2) + spacing;  // Две цифры + промежуток
    int height = PATTERN_HEIGHT * scale;
    
    // Очищаем прямоугольную область
    for (int y = pos_y; y < pos_y + height; y++) {
        for (int x = pos_x; x < pos_x + total_width; x++) {
            if (x >= 0 && x < frame_width && y >= 0 && y < frame_height) {
                frame[y * frame_width + x] = 0;  // Закрашиваем черным
            }
        }
    }
    return OK;
}