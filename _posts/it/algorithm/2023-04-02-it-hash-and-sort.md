---
title: "[알고리즘] 해시와 정렬"
author: dapin1490
date: 2023-04-02T00:00:00+09:00
categories: [IT, Algorithm]
tags: [지식, IT, 알고리즘, 선택 문제]
render_with_liquid: false
---

<style>
  figure { text-align: center; }
</style>

## Table of Contents
- [할 일](#할-일)
- [선형 중앙값 찾기](#선형-중앙값-찾기)
  - [덤 - pivot 잘 고르기](#덤---pivot-잘-고르기)
- [참고 자료](#참고-자료)

# 할 일
1. Describe linear median finding algorithm. Show that its time complexity is Θ(n).
2. In hashing function, why the coefficient a should not be 0?
3. Read chapter 8.4. Solve example 8.1 in the chapter. (X)
4. Use the birthday dataset, do the followings:
    1. Put them into your unsorted array using set.
    2. Order them with the birth day. You should consider the following algorithms.
        * Basic quick sort  
          Pivot X = A[0] or A[n-1]
        * Intelligent quick sort  
          Pivot X = median of A
        * Paranoid quick sort  
          Pivot X = E(Good choice)
        * Tuple sort  
            1. The month comes first, and the date second
            2. The date comes first, and the month second
    3. Compare the sorting algorithms

1. 선형 중앙값 찾기 알고리즘을 설명합니다. 시간 복잡도가 Θ(n)임을 나타냅니다.
2. 해싱 함수에서 계수 a가 0이 아니어야 하는 이유는 무엇입니까?
3. 8.4장을 읽는다. 이 장의 예제 8.1을 풉니다. (X)
4. 생일 데이터 집합을 사용하여 다음을 수행합니다:
    1. unsorted array using set 사용하여 정렬되지 않은 배열에 넣습니다.
    2. 생일을 기준으로 정렬합니다. 다음 알고리즘을 고려해야 합니다.
        * Basic quick sort  
          피벗 X = A[0] 또는 A[n-1]
        * Intelligent quick sort  
          피벗 X = A의 중앙값
        * Paranoid quick sort  
          피벗 X = E(좋은 선택)
        * Tuple sort  
            1. 월이 첫 번째, 날짜가 두 번째
            2. 날짜가 먼저 오고 월이 두 번째
    3. 정렬 알고리즘 비교

# 선형 중앙값 찾기
할 일: 선형 중앙값 찾기 알고리즘을 설명합니다. 시간 복잡도가 Θ(n)임을 나타냅니다.

일반적으로 중앙값의 정의에 따라 중앙값을 찾는다고 하면, 정렬을 해야 하기 때문에 아무리 빨라도 `O(n log n)`이다. 그런데 여기 n log n에 만족하지 못한 누군가가 더 빠른 중앙값 찾기 알고리즘을 만들어뒀다. 내가 만든 건 아니고, 무공 비급서처럼 전해지는 알고리즘을 공부해서 이해한 대로 설명할 뿐이다.

이 알고리즘을 이해하려면 퀵 정렬에 대해 먼저 알면 좋다. 퀵 정렬은 배열에서 pivot을 선택하고, pivot의 값을 기준으로 배열을 반으로 나누어(≠ 이등분) 반씩 부분적으로 정렬해나가는 알고리즘이다. 이 원리를 오로지 중앙값을 찾는 데에만 집중한 알고리즘이 선형 중앙값 찾기 알고리즘이다.

퀵 정렬은 정렬이기 때문에 모든 요소가 몇 번째로 와야 하는지 찾는 것과 같다. 그렇기 때문에 배열을 pivot의 좌우로 나눴을 때, 양쪽 부분 배열 모두에 대해 재귀적으로 정렬을 수행한다. 그러나 중앙값을 찾을 때는 그럴 필요가 없다. 중앙값은 항상 가운데에 있는 값이기 때문에 두 부분 배열 중 가운데에 와야 할 값이 포함된 쪽만 다시 확인하고 나머지는 냅둬도 된다. 알고리즘의 수행 과정은 다음과 같다.

1. pivot을 고른다.
2. pivot을 기준으로 왼쪽에는 pivot보다 작은 값, 오른쪽에는 pivot보다 큰 값을 모아 배열을 반으로 나눈다.
3. 두 부분 배열의 길이와 전체 배열에서 중앙값이 위치해야 하는 인덱스를 고려해, 중앙값이 존재할 부분 배열에 대해서만 위 과정을 반복한다.
4. 중앙값을 찾으면 종료한다.

위 과정대로 하면 pivot을 잘 골랐다고 할 때, 크기가 n인 배열에 대해 매 반복마다 대략 n/2으로 길이가 줄어들기 때문에 O(log n), 부분 배열의 요소를 전부 확인하기 때문에 O(n), 합쳐서 O(n log n) 시간으로 중앙값을 찾을 수 있고, 만약 pivot이 항상 남은 배열 중 최댓값 혹은 최솟값이라서 모든 요소를 확인할 수밖에 없었다고 한다면 O(n²)이다.

지금은 중앙값에 대해서만 얘기했지만, 위 방법을 응용하면 특정 인덱스의 값을 찾는 것도 가능하다.

## 덤 - pivot 잘 고르기
퀵 정렬과 선형 중앙값 알고리즘 모두 pivot을 잘못 고르면 시간복잡도가 최악으로 치닫는다. 잘못 고른 pivot이 문제라면 pivot을 잘 고르면 된다!

pivot을 잘 고른다는 게 무슨 말일까? pivot을 잘 고르면 어떻게 될까? 잘못 고른 pivot은 배열을 균등하게 나누지 못하고 한쪽에 너무 많은 요소가 치우치게 만든다. 반대로 말하면 잘 고른 pivot은 배열을 균등하게 나눌 수 있고, 한쪽에 너무 많은 요소가 치우치지 않게 만든다고 볼 수 있다.


# 참고 자료
1. 선형 시간에 중간값 구하기 (Quick-Select & Median-of-Medians), <a href="https://gazelle-and-cs.tistory.com/58" target="_blank">https://gazelle-and-cs.tistory.com/58</a>


<!--
<style> // _layouts\post.html에 지정된 스타일
  .x-understand { color: #ccb833; }
  .understand { color: #0099FF; }
  .tab { white-space: pre; }
  .underline { text-decoration: underline; }
  .cancle { text-decoration: line-through; }
  .green { color: #339966; }
</style>

<a href="" target="_blank"></a>

<span class="x-understand"></span>
<span class="understand"></span>
<span class="tab"></span>
<span class="underline"></span>
<span class="cancle"></span>
<span class="green"></span>

<code class="language-plaintext highlighter-rouge"></code>

[<a id="" href="">1</a>] 참고자료1
[<a id="" href="" title="">2</a>] 참고자료2, <a href="링크" target="_blank">링크</a>
<sup><a id="" href="" target="_blank" title=""></a></sup>

<figure>
  <img src="/assets/img/category-#/#">
  <figcaption>이미지 이름</figcaption>
</figure>

<details>
  <summary>더보기</summary>
  <figure>
    <img src="/assets/img/category-#/#">
    <figcaption>이미지 이름</figcaption>
  </figure>
</details>

<details>
  <summary>더보기</summary>
  <p></p>
</details>
-->