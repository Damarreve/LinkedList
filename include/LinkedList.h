#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * Элемент связного списка.
 */
template <typename T>
struct Entry
{
    private:
        // Значение
        T value;
        // Ссылка на следующий элемент
        Entry<T>* next;
    public:
        /**
         * Конструктор.
         */
        Entry();

        /**
         * Конструктор по значению.
         */
        Entry(T value);

        /**
         * Получение значения.
         */
        T get_value();

        /**
         * Установка значения.
         */
        void set_value(T value);

        /**
         * Получение следующего элемента.
         */
        Entry<T>* get_next();

        /**
         * Установка следующего элемента.
         */
        void set_next(Entry<T>* next);
};

/**
 * Связный список. Нумерация элементов начинается с нуля.
 */
template <typename T>
class LinkedList
{
    private:
        Entry<T>* first_element;
        Entry<T>* current_element;
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
         * Добавление элемента в конец списка.
         */
        void add(T value);
};

#endif
