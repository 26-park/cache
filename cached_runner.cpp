#include "cached_runner.h"
#include "task_runner.h"


// TODO: 필요한 함수 구현

CachedRunner::CachedRunner(Cache &cache) : c(cache){
    
};
// 파일의 숫자를 전부 곱하여 반환한다
double CachedRunner::multiply(std::string filename){
    double a;
    if (c.get(filename,a))
    {
        hit+=1;
        return a;
    }else{
        miss+=1;
        a=TaskRunner::multiply(filename);
        c.add(filename,a);
        
        return a;
    }
    
    
    
};

// 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
int CachedRunner::palindrome(std::string filename){
    
    int a;
    if (c.get(filename,a))
    {
        hit+=1;
        return a;
    }else{
        miss+=1;
        a=TaskRunner::palindrome(filename);
        c.add(filename,a);
        
        return a;
    }
}

// 캐시에 히트한 횟수를 반환한다
int CachedRunner::hits(){
    return hit;

};

// 캐시에 미스한 횟수를 반환한다
int CachedRunner::misses(){
    return miss;
};
