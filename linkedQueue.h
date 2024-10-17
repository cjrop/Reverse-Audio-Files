#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <iostream>
using namespace std;
template <class myType>

// node + link + data inside Node
struct queueNode{
    myType *dataSet;
    unsigned int front, back;
    queueNode<myType> *link;
};

template <class myType>
class linkedQueue{
private:
    queueNode<myType> *queueFront, *queueRear;
    unsigned int size, count;

public:
    static constexpr unsigned int ARR_MIN = 5;
    static constexpr unsigned int ARR_MAX = 9600;
    static constexpr unsigned int ARR_DEFAULT = 22050;

    linkedQueue(unsigned int size = ARR_DEFAULT);
    ~linkedQueue();
    bool isEmptyQueue() const;
    void initializeQueue();
    void addItem(const myType& newItem);
    myType front() const;
    myType back() const;
    void deleteItem();
    unsigned int queueCount();
    void printQueue();
};

template <class myType> 
linkedQueue<myType>::linkedQueue(unsigned int size){

    if(size < ARR_MIN || size > ARR_MAX){
        size = ARR_DEFAULT; 
    }
    //set front and rear to an empty state
    //front, rear count members
    queueFront = nullptr;
    queueRear = nullptr;
    count = 0;
    this->size = size;
}

template <class myType>
linkedQueue<myType>::~linkedQueue(){
    queueNode<myType> *temp;
    while(queueFront != nullptr){
        temp = queueFront;
        queueFront = queueFront->link;
        delete [] temp->dataSet;
        delete temp;
    }
}

template <class myType>
bool linkedQueue<myType>::isEmptyQueue() const{
    return (this->queueFront == nullptr);
}


template <class myType>
void linkedQueue<myType>::initializeQueue(){
    if(size < ARR_MIN || size > ARR_MAX){
        size = ARR_DEFAULT; 
    }  
}

template <class myType>
void linkedQueue<myType>::addItem(const myType& newItem){
    if(isEmptyQueue()){
        //create a new node
        queueNode<myType> *node = new queueNode<myType>();
        node->dataSet = new myType[this->size];
        //put item into the dataSet
        node->front = 0;
        node->back = 0;
        node->dataSet[0] =  newItem;
        node->link = nullptr;
        this->queueFront = node;
        this->queueRear = node;
    } else {
    //if other queue is full
        if(this->count % this->size == 0){
            //create a new node
            queueNode<myType> *node = new queueNode<myType>();
            node->dataSet = new myType[this->size];
            //put item into the dataSet
            //set f, b, qr, queueFront
            node->front = 0;
            node->back = 0;
            node->dataSet[0] =  newItem;
            node->link = nullptr;
            //link up to new node 
            this->queueRear->link = node;
            this->queueRear = node; 
        } else {
            //q is not full
            this->queueRear->back = (this->queueRear->back + 1) % this->size;
            this->queueRear->dataSet[this->queueRear->back] = newItem;
        } 
    }
    this->count+=1;
}

template <class myType>
myType linkedQueue<myType>::front() const{
    return this->queueFront->dataSet[this->queueFront->front];
}


template <class myType>
myType linkedQueue<myType>::back() const{
    return this->queueRear->dataSet[this->queueRear->back];
}


template <class myType>
void linkedQueue<myType>::deleteItem(){
    //if there is a node and in that node front and back point 
    //to the same index
    if(this->queueFront != nullptr){ 
        if(this->queueFront->front == this->queueFront->back){ 
            queueNode<myType> *temp = this->queueFront;
            this->queueFront = queueFront->link;
            delete[]  temp->dataSet; 
            delete temp;
        } else {
            //if not equal front points to new index
            this->queueFront->front = 
                (this->queueFront->front + 1) % this->size;
        }
        this->count-=1;
    } 
}

template <class myType>
unsigned int linkedQueue<myType>::queueCount(){
    return this->count;
}
#endif