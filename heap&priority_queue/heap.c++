#include <iostream>
#include <cstdio>

using namespace std;

template <typename T>
class HEAP {
private:
    int _sz;
    T *heapArr;

    int max(int a, int b) {
            return a>b;
    }

    /*
    * k번째 노드의 자식이 k*2, K*2+1
    * 부모는 k
    * 부모는 /2 로 확인이 가능하며 (k*2)/2 그리고 (k*2+1)/2 로 나타낼 수 있다.
    */
    void push_swap(int cur) {
            if(cur == 1)
                return;

            int par = cur / 2;
            if(heapArr[par] < heapArr[cur]) {
                    T tmp = heapArr[par];
                    heapArr[par] = heapArr[cur];
                    heapArr[cur] = tmp;
                    push_swap(cur / 2);
            }
    }

    /*
    * 왼쪽 자식이 존재한다면 cur*2 가 힙의 크기보다 작거나 같아야 한다 == 자식 존재 여부 판단
    * left와 right를 위와 같은 방식으로 구하고 자식이 없다면 -1 이라는 값으로 set
    * 힙이 완전 이진 트리 기반이기 때문에 왼쪽 자식이 없으면 당연히 오른쪽 자식은 없다.
    */
    void pop_swap(int cur) {
            int left, right, child;
            left = (cur * 2 <= _sz ? cur * 2 : -1);
            right = (cur * 2 + 1 <= _sz ? cur % 2 + 1: -1);

            if(left == -1 && right == -1) 
                    child = -1;
            else if(left != -1 && right == -1)
                    child = left;
            else
                    child = (heapArr[left] > heapArr[right] ? left : right);

            if(child == -1)
                    return;
            // 자신보다 자식이 더 큰 값을 가젔을 때 swap
            if(heapArr[child] > heapArr[cur]) {
                    T tmp = heapArr[child];
                    heapArr[child] = heapArr[cur];
                    heapArr[cur] = tmp;
                    pop_swap(child);
            }
    }

public:
    HEAP(int n) {
        int _sz = 0;
        heapArr = new int[n + 1];
    }
    ~HEAP() {
        delete[] heapArr;
    }

    int empty() {
        return !_sz;
    }

    int size() {
        return _sz;
    }

    T top() {
        return !_sz ? -1 : heapArr[1];
    }

    /*
    * Heap의 마지막 부분에 삽입 (_sz = 힙의 크기)
    */
    void push(int val) {
        heapArr[++_sz] = val;
        push_swap(_sz);
    }

    /*
    * !_sz == 0 이면 pop 할것이 없으니 return
    * 힙의 root를 우선 삭제해주고 힙의 마지막에 위치한 값을 root에 넣어준다 == heapArr[1] = heapArr[_sz--];
    */
    void pop() {
        if (!_sz)
            return;

        heapArr[1] = heapArr[_sz--];
        pop_swap(1);
    }
};

int main() {
    int size;
    cin >> size;
    HEAP<int> pq(size);

    int arr[] = {2, 4, 11, 12, 8, 10, 14, 12, 20};
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) 
        pq.push(arr[i]);

    pq.push(30);
    pq.push(15);

    pq.pop();
    pq.pop();

    cout << "최종적으로 maxheap에서의 root 값 : " << pq.top() << endl;
    return 0;
}