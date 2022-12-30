---
title: "[UROP] 1주 - 2. CNN 스터디"
author: dapin1490
date: 2022-05-26T00:00:00+09:00
categories: [IT, Machine Learning]
tags: [프로젝트, 지식, IT, CNN, 딥러닝, 과학]
render_with_liquid: false
---

<style>
	.x-understand { color: #f59908; }
	.understand { color: #1a9ac1 }
	.more-study { color: #915ee7 }
	.tab { white-space: pre; }
</style>

<p>
	* <span class="x-understand">노란 글씨</span> : 이해 잘 안 됨<br>
	* <span class="understand">파란 글씨</span> : 이해 후 재서술<br>
	* <span class="more-study">보라색 글씨</span> : 더 찾아볼만한 개념<br>
</p>
<p>
	<h2>개요</h2>
	<ul>
		<li><strong>CNN, Convolutional Neural Networks</strong> : 딥러닝에서 주로 이미지나 영상 데이터를 처리할 때 쓰이며, Convolution이라는 전처리 작업이 들어가는 Neural Network 모델.</li>
		<li><strong>왜 CNN을 사용할까?</strong> - DNN에 문제가 있었기 때문<br>
			DNN은 1차원 데이터만을 사용할 수 있다. 그러니 2차원 데이터를 DNN에 입력하려면 1차원으로 뭉개야 하고 그것으로 원본 데이터의 공간적, 지역적 정보가 손실된다. 그리고 추상화(abstractions, 다량의 데이터나 복잡한 자료들 속에서 핵심적인 내용 또는 기능을 요약하는 작업) 과정 없이 바로 연산하기 때문에 비효율적이다.<br>
			CNN은 2차원 데이터를 그대로 사용할 수 있다. 원본 데이터의 공간적, 지역적 정보를 보존한 채로 그 이미지의 특성을 층층이 쌓아간다. CNN은 전체보다는 부분, 그리고 부분에서도 각 픽셀 사이의 연관성을 알아낸다.<br>
			어떤 이미지로부터 필요한 정보를 알아낼 때(예: 이 사진이 새의 사진인가?), 반드시 이미지의 전체가 필요하지는 않다. 특징적인 일부분만 있으면 된다(예: 새의 부리). CNN이 이 특징 부분을 잘라주는 역할을 한다. 또한 특징 부분은 언제나 같은 위치에 있지는 않기 때문에 이미지의 부분부분을 잘 확인하는 게 전체를 보는 것보다 효율적이다.</li>
	</ul>
</p>
<p>
	<h2>원리</h2>
	<ul>
		<li><strong>사전 개념</strong> : 2차원 이미지는 픽셀 단위로 구성되어 있다. 가로 w, 세로 h인 이미지는 (w, h) 크기의 행렬로 나타낸다. 이 행렬을 CNN의 입력값으로 사용한다.</li>
		<li><strong>커널</strong> : 이미지의 특징을 걸러내기 위한 필터. 입력 이미지와 마찬가지로 (n, m) 크기의 행렬이다. 이것으로 이미지를 창문 닦듯이 훑어가며 행렬 간의 내적 연산을 한다.</li>
		<li><strong>행렬 내적</strong> : 같은 크기의 두 행렬을 놓고, 서로 같은 위치에 있는 요소끼리 곱해 모든 값을 더한다.</li>
		<li><strong>커널이 지나가고 나면</strong> : 보통은 입력 이미지보다 작고 (1, 1)보다는 큰 커널을 사용할 테고, 그렇게 되면 커널이 지나간 후 나오는 결과 이미지는 원본보다 작아지는 것이 당연하다. (1, 1) 크기의 커널을 사용하면 이미지의 크기는 줄어들지 않을 테지만 특징을 추출하는 효과도 없다!</li>
		<li><strong>패딩</strong> : 커널은 쓰고 싶지만 이미지의 크기는 줄이고 싶지 않을 수 있다. 그럴 때 사용하는 것이 패딩. 이미지의 주변에 0으로 채워진 테두리를 둘러 크기를 키워, 커널이 지나간 후 이미지가 줄어들어서 원래 크기가 되게 만든다.</li>
		<li><strong>stride</strong> : 커널을 꼭 한 칸씩만 움직여야 한다는 법은 없다. 원한다면 두 칸 세 칸씩 움직여도 된다! 그 값을 지정하는 것이 stride. 이 값이 클수록 결과 이미지는 작아진다.</li>
		<li><strong>order-3 tensor</strong> : 컬러 이미지는 R, G, B 세 가지 값으로 색이 나뉘기 때문에 3차원 행렬이 된다. 이런 모양을 order-3 tensor라고 부르는데 연산 방법은 2차원 행렬과 똑같다. 그러므로 결과 이미지는 마찬가지로 2차원 행렬이 된다.</li>
	</ul>
</p>
<p>
	<h2>구조</h2>
	CNN은 모든 층과 노드가 연결되어 있던 DNN과는 구조가 좀 다르다. 근데 이 설명은 말로만 하면 어렵다. 자세한 설명은 아래 참고자료에서 찾자.<br>
	<ol>
		<li><strong>컨볼루션 층</strong> : 이 층에서는 앞서 설명한 커널을 이용한다. 커널은 한 번에 여러 개 사용할 수 있다. 한 층에 커널이 3개 있다면 결과 이미지도 3개, 5개 있다면 결과도 5개 나온다. 이 결과에 활성화 함수를 적용해 다음 층으로 값을 넘긴다.
			<ul>
				<li><strong>활성화 함수</strong> : 요약하자면 선형 함수(linear function)인 컨볼루션에 비선형성(nonlinearity)을 추가하기 위해 사용한다고 한다. <span class="understand">내가 이해한 대로 다시 설명해보자. 우선 선형이라 함은 직선을 이른다. 수학에서 직선은 일차방정식이고, 일차방정식은 미분하면 상수가 된다.</span> 오차 역전파는 미분이 기본인데 미분한 값이 상수가 되어버리면 입력값(x)과 출력값(y)의 관계성이 전혀 없으니 역전파의 의미가 없어진다. 참고한 글을 인용하자면 “입력 뉴런의 어떤 가중치가 더 나은 예측을 제공할 수 있는지 이해하는 것은 불가능합니다”라고 한다. 또한 이런 직선의 층이 이어져봐야 아무리 층이 많아도 결과적으로는 첫 번째 층의 선형 함수가 될 뿐이다. 그러니 (1) 오차 역전파를 수행하고, (2) 은닉층을 단순하게 만들지 않기 위해 비선형 활성화 함수가 필요하다.</li>
			</ul>
			활성화 함수는 그럼 무슨 역할을 하나? 해당 층에서 계산한 값을 다음 층으로 넘길지 말지, 또는 어떤 값으로 바꾸어서 넘길지 정한다. 은닉층에 있는 각 노드의 on/off 스위치이다. 이 함수가 비선형 함수이면 위의 두 가지 문제가 해결된다. 미분해도 입력과 출력의 관계성이 사라지지 않기 때문에 역전파가 가능하고, <span class="x-understand">여러 개의 은닉층을 “쌓을 수 있다”고 한다</span>(← 출력이 여러 레이어를 통과하는 입력의 비선형 조합이 되므로 뉴런의 여러 레이어를 쌓을 수 있다). 자료를 좀 더 찾아봤는데, 활성화 함수는 다음 층으로 넘길 신호의 세기를 결정한다고 한다. 중요한 신호는 세게, 그렇지 않은 신호는 약하게.
		</li>
		<li><strong>풀링 층</strong> : 풀링의 개념에 대해서는 지난 스터디에서 살펴본 바 있지만 다시 공부하자.
			<ul>
				<li><strong>풀링</strong> : 풀링은 이전 층인 컨볼루션 층에서 나온 결과 이미지의 크기를 줄이는 것이 목적이다. 이때 줄인다는 그 “크기”는 컨볼루션의 결과로 나온 이미지의 개수가 아니라 행렬의 가로 세로 크기이다. 내가 참고한 글에서는 상관관계가 낮은 부분을 지워서 이미지의 크기를 줄인다고 했다. 풀링은 대표적으로 최댓값 풀링과 평균값 풀링이 있다. 풀 사이즈(이미지를 얼마나 줄일지에 따라 다름)에 따라 나눠진 구역 안에서 최댓값만을 남기는지, 평균값을 남기는지의 차이이다.</li>
			</ul>
		</li>
		<li><strong>필요한 만큼 컨볼루션+풀링 반복</strong> : 과정을 거듭할수록 작고 두꺼운 데이터가 만들어진다. 행렬의 크기가 작고, 그 행렬들이 여러 개 겹쳐서 두꺼운 데이터라는 말이다.</li>
		<li><strong>Flatten</strong> : 지금까지 만든 작고 두꺼운 이미지 데이터를 쭉 펼쳐 1차원 데이터로 만든다. 원본 이미지를 뭉개는 것과의 차이는, 원본 이미지는 아무 연산도 하지 않은 진짜 이미지 데이터였기 때문에 그걸 1차원으로 뭉개면 그나마 있던 특징도 다 흩어지지만, 컨볼루션 이후의 데이터는 이미지의 특징만을 모아놓은 데이터이기 때문에 형태를 바꾸어도 특징이 유지된다는 점이다. 그래서 1차원으로 바꿔도 된다.</li>
		<li><strong>Dense 층과 softmax</strong> : 결과 출력을 위한 층이다. Dense 층은 하나 이상 쓰면 된다.</li>
	</ol>
</p>
<p>
	<h2>파라미터(Parameter)와 하이퍼파라미터(Hyper-parameter)</h2>
	<ul>
		<li><strong>지난 스터디 복기</strong> : 파라미터는 모델 내부에서 알아서 학습하고 설정하는 값, 내가 건드릴 수 없음. 하이퍼파라미터는 내가 사전에 정해줘야 하는 값, 모델이 건드릴 수 없으니 다른 알고리즘을 이용하거나 경험적으로 적당히 골라야 함.</li>
	</ul>
	<ul>
		<li><strong>학습 가능한 파라미터의 수</strong>
			<ul>
				<li><strong>컨볼루션</strong> : 커널 크기 × 커널 개수 (× 사용한 텐서 개수)</li>
				<li><strong>풀링</strong> : 크기만 줄이기 때문에 파라미터 없음</li>
				<li><strong>Dense</strong> : 이전 층의 데이터 크기에 비례함</li>
				<li><strong>결론</strong> : 매우 많다.</li>
			</ul>
		</li>
		<li><strong>하이퍼파라미터</strong>
			<ul>
				<li><strong>컨볼루션 층</strong> : 필터 개수와 크기, stride 값, 패딩 여부</li>
				<li><strong>풀링</strong> : 풀링 방식 선택, 풀 크기, <span class="more-study">Pool stride 값(overlapping)</span></li>
				<li><strong>Dense</strong> : 너비</li>
				<li><strong>활성함수</strong> : ReLU, softmax, 시그모이드 등</li>
				<li><strong>오차함수</strong> : 교차 엔트로피 계열, L1, L2</li>
				<li><strong>optimizer</strong> : SGD, AdaGrad, RMSprop</li>
				<li><span class="more-study"><strong>랜덤 초기화</strong> : Gaussian or uniform, Scaling</span></li>
			</ul>
		</li>
	</ul>
</p>
<p>
	<h2>참고자료</h2>
	<ul>
		<li><a href="https://halfundecided.medium.com/%EB%94%A5%EB%9F%AC%EB%8B%9D-%EB%A8%B8%EC%8B%A0%EB%9F%AC%EB%8B%9D-cnn-convolutional-neural-networks-%EC%89%BD%EA%B2%8C-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-836869f88375" target="_blank" title="">[딥러닝/머신러닝] CNN(Convolutional Neural Networks) 쉽게 이해하기</a></li>
		<li><a href="https://ko.wikipedia.org/wiki/%EB%94%A5_%EB%9F%AC%EB%8B%9D" target="_blank" title="">위키백과 - 딥러닝</a></li>
		<li><a href="https://medium.com/@snaily16/what-why-and-which-activation-functions-b2bf748c0441" target="_blank" title="">What, Why and Which?? Activation Functions</a></li>
		<li><a href="https://velog.io/@hyunsuki/Activation-Function%ED%99%9C%EC%84%B1%ED%99%94-%ED%95%A8%EC%88%98" target="_blank" title="">Activation Function(활성화 함수)</a></li>
	</ul>
</p>