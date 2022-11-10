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
- 코사인 점수 계산 줄이는 방법 : 문서별 계산 X, 단어별로 계산하기, 0은 곱하지 않기
  
### 코사인 점수 랭킹 효과적으로 골라내기
**검색 결과를 반환할 때는 코사인 점수가 높은 k개의 문서를 찾아줘야 한다. 전체 문서가 아주 많으면 코사인 점수를 정렬하는 것도 일이다.**  
- 더 빠른 코사인 점수 : 가중치 없는 쿼리 계산 안 하기.
- 상위 k개 문서 효과적으로 고르기 : 힙 사용. 노드 1백만 개, 결과 문서 100개라고 치면 전체 정렬과 비교해서 연산 횟수가 60만:20만 정도로 차이남.
- 대충 고르기 : 덜 정확하지만(코사인 점수도 정확한 거 아니니까 상관 없음) 빠름. 먼저 검색 대상 그룹을 한정하고(전체 문서 수보다는 적지만 필요한 결과 수보다는 많게) 그 안에서만 고름. 추려낸 문서는 실제 상위 k개 문서를 포함하지 않을 수 있지만 가능성은 높다고 봄. 아래는 검색 대상 그룹을 한정하는 방법들
	1. Index elimination : 질의로 들어온 단어 중 최소 하나 이상이 포함된 문서만 추리기. 아래는 추가로 추리는 방법.
		- idf가 높은 단어만 검색하기 : idf가 낮은 건 별로 안 중요한 단어다. 흔한 단어의 idf는 작아서 전체 점수에 큰 영향을 못 준다.
		- 전체 질의에서 몇 개 이상이 포함된 문서만 골라 검색하기
	2. Champion lists : tf 기준 상위 r(> k)개의 문서. 인덱싱할 때 미리 만들어둠.
	3. Static quality scores : 문서의 권위를 수치화(문서의 권위: 얼마나 믿을만한 문서인지). 질의와 무관하니 static함. 챔피언 리스트와 결합 가능
	4. Impact ordering : 모든 문서를 w<sub>t,d</sub> 순으로 정렬 (w<sub>t,d</sub>는 tf \* idf). 이 정렬로 상위 k개 문서 고르는 방법 2가지
		- 조기종료 : 검색 도중 정해진 개수의 문서를 다 봤거나, w<sub>t,d</sub>가 미리 정해둔 값보다 떨어지면 검색하지 말자
		- idf순 단어 : idf 값이 미리 정해진 값보다 큰 것만 계산하자. Index elimination에도 적용 가능
	5. Cluster pruning(가지치기)
		- 전처리 : 전체 문서 중 √n개 추출해(랜덤 샘플링) 리더 임명 후 유사도 계산해 비슷한 것끼리 군집화
		- 쿼리 전처리 : 질의와 리더들의 유사도 계산 후 유사도가 높은 클러스터만 검색
		- General variants : 전처리 단계에서 각 팔로워가 여러 리더를 따르도록 처리, 질의를 처리할 때 여러 개의 클러스터에 대해 검색하도록 함 → 결과가 정확해질 가능성이 높아지지만 계산량 많아짐
- Tiered indexes : 포스팅 리스트를 둘 이상의 티어로 나누어 생성, 높은 티어부터 검색. 티어는 인덱스 생성 시 분류함.
- Query parsers : 사용자가 free text로 검색하면 파서가 1개 이상의 쿼리 생성해 검색, 다 해봐도 안 되면 벡터 검색
- Aggregate scores : 여러 방식으로 검색한 결과의 score 합치기. 전문가가 튜닝하거나 기계학습 이용.
- Vector Space Model vs Boolean Model : 벡터 모델의 인덱스는 불린 모델 검색에도 사용 가능, 역은 불가능

