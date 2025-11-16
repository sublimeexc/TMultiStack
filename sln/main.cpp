#include "tstack.h"
#include "tmultistack.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        std::cout << "Создаем TMultiStack с 20 элементами и 3 стеками..." << std::endl;
        TMultiStack<int> ms(20, 3);

        std::cout << "Размер: " << ms.GetSize() << std::endl;

        // Тестируем добавление
        std::cout << "Добавляем элементы..." << std::endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 1; j <= 5; j++) {
                ms.Push(i * 10 + j, i);
                std::cout << "Добавлен " << (i * 10 + j) << " в стек " << i << std::endl;
            }
        }

        // Тестируем извлечение
        std::cout << "Извлекаем элементы..." << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "Стек " << i << ": ";
            while (!ms.IsEmpty(i)) {
                std::cout << ms.Pop(i) << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Тест завершен успешно!" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
}