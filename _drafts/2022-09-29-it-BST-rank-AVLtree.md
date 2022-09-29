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

## 과제

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

## Data structures augmentation
**Data structures augmentation** : 데이터 구조가 효율적으로 구현될 수 있도록 기존 데이터 구조에 몇 가지 추가 정보를 추가하는 것을 의미한다<sup><a href="#cite_note-1" title="Augmenting Data Structure">[1]</a></sup>. <a href="https://dapin1490.github.io/satinbower/posts/it-bin-search-tree/" target="_blank" title="[자료구조] Big-O와 이진 탐색 트리">지난 글</a>에서는 트리에서 각 노드가 갖는 자손 노드의 수를 노드 클래스의 멤버 변수로 추가하여 특정 값보다 크거나 작은 값의 개수를 구하는 메소드를 구현했는데, 이것이 Data structures augmentation 자료구조 증강에 해당한다. 편의상 앞으로는 자료구조 증강이라 부르겠다.  
  
### Rank 구현
이진 탐색 트리는 모든 탐색을 루트에서부터 시작하고, 루트에서 수많은 가지로 뻗어나가는 형태이기 때문에 특정 범위의 값에 대한 연산이 곤란한 경우가 있다. 어떤 값보다 큰 요소의 개수, 작은 요소의 개수를 구하는 문제가 이런 문제이다. 이를 해결하기 위해 이진 탐색 트리의 각 노드에 자기 자신을 포함해 해당 노드가 갖는 자손 노드의 수를 멤버 변수로서 함께 저장할 수 있다. 코드는 <a href="https://dapin1490.github.io/satinbower/posts/it-bin-search-tree/" target="_blank" title="[자료구조] Big-O와 이진 탐색 트리">지난번</a>에 이미 보여주긴 했지만 이번엔 내가 그 코드를 구상한 과정을 설명해보겠다.  

## 참고 자료
<ol>
    <li id="cite_note-1"><a href="https://www.includehelp.com/data-structure-tutorial/augmenting-data-structure.aspx" target="_blank" title="">Augmenting Data Structure</a></li>
</ol>