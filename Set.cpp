//
// Created by alexc on 5/12/2019.
//

#include "Set.h"

Set::Set()
{
    _head = nullptr;
}

Set::~Set()
{
    if(_head != nullptr)
    {
        _head = deleteSet(_head);
    }
}

void Set::READFILE(const char *filename)
{
    std::cout << "READ START " << filename << std::endl;
    std::ifstream myReadFile;
    myReadFile.open(filename);

    if (myReadFile.is_open())
    {
        char data[20];
        int d;
        int k;
        myReadFile >> d;
        myReadFile >> data;
        myReadFile >> k;
        if(_head == nullptr)
        {
            //создаем новую голову и добавляем в нее
            _head = new node(d);
            add_to_end(_head, k);
            _head -> s_next = add_to_sublist(_head -> s_next, _head -> el);
            _head -> el -> count++;
        }
        node * temp;
        node * temp2;
        node * l_el = _head -> el;
        while (!myReadFile.eof())
        {
            myReadFile >> d;
            myReadFile >> data;
            myReadFile >> k;
            temp = existEl(_head, d);
            temp2 = existEl(_head, k);
            if(temp == nullptr)
            {
                temp = add_to_end(l_el, d);
                l_el = l_el -> el;
            }
            if(temp2 == nullptr)
            {
                temp2 = add_to_end(l_el, k);
                l_el = l_el -> el;
            }
            temp -> s_next = add_to_sublist(temp -> s_next, temp2);
            temp2 -> count++;
        }
        myReadFile.close();
    }
}

bool Set::SORT()
{
    node * temp = _head;
    node * newhead = nullptr;
    node * prev = nullptr;
    node * l_el = nullptr;
    sub_node * sub;
    while (temp != nullptr)
    {
        if(temp -> count == 0)
        {
            if(newhead == nullptr)
            {
                newhead = temp;
            } else
            {
                l_el -> el = temp;
            }
            if(temp -> s_next != nullptr)
            {
                sub = temp -> s_next;
                while(sub != nullptr)
                {
                    sub -> el -> count--;
                    sub = sub -> s_next;
                }
                temp -> s_next = deleteList(temp -> s_next);
            }
            //убираем связь из списка
            if(temp == _head)
            {
                _head = _head -> el;
            } else
            {
                prev -> el = temp -> el;
            }
            temp -> el = nullptr;
            l_el = temp;
            temp = _head;
            prev = nullptr;
            continue;
        }
        prev = temp;
        temp = temp -> el;
    }
    if(_head != nullptr)
    {
        //чистим оба списка
        _head = deleteSet(_head);
        newhead = deleteSet(newhead);
        return false;
    }
    _head = newhead;
    return true;
}

void Set::PRINT() const
{
    std::cout << "Print: " << std::endl;
    if(_head == nullptr)
        return;
    node * temp = _head;
    while (temp != nullptr)
    {
        std::cout << "data: " << temp -> data << " count: " << temp -> count  << std::endl;
        if(temp -> s_next != nullptr)
        {
            std::cout << "{" << std::endl;
            sub_node * temp2 = temp -> s_next;
            while (temp2 != nullptr)
            {
                std::cout << "s_data: " << temp2 -> el -> data << std::endl;
                temp2 = temp2 -> s_next;
            }
            std::cout << "}" << std::endl;
        }
        temp = temp -> el;
    }
}

node * Set::deleteSet(node * head)
{
    node * temp1;
    node * temp2 = head;
    while (temp2 != nullptr)
    {
        temp1 = temp2;
        temp2 = temp2 -> el;
        if(temp1 -> s_next != nullptr)
            temp1 -> s_next = deleteList(temp1 -> s_next);
        delete temp1;
    }
    head = nullptr;
    return head;
}

sub_node * Set::deleteList(sub_node * head)
{
    sub_node * temp1;
    sub_node * temp2 = head;
    while (temp2 != nullptr)
    {
        temp1 = temp2;
        temp2 = temp2 -> s_next;
        delete temp1;
    }
    head = nullptr;
    return head;
}

node * Set::existEl(node * head, unsigned int d) const
{
    if(head -> data == d)
        return head;
    node * temp = head -> el;
    while(temp != nullptr)
    {
        if(temp -> data == d)
            return temp;
        temp = temp -> el;
    }
    return nullptr;
}

node * Set::add_to_end(node * tail, unsigned  int d)
{
    tail -> el = new node(d);
    return tail -> el;
}

sub_node * Set::add_to_sublist(sub_node * head, node * el)
{
    if(head == nullptr)
    {
        head = new sub_node(el, nullptr);
        return head;
    }
    sub_node * temp = head;
    sub_node * temp2 = head -> s_next;
    while (temp2 != nullptr)
    {
        temp = temp -> s_next;
        temp2 = temp2 -> s_next;
    }
    temp -> s_next = new sub_node(el, nullptr);
    return head;
}