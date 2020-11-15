#include <iostream>
#include "LinkedList.h"

/*
Реализации методов структуры элемента списка.
 */

template<typename T>
Entry<T>::Entry()
{
    this->next = nullptr;
}

template<typename T>
Entry<T>::Entry(T value)
{
    this->value = value;
    this->next = nullptr;
}

template<typename T>
T Entry<T>::get_value()
{
    return this->value;
}

template<typename T>
void Entry<T>::set_value(T value)
{
    this->value = value;
}

template<typename T>
Entry<T>* Entry<T>::get_next()
{
    return this->next;
}

template<typename T>
void Entry<T>::set_next(Entry<T>* next)
{
    this->next = next;
}

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
        first_element = new Entry<T>(value);
        current_element = first_element;
    }
    else
    {
        current_element->set_next(new Entry<T>(value));
        current_element = current_element->get_next();
    }
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    // Если пустой список, то и удалять нечего
    if (first_element == nullptr) return;
    // Если есть хотя бы один элемент - удалим по очереди все
    Entry<T>* current;
    Entry<T>* to_delete = first_element;
    do
    {
        current = to_delete->get_next();
        delete to_delete;
        to_delete = current;
    } while (current != nullptr);
}

template<typename T>
void LinkedList<T>::print_list()
{
    Entry<T>* entry = first_element;
    std::cout << '[';
    do
    {
        std::cout << entry->get_value() << (entry->get_next() == nullptr ? "" : ", ");
        entry = entry->get_next();
    } while (entry != nullptr);
    std::cout << ']' << std::endl;
}

/*
Возможные типы списка. Если нужны какие-то другие типы - можно добавить по аналогии.
*/

template class Entry<int>;
template class LinkedList<int>;

template class Entry<float>;
template class LinkedList<float>;

template class Entry<double>;
template class LinkedList<double>;

template class Entry<std::string>;
template class LinkedList<std::string>;
