#pragma once

namespace Utility {
template<typename T>
class RotatingList {
  public:
    RotatingList() :pHead(nullptr), pCurrent(nullptr), pTail(nullptr){}
    ~RotatingList(){
        Node* temp = pHead;
        while(temp != nullptr){
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    void addNode(T data) {
        Node* newNode = new Node{ data, nullptr };
        if (pHead == nullptr) {
            pHead    = newNode;
            pTail    = newNode;
            pCurrent = newNode;
        } else {
            pTail->next   = newNode;
            pTail         = newNode;
            newNode->next = pHead;
        }
    }

    void next(){
        pCurrent = pCurrent->next;
    }

    T getContent() const{
        return pCurrent->data;
    }

  protected:
  private:
    struct Node{
        T data;
        Node* next;
    };

    Node* pHead;
    Node* pTail;
    Node* pCurrent;
};

}