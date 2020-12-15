#include <iostream>
#include "LinkedList.h"

/*
Реализации методов класса связного списка.
 */

template<typename T>
LinkedList<T>::LinkedList()
{
    // Пустой список не содержит элементов
    this->first_element = nullptr;
    this->current_element = first_element;
}

template<typename T>
LinkedList<T>::LinkedList(T* values, int length)
{
    // Заполняем список соответствующими значениями из массива
    if (length > 0) for (int i = 0; i < length;) add(values[i++]);
    else throw std::runtime_error("LinkedList(T*, int): Размер массива должен быть больше нуля.");
}

template<typename T>
LinkedList<T>* LinkedList<T>::add(T value)
{
    // Добавляем элемент
    if (first_element == nullptr)
    {
        // Если элементов нет, добавляем его как первый
        first_element = new Entry(value);
        current_element = first_element;
    }
    else
    {
        // Если элементы уже были, добавляем его после последнего
        // и обновляем ссылку на последний эл-т
        current_element->next = new Entry(value);
        current_element = current_element->next;
    }
    return this;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    // Деструктор, освобождаем память
    // Если пустой список, то и удалять нечего
    if (first_element == nullptr) return;
    // Если есть хотя бы один элемент - удалим по очереди все
    Entry* current;
    Entry* to_delete = first_element;
    do
    {
        // Пройдёмся в цикле до тех пор, пока не закончатся элементы
        // и удалим каждый по очереди
        current = to_delete->next;
        delete to_delete;
        to_delete = current;
    } while (current != nullptr);
}

template<typename T>
void LinkedList<T>::print_list()
{
    if (is_empty())
    {
        std::cout << "[]" << std::endl;
        return;
    }
    // Просто выводим список, по очереди проходимся по всем элементам
    Entry* entry = first_element;
    std::cout << '[';
    do
    {
        std::cout << entry->value << (entry->next == nullptr ? "" : ", ");
        entry = entry->next;
    } while (entry != nullptr);
    std::cout << ']' << std::endl;
}

template<typename T>
int LinkedList<T>::size()
{
    // Размер списка
    if (first_element == nullptr) return 0;
    // Пройдёмся по очереди по всем элементам, пока не закончатся
    // По пути посчитаем количество элементов, это и будет размер
    Entry* pointer = first_element;
    int size = 1;
    while ((pointer = pointer->next) != nullptr) size++;
    return size;
}

template<typename T>
void LinkedList<T>::insert(T value, int index)
{
    // Вставка элемента
    if (index < 0 || index > size()) throw std::runtime_error("LinkedList::insert(T, int): Неверный индекс.");
    Entry* previous = first_element;
    if (index == 0)
    {
        // Меняем первый элемент
        first_element = new Entry(value);
        first_element->next = previous;
    }
    else if (index == size())
    {
        // Проверим - может быть индекс соответствует размеру списка и достаточно просто добавить элемент
        add(value);
    }
    else
    {
        // Находим предыдущий элемент перед необходимым индексом
        for (int i = 1; i < index; i++) previous = previous->next;
        // Вставляем значение и обновляем ссылки
        Entry* new_entry = new Entry(value);
        new_entry->next = previous->next;
        previous->next = new_entry;
    }
}

template<typename T>
void LinkedList<T>::emplace(LinkedList<T>* list, int index)
{
    // Вставка списка в существующий список
    if (index < 0 || index > size()) throw std::runtime_error("LinkedList::emplace(LinkedList*, int): Неверный индекс.");
    if (list->size() < 1) throw std::runtime_error("LinkedList::emplace(LinkedList*, int): Вставка пустого списка невозможна.");
    // Изобретать велосипед не будем, вставим по очереди элементы существующей функцией
    for (int i = 0; i < list->size(); i++) insert(list->get(i), index + i);
}

template<typename T>
T* LinkedList<T>::as_array()
{
    // Вернём список как массив значений
    T* arr = new T[size()];
    for (int i = 0; i < size(); i++) arr[i] = get(i);
    return arr;
}

template<typename T>
int LinkedList<T>::find(T value)
{
    // Поиск элемента по значению
    int counter = 0;
    Entry* pointer = first_element;
    // Сравниваем все элементы по очереди с нужным
    // Если найдём необходимый, вернём индекс
    // Если ничего не найдём, вернём -1
    while (pointer != nullptr)
    {
        if (pointer->value == value) return counter;
        pointer = pointer->next;
        counter++;
    }
    return -1;
}

template<typename T>
void LinkedList<T>::remove_by_index(int index)
{
    // Удаляем по индексу
    int length = size();
    if (index >= length) throw std::runtime_error("LinkedList::remove_by_index(int): Индекс превышает размер списка.");
    Entry* pointer;
    if (index == 0)
    {
        // Если нужно удалить первый элемент, тут всё довольно просто
        // Берём следующий за первым элемент и ставим его на первое место,
        // а ненужный просто удалим
        pointer = first_element;
        first_element = first_element->next;
        delete pointer;
        return;
    }
    // Если удаляем не первый элемент списка, то для начала находим предыдущий элемент от удаляемого
    int counter = 1;
    pointer = first_element;
    while (counter != index && pointer != nullptr)
    {
        pointer = pointer->next;
        counter++;
    }
    // Обновляем ссылку, чтобы элемент перед удаляемым указывал на элемент после удаляемого
    Entry* to_delete = pointer->next;
    pointer->next = to_delete->next;
    delete to_delete;
    // Если удалили последний элемент, нужно обновить ссылку на текущий элемент
    if (length - 1 == index) current_element = pointer;
}

template<typename T>
void LinkedList<T>::remove_by_value(T value)
{
    // Удаление элементов по значению (удаляются все элементы с таким значением)
    // Опять же изобретать велосипед не будем, используем функции поиска и удаления по индексу
    int position;
    while ((position = find(value)) > -1) remove_by_index(position);
}

template<typename T>
T LinkedList<T>::get_first()
{
    // Возвращаем значение первого элемента
    return first_element->value;
}

template<typename T>
T LinkedList<T>::get(int index)
{
    // Возвращаем значение элемента по индексу
    int counter = 0;
    Entry* pointer = first_element;
    while (counter++ != index) pointer = pointer->next;
    return pointer->value;
}

template<typename T>
T LinkedList<T>::get_last()
{
    // Возвращаем значение последнего элемента
    return current_element->value;
}

template<typename T>
bool LinkedList<T>::is_empty()
{
    // Если размер равен нулю, значит список пуст
    return size() == 0;
}

template<typename T>
void LinkedList<T>::clear()
{
    // Чистим список, убираем все значения
    this->~LinkedList();
    // Отличие от деструктора в том, что нужно заново инициализировать переменные
    first_element = nullptr;
    current_element = first_element;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator+(const T& additional)
{
    // Оператор сложения
    // Складываем каждый элемент списка с переданным элементом
    first_element->value += additional;
    Entry* pointer = first_element;
    while ((pointer = pointer->next) != nullptr) pointer->value += additional;
    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator+(const LinkedList<T>& additional)
{
    // Оператор сложения
    // Складываем каждый элемент списка с соответствующим элементом из переданного списка
    Entry* this_entry = first_element;
    Entry* additional_entry = additional.first_element;
    while (this_entry != nullptr && additional_entry != nullptr)
    {
        this_entry->value += additional_entry->value;
        this_entry = this_entry->next;
        additional_entry = additional_entry->next;
    }
    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator*(const T& multiplier)
{
    // Оператор умножения
    // Умножаем каждый элемент списка на переданный элемент
    first_element->value *= multiplier;
    Entry* pointer = first_element;
    while ((pointer = pointer->next) != nullptr) pointer->value *= multiplier;
    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator*(const LinkedList<T>& multiplier)
{
    // Оператор умножения
    // Перемножаем каждый элемент списка с соответствующим элементом из переданного списка
    Entry* this_entry = first_element;
    Entry* multiplier_entry = multiplier.first_element;
    while (this_entry != nullptr && multiplier_entry != nullptr)
    {
        this_entry->value *= multiplier_entry->value;
        this_entry = this_entry->next;
        multiplier_entry = multiplier_entry->next;
    }
    return *this;
}

/*
Возможные типы списка. Если нужны какие-то другие типы - можно добавить по аналогии.
 */

template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<double>;
