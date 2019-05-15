//
// Created by alexc on 5/12/2019.
//

#ifndef ITMO_F_PARTORDERSET_SET_H
#define ITMO_F_PARTORDERSET_SET_H

#include <iostream>
#include <fstream>
#include "string.h"

struct node;
struct sub_node
{
    node * el;
    sub_node * s_next;
    sub_node()
    {
        el = nullptr;
        s_next = nullptr;
    };
    sub_node(node * elem, sub_node * sub):el(elem),s_next(sub)
    {}
};
 
struct node : sub_node
{
    int data;
    unsigned int count;
    node()
    {
        data = 0;
        count = 0;
    };
    node(unsigned int d):data(d)
    {
        count = 0;
    }
};

class Set
{
public:
    Set();
    ~Set();
    void PRINT() const;
    bool SORT();
    void READFILE(const char * filename);
private:
    node * _head;
    node * deleteSet(node * head);
    sub_node * deleteList(sub_node * head);
    node * existEl(node * head, unsigned int d) const;
    node * add_to_end(node * tail, unsigned  int d);
    sub_node * add_to_sublist(sub_node * head, node * el);
};

#endif //ITMO_F_PARTORDERSET_SET_H
