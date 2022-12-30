---
title: "[UROP] 2주 - 2. 다양한 regression"
author: dapin1490
date: 2022-06-02T00:00:00+09:00
categories: [IT, Machine Learning]
tags: [프로젝트, 지식, IT, 회귀, regression]
render_with_liquid: false
---

<style>
	.x-understand { color: #f59908; }
	.understand { color: #1a9ac1 }
	.more-study { color: #915ee7 }
    .tab { white-space: pre; }
</style>

&#42; <span class="x-understand">노란 글씨</span> : 이해 잘 안 됨  
&#42; <span class="understand">파란 글씨</span> : 이해 후 재서술  

<br>

## 분류
- 단순 선형 회귀
- 다중 선형 회귀
- 로지스틱 회귀
- Cox 비례 회귀

<br>

## 단순 선형 회귀
독립 변수가 1개인 선형 회귀, 2차원 좌표 평면에 나타낼 수 있음. 독립 변수에 대한 함수(비수직 직선)로 가능한 정확하게 종속 변수를 예측함. 각 예측의 정확도는 오차의 제곱으로 측정한다. 오차의 제곱 값이 가능한 한 작도록 만드는 것이 목표이다. 현실의 사건들은 단 한 가지 요소만으로 결정되지 않기 때문에 잘 쓰이지는 않는다고 함.  
  
단순 선형 회귀는 몇 가지 가정을 전제로 한다.([원문](https://datalabbit.tistory.com/48?category=1121492)과 표현의 차이가 있을 수 있음)  
- 독립 변수 x는 상수로 간주한다 : x가 변하는 것까지 예측하기엔 너무 복잡하고 할 일이 많다.  
- 오차항의 기댓값은 0이고, y의 조건부기댓값은 오차항을 제외한 부분과 같다 : <span class="x-understand">내가 이 말 때문에 원문에 있던 식까지 다 같이 보려고 했는데, 개념이 이어지면 이어질수록 통계학이 돼서 중간에 접었다..</span> 이해한 만큼만 말하자면 오차의 총합은 0이고, 기댓값도 0이기 때문에 <span class="understand">y의 조건부기댓값에서 오차가 빠진다는 것 같다. 어차피 0이니까 계산에 의미가 없다는 말.</span> 그리고 조건부기댓값이라 부르는 이유는 상수가 아닌 x를 상수로 간주했기 때문이라고 한다.  
- 오차항의 분산은 σ^2이다 : 오차항의 분산이 상수로 정해져 있다고 한다. 그렇기 때문에 x에 대한 y 값이 퍼진 정도가 모든 구간에서 동일하고, 이 성질을 등분산성이라고 한다. 만약 그렇지 않다면 그것은 이분산성이라고 한다.  
- 서로 다른 오차에 대해 공분산은 0이다 : 서로 다른 오차 사이에는 어떠한 상관관계도 존재하지 않아야 한다. 오차 사이에 관계가 있는 경우도 있다. 예를 들어 시계열 데이터. 이런 경우에는 오차의 패턴도 같이 고려해야 한다.  
  
열심히 따라 적긴 했는데 내가 공부했어야 할 방향과는 좀 다른 것 같다. 아까우니까 지우지는 않고 남기겠습니다..  

<br>

## 다중 선형 회귀
단순 선형 회귀와 비슷하지만 한 가지 다른 점이 있다. 독립 변수를 여러 개 갖는다. 종속 변수는 그대로 1개이다. 좌표 공간에 나타내면 평면이 된다. 다중 선형 회귀는 약간의 전제가 필요하다. 서로 다른 독립 변수끼리는 독립적이어야 한다. 독립 변수와 종속 변수 사이의 관계를 찾는 것이 목적이기 때문에 독립 변수 사이에 관계가 존재할 경우 관계를 분석하기 어렵다고 한다. 그리고 오차가 정규분포를 이루어야 한다고 한다. 독립 변수와 종속 변수 사이에 관계가 있는지는 산점도를 보면 알 수 있다.  

<br>

## 로지스틱 회귀
위키백과는 로지스틱 회귀를 "영국의 통계학자인 D. R. Cox가 1958년에 제안한 확률 모델로서 독립 변수의 선형 결합을 이용하여 사건의 발생 가능성을 예측하는데 사용되는 통계 기법"이라고 정의하고 있다. Cox라는 이름이 눈에 띈다. 이 주제 다음에 쓸 내용이 Cox 비례 회귀인데 이 사람이 그 사람인 것 같다.  
정의를 좀 자세히 보자. "독립 변수의 선형 결합"이 뭘까? 위키백과를 좀 더 읽어보니 <span class="understand">다른 선형 회귀와 마찬가지로 독립 변수들이 갖는 선형의 경향을 말하는 것 같다.</span> 그 다음은 "사건의 발생 가능성"이다. 앞부분만 봤을 때는 다른 회귀와 뭐가 다른가 싶었는데 그 차이가 여기 있었다. <span class="understand">가능성이라 함은 확률을 말하는 것일 테고, 확률은 0과 1 사이의 값만을 갖는다. 출력 범위가 제한된 회귀라는 말이다.</span>  
로지스틱 회귀는 선형 회귀 분석과는 다르게 종속 변수가 범주형 데이터를 대상으로 하며 입력 데이터가 주어졌을 때 해당 데이터의 결과가 특정 분류로 나뉘기 때문에 일종의 분류 (classification) 기법으로도 볼 수 있다고 한다. 그럼 타이타닉 문제도 로지스틱 회귀로 풀 수 있겠네.  
보통 말하는 로지스틱 회귀는 종속 변수가 둘 중 하나의 값만을 갖는 유형이지만 종속 변수의 범주에 따라 다항, 분화, 서수 로지스틱 회귀도 있다고 한다. 이항형 로지스틱 회귀는 종속 변수가 단 두 가지 범주만을 갖고, 각 범주는 0과 1로 표시되며 두 범주에 대한 결과 값의 합은 1이 된다고 한다.  
로지스틱 회귀와 앞서 정리한 선형 회귀의 차이는 두 가지가 있다. 첫 번째는 종속 변수의 범위가 0 이상 1 이하로 제한된다는 것이고, 두 번째는 조건부확률 P(y | x)의 분포가 정규분포가 아닌 이항분포가 된다는 점이다. 종속 변수가 이진적이기 때문이라고 한다. 이 차이점에 해당하는 경우에 대해 로지스틱 회귀가 아닌 선형 회귀를 적용하면 결과 값의 범위가 y의 범위를 벗어나기 때문에 정확도가 떨어진다고 한다.  
  
다른 로지스틱 회귀를 다 공부하기엔 내가 오늘 과제가 있어서 시간이 좀 부족할 것 같고, 내가 하려는 프로젝트는 다항 로지스틱 회귀와 관련이 있을 것 같아서 다항 로지스틱 회귀에 대해서만 추가로 찾아봤다. 다항 로지스틱 회귀는 종속변수가 두 개의 범주로 제한되지 않으므로 로지스틱 회귀분석보다 일반적으로 사용할 수 있다고 한다. 예를 들면 관객이 좋아할만한 영화의 종류를 예측하는 데에 쓸 수 있다.  
다항 로지스틱 회귀를 하기 위한 고려사항이 있다. 종속변수는 범주형이어야 하고, 독립변수는 요인 또는 공분산 변수여야 한다. 요인과 공분산 변수가 뭔지는 통계학을 알아야 하는 것 같다.. 어쨌든 x는 어떠한 분포가 있는 값이어야 하고 y는 몇 가지 선택지로 나뉠 수 있어야 한다는 말로 이해해야겠다. 그리고 독립 변수의 범주끼리는 독립적이어야 한다고 하더라.  

<br>

## Cox 비례 회귀
이것은 생존 분석의 한 종류라고 한다. 생존 분석이란 사망이나 질병 같은 사건이 발생하기까지 걸리는 시간을 분석하는 분석 기법이다. Cox 회귀 분석의 종속 변수가 사건이 발생하기까지 걸리는 시간이다. 이 분석을 통해 생존율에 영향을 미치는 위험 인자를 알아낸다. 예를 들어 폐암 발병 시기에 성별과 흡연량이 미치는 영향 등을 연구할 수 있다고 한다. <span class="x-understand">오늘 정리한 회귀 방법 중 가장 생소한 내용이라 찾아본 자료들은 거의 이해하지 못했다.</span>

<br>

## 참고 자료
1. [회귀 분석(Regression analysis)](https://bioinformaticsandme.tistory.com/70)
2. [Simple linear regression - From Wikipedia, the free encyclopedia](https://en.wikipedia.org/wiki/Simple_linear_regression)
3. [[회귀분석] 단순선형회귀분석(Simple Linear Regression) 개념](https://datalabbit.tistory.com/48)
4. [[머신러닝] 다중 선형 회귀(Multiple Linear Regression)](https://rebro.kr/187?category=511037)
5. [Multiple Linear Regression (MLR) Definition](https://gocardless.com/en-us/guides/posts/multiple-linear-regression-mlr-definition/)
6. [로지스틱 회귀 - 위키백과, 우리 모두의 백과사전.](https://ko.wikipedia.org/wiki/%EB%A1%9C%EC%A7%80%EC%8A%A4%ED%8B%B1_%ED%9A%8C%EA%B7%80)
7. [다항 로지스틱 회귀분석 - IBM Documentation](https://www.ibm.com/docs/ko/spss-statistics/SaaS?topic=regression-multinomial-logistic)
8. [[R 통계분석] 13. 콕스 회귀분석, 콕스 비례-위험 모형(Cox Regression analysis, Cox Proportional-Hazard Model)](https://blog.naver.com/PostView.nhn?blogId=paperfactor_ceo&logNo=222219314059&parentCategoryNo=&categoryNo=7&viewDate=&isShowPopularPosts=true&from=search)
9. [Cox 회귀분석 분석 - IBM Documentation](https://www.ibm.com/docs/ko/spss-statistics/25.0.0?topic=statistics-cox-regression-analysis)