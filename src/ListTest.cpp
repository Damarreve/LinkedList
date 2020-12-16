#include <iostream>
#include <cstdlib>
#include "LinkedList.h"
#include "LinkedMatrix.h"

using namespace std;

constexpr int ARRAY_SIZE = 5;

// Демонстрация работы функций (тип списка - float)
// Аналогично будет работать и для типов int, double
void do_test_float()
{
    srand(static_cast<unsigned int>(time(0)));
    float* f_array = new float[ARRAY_SIZE];
    cout << "Random array: ";
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        f_array[i] = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 1000.0);
        cout << '\'' << f_array[i] << '\'' << (i == ARRAY_SIZE - 1 ? "" : ", ");
    }
    cout << endl;

    LinkedList<float>* basic_list = new LinkedList<float>(f_array, ARRAY_SIZE);
    cout << "List: ";
    basic_list->print_list();

    basic_list->add(10.f);
    cout << "List->add(10.f): ";
    basic_list->print_list();

    basic_list->insert(0.f, 2);
    cout << "List->insert(0.f, 2): ";
    basic_list->print_list();

    basic_list->insert(12.3456f, 3);
    cout << "List->insert(12.3456f, 3): ";
    basic_list->print_list();

    basic_list->insert(12.3456f, 6);
    cout << "List->insert(12.3456f, 6): ";
    basic_list->print_list();

    cout << "List->size(): " << basic_list->size() << endl;
    cout << "List->is_empty(): " << (basic_list->is_empty() ? "true" : "false") << endl;

    basic_list->remove_by_index(5);
    cout << "List->remove_by_index(5): ";
    basic_list->print_list();

    basic_list->remove_by_index(1);
    cout << "List->remove_by_index(1): ";
    basic_list->print_list();

    basic_list->remove_by_index(0);
    cout << "List->remove_by_index(0): ";
    basic_list->print_list();

    basic_list->remove_by_value(12.3456f);
    cout << "List->remove_by_value(12.3456f): ";
    basic_list->print_list();

    cout << "List->find(10.f): " << basic_list->find(10.f) << endl;
    cout << "List->get_first(): " << basic_list->get_first() << endl;
    cout << "List->get_last(): " << basic_list->get_last() << endl;
    cout << "List->get(1): " << basic_list->get(1) << endl;

    basic_list->clear();
    cout << "List->clear(); List->size(): "
        << basic_list->size()
        << "; List->is_empty(): "
        << (basic_list->is_empty() ? "true" : "false")
        << ';'
        << endl;
    delete basic_list;
    delete f_array;

    cout << endl << "Create new Lists" << endl;
    LinkedList<float>* op_list1 = new LinkedList<float>(new float[3] {1.f, 2.f, 3.f}, 3);
    LinkedList<float>* op_list2 = new LinkedList<float>(new float[3] {4.f, 9.f, 16.f}, 3);

    cout << "List1: ";
    op_list1->print_list();
    cout << "List2: ";
    op_list2->print_list();

    op_list1->operator+(5.f);
    cout << "List1->operator+(5.f): ";
    op_list1->print_list();

    op_list2->operator*(2.1f);
    cout << "List1->operator+(2.1f): ";
    op_list2->print_list();

    op_list1->operator+(*op_list2);
    cout << "List1->operator+(*List2): ";
    op_list1->print_list();

    op_list2->operator*(*op_list1);
    cout << "List2->operator*(*List1): ";
    op_list2->print_list();

    delete op_list2;
    delete op_list1;
}

void do_test_matrix()
{
    int** arr = new int*[5];
    for (int i = 0; i < 5; i++)
    {
        arr[i] = new int[3];
        for (int j = 0; j < 3; j++)
        {
            arr[i][j] = i + (i + 1) * j;
        }
    }
    LinkedMatrix<int>* matrix = new LinkedMatrix<int>(arr, 5, 3);
    matrix->print_matrix();
    cout << "Matrix dimension: " << matrix->cols() << "x" << matrix->rows() << endl;
    cout << "add [100, 100, 100]" << endl;
    matrix->add(new LinkedList<int>(new int[3]{100, 100, 100}, 3));
    matrix->print_matrix();
    cout << "insert [3, 2, 1] on 2" << endl;
    matrix->insert(new LinkedList<int>(new int[3]{3, 2, 1}, 3), 2);
    matrix->print_matrix();
    cout << "remove 4" << endl;
    matrix->remove(4);
    matrix->print_matrix();
    cout << "get 3" << endl;
    matrix->get(3)->print_list();
    delete matrix;
}

int main(int argc, char* argv[])
{
    do_test_float();
    //do_test_matrix();
    return 0;
}
