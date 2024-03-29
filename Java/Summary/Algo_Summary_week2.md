# 알고리즘 2

## 정렬
|알고리즘|평균수행시간|최악수행시간|알고리즘 기법|비고|
|:---:|:---:|:---:|:---:|:---:|
|버블 정렬|O(n^2)|O(n^2)|비교와 교환|코딩이 가장 쉽다|
|카운팅 정렬|O(n+k)|O(n+k)|비교환 방식|n이 비교적 작을 때만 가능하다|
|선택 정렬|O(n^2)|O(n^2)|비교와 교환|교환의 회수가 버블, 삽입정렬보다 작다|
|퀵 정렬|O(n log n)|O(n^2)|분할 정복|최악의 경우 O(n^2) 이지만, 평균적으로는 가장 빠르다|
|삽입 정렬|O(n^2)|O(n^2)|비교와 교환|n의 개수가 작을 때 효과적이다|
|병합 정렬|O(n log n)|O(n log n)|분할 정복|연결리스트의 경우 가장 효율적인 방식|


#### 버블 정렬
버블 정렬은 1회전을 수행하면, 가장 큰 값(또는 가장 작은 값)이 맨 뒤로 가게 된다.<br>
그러므로, 1회 수행시마다 안쪽 반복문의 **반복 횟수를 1씩 줄여**나가면 효율적이게 된다.

#### 카운팅 정렬
각 숫자별로 빈도수를 세고, 나보다 작은 수의 갯수 + 1 만큼의 자리가 자리
이를 위해, 0부터 N까지의 인덱스를 갖는 배열을 만들고, 각 인덱스에 해당 숫자의 빈도를 기록

- 한계 : 제약사항이 많다
    - 정수 or 정수형으로 나타낼 수 있는 데이터에만 정렬 가능
    - 가장 큰 정수를 알아야 한다
    - 필요없는 공간을 차지할 수 있다 ( ex. 1, 2, 3, 1000 일 때, 배열은 1000개가 만들어져야 한다 )

## 부분집합 구하기
부분집합의 갯수는 2^n 개 이다

- 부분집합을 구하는 방법
    1. 비트마스크 활용
        - 비트연산자는 비트단위로 연산을 하게 됨. 즉, int형 정수 (4byte : 32 bit)의 32bit 모두에 대하여 각각 자리에 맞게 bit연산을 수행함
        - 그러므로 따로 변한해주지 않아도 bit연산을 하므로 신경쓸게 줄어든다

    ```java
        // 원소가 3개인 집합의 부분집합 구하기
        // bit operator 이용
        // 8은 1<<3 으로 나타낼수 있다.
        String[] fruit
        for(int i = 0; i<8; i++){
            if((1&i) != 0)  // 첫번째 자리 체크
                System.out.println(fruit[i]);
            if((2&i) != 0)  // 두번째 자리 체크
                System.out.println(fruit[i]);
            if((3&i) != 0)  // 세번째 자리 체크
                System.out.println(fruit[i]);
        }

        // 위 코드를 보기 쉽게 변형한 것
        for (int i = 0; i < (1 << 3); i++) {
            for (int j = 0; j < 3; j++) {
                if (((1 << j) & i) != 0) {
                    System.out.print(fruits[j] + " ");
                }
            }
            System.out.println();
        }

    ```


    2. 재귀함수 활용


## 이진검색
자료의 가운데에 있는 항목의 키 값과 비교하여 다음 검색의 위치를 결정하고 검색을 계속 진행하는 방법
    - 목적 키를 찾을 때까지 이진 검색을 순환적으로 반복 수행함으로써 검색 범위를 반으로 줄여가면서 보다 빠르게 검색을 수행함
> 이진 검색을 하기 위해서는 자료가 정렬된 상태여야 한다.

#### 검색 과정
1. 자료의 중앙에 있는 원소를 고른다.
2. 중앙 원소의 값과 찾고자 하는 목표 값을 비교한다
3. 목표 값이 중앙 원소의 값보다 작으면 자료의 왼쪽 반에 대해서 새로 검색을 수행, 크다면 자료의 오른쪽 반에 대해 새로 검색을 수행
4. 1~3의 과정을 반복


## 재귀함수
일반적인 반복문은 반복의 조건에 사용된 변수 중 하나가 반복할 명령문들 안에서 `조작`됨
반복문은 조건이 맞으면 딸린 문장을 수행하고 다시 조건을 확인

일반적인 재귀함수는 `기저영역` 이라고 해서, 특정 조건이 되면 함수를 종료시키는 조건문을 갖게 됨

재귀적으로 자신을 호출할 때는, `기저영역`에서 검사되는 조건에 해당하는 값을 변화시키는게 일반적

#### 재귀함수에서 누적 합 구하기
재귀함수에서 호출 스택공간보다 하나 밖 영역에 변수를 만들어주어서 합을 누적하기
```java

public static void main(String[] args){
    int n = 3;
    static int sum = 0;
    recur(n,0);
}

static void recur(int n){
    if(n==0)
        return;

    sum += n;
    System.out.println(n);
    recur(n-1);
}
```
<span>재귀함수를 이용한 누적합 : 전역변수 활용</span>
```java
public static void main(String[] args){
    int n = 3;

    recur(n,0);
}

static void recur(int n, int sum){
    if(n==0){
        System.out.println(sum);
        return;
    }
    System.out.println(n);
    recur(n-1, sum+n);
}
```
<span> 재귀함수를 이용한 누적합2 : 인자값을 이용</span>


```java
public static void main(String[] args){
    int[] arr = {1,2,3,4};
    travrsalArr(arr,0);
}

// 변수로 인덱스값을 받는다
static void travrsalArr(int[] arr, int idx){
    // 배열의 길이만큼 탐색했으면 종료
    if(idx == arr.length){
        return;
    }
}

System.out.println(arr[idx]);   // 배열 출력
traversalArr(arr,idx+1);
```
<span>재귀함수를 이용한 배열 탐색</span>

### 재귀함수를 이용한 부분집합 구하기
```java
public static void main(String[] args){
    boolean[] sel = new boolean[3];
    powerset(sel,0);
}

static void powerset(boolean[] sel, int idx){
    // idx는 기저조건
    if(idx == sel.length){
        // 배열 길이만큼 탐색을 하였으므로, 출력 후 종료
        System.out.println(Arrays.toString(sel));
        return ;
    }

    // 각각의 상태로 분기해야 하므로, 바꾸고 다음 루틴으로 넘어간다.
    sel[idx] = true;
    powerset(sel,idx+1);
    sel[idx] = false;
    powerset(sel,idx+1);
}
```

> **재귀함수를 전역변수와 함께 쓸 때, 전역변수 초기화에 주의한다!**