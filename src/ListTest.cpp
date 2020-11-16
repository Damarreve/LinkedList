#include <iostream>
#include <cstdlib>
#include "LinkedList.h"

constexpr int ARRAY_SIZE = 5;

void do_list_test_float()
{
    srand(static_cast<unsigned int>(time(0)));
    float* arr = new float[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE;) arr[i++] = static_cast<float>(rand() / static_cast<float>(RAND_MAX) * 1000.0);
    LinkedList<float>* list = new LinkedList<float>(arr, ARRAY_SIZE);
    list->print_list();
    std::cout << "List size is " << list->size() << std::endl;
    list->insert(10.0, 3);
    list->print_list();
    std::cout << "Value '10' on position #" << list->find(10) << std::endl;
    std::cout << "First element == " << list->get_first() << std::endl;
    std::cout << "Element #2 == " << list->get(2) << std::endl;
    std::cout << "Element #3 == " << list->get(3) << std::endl;
    std::cout << "Element #4 == " << list->get(4) << std::endl;
    std::cout << "Last element == " << list->get_last() << std::endl;
    std::cout << "List is " << (list->is_empty() ? "" : "not ") << "empty" << std::endl;
    list->remove_by_value(10);
    list->print_list();
    list->clear();
    std::cout << "List is " << (list->is_empty() ? "" : "not ") << "empty" << std::endl;
    delete list;
}

void do_list_test_std_string()
{
    LinkedList<std::string>* ch_list = new LinkedList<std::string>();
    ch_list->add("Hello")->add("friend")->add("how")->add("are")->add("you")->add("?");
    ch_list->print_list();
    ch_list->insert("my", 1);
    ch_list->print_list();
    ch_list->remove_by_index(0);
    ch_list->print_list();
    ch_list->remove_by_value("my");
    ch_list->print_list();
    ch_list->remove_by_index(0);
    ch_list->print_list();
    ch_list->remove_by_index(3);
    ch_list->print_list();
    delete ch_list;
}

int main(int argc, char* argv[])
{
    do_list_test_float();
    do_list_test_std_string();
    return 0;
}
