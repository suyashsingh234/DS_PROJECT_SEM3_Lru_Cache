#include <iostream>
#include <map>
using namespace std;
class Node {
    public:
    int key, value;
    Node *prev, *next;
    Node(int k, int v)
    {
        key=k;
        value=v;
        prev=next=nullptr;
    }
};

class DoublyLinkedList {
  Node *front, *rear;

  bool isEmpty() {
      return rear == NULL;
  }

  public:
  DoublyLinkedList(){
    front=rear=nullptr;
  }

  Node* add_page_to_head(int key, int value) {
      Node *page = new Node(key, value);
      if(!front && !rear) {
          front = rear = page;
      }
      else {
          page->next = front;
          front->prev = page;
          front = page;
      }
      return page;
  }

  void move_page_to_head(Node *page) {
      if(page==front) {
          return;
      }
      if(page == rear) {
          rear = rear->prev;
          rear->next = nullptr;
      }
      else {
          page->prev->next = page->next;
          page->next->prev = page->prev;
      }

      page->next = front;
      page->prev = nullptr;
      front->prev = page;
      front = page;
  }

  void remove_rear_page() {
      if(isEmpty()) {
          return;
      }
      if(front == rear) {
          delete rear;
          front = rear = nullptr;
      }
      else {
          Node *temp = rear;
          rear = rear->prev;
          rear->next = nullptr;
          delete temp;
      }
  }
  Node* get_rear_page() {
      return rear;
  }

};

class LRUCache{
  int capacity, size;
  DoublyLinkedList *pageList;
  map<int, Node*> pageMap;

  public:
    LRUCache(int c) {
      this->capacity = c;
      size = 0;
        pageList = new DoublyLinkedList();
        pageMap = map<int, Node*>();
    }

    int get(int key) {
        if(pageMap.find(key)==pageMap.end()) {
          return -1;
        }
        int val = pageMap[key]->value;
        pageList->move_page_to_head(pageMap[key]);
        return val;
    }

    void put(int key, int value) {
      if(pageMap.find(key)!=pageMap.end()) {
          pageMap[key]->value = value;
          pageList->move_page_to_head(pageMap[key]);
          return;
      }

        if(size == capacity) {
          int k = pageList->get_rear_page()->key;
          pageMap.erase(k);
          pageList->remove_rear_page();
          size--;
        }
        Node *page = pageList->add_page_to_head(key, value);
        size++;
        pageMap[key] = page;
    }

    ~LRUCache() {
      map<int, Node*>::iterator i1;
      for(i1=pageMap.begin();i1!=pageMap.end();i1++) {
          delete i1->second;
      }
      delete pageList;
    }
};

int main()
{
  LRUCache cache(2);
  cache.put(2,6);
  cout << cache.get(2) << endl;
  cout << cache.get(1) << endl;
  cache.put(1,1);
  cache.put(1,3);
  cout << cache.get(1) << endl;
  cout << cache.get(2) << endl;
  cache.put(8,9);
  cout << cache.get(1) << endl;
  cout << cache.get(8) << endl;

}
