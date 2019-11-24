//lru cache
#include <iostream>
#include <map>
using namespace std;
template<typename U,typename V>
class Node {
    public:
    U key;
    V value;
    Node *prev, *next;
    Node(U k, V v)
    {
        key=k;
        value=v;
        prev=next=nullptr;
    }
};
template<typename U,typename V>
class DoublyLinkedList {
  Node<U,V> *front, *rear;

  bool isEmpty() {
      return rear == nullptr;
  }

  public:
  DoublyLinkedList(){
    front=rear=nullptr;
  }

  Node<U,V>* add_page_to_head(U key, V value) {
      Node<U,V> *page = new Node<U,V>(key, value);
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

  void move_page_to_head(Node<U,V> *page) {
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
          Node<U,V> *temp = rear;
          rear = rear->prev;
          rear->next = nullptr;
          delete temp;
      }
  }
  Node<U,V>* get_rear_page() {
      return rear;
  }

};
template<typename U,typename V>
class LRUCache{
  int capacity, size;
  V notfound;
  DoublyLinkedList<U,V> *pageList;
  map<U, Node<U,V>*> pageMap;

  public:
    LRUCache(int c,V n) {
      this->capacity = c;
      this->notfound=n;
      size = 0;
        pageList = new DoublyLinkedList<U,V>();
        pageMap = map<U, Node<U,V>*>();
    }

    V get(U key) {
        if(pageMap.find(key)==pageMap.end()) {
            return notfound;
        }
        V val = pageMap[key]->value;
        pageList->move_page_to_head(pageMap[key]);
        return val;
    }

    void put(U key, V value) {
      if(pageMap.find(key)!=pageMap.end()) {
          pageMap[key]->value = value;
          pageList->move_page_to_head(pageMap[key]);
          return;
      }

        if(size == capacity) {
          U k = pageList->get_rear_page()->key;
          pageMap.erase(k);
          pageList->remove_rear_page();
          size--;
        }
        Node<U,V> *page = pageList->add_page_to_head(key, value);
        size++;
        pageMap[key] = page;
    }

    ~LRUCache() {
      typename map<U, Node<U,V>*>::iterator i1;
      for(i1=pageMap.begin();i1!=pageMap.end();i1++) {
          delete i1->second;
      }
      delete pageList;
    }
};

int main()
{
    cout<<"Integer"<<endl;
    LRUCache<int,int> cache(2,-1);
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

    cout<<"String"<<endl;
    LRUCache<string,string> cache2(2,"-1");
    cache2.put("b","f");
    cout << cache2.get("b") << endl;
    cout << cache2.get("a") << endl;
    cache2.put("a","a");
    cache2.put("a","c");
    cout << cache2.get("a") << endl;
    cout << cache2.get("b") << endl;
    cache2.put("h","i");
    cout << cache2.get("a") << endl;
    cout << cache2.get("h") << endl;

    cout<<"Character"<<endl;
    LRUCache<char,char> cache3(2,'-');
    cache3.put('b','f');
    cout << cache3.get('b') << endl;
    cout << cache3.get('a') << endl;
    cache3.put('a','a');
    cache3.put('a','c');
    cout << cache3.get('a') << endl;
    cout << cache3.get('b') << endl;
    cache3.put('h','i');
    cout << cache3.get('a') << endl;
    cout << cache3.get('h') << endl;

}
