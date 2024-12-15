struct LinkNode{
    int key , value ;
    LinkNode* pre;
    LinkNode* next;
    LinkNode(): key(0),value(0),pre(nullptr),next(nullptr) {}
    LinkNode( int _key , int _value ) : key(_key),value(_value),pre(nullptr),next(nullptr) {}
};

class LRUCache {
private:
    unordered_map< int , LinkNode* > cache;
    LinkNode* head ;
    LinkNode* tail;
    int size;
    int capacity ;
public:
    LRUCache(int _capacity) : capacity(_capacity) , size(0) {
        
        capacity = _capacity;
        head = new LinkNode();
        tail = new LinkNode();
        head->next = tail ;
        tail->pre = head;
    }
    
    int get(int key) {
        if ( !cache.count(key) ) {
            return -1 ;
        }
        LinkNode* tmp = cache[ key ] ;
        moveToHead( tmp ) ;
        return tmp->value;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            LinkNode* tmp = new LinkNode(key , value);
            cache[key] = tmp;
            addToHead(tmp);
            ++size;
            if (size > capacity ) {
                LinkNode* remove = removeTail();
                cache.erase(remove->key);
                delete remove;
                --size;
            }
        } else {
            LinkNode* tmp = cache[ key ] ;
            tmp->value = value;
            moveToHead( tmp );
        }
    }

    void addToHead( LinkNode* node ) {
        node->pre = head ;
        node->next = head->next;
        head->next->pre = node ;
        head->next = node ;
    }


    LinkNode* removeTail() {
        LinkNode* tmp = tail->pre;
        tmp->pre->next = tmp->next;
        tmp->next->pre = tmp->pre;
        return tmp;
    }
    void moveToHead( LinkNode* node ) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
        addToHead( node ) ;
    }

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
