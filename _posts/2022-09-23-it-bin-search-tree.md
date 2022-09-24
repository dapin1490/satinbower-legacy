---
title: "[자료구조] Big-O와 이진 탐색 트리"
author: dapin1490
date: 2022-09-23T22:35:00+09:00
categories: [지식, IT]
tags: [지식, IT, 자료구조, 이진 탐색 트리, 시간복잡도, Big-O, 과제]
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
1. 스케줄링 문제에 접근하는 이진 탐색 트리 소개(필수) (-> 응답시간 대기시간 등등 말하는 것 같음. "좋은 스케줄링은 프로세서의 효율성을 높이고, 프로세스의 응답시간을 최소화하여 시스템의 작업 처리 능력을 향상시킨다.")
2. Big-O 소개(선택)
3. 문제 풀이
3.1. LeetCode 98, 99, 700, 701(필수)
3.2. 백준 5639, 1539(선택)

LeetCode (ex. https://leetcode.com/problems/validate-binary-search-tree/) 문제는 기본적인 BST 구성으로 천천히 코드를 만들어 보세요.
접속해 보면 BST 구성을 위한 간단한 안내도 함께 있으니, 참조 코드들을 활용하지 않고 수강생 본인이 직접 알고리즘을 만들어 보면 많은 도움이 됩니다.
(선택) 항목인 3.2. 문제는 원하는 학생만 풀어서 작성하면 됩니다.
여러 페이지로 나누어 작성할 시, 다른 접속자들(친구들)이 보기 편하게 다른 페이지를 링크 시켜서 작성하세요.
```  

## 차례
1. Big-O와 여러 가지 예시
2. 이진 탐색 트리(BST), BST의 효율적인 탐색 방법
3. 문제 풀기(링크 첨부)
  
<br>
<hr>
<br>

# Big-O
## 알고리즘의 성능 분석
알고리즘의 성능 분석 방법에는 두 가지가 있다. 알고리즘의 실행 시간을 계산하는 시간 복잡도와 알고리즘이 사용하는 메모리를 분석하는 공간 복잡도이다. Big-O는 둘 중 시간 복잡도를 계산하며, 입력의 크기에 따라 알고리즘이 수행되는 최악의 경우를 상정한다.  
이때 최악의 경우를 상정한다고 해도 식은 가능한 타이트하게 잡는다. 예를 들자면 "어디 살아요?"라는 질문에 "지구에 살아요."라고 대답하면 그것은 너무 광범위한 대답이지만 "ㅁㅁ시에 살아요."라고 대답하는 것이 적절한 것처럼 시간 복잡도도 너무 넉넉하게 계산하지 않는다.  
  
## Big-O의 종류
전제 : 입력의 크기는 `n`이고, 시간 복잡도에서 사용되는 log의 밑은 2이다.  
  
### O(1)
어떤 입력이 들어와도 무조건 같은 횟수의 연산을 한다. 수행 시간 면에서만 본다면 최상의 알고리즘.  
  
### O(logn)
입력의 크기 n이 작을 때는 수행 시간의 상승폭이 크지만, n이 커질수록 수행 시간의 상승폭은 줄어든다. 컴퓨터 사이언스에서 log는 기본적으로 밑을 2로 갖는다고 한다(출처 : 교수님 설명).  
  
### O(n)  
선형 증가. 입력의 모든 요소를 한번씩 확인해야 하는 경우가 이에 해당한다. 예를 들면 정렬되지 않은 배열에서 최댓값 찾기, 배열의 모든 요소의 합 구하기 등이 있다. 시간 복잡도가 이정도만 나와도 준수한 알고리즘이다(출처 : 교수님 설명, 이하 '교수님'으로 표기).  
  
### O(nlogn)
`n ⅹ logn`이다. 여기까지도 괜찮은 알고리즘이다(교수님).  
  
### O(n<sup>2</sup>)
갈수록 상승폭이 커지기 때문에 안 좋은 알고리즘(교수님).  
  
### O(2<sup>n</sup>)
처음부터 발산하기 때문에 쓰면 안 된다(교수님).  
  
## 시간 복잡도 연산
O() 안에 쓰인 식의 계수와 상수항은 전혀 의미가 없고, 무조건 최고차항의 비교만 의미있다. 무한대로 늘어나는 입력에 따른 시간 복잡도 계산 결과에서 가장 큰 영향을 미치는 것은 최고차항이기 때문.  
  
### 예제
- O(1) + O(1) == O(1) ⇒ 참
- O(3n<sup>2</sup>) == O(1/2n<sup>2</sup>) ⇒ 참
  
## 여러 가지 예시
  
### 힙 삽입 연산의 Big-O
**레벨(h) 3, 노드(n) 6개 있는 힙에 새 요소 추가하기**  
최선의 경우 : 어떠한 교환 연산도 일어나지 않음 → O(1)  
최악의 경우 : 새 노드가 루트까지 교환됨 → O(h)  
노드의 개수 n은 (2<sup>h</sup> - 1)로 나타낼 수 있다. 고로 O(logn)이다. 자세한 이항 과정은 생략한다. 이 정도는 할 수 있잖아요.  
  
### 피보나치 수열의 big-o  
> 재귀로 구현한다면 O(2<sup>n</sup>)이지만 이건 loose bound이고, 잘만 하면 이것보다는 낫다는 것을 증명한 사람이 있다. 그건 알아서 찾아보라. (교수님)
  
### 예제 - 오븐
1. 오븐 1개 예약받기
2. 예약 → 오븐에 넣는 시간 t 결정
3. k 시간 예약 없으면 t ∊ R
4. 다 구우면 Extraction
  
계산의 편의를 위해 `k = 2`라고 가정하자. 현재 예약된 시간은 `2, 6, 8, 12, 17, 19, 23`  
현재 예약된 시간의 집합은 R, Big-O는 O(logn)으로 하고 싶다. 어떻게 할 수 있을까?  
  
- 방법  
  
	<ol>
		<li>unsorted array : O(n)</li>
		<li>sorted array : O(n)
			<ol>
				<li>search : O(logn)</li>
				<li>compare : O(1)</li>
				<li>insert : 삽입하려면 전부 자리를 하나씩 움직여야 하므로 O(n) → 이게 문제</li>
			</ol>
		</li>
		<li>(linked) list
			<ol>
				<li>search : O(n) → 삽입 연산은 간단하지만 이게 문제</li>
			</ol>
		</li>
		<li>heap<br>
			힙은 weekly invariant하기 때문에 삽입해도 되는지 검증하려면 모든 노드를 방문해야 한다. 고로 O(n)
		</li>
	</ol>
  
- 제안  
  정렬된 배열의 탐색과 비교 연산, 힙의 삽입 연산을 합치면 O(logn)이 될 수 있다. → 서브트리의 좌우 크기까지 정렬하는 이진 탐색 트리를 쓴다.  
  탐색의 방향이 정해져 있고(탐색 O(h) == O(logn)), 삽입도 간단하니 모든 과정을 합해 O(logn) 가능?  
  
- 문제  
  이진 탐색 트리의 루트 노드는 어떻게 정하나? 잘못 정하면 리스트와 다를 게 없어진다. 높이를 최소화해야 한다.  
  
- 해결  
  양쪽 서브트리의 높이 차이를 1 이하로 유지한다.

- 이진 탐색 트리의 문제  
  서치는 간단하다. 그런데 만약 특정 값보다 작거나 큰 값의 개수를 세고 싶다면?  
  
- 이진 탐색 트리 문제 해결  
  각 노드에 자기 자신을 포함한 자손 노드의 개수를 같이 저장한다.  
  원하는 값을 찾을 때까지 내려가면서  
  (1) 자기 자신보다 작거나 같으면 or 크거나 같으면 +1,  
  (2) 해당 노드의 왼쪽 or 오른쪽 자손 노드의 개수도 더한다.  
  원하는 노드를 찾으면 해당 노드의 개수를 세고 끝낸다.

<br>

# 이진 탐색 트리
급하게 벼락치기한 글 구경하기 : [[자료구조] 이진 탐색 트리](https://dapin1490.github.io/satinbower/posts/it-data-structure-binary-search-tree/)  
  
## 이진 탐색 트리의 기본
[지난 글](https://dapin1490.github.io/satinbower/posts/it-priority-queue-heap/)에서 힙에 대해 공부했다. 이진 탐색 트리는 힙과 달리 서브 트리의 좌우 정렬까지 고려하는 트리이다. 왼쪽의 값이 루트보다 크고, 오른쪽의 값이 루트보다 작다. 간단히 구글에 검색해봤는데, STL 라이브러리는 없고, 직접 구현해야 한다.  
  
## 이진 탐색 트리 설계 및 구현
**코드 출처 : 교수님**  
**개인적 편집 있음**  
  
### 노드
필요한 데이터를 담을 수 있어야 하고, 자신의 왼쪽과 오른쪽 서브트리를 가리켜야 한다. 일단 데이터는 간단하게 `int`로 하자.  
연산은 생성자, 데이터 설정, 좌우 서브트리 설정, 리프노드 여부 등.
  
### 트리
자료형은 노드가 다 알아서 한다. 트리 클래스는 루트 관리, 삽입, 삭제, 탐색 등을 한다.  
  
### 전체 구현 코드 보기
&#42; 웬만한 설명은 다 주석과 출력문에 있다. 코드를 읽기만 해서는 아무리 봐도 이해가 잘 안 돼서 출력문을 잔뜩 추가하고 트리 그림까지 그려봤다. 적어도 어떻게 일이 돌아가는지는 알게 되었다. 출력문 자세히 썼으니 궁금하면 복사해서 직접 실행해보셔라.  

```cpp
#include <iostream>
#include <string>
using namespace std;

class node {
public:
	int data;
	node* left;
	node* right;
};

class bst {
private:
	node* find_impl(node* current, int value) { // private 탐색 메소드
		if (!current) { // 현재 탐색하는 노드가 NULL인 경우
			cout << "No matching value found for " << value << ".\n";
			return NULL;
		}

		if (current->data == value) { // 원하는 값 찾음
			cout << value << " has been found.\n";
			return current;
		}

		if (value < current->data) { // 원하는 값이 더 작음
			cout << "current is " << current->data << ". pointer moved to left.\n";
			return find_impl(current->left, value); // 왼쪽 서브트리로 이동
		}

		// 위의 모든 선택문을 패스했다면 원하는 값이 더 큰 경우임
		cout << "current is " << current->data << ". pointer moved to right.\n";
		return find_impl(current->right, value); // 오른쪽 서브트리로 이동
	}

	void insert_impl(node* current, int value) { // private 삽입 메소드
		if (value < current->data) { // 삽입할 값이 현재 탐색하는 노드보다 작음
			if (!current->left) { // 왼쪽 서브트리 없음
				current->left = new node{ value, NULL, NULL }; // 바로 붙임
				cout << "current is " << current->data << ", " << value << " is inserted left\n";
			}
			else // 왼쪽 서브트리 있음
				insert_impl(current->left, value); // 왼쪽 서브트리에 삽입 메소드 다시 호출
		}
		else { // else: 삽입할 값이 현재 탐색하는 노드보다 크거나 같음
			if (!current->right) { // 오른쪽 서브트리 없음
				current->right = new node{ value, NULL, NULL }; // 바로 붙임
				cout << "current is " << current->data << ", " << value << " is inserted right\n";
			}
			else // else: 오른쪽 서브트리 있음
				insert_impl(current->right, value); //오른쪽 서브트리에 삽입 메소드 다시 호출
		}
	}

	void inorder_impl(node* start) { // private 중위순회(LDR) 메소드
		if (!start) // 현재 탐색중인 노드가 NULL
			return; // 돌아감

		inorder_impl(start->left); // L: 왼쪽 서브트리 순회 호출
		cout << start->data << " "; // D: 현재 노드 데이터 출력
		inorder_impl(start->right); // R: 오른쪽 서브트리 순회 호출
	}

	node* delete_impl(node* start, int value) { // private 특정 값 삭제 메소드
		cout << "current node is " << (start ? to_string(start->data) : "NULL") << ".\n";

		if (!start) { // 현재 노드가 NULL
			cout << "No value matches " << value << ".\n";
			return NULL; // 삭제한 노드 없음, NULL 반환
		}

		if (value < start->data) // 삭제할 값이 현재 노드보다 작음
			start->left = delete_impl(start->left, value); // 왼쪽 서브트리에 삭제 메소드 다시 호출
		else if (value > start->data) // else if: 삭제할 값이 현재 노드보다 큼
			start->right = delete_impl(start->right, value); // 오른쪽 서브트리에 삭제 메소드 다시 호출
		else { // else: 삭제할 값이 현재 노드와 같음
			if (!start->left) { // 왼쪽 서브트리가 없음
				cout << "there is no left subtree. bring the right subtree.\n";
				auto tmp = start->right; // 현재 노드의 오른쪽 서브트리를 가져옴
				cout << "delete " << value << ".\n";
				delete start; // 현재 노드를 지움
				return tmp; // 아까 가져온 오른쪽 서브트리 반환
			}

			if (!start->right) { // 오른쪽 서브트리가 없음
				cout << "there is no right subtree. bring the left subtree.\n";
				auto tmp = start->left; // 현재 노드의 왼쪽 서브트리 가져옴
				cout << "delete " << value << ".\n";
				delete start; // 현재 노드를 지움
				return tmp; // 아까 가져온 왼쪽 서브트리 반환
			}

			cout << "there are both subtrees. need successor.\n";
			auto succNode = successor(start); // 후계자 반환 메소드 호출
			start->data = succNode->data; // 현재 노드의 값을 후계자의 값으로 대체
			start->right = delete_impl(start->right, succNode->data); // 아까 가져온 후계자의 원래 노드 삭제
		}

		return start;
	}

public:
	node* root = nullptr;

	node* find(int value) { // 특정 값 탐색 메소드
		return find_impl(root, value); // 따로 구현된 private 탐색 메소드 호출
	}

	void insert(int value) { // 삽입 메소드
		if (!root) { // 루트가 비어있다면
			root = new node{ value, NULL, NULL }; // 로트에 바로 넣음
			cout << value << " is inserted into root\n";
		}
		else // else: 루트가 비어있지 않다면
			insert_impl(root, value); // 따로 구현된 private 삽입 메소드 호출
	}

	void inorder() { // 중위순회 메소드
		inorder_impl(root); // 호출
	}

	node* successor(node* start) { // 후계자 반환 메소드
		auto current = start->right; // 현재 노드의 오른쪽 서브트리 가져옴

		while (current && current->left) // 지금 갖고있는 노드와 그 노드의 왼쪽 서브트리가 모두 존재하는 동안 반복
			current = current->left; // 왼쪽 서브트리로 이동

		cout << "successor is " << (current ? to_string(current->data) : "NULL") << ".\n";
		return current; // 결과: 오른쪽 서브트리 왼쪽 맨 아래 리프노드 반환
	}

	void deleteValue(int value) { // 특정 값 삭제
		root = delete_impl(root, value); // 호출
	}
};

int main()
{
	bst tree;

	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);
	tree.insert(27);

	cout << "Inorder Traversal: ";
	tree.inorder();
	cout << "\n";

	tree.deleteValue(12);
	cout << "Delete 12 and Do Inorder Traversal: ";
	tree.inorder();
	cout << "\n";

	if (tree.find(12))
		cout << "Value 12 is in the tree.\n";
	else
		cout << "Value 12 is not in the tree.\n";

	tree.deleteValue(11);
	tree.deleteValue(4);
	tree.deleteValue(0);
	tree.inorder();
}
```  
  
## 이진 탐색 트리의 효율적인 탐색
이진 탐색 트리는 그것이 필요한 상황이라는 전제 하에, 특정 값에 대한 연산에는 효율적이다. 하지만 특정 범위에 대한 연산은 어떨까? 예를 들어 위의 예제 코드로 만들어진 트리에서 10보다 큰 값을 개수를 세고 싶다면 어떻게 해야 할까? 교수님은 맛있는 휘낭시에를 걸고 이 문제를 퀴즈로 내셨지만 아무도 시간 내에 맞히지 못했다(*<span class="x-understand">교수님이 주신 시간이 너무 적었다!</span>*).  
교수님이 직접 공개한 정답은 각 노드에 자기 자신을 포함한 자식 노드의 수를 따로 기록하는 것이었다. 교수님의 코드를 개조해서 직접 구현해보고자 했지만 삭제 연산을 제대로 구현하지 못해 실패했다. 우선은 예시 코드에 재귀로 사용된 각종 탐색 메소드부터 반복으로 바꾸고 나서 생각해봐야 할 것 같다. 미래의 제게 맡기겠습니다.  
  
# 문제 풀기

```txt
1. LeetCode 98, 99, 700, 701(필수)
2. 백준 5639, 1539(선택)
```

링크 준비중  
  
<br>
<hr>
<br>

# 참고 자료
1. 『C++로 쉽게 풀어쓴 자료구조』, 천인국ㆍ최영규 지음, 생능 출판사
2. 『코딩 테스트를 위한 자료 구조와 알고리즘 with C++』, 존 캐리ㆍ셰리안 도시ㆍ파야스 라잔 지음, 황선규 옮김, 길벗 출판사