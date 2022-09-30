---
title: "[자료구조] 이진 탐색 트리 Rank, AVL 트리"
author: dapin1490
date: 2022-09-29T23:55:00+09:00
categories: [지식, IT]
tags: [지식, IT, 자료구조, 이진 탐색 트리, AVL 트리, 과제]
render_with_liquid: false
---

<style>
	.x-understand { color: #ccb833; }
	.understand { color: #1380da; }
	.tab { white-space: pre; }
</style>

# 과제

```txt
아래 내용을 포함하는 포트폴리오를 작성하고, 웹페이지 주소를 제출합니다.
1. Data structures augmentation 코딩
- Rank 구현
- AVL tree 구현
2. AVL tree 정의 등 강의 내용 정리
*Geeks for geeks 참조하세요.
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
3. Leet code 문제 풀이
https://leetcode.com/problems/balanced-binary-tree/
```  

<br>
<hr>
<br>

# Data structures augmentation
**Data structures augmentation** : 데이터 구조가 효율적으로 구현될 수 있도록 기존 데이터 구조에 몇 가지 추가 정보를 추가하는 것을 의미한다<sup>[<a id="body-cite-1" href="#ref-cite-1" title="Augmenting Data Structure">1</a>]</sup>. <a href="https://dapin1490.github.io/satinbower/posts/it-bin-search-tree/" target="_blank" title="[자료구조] Big-O와 이진 탐색 트리">지난 글</a>에서는 트리에서 각 노드가 갖는 자손 노드의 수를 노드 클래스의 멤버 변수로 추가하여 특정 값보다 크거나 작은 값의 개수를 구하는 메소드를 구현했는데, 이것이 Data structures augmentation 자료구조 증강에 해당한다. 편의상 앞으로는 자료구조 증강이라 부르겠다.  
  
## Rank 구현
이진 탐색 트리는 모든 탐색을 루트에서부터 시작하고, 루트에서 수많은 가지로 뻗어나가는 형태이기 때문에 특정 범위의 값에 대한 연산이 곤란한 경우가 있다. 어떤 값보다 큰 요소의 개수, 작은 요소의 개수를 구하는 문제가 이런 문제이다. 이를 해결하기 위해 이진 탐색 트리의 각 노드에 자기 자신을 포함해 해당 노드가 갖는 자손 노드의 수를 멤버 변수로서 함께 저장할 수 있다. 코드는 <a href="https://dapin1490.github.io/satinbower/posts/it-bin-search-tree/" target="_blank" title="[자료구조] Big-O와 이진 탐색 트리">지난번</a>에 이미 보여주긴 했지만 이번엔 내가 그 코드를 구상한 과정을 설명해보겠다.  
  
<a href="https://github.com/dapin1490/satinbower/tree/main/assets/files/code/countBST.cpp" target="_blank" title="countBST.cpp">전체 코드 깃허브에서 보기</a>  
<a href="https://ideone.com/7FMgZ9" target="_blank" title="countBST.cpp 실행 결과 보기">코드 실행 결과 보기</a>  

### 원래 예시 코드에서 달라진 점
<a href="https://github.com/dapin1490/satinbower/tree/main/assets/files/code/BSTexample.cpp" target="_blank" title="BSTexample.cpp">원래 예시 코드 깃허브에서 보기</a>  
<a href="https://ideone.com/ORGQ01" target="_blank" title="BSTexample.cpp 실행 결과 보기">코드 실행 결과 보기</a>  
  
원래 예시 코드에는 노드 클래스에 멤버 변수만 있고 모든 메소드가 트리 클래스에 있었다. 노드 클래스의 멤버 변수가 public으로 선언되었기 때문에 getter나 setter도 없이 모든 변수에 직접 접근했었다. 내가 Rank를 구현하기 위해 코드를 바꾸기 시작하면서, 이 변수들에 직접 접근하는 건 실수의 여지가 많다고 생각해서 getter와 setter를 만들고 멤버 변수는 모두 private으로 바꿨다. 하는 김에 생성자도 추가했는데 이건 필요해서 했다기보다는 내가 허전해서 만들었다. 어쨌든 일단은 이게 첫 번째이다.  
  
두 번째는 재귀로 구현된 일부 메소드를 반복문으로 바꿨다는 것이다. 루트에서 특정 노드까지 따라가면서 자손 노드의 수를 세도록 만들 계획이었는데, 재귀로 해서는 개수가 제대로 세어지지 않을 게 뻔했기 때문에 최대한 재귀를 없애야 했다. 그 결과 삭제 메소드와 중위순회 메소드를 제외한 모든 메소드를 반복으로 구현할 수 있었다. 삭제 메소드는 포인터를 다루는 부분에서 오류가 났고, 그것을 내 힘으로 고치지 못해서 그대로 두었다. 대안이 있었으니 괜찮다. 그 대안은 나중에 할 코드 설명과 겹치니 그때 설명하겠다.  
  
### 노드 클래스
가장 기본적으로 각 노드가 자신을 포함한 자손 노드의 수를 저장할 수 있어야 한다. 편의상 카운트 변수라고 부르자. 자기자신을 포함하기 때문에 리프노드라도 기본값은 1에서 시작한다. 이 값은 생성자에는 포함하지 않았고 멤버 변수 선언에서부터 초기화했다. 카운트 변수는 자주 증감연산을 할 수 있고, 보통은 1 단위로 증감하기 때문에 외부에서 불 때 구분하기 쉽도록 증감 메소드를 따로 만들었다.  
카운트 변수 이외에도 다양한 getter와 setter를 추가했고, 해당 노드가 리프노드인지 확인하는 메소드도 추가했다. 리프노드 확인 메소드는 삭제 연산에서 사용한다.  

```cpp
class node {
private:
  int data;
  node* left;
  node* right;

  int cnt = 1;

public:
  node(int d, node* l, node* r) {
    data = d;
    left = l;
    right = r;
  }
  ~node() {}

  int getData() { return data; }
  node* getLeft() { return left; }
  node* getRight() { return right; }
  int getcnt() { return cnt; }

  void setLeft(node* le) { left = le; }
  void setRight(node* ri) { right = ri; }
  void upcnt() { cnt += 1; }
  void downcnt() { cnt -= 1; }
  void setData(int d) { data = d; }

  bool isLeaf() { return left == nullptr && right == nullptr; }
};
```  
  
### 트리 탐색 메소드
탐색을 재귀에서 반복으로 바꾸는 것은 쉽다. 재귀 호출이 있던 부분을 모두 서브트리로 이동하는 것으로 바꾸고, 탐색의 모든 과정을 while 반복문 안에 넣으면 된다. 탐색이 끝나면 결과를 바로 return한다. 특정 값을 찾는 탐색은 트리를 전혀 조작하지 않기 때문에 카운트 변수와는 상관이 없다. public 메소드와 private 메소드가 따로 구현된 것은 원래의 예시 코드를 그대로 따랐다.  
```cpp
private:
  node* find_impl(node* current, int value) { // private 탐색 메소드
    while (true) {
      if (current == nullptr) { // 현재 탐색하는 노드가 NULL인 경우
        cout << "No matching value found for " << value << ".\n";
        return NULL;
      }

      if (current->getData() == value) { // 원하는 값 찾음
        cout << value << " has been found.\n";
        return current;
      }
      else if (value < current->getData()) { // 원하는 값이 더 작음
        cout << "current is " << current->getData() << ". pointer moved to left.\n";
        current = current->getLeft(); // 왼쪽 서브트리로 이동
      }
      else { // 위의 모든 선택문을 패스했다면 원하는 값이 더 큰 경우임
        cout << "current is " << current->getData() << ". pointer moved to right.\n";
        current = current->getRight(); // 오른쪽 서브트리로 이동
      }
    }
  }

public:
  node* find(int value) { // 특정 값 탐색 메소드
    return find_impl(root, value); // 따로 구현된 private 탐색 메소드 호출
  }
```  




# 참고 자료
[<a id="ref-cite-1" href="#body-cite-1">1</a>] Augmenting Data Structure <a href="https://www.includehelp.com/data-structure-tutorial/augmenting-data-structure.aspx" target="_blank" title="Augmenting Data Structure">https://www.includehelp.com/data-structure-tutorial/augmenting-data-structure.aspx</a>