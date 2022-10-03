---
title: "[자료구조] 균형 이진 트리, AVL 트리"
author: dapin1490
date: 2022-10-02T22:03:00+09:00
categories: [지식, IT]
tags: [지식, IT, 자료구조, 균형 이진 트리, AVL 트리, 과제]
render_with_liquid: false
---

<style>
	.x-understand { color: #ccb833; }
	.understand { color: #1380da; }
	.tab { white-space: pre; }
  .underline { text-decoration: underline; }
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

# 목차
<ol>
    <li>균형 이진 트리</li>
    <li>AVL 트리
        <ol>
            <li>삽입과 삭제</li>
            <li>회전 유형</li>
        </ol>
    </li>
    <li>AVL 트리 구현</li>
</ol>

<br>
<hr>
<br>

# 균형 이진 트리
&#42; 이 글은 <a href="https://dapin1490.github.io/satinbower/posts/it-bst-rank/" target="_blank" title="">[자료구조] 이진 탐색 트리 Rank</a>에서 이어지는 글이며, 독자가 이진 탐색 트리에 대해 알고 있음을 전제로 한다. 이진 탐색 트리의 개념에 대한 글은 <a href="https://dapin1490.github.io/satinbower/posts/it-bin-search-tree/" target="_blank" title="[자료구조] Big-O와 이진 탐색 트리">여기</a>에서 볼 수 있다.  
  
보통 이진 탐색 트리는 탐색 연산의 시간 복잡도를 O(logn)으로 간주하며, 그것이 최선이다. 그러나 모든 이진 탐색 트리가 최선을 보장하지는 못한다. 예를 들어 정렬된 배열이 순서대로 이진 탐색 트리에 입력되었다고 해보자. 최선을 보장하지 못하는 이진 탐색 트리는 첫 번째 요소를 루트로 하고 다음으로 입력되는 모든 값을 적절한 자리에 넣을 것이다. 결과적으로 그 트리의 모양은 배열과 다를 바 없게 된다. 그러므로 이 트리는 O(n)의 시간 복잡도를 갖는다.  
  
항상 그랬듯이 내가 문제점을 설명하는 건 다 해결하기 위해서다. 어떻게 할 수 있을까? 답은 이 본문의 소제목에 있다. 배열처럼 곧게 뻗은 트리를 구부려 트리처럼 만들어주면 된다. 그것이 균형 트리이고, 지금은 이진 트리에 대해서만 공부하고 있기 때문에 균형 이진 트리이다.  
  
내가 공부하는 교재<sup><a id="body-cite-01" href="#ref-cite-01" title="『C++로 쉽게 풀어쓴 자료구조』, 천인국ㆍ최영규 지음, 생능 출판사">[1]</a></sup>의 설명에 따르면 균형 트리를 만드는 방법은 아주 다양하고 복잡하다고 한다. 그렇기 때문에 책에서는 AVL 트리에 대해서만 설명하였고, 지금은 나도 그에 대해서만 공부할 것이다.  
  
# AVL 트리
> AVL 트리는 Adelson-Velskii와 Landis에 의해 제안된 트리로 각 노드에서 **왼쪽 서브트리의 높이와 오른쪽 서브트리의 높이 차이가 1 이하인 이진 탐색 트리**를 말한다.<sup><a id="body-cite-01" href="#ref-cite-01" title="『C++로 쉽게 풀어쓴 자료구조』, 천인국ㆍ최영규 지음, 생능 출판사">[1]</a></sup>  
  
AVL 트리의 정의는 간단하게 책에 써있는 것을 그대로 인용했다. AVL 트리는 저 균형을 유지하기 위해 트리의 균형이 깨지는 순간 노드를 재배치해 다시 균형 상태로 만든다. 그렇게 함으로써 O(logn)의 연산 시간을 보장한다. 탐색 연산은 이진 탐색 트리와 같고, 바꾸어야 할 것은 삽입과 삭제 연산이다.  
  
삽입과 삭제 연산을 설명하기에 앞서, 트리의 높이에 대해 정의해야 한다. AVL 트리에서 말하는 높이란, 어떤 노드에 대하여 그 노드에서 찾아갈 수 있는 가장 낮은 리프노드까지의 높이 차를 말한다. 리프노드는 자신이 리프노드이기 때문에 높이가 0이고, 리프노드의 부모 노드는 1, 그 위의 노드는 2가 되는 방식이다. 트리 전체의 레벨 수를 의미하는 높이와는 다르다.  
  
## 삽입과 삭제
AVL 트리에 새 요소를 삽입할 때는 통상의 트리 삽입과 같은 연산을 수행한다. 이후 새 요소의 부모 노드의 높이를 업데이트하고 균형을 검사하는 것이다. 새 노드 위의 부모 노드의 균형 상태에 따라 수행할 회전 연산이 결정된다.  
  
삭제 연산도 삽입 연산과 마찬가지로 삭제를 한 후에 균형을 바로잡는다. 이때도 부모 노드의 높이를 업데이트하고 균형을 검사하며, 회전 연산의 유형 결정 방식은 삽입 연산과 동일하다.  
  
삽입 및 삭제의 과정은 참고자료 <a id="body-cite-02" href="#ref-cite-02" title="AVL Tree | Set 1 (Insertion)">[2]</a>, <a id="body-cite-03" href="#ref-cite-03" title="AVL Tree | Set 2 (Deletion)">[3]</a>을 참고하여 서술했다.  
  
## 회전 연산
AVL 트리에서 사용하는 회전 연산은 네 가지 유형이 있다.  
  
`----------------------------------------------`  

혹시나 내가 글을 완성하지 못할 때를 대비해 써둡니다. 코로나 의심 증상이 있어서 검사도 받고 하루 쉬느라 글을 완성하지 못했습니다. 이상 변명 끝.  
  




# 참고 자료
[<a id="ref-cite-01" href="#body-cite-01">1</a>] 『C++로 쉽게 풀어쓴 자료구조』, 천인국ㆍ최영규 지음, 생능 출판사  
[<a id="ref-cite-02" href="#body-cite-02" title="">2</a>] AVL Tree &#124; Set 1 (Insertion), <a href="https://www.geeksforgeeks.org/avl-tree-set-1-insertion/">https://www.geeksforgeeks.org/avl-tree-set-1-insertion/</a>  
[<a id="ref-cite-03" href="#body-cite-03" title="">3</a>] AVL Tree &#124; Set 2 (Deletion), <a href="https://www.geeksforgeeks.org/avl-tree-set-2-deletion/">https://www.geeksforgeeks.org/avl-tree-set-2-deletion/</a>