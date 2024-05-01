#include "cache.h"
#include <sstream>
#include <iostream>

Cache::Cache() {
    // Cache 객체 생성 시 초기화 작업 수행
    // 초기화할 내용이 없다면 생략 가능
    first.next=nullptr;
    
}

Cache::~Cache() {
    node* current = first.next; // 첫 번째 노드를 가리키는 포인터
    while (current != nullptr) {
        node* next = current->next; // 다음 노드를 임시로 저장
        delete current; // 현재 노드 삭제
        current = next; // 다음 노드로 이동
    }
}
int hashFunction(std::string key){
    int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % CACHE_SIZE;
        }
        return hash;

}
void Cache::add(std::string key, int value) {
   
    node* newNode = new node;
    newNode->val=new int(value);
    newNode->keyValue=key;
    newNode->next = first.next;
    
    
    first.next = newNode;
    cashsize++;
    if (cashsize > CACHE_SIZE) {
        node* current = &first;
        node* prev = nullptr;
        while (current->next != nullptr) {
            prev = current;
            current = current->next;
        }
        
        
        // 노드 삭제
        delete current; 
        prev->next = nullptr; // 이전 노드의 next를 nullptr로 설정하여 리스트에서 삭제한 노드 제거
        cashsize--;
    }


        


    }
    


void Cache::add(std::string key, double value) {
    
    node* newNode = new node;
    
    newNode->val=new double(value);
    newNode->keyValue=key;
    newNode->next = first.next;
    
    
    first.next = newNode;
    cashsize++;
    if (cashsize > CACHE_SIZE) {
        node* current = &first;
        node* prev = nullptr;
        while (current->next != nullptr) {
            prev = current;
            current = current->next;
        }

        

        delete current; // 노드 삭제
        prev->next = nullptr; // 이전 노드의 next를 nullptr로 설정하여 리스트에서 삭제한 노드 제거
        cashsize--;
    }
    
}

bool Cache::get(std::string key, int &value) {
    bool flag = false;
    node *current = &first; // 헤드 노드부터 시작
    
    node *nex;

    
    
    // 주어진 키에 해당하는 노드와 그 이전 노드를 찾음
    while (current->next != nullptr) { 
        
        nex = current->next;
        if (nex->keyValue == key)
        {
            flag=true;
            break;
        }
        
        current = current->next;
    }
    
    if (flag) {
        if (nex->next!=nullptr)
        {
            node *target = nex; // 찾은 노드
            node *before = current;       // 이전 노드

            // 찾은 노드를 링크드 리스트의 맨 앞으로 이동
            before->next = target->next;
        

            // 값을 가져옴
            value = *(static_cast<int*>(target->val));
            cashsize--;
            Cache::add(key,value);
        }else{
            cashsize--;
            Cache:add(key,value);

            current->next=nullptr;
        }
        
        
    }
    
    
    
    return flag;
}

bool Cache::get(std::string key, double &value) {
    bool flag = false;
    node *current = &first; // 헤드 노드부터 시작
    
    node *n;
    // 주어진 키에 해당하는 노드와 그 이전 노드를 찾음
    while (current->next != nullptr) { 
        
       n = current->next;
        if (n->keyValue == key)
        {
            flag=true;
            break;
        }
        
        current = current->next;
    }//n->current
    
    if (flag) {//current->n
        if(n->next!=nullptr){
            // 찾은 노드를 링크드 리스트의 맨 앞으로 이동
            current->next = n->next;
        

            // 값을 가져옴
            value = *(static_cast<double*>(n->val));
            cashsize--;
            Cache::add(key,value);


        }else{
            cashsize--;
            Cache::add(key,value);
            current->next=nullptr;

        }

        
    }
    
    

    return flag;
}

std::string Cache::toString() {
    std::stringstream ss;
    
    node* current=&first;
    
    current=current->next;
    while (current != nullptr) {
        
        std::string s=current->keyValue;
        if (s.find("multiply")!=std::string::npos)
        {   
            if (current->next!=nullptr)
            {
                ss << "[multiply(" << s << "): " << *(static_cast<double*>(current->val)) << "] -> ";
            }else{
                ss << "[multiply(" << s << "): " << *(static_cast<double*>(current->val)) << "]";
            }
            
            
        }else{
            if (current->next!=nullptr)
            {
                ss << "[palindrome(" << s << "): " << *(static_cast<int*>(current->val)) << "] -> ";
            }else{
                ss << "[palindrome(" << s << "): " << *(static_cast<int*>(current->val)) << "]";
            }
            
        }
        
        
        current = current->next;
       
        
    }
    
    return ss.str();
}





  