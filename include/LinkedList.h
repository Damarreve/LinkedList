#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * Связный список. Нумерация элементов начинается с нуля.
 */
template <typename T>
class LinkedList
{
    private:
        /**
         * Элемент связного списка.
         */
        struct Entry
        {
            T value;
            Entry* next = nullptr;
            Entry(T value) { this->value = value; }
        };
        Entry* first_element;
        Entry* current_element;
    public:
        /**
         * Конструктор.
         */
        LinkedList();

        /**
         * Конструктор по существующему массиву.
         * \values - сам массив
         * \length - длина массива
         */
        LinkedList(T* values, int length);

        /**
         * Деструктор.
         */
        virtual ~LinkedList();

        /**
         * Вывод значений списка по порядку.
         */
        void print_list();

        /**
         * Получение размера списка.
         */
        int size();

        /**
         * Добавление элемента в конец списка.
         */
        LinkedList* add(T value);

        /**
         * Вставка элемента в произвольное место в списке.
         */
        void insert(T value, int index);

        /**
         * Поиск элемента по значению.
         * \return индекс элемента в списке или -1, если элемент не найден.
         */
        int find(T value);

        /**
         * Получение первого элемента списка.
         */
        T get_first();

        /**
         * Получение элемента списка по индексу.
         */
        T get(int index);

        /**
         * Получение последнего элемента списка.
         */
        T get_last();

        /**
         * Проверка на пустоту.
         * \return true - список пуст, false - список не пуст.
         */
        bool is_empty();

        /**
         * Очистка списка.
         */
        void clear();
};

#endif
