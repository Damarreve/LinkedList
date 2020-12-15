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
            int index;
            T value;
            Entry* next = nullptr;
            Entry(T value) { this->value = value; }
        };
        int length;
        // Первый элемент
        Entry* first_element;
        // Текущий (последний) элемент
        Entry* current_element;

        enum Action { PLUS, MINUS };
        void update_indices(int index, Action action);
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
         * \return текущий список (для удобства добавления элементов).
         */
        LinkedList* add(T value);

        /**
         * Вставка элемента в произвольное место в списке.
         */
        void insert(T value, int index);

        /**
         * Вставка списка в существующий список в определённое место.
         */
        void emplace(LinkedList* list, int index);

        /**
         * Преобразование списка в массив.
         */
        T* as_array();

        /**
         * Поиск элемента по значению.
         * \return индекс элемента в списке или -1, если элемент не найден.
         */
        int find(T value);

        /**
         * Удаление элемента по индексу.
         */
        void remove_by_index(int index);

        /**
         * Удаление всех элементов с указанным значением.
         */
        void remove_by_value(T value);

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

        /**
         * Добавление определённого значения ко всем элементам списка.
         * \additional значение, которое нужно добавить к элементам.
         */
        LinkedList& operator+(const T& additional);

        /**
         * Сложение списков поэлементно.
         * \additional список, который нужно поэлементно добавить к текущему.
         */
        LinkedList& operator+(const LinkedList& additional);

        /**
         * Умножение списка на определённое значение.
         * \multiplier значение, на которое нужно умножить каждый элемент.
         * @note не работает для списков с типом значения std::string.
         */
        LinkedList& operator*(const T& multiplier);

        /**
         * Умножение списков поэлементно.
         * \multiplier список, который нужно поэлементно перемножить с текущим.
         * @note не работает для списков с типом значения std::string.
         */
        LinkedList& operator*(const LinkedList& multiplier);
};

#endif
