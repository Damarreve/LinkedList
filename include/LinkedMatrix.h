#ifndef LINKEDMATRIX_H
#define LINKEDMATRIX_H

#include "LinkedList.h"

template <typename T>
class LinkedMatrix
{
    private:
        struct Entry
        {
            LinkedList<T>* value;
            Entry* next;
            Entry(LinkedList<T>* value)
            {
                this->value = value;
                this->next = nullptr;
            }
        };
        // Первый элемент
        Entry* first_element;
        // Текущий (последний) элемент
        Entry* current_element;
    public:
        LinkedMatrix(T** values, int rows, int cols);
        virtual ~LinkedMatrix();
        void add(LinkedList<T>* row);
        void remove(int index);
        void insert(LinkedList<T>* value, int index);
        LinkedList<T>* get(int index);
        void print_matrix();
        int rows();
        int cols();
};

#endif // LINKEDMATRIX_H
