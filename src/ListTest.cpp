#include <iostream>
#include "LinkedList.h"

constexpr int ARRAY_SIZE = 5;

int main()
{
    float* arr = new float[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE;) arr[i++] = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 10.0);
    LinkedList<float>* list = new LinkedList<float>(arr, ARRAY_SIZE);
    list->print_list();
    delete list;
    return 0;
}
