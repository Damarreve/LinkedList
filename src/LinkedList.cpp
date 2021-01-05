#include <iostream>

using namespace std;

/**
 * Элемент связного списка.
 */
struct Node
{
    public:
        // Значение элемента
        double value;
        // Ссылка на следующий элемент
        Node* next = nullptr;
        // Конструктор элемента (по значению)
        Node(double value)
        {
            this->value = value;
        }
};

/**
 * Связный список (тип элементов - double).
 */
class LinkedList
{
    private:
        // Первый элемент
        Node* first_node;
        // Текущий элемент
        Node* current_node;
    public:
        /**
         * Пустой конструктор.
         */
        LinkedList()
        {
            // В пустом списке нет элементов
            this->first_node = nullptr;
            this->current_node = nullptr;
        }

        /**
         * Конструктор по массиву.
         */
        LinkedList(double* values, int length)
        {
            // Заполняем список соответствующими значениями из массива
            if (length > 0)
            {
                for (int i = 0; i < length; i++)
                {
                    push_back(values[i]);
                }
            }
            else
            {
                cout << "Размер входного массива должен быть больше нуля" << endl;
            }
        }

        /**
         * Деструктор.
         */
        ~LinkedList()
        {
            // Если список пуст, просто выходим
            if (first_node == nullptr)
            {
                return;
            }
            // Если есть хотя бы один элемент - удалим по очереди все
            Node* current;
            Node* to_delete = first_node;
            // Пока удаляемый элемент ссылается на какой-то существующий элемент, цикл выполняется
            do
            {
                // По очереди удаляем элементы, начиная с первого
                // Запоминаем ссылку на следующий элемент у удаляемого
                current = to_delete->next;
                delete to_delete;
                to_delete = current;
            } while (current != nullptr);
        }

        /**
         * Вывод значений списка по порядку.
         */
        void print()
        {
            // Если список пуст, то выведем уведомление
            if (empty())
            {
                cout << "Список пуст" << endl;
                return;
            }
            // Просто выводим список, по очереди проходимся по всем элементам
            // Алгоритм цикла схож с деструктором, только ничего не удаляется
            Node* node = first_node;
            do
            {
                cout << node->value << " ";
                node = node->next;
            } while (node != nullptr);
            cout << endl;
        }

        /**
         * Получение размера списка.
         */
        int size()
        {
            // Если первый элемент отсутствует, значит список пуст
            if (first_node == nullptr)
            {
                return 0;
            }

            int i = 0;
            Node* node = first_node;
            // Идём в цикле по очереди по элементам и попутно увеличиваем счётчик
            do
            {
                i++;
                node = node->next;
            } while (node != nullptr);
            // Возвращаем значение счётчика
            return i;
        }

        /**
         * Добавление элемента в конец списка.
         */
        void push_back(double value)
        {
            // Проверяем, есть ли первый элемент
            if (first_node == nullptr)
            {
                // Если первого элемента нет, добавляем как первый
                first_node = new Node(value);
                // Текущий элемент - первый элемент
                current_node = first_node;
            }
            else
            {
                // Если элементы уже были, добавляем новый элемент после текущего
                current_node->next = new Node(value);
                // И обновляем ссылку на последний элемент
                current_node = current_node->next;
            }
        }

        /**
         * Вставка элемента в произвольное место в списке.
         */
        void insert(double value, int index)
        {
            // Вставка элемента
            if (index < 0 || index > size())
            {
                cout << "Неверный индекс" << endl;
                return;
            }
            Node* previous = first_node;
            if (index == 0)
            {
                // Меняем первый элемент
                first_node = new Node(value);
                first_node->next = previous;
            }
            else if (index == size())
            {
                // Проверим - может быть индекс соответствует размеру списка и достаточно просто добавить элемент
                push_back(value);
            }
            else
            {
                // Находим предыдущий элемент перед необходимым индексом
                for (int i = 1; i < index; i++) previous = previous->next;
                // Вставляем значение и обновляем ссылки
                Node* new_entry = new Node(value);
                new_entry->next = previous->next;
                previous->next = new_entry;
            }
        }

        /**
         * Вставка списка в существующий список в определённое место.
         */
        void emplace(LinkedList* list, int index)
        {
            if (index < 0 || index > size())
            {
                cout << "Неверный индекс" << endl;
                return;
            }
            if (list->size() < 1)
            {
                cout << "Вставка пустого списка невозможна" << endl;
                return;
            }
            // Вставим по очереди элементы существующей функцией
            for (int i = 0; i < list->size(); i++)
            {
                insert(list->at(i), index + i);
            }
        }

        /**
         * Поиск элемента по значению.
         * Возвращает индекс элемента в списке или -1, если элемент не найден.
         */
        int find(double value)
        {
            // Поиск элемента по значению
            int counter = 0;
            Node* pointer = first_node;
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

        /**
         * Удаление элемента по индексу.
         */
        void remove(int index)
        {
            // Удаляем по индексу
            int length = size();
            // Если индекс больше размера списка, то удалять нечего
            if (index >= length)
            {
                cout << "Индекс превышает размер списка" << endl;
                return;
            }
            Node* pointer;
            if (index == 0)
            {
                // Если нужно удалить первый элемент, тут всё довольно просто
                // Берём следующий за первым элемент и ставим его на первое место,
                // а ненужный просто удалим
                pointer = first_node;
                first_node = first_node->next;
                delete pointer;
                return;
            }
            // Если удаляем не первый элемент списка, то для начала находим предыдущий элемент от удаляемого
            int counter = 1;
            pointer = first_node;
            while (counter != index && pointer != nullptr)
            {
                pointer = pointer->next;
                counter++;
            }
            // Обновляем ссылку, чтобы элемент перед удаляемым указывал на элемент после удаляемого
            Node* to_delete = pointer->next;
            pointer->next = to_delete->next;
            delete to_delete;
            // Если удалили последний элемент, нужно обновить ссылку на текущий элемент
            if (length - 1 == index) current_node = pointer;
        }

        /**
         * Получение элемента списка по индексу.
         */
        double at(int index)
        {
            // Если индекс больше размера списка или отрицательный, то выходим
            if (index > size() || index < 0)
            {
                cout << "Неверный индекс" << endl;
                return -1;
            }
            // Возвращаем значение элемента по индексу
            int counter = 0;
            Node* pointer = first_node;
            // В цикле
            while (counter++ != index) pointer = pointer->next;
            return pointer->value;
        }

        /**
         * Проверка на пустоту.
         * Возвращает true, если список пуст, или false, если список не пуст.
         */
        bool empty()
        {
            // Если размер равен нулю, значит список пуст
            return size() == 0;
        }

        /**
         * Очистка списка.
         */
        void clear()
        {
            // Чистим список, убираем все значения
            this->~LinkedList();
            // Отличие от деструктора в том, что нужно заново инициализировать переменные
            first_node = nullptr;
            current_node = first_node;
        }
};

int main()
{
    // Создаём массив и наш список
    double* values = new double[5];
    for (int i = 0; i < 5; i++)
    {
        values[i] = i + 1;
    }
    LinkedList list(values, 5);
    list.print();

    // Добавляем в конец "6"
    list.push_back(6);
    list.print();

    // Вставляем между нулевым и первым элементом "1.5"
    // Нумерация элементов идёт с нуля!
    list.insert(1.5, 1);
    list.print();

    // Удаляем нулевой (первый) элемент
    list.remove(0);
    list.print();

    // Выводим значение нулевого (первого) элемента
    cout << list.at(0) << endl;

    // Очищаем список и выводим
    list.clear();
    list.print();

    return 0;
}
