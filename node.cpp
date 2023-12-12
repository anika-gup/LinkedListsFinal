#include "node.h"

Node::Node(Student* s) : student(s), next(0) {}

Node::~Node() {
    // Assuming proper memory management for Student objects is handled elsewhere
}

void Node::setStudent(Student* s) {
    student = s;
}

void Node::setNext(Node* n) {
    next = n;
}

Student* Node::getStudent() {
    return student;
}

Node* Node::getNext() {
    return next;
}

