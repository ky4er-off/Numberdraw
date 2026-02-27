#ifndef _DRAW_NUMBER_H_
#define _DRAW_NUMBER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OK = 0,     ///< Успешное выполнение.
    ERROR = -1  ///< Неудача.
} STATUS;

/// @brief Функция отрисовка одной цифры с целочисленным масштабированием
/// @param frame        кадр(массив пикселей вида unsigned char)
/// @param digit        Отрисовываемая цифра(от 0 до 9)
/// @param start_x      Начальная координата(x левого верхнего угла)
/// @param start_y      Начальная координата(У левого верхнего угла)
/// @param scale        Коэфициент масштабирования (1 = 3х5 пикселей на цифру, 2 - 6х10 пикселей на цифру)
/// @param frame_width  Ширина кадра
/// @param frame_height Высота кадра
/// @return             STATUS - ОК или ERROR
STATUS draw_digit_scaled(unsigned char *frame, int digit, int start_x, int start_y, int scale, int frame_width, int frame_height);

/// @brief Функция отрисовки числа от 0 до 99
/// @param frame        Кадр - массив пикселей unsigned char
/// @param start_x      Х координата левой верхней точки
/// @param start_y      У координата левой верхней точки
/// @param number       Число от 0 до 99 (целое)
/// @param scale        Коэффициент масштабирования(целочисленный)
/// @param spacing      Расстояние между цифрами(в пикселях)
/// @param frame_width  Ширина кадра
/// @param frame_height Высота кадра
STATUS draw_number_scaled(unsigned char *frame, int start_x, int start_y, int number, int scale, int spacing, 
                                                                        int frame_width, int frame_height);

/// @brief Основная функция отрисовки индикатора скорости
/// @param frame        Кадр - массив пикселей unsigned char
/// @param speed        Скорость(отрисовываемое целое число от 0 до 99)
/// @param pos_x        Х координата левого верхнего угла
/// @param pos_y        У координата левого верхнего угла
/// @param scale        Коэффициент масштабирования
/// @param frame_width  Ширина кадра
/// @param frame_height Высота кадра
/// @return             STATUS OK - все хорошо, ERROR - ошибка
STATUS draw_speed_indicator(unsigned char *frame, int speed, int pos_x, int pos_y, int scale, int frame_width, int frame_height);

/// @brief Функция для очистки части изображения под индикатор скорости 
/// @param frame        Кадр в виде массива яркостей пикселей unsigned char
/// @param pos_x        Х координата левого верхнего угла начальной точки
/// @param pos_y        У координата левого верхнего угла начальной точки
/// @param scale        Коэффциеинт масштабирования(целочисленный)
/// @param spacing      Отступ между символами(по-умолчанию равен 5)
/// @param frame_width  Ширина кадра
/// @param frame_height Высота кадра
/// @return             STATUS OK - все хорошо, ERROR - ошибка
STATUS clear_digit_area(unsigned char *frame, const int pos_x, const int pos_y, 
                      const int scale, const int spacing,  const int frame_width, const int frame_height);

#ifdef __cplusplus
}
#endif

#endif
