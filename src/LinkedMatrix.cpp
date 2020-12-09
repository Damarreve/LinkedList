#include <iostream>
#include "LinkedMatrix.h"

template<typename T>
LinkedMatrix<T>::LinkedMatrix(T** values, int rows, int cols)
{
    for (int i = 0; i < rows; i++) add(new LinkedList<T>(values[i], cols));
}

template<typename T>
void LinkedMatrix<T>::add(LinkedList<T>* row)
{
    if (first_element == nullptr)
    {
        first_element = new Entry(row);
        current_element = first_element;
    }
    else
    {
        current_element->next = new Entry(row);
        current_element = current_element->next;
    }
}

template<typename T>
void LinkedMatrix<T>::remove(int index)
{
    // Удаляем по индексу
    int length = rows();
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
void LinkedMatrix<T>::insert(LinkedList<T>* value, int index)
{
    // Вставка элемента
    if (index < 0 || index > rows()) throw std::runtime_error("LinkedList::insert(T, int): Неверный индекс.");
    Entry* previous = first_element;
    if (index == 0)
    {
        // Меняем первый элемент
        first_element = new Entry(value);
        first_element->next = previous;
    }
    else if (index == rows())
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
LinkedList<T>* LinkedMatrix<T>::get(int index)
{
    // Возвращаем значение элемента по индексу
    int counter = 0;
    Entry* pointer = first_element;
    while (counter++ != index) pointer = pointer->next;
    return pointer->value;
}

template<typename T>
LinkedMatrix<T>::~LinkedMatrix()
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
void LinkedMatrix<T>::print_matrix()
{
    Entry* act = first_element;
    do act->value->print_list();
    while ((act = act->next) != nullptr);
}

template<typename T>
int LinkedMatrix<T>::rows()
{
    // Размер матрицы
    if (first_element == nullptr) return 0;
    // Пройдёмся по очереди по всем элементам, пока не закончатся
    // По пути посчитаем количество элементов, это и будет размер
    Entry* pointer = first_element;
    int size = 1;
    while ((pointer = pointer->next) != nullptr) size++;
    return size;
}

template<typename T>
int LinkedMatrix<T>::cols()
{
    // Размер матрицы
    if (first_element == nullptr) return 0;
    // Пройдёмся по очереди по всем элементам, пока не закончатся
    // По пути посчитаем количество элементов, это и будет размер
    return first_element->value->size();
}

/*
Возможные типы матрицы. Если нужны какие-то другие типы - можно добавить по аналогии.
 */

template class LinkedMatrix<int>;
template class LinkedMatrix<float>;
template class LinkedMatrix<double>;
template class LinkedMatrix<std::string>;
