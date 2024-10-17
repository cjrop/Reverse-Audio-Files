#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

template <class myType>
struct nodeType{
    myType *dataSet;
    unsigned int top; 
    nodeType<myType> *link;
};

template <class myType>
class linkedStack{

private:
    unsigned int size, count;
    nodeType<myType> *stackTop;

    static constexpr unsigned int ARR_MIN = 5;
    static constexpr unsigned int ARR_MAX = 9600;
    static constexpr unsigned int ARR_DEFAULT = 22050;

public:
    linkedStack(unsigned int size = ARR_DEFAULT);
    ~linkedStack();
    bool isEmptyStack() const;
    void initializeStack();
    unsigned int stackCount();
    void push(const myType& newItem);
    myType top() const;
    void pop();
};

/* initializes to zero if min and max aren't met */
template <class myType> 
linkedStack<myType>::linkedStack(unsigned int size){
    if(size < ARR_MIN || size > ARR_MAX){
        size = ARR_DEFAULT;
    }

    this->stackTop = nullptr;
    this->size = size; 
    this->count = 0;
}

/* uses initializeStack() to destry object */
template <class myType>
linkedStack<myType>::~linkedStack(){
    this->initializeStack();
}

template <class myType>
bool linkedStack<myType>::isEmptyStack() const{
    return this->count == 0;
}

/* check if stack is empty then pop */
template <class myType>
void linkedStack<myType>::initializeStack(){

    if(isEmptyStack())
        while(this->count > 0)
            this->pop();
}

/* return total elements */
template <class myType>
unsigned int linkedStack<myType>::stackCount(){
    return this->count;
}

template <class myType>
void linkedStack<myType>::push(const myType& newItem){

    //if empty stack perform
    if(isEmptyStack()){
         
        this->stackTop = new nodeType<myType>();
        this->stackTop->dataSet = new myType[this->size];
        this->stackTop->dataSet[0] = newItem;
        this->stackTop->top = 0; 
        this->stackTop->link = nullptr;

    } else {  //when not empty

        if(this->stackTop->top == (this->size - 1)){
            nodeType<myType>* newNode = new nodeType<myType>();
            newNode->link = this->stackTop;

            newNode->dataSet = new myType[this->size];
            newNode->dataSet[0] = newItem;
            newNode->top = 0;
            newNode->link = this->stackTop;
            this->stackTop = newNode; 

        } else {

            this->stackTop->top+=1; 
            this->stackTop->dataSet[this->stackTop->top] = newItem;

        }
    }
    this->count+=1;
}

template <class myType>
myType linkedStack<myType>::top() const{
    //return top element of stack
    return this->stackTop->dataSet[this->stackTop->top];
}


template <class myType>
void linkedStack<myType>::pop(){
    //pop/remove top element of stack
    if(this->count > 0){
        if(this->stackTop->top == 0){
            nodeType<myType> *temp = stackTop;
            this->stackTop = this->stackTop->link;
            delete [] temp->dataSet;
            delete temp; 
        } else {
            this->stackTop->top-=1;  
        }
        this->count-=1;
    }
}
#endif