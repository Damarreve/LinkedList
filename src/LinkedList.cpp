#include <iostream>
#include "LinkedList.h"

/*
Реализации методов класса связного списка.
 */

template<typename T>
LinkedList<T>::LinkedList()
{
    this->first_element = nullptr;
    this->current_element = first_element;
}

template<typename T>
LinkedList<T>::LinkedList(T* values, int length)
{
    if (length > 0)
    {
        for (int i = 0; i < length;) add(values[i++]);
    }
    else
    {
        throw std::runtime_error("LinkedList(T*, int): Размер массива должен быть больше нуля.");
    }
}

template<typename T>
void LinkedList<T>::add(T value)
{
    if (first_element == nullptr)
    {
        first_element = new Entry(value);
        current_element = first_element;
    }
    else
    {
        current_element->next = new Entry(value);
        current_element = current_element->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    // Если пустой список, то и удалять нечего
    if (first_element == nullptr) return;
    // Если есть хотя бы один элемент - удалим по очереди все
    Entry* current;
    Entry* to_delete = first_element;
    do
    {
        current = to_delete->next;
        delete to_delete;
        to_delete = current;
    } while (current != nullptr);
}

template<typename T>
void LinkedList<T>::print_list()
{
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
    if (first_element == nullptr) return 0;
    Entry* pointer = first_element;
    int size = 1;
    while ((pointer = pointer->next) != nullptr) size++;
    return size;
}

template<typename T>
void LinkedList<T>::insert(T value, int index)
{
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
        // Вставляем значение
        Entry* new_entry = new Entry(value);
        new_entry->next = previous->next;
        previous->next = new_entry;
    }
}

template<typename T>
int LinkedList<T>::find(T value)
{
    int counter = 0;
    Entry* pointer = first_element;
    while (pointer != nullptr)
    {
        if (pointer->value == value) return counter;
        pointer = pointer->next;
        counter++;
    }
    return -1;
}

template<typename T>
T LinkedList<T>::get_first()
{
    return first_element->value;
}

template<typename T>
T LinkedList<T>::get(int index)
{
    int counter = 0;
    Entry* pointer = first_element;
    while (counter++ != index) pointer = pointer->next;
    return pointer->value;
}

template<typename T>
T LinkedList<T>::get_last()
{
    return current_element->value;
}

template<typename T>
bool LinkedList<T>::is_empty()
{
    return size() == 0;
}

template<typename T>
void LinkedList<T>::clear()
{
    this->~LinkedList();
    // Отличие от деструктора в том, что нужно заново инициализировать переменные
    first_element = nullptr;
    current_element = first_element;
}

/*
Возможные типы списка. Если нужны какие-то другие типы - можно добавить по аналогии.
*/

template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<double>;
template class LinkedList<std::string>;
