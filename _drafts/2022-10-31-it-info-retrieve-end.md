---
title: "정보 검색 기말고사"
author: dapin1490
date: 2022-10-31T19:01:00+09:00
categories: [지식, IT]
tags: [지식, IT, 정보 검색, 필기]
render_with_liquid: false
---

<style>
	.x-understand { color: #ccb833; }
	.understand { color: #1380da; }
	.tab { white-space: pre; }
	.underline { text-decoration: underline; }
	.green { color: forestgreen;}
	figure { text-align: center; }
</style>

<!--
<span class="x-understand"></span>
<span class="understand"></span>
<span class="tab"></span>
<span class="underline"></span>

[<a id="" href="">1</a>] #####
[<a id="" href="" title="">2</a>] #####, <a href="#" target="_blank">#</a>
<sup><a id="" href="" target="_blank" title=""></a></sup>
-->

## 9주
주제 : 질의어-문서 계산 빠르게 하는 법  
  
**<span class="green">코사인 점수</span>**  
문서 벡터는 tf-idf 점수로 이미 계산되어 있고, 질의 벡터에도 가중치를 줄 수 있다.  
기존의 코사인 점수는 한번에 한 문서씩 계산했다.  
  
코사인 점수를 한번에 한 단어씩 계산하면 문서별로 계산하는 것보다 약간 빨리 계산할 수 있다.  
질의와 모든 문서별로 단어 하나씩 곱해서 각 문서별 결과를 누적합하고(질의에서 0인 건 곱해도 0이니까 곱하지 않음), 곱셈이 끝나면 벡터의 길이로 나누어 점수를 구한다.  
  
**<span class="green">효과적인 코사인 랭킹</span>**  
검색 결과를 반환할 때는 코사인 점수가 높은 k개의 문서를 찾아줘야 한다. 전체 문서가 아주 많으면 코사인 점수를 정렬하는 것도 일이다.  
  
(1) 가중치 없는 질의  
사람은 어떤 숫자에 1을 곱하면 결과는 달라지지 않는다는 것을 알지만 컴퓨터는 CPU를 이용해 실제로 계산한다. 가중치가 주어지지 않은 질의어 벡터로 검색할 때는 어차피 1이니까 곱하지 말자.  
  
(2) 효과적으로 상위 k개 골라내기  
검색 결과로 모든 문서가 필요한 게 아니니 정렬도 모든 문서에 대해 할 필요가 없다. 힙을 쓰자.  
힙은 모든 부모노드가 자식보다 큰 값을 갖는 이진트리이다.  
노드 개수가 1백 만, 결과로 원하는 문서 개수가 100개일 때 결과를 반환하는 데 필요한 연산 횟수는 전체를 정렬하는 경우 O(nlogn) = 6 \* 10<sup>6</sup> * log<sub>2</sub>10이고, 힙을 사용하면 2 \* 10<sup>6</sup> + 600 * log<sub>2</sub>10 ≈ 2 \* 10<sup>6</sup>이다. 600 * log<sub>2</sub>10은 2 \* 10<sup>6</sup>에 비해 무시할만한 수라서 빠졌다.  
요약하자면, 전체 정렬과 힙 사용이 60만:20만 정도로 큰 차이가 나니 힙을 사용한다는 말이다.  
  
**<span class="green">대충 상위 k개 골라내기</span>**  
모든 문서의 코사인 점수를 계산하고 크기까지 비교하는 건 컴퓨터에 많이 부담이 된다. 그래서 상위 k개를 대충 고르기로 했다. 상위 k개를 대충 고르는 대신 빠르다. 애초에 코사인 점수도 정확한 결과를 찾아주는 것이 아니기 때문에 대충 해도 괜찮다.  
  
기본적인 접근 : 원하는 개수(k)보다 많고, 전체 문서 개수(N)보다는 훨씬 적은 양(A)의 문서를 골라낸다. A는 실제 상위 k개의 문서를 포함하지 않을 수도 있지만 그럴 가능성은 높다고 보고, A 중에서만 검색 후 결과를 반환한다. A를 고르는 기준은 5가지가 있다.  
  
1. 인덱스 제거 Index elimination  
	* FastCosineScore 알고리즘은 질의어로 들어온 단어 중 일정 개수 이상이 포함된 문서만 추려서 검색한다.  
	* (1) High-idf query terms only : 질의에서 너무 흔해서(df 큼) 별로 안 중요한 단어를 빼고 검색하자. 흔한 단어의 idf는 작아서 전체 점수에 큰 영향을 못 준다.  
	* (2) Docs containing many query terms : 전체 질의에서 몇 개 이상의 단어가 포함된 문서만 골라 검색하겠다.
2. Champion lists




9주 28페이지부터 이어서
