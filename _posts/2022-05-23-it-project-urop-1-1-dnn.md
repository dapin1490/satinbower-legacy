---
title: "[UROP] 1주 - 1. DNN 스터디"
author: dapin1490
date: 2022-05-23 00:00:00 +0900
categories: [지식, IT]
tags: [프로젝트, 지식, IT, DNN, 딥러닝, 과학]
render_with_liquid: false
---

<style>
	.x-understand { color: #ccb833; }
	.understand { color: #1380da; }
	.tab { white-space: pre; }
	.code-block {
		font-family: Consolas, 'Liberation Mono', Menlo, Courier, monospace !important;
		width: 700px;
		display: block;
		background-color: #272727;
		color: #f0f0f0;
	}
	.inline-code {
		white-space: pre-wrap;
		background-color: #272727;
		color: #f0f0f0;
	}
</style>

<p>* <span class="x-understand">노란 글씨</span> : 이해 못 한 부분<br>
* <span class="understand">파란 글씨</span> : 내가 이해해서 추가한 부분</p>

<p><h2>인공지능, 머신러닝, 딥러닝</h2>
	<ul>
		<li><strong>인공지능</strong> : 인간의 지능과 같은 기능을 하는 컴퓨터 시스템</li>
		<li><strong>머신러닝</strong> : 컴퓨터가 학습할 수 있도록 하는 알고리즘과 기술을 개발하는 분야</li>
		<li><strong>딥러닝</strong> : 여러 가지 비선형 변환기법의 조합을 통해 높은 수준의 추상화를 시도하는 기계학습 알고리즘의 집합</li>
	</ul>
	<span class="tab">&#9;</span>→ 포함 관계 : 딥러닝 ⊂ 머신러닝 ⊂ 인공지능
</p>

<p><h2>ANN, DNN, CNN</h2>
	<ul>
		<li><strong>ANN, Artificial Neural Network : 인공신경망</strong><br>
			사람의 신경망 원리와 구조를 모방하여 만든 기계학습 알고리즘<br>
			키워드 : 입력층, 출력층, 은닉층, 가중치, 바이어스<br>
			문제 : 기울기 소실, 과적합, 학습 오래걸림 등 → 해결 가능함
		</li>
		<li><strong>DNN, Deep Neural Network</strong><br>
			딥러닝 모델 내 은닉층을 늘려 학습의 결과를 향상시킨다. 은닉층을 2개 이상 지닌 학습 방법을 뜻함. 이것을 응용한 알고리즘으로 CNN, RNN, LSTM, GRU 등이 있음.<br>
			<span class="understand">→ DNN은 대부분 딥러닝 모델의 밑바탕이 되는 기본적인 구조이다.</span>
		</li>
		<li><strong>CNN, Convolution Neural Network : 합성곱신경망</strong><br>
	데이터의 특징을 추출해 그 패턴을 파악한다. 컨볼루션과 풀링의 조합으로 이루어진다. 정보 추출, 문장 분류, 얼굴 인식 등에 널리 사용됨.
		</li>
		<li><strong>컨볼루션</strong> : 커널을 이용해 일정 구역의 데이터의 특징을 추출해낸다. 이 결과로 만들어지는 층을 컨볼루션 레이어라고 한다. 파라미터의 개수를 효과적으로 줄일 수 있음.
		</li>
		<li><strong>풀링</strong> : 컨볼루션 이후 레이어의 사이즈를 줄임. 노이즈를 상쇄하고 미세한 부분에서 일관적이 특징을 제공한다고 함. <span class="x-understand">그러나 풀링이 어째서 그런 효과를 내는지는 모름.</span>
		</li>
	</ul>
</p>

<p><h2>지도학습과 비지도학습</h2>
	<ul>
		<li><strong>지도학습</strong> : 문제와 정답 모두 제공, 문제 유형에 따라 사용하는 손실 함수가 달라짐.</li>
		<li><strong>비지도학습</strong> : 문제만 제공. 정답이 정해진 문제가 아님. 데이터의 패턴을 분석해 특징이나 구조를 발견하도록 함.</li>
	</ul>
</p>

<p><h2>DNN의 개념과 원리</h2>
	<ul>
		<li><strong>DNN</strong> : 은닉층이 여러 개인 인공신경망</li>
		<li><strong>과적합</strong> : 모델이 학습 데이터에 너무 최적화되어 전체적인 특성에서 멀어지는 문제</li>
		<li><strong>오차 역전파</strong> : 출력층에서 입력층 방향으로 계산하며 가중치를 업데이트하는 방식</li>
		<li><strong>경사하강법</strong> : 함수의 기울기를 이용해 값이 극값에 이르도록 이동시키는 것.</li>
		<li><strong>손실 함수(오차 함수)</strong> : 가중치에 따라 오차가 얼마나 커지고 작아지는지 평가하는 함수
			<ul>
				<li><strong>평균 제곱 오차(MSE)</strong> : 실제 값과 추정 값의 차이를 나타내며 회귀 문제에 사용</li>
				<li><strong>교차 엔트로피 함수(CEE)</strong> : 두 분포 간의 차이를 나타내는 척도, 분류 문제에 사용</li>
			</ul>
		</li>
		<li><strong>활성화 함수</strong> : DNN 모델이 비선형성을 표현할 수 있도록 도와준다<br>
		<span class="understand">→ 직선밖에 볼 줄 모르는 DNN 모델이 제대로 기능할 수 있도록 곡선을 직선으로 바꿔준다. 곡선을 왜곡해 직선처럼 보이게 한다. 퍼셉트론의 XOR 문제처럼.</span></li>
		<li><strong>편향(bias)과 분산(variance)</strong><br>
			편향은 bias, 모델이 예측하는 값이 정답으로부터 얼마나 멀리 떨어져있는지 나타낸다. 분산은 variance, 모델이 예측하는 값들이 얼마나 서로 비슷한지 나타낸다. 모델의 예측값이 정답과 가까울수록 편향이 낮고, 예측값이 일정할수록 분산이 낮다.<br>
			편향과 분산은 모델이 ‘복잡하게 생긴 정도’와 관련이 있다.<br>
			아래 이미지는 회귀 모델의 정답(점)과 모델의 학습 결과(선)을 그래프로 나타낸 것이다. 셋 중 가장 나은 모델은 가운데 모델이다. 선이 정답과 가까우므로 편향 양호, 선이 지나치게 구불구불하지 않으니 분산도 양호하다.
			<figure style="text-align:center">
				<img src="https://raw.githubusercontent.com/dapin1490/satinbower/main/assets/img/categoty-it/220523-1-bias-variance.png">
				<figcaption>[이미지 1] 회귀 모델의 편향과 분산에 따른 결과 그림</figcaption>
			</figure>
			아래 이미지는 분류 모델을 위와 같은 방식으로 나타낸 것이다.<br>
			위와 마찬가지로 가운데 모델이 가장 양호하다.
			<figure style="text-align:center">
				<img src="https://raw.githubusercontent.com/dapin1490/satinbower/main/assets/img/categoty-it/220523-2-classify-bias-variance.png">
				<figcaption>[이미지 2] 분류 모델의 편향과 분산에 따른 결과 그림</figcaption>
			</figure>
		</li>
		<li><strong>모델의 복잡도</strong><br>
			편향과 분산은 어느 한 쪽이 증가하면 다른 한 쪽이 감소하는 경향을 보인다.<br>
			모델이 데이터를 반복 학습하는 수가 늘어날수록 모델의 복잡도가 커진다. 이때 학습 오차는 점점 감소하지만 테스트 오차는 같이 감소하다가 특정 시점 이후로 다시 증가하게 된다. 모델이 학습용 데이터를 외워서 학습하기 때문이다. 테스트 오차가 최소가 되는 지점에서 모델의 학습을 멈춰야 한다.<br>
			학습 오차는 모델을 학습시킬 때 발생하는 오차이며, 이 오차를 줄이는 방향으로 모델을 변화시킨다. 반면 테스트 오차는 테스트용 데이터로 모델을 평가할 때 발생하는 오차이며, 모델에게는 영향을 주지 않고 학습 경과를 확인하기 위한 용도로만 사용된다.
		</li>
		<li><strong>Regularization : 정규화</strong> (≠ Normalization 표준화) ← 전제 : 지도학습<br>
			과적합을 줄이는 방법 중 하나이다.<br>
			모델이 가질 수 있는 분산에 제한을 부여함으로써 과적합을 방지한다. 직역은 정규화가 맞지만 normalization과의 구분을 위해 ‘규제’라고도 한다. 분산을 제한하면 편향이 증가할 수 있기 때문에 적당히 해야 한다.<br>
			규제 원리 : 대부분 규제항(Regularization Term)을 이용한다. 모델의 복잡도가 올라갈수록 증가하는 함수(예: L2 함수)를 모델의 오차(cost) 함수에 규제항으로 더하여, 모델이 너무 복잡해지면 정확도와 관계 없이 오차(cost)가 증가하도록 한다.<br>
			요점 : 딥러닝 모델은 학습 데이터에 익숙해지는 방향으로 학습한다. 가중치가 낮은 데이터는 모델에게 큰 영향을 미치지 못하지만 가중치가 큰 데이터는 모델에 영향을 줄 수 있다. 모델이 지나치게 학습 데이터에만 익숙해지면 일반화 성능이 떨어지기 때문에, 가중치가 큰 학습 데이터에 제약을 걸어 과적합을 줄인다.<br>
			<ul>
				<li><strong>규제항 종류</strong> : L1 norm, L2 norm<br>
					L1 norm은 outlier에 비교적 덜 영향을 받으며 0인 지점에서 미분이 불가능하다는 단점이 있다. L2 norm은 outlier에 비교적 큰 영향을 받는다.
					<ul>
						<li><strong>norm</strong> : 벡터의 길이(또는 크기)를 측정하는 방법이나 함수. 두 벡터 사이의 거리를 측정하는 방법이기도 하다.</li>
						<li><strong>L1 norm</strong> : 두 벡터의 각 원소들의 차의 절댓값의 합. 여러 가지로 표현될 수 있음.</li>
						<li><strong>L2 norm</strong> : 두 벡터의 직선 거리. 유일하게 표현됨.</li>
						<li><strong>L1 loss</strong> : 오차의 절댓값의 합</li>
						<li><strong>L2 loss</strong> : 오차의 제곱의 합</li>
						<li><strong>선택 기준</strong> : L1 norm은 표현이 유일하지 않기 때문에 feature selection이 가능하다. <span class="x-understand">그로 인해 Sparse model(coding)에 적합하며 convex optimization에 유용하게 쓰인다고 한다.</span> 다만 미분 불가능한 점이 있기 때문에 기울기 기반 학습에 사용하려면 주의가 필요하다. <span class="understand">L2 norm은 outlier에 영향을 잘 받으니 outlier를 배제하고 싶을 때 사용하면 좋을 것 같다.</span></li>
					</ul>
				</li>
			</ul>
		</li>
		<li><strong>기울기 소실 문제</strong><br>
			DNN 모델은 은닉층이 여러 개이기 때문에 사용하는 활성화 함수에 따라 기울기가 0으로 수렴하여 경사하강법이 의미가 없어질 수 있음.<br>
			해결 : ReLU 함수 사용
		</li>
		<li><strong>학습 데이터의 입력량과 가중치 업데이트 시점에 따른 분류</strong>
			<ul>
				<li><strong>Stochastic Gradient Descent(SGD)</strong> : 모델에게 한 번에 하나의 데이터만 먹이기. 매 데이터마다 가중치 업데이트함.<br>
					개별 데이터로 가중치를 바로 업데이트함. 문제 공간이 매번 들어오는 입력 데이터로 바뀌는 셈인데, 그래서 전체 이미지에 대한 분류 문제가 굉장히 많은 개별 이미지에 대한 문제 공간의 집합이 됨. 배치 방식과 달리 입력된 값에 따라 가중치가 아주 다르게 나올 수도 있기 때문에 지역 최솟값에 빠질 가능성은 낮다.
				</li>
				<li><strong>Batch Gradient Descent(BGD)</strong> : 배치 단위(모든 데이터)로 묶어서 먹임. 배치 내의 데이터들에 대한 오차의 평균으로 가중치 업데이트.<br>
					모든 개별 데이터의 오차를 계산하고 그걸 또 평균내서 가중치를 업데이트하기 때문에 오래 걸린다. 모든 데이터를 순회하고 나서야 가중치가 업데이트되는 셈. 또한 지역 최솟값에서 빠져나오기 어렵다는 문제가 있다.
				</li>
				<li><strong>Mini-Batch</strong> : 위 두 가지 방식을 절충한 방식<br>
					전체 데이터에서 일부를 묶어 오차를 계산하고 가중치 업데이트.
				</li>
			</ul>
		</li>
		<li><strong>Batch Normalization(배치 정규화)</strong><br>
			데이터를 모델에 입력하기 전에 정규화를 실행하는 것과 다르다. 모델 내부에서 은닉층의 가중치가 치우치는 것을 막기 위해(아래 [이미지 3]과 같이 되는 것을 막기 위해), 어떤 층에서 다음 층으로 가중치를 넘겨주기 전에 정규화를 하여 가중치의 범위를 제한한다. 케라스의 <em>BatchNormalization</em> 층을 말한다.
			<figure style="text-align:center">
				<img src="https://raw.githubusercontent.com/dapin1490/satinbower/main/assets/img/categoty-it/220523-3-batch-normalization.png">
				<figcaption>[이미지 3] 학습이 진행될수록 가중치가 치우쳐가는 은닉층 그림</figcaption>
			</figure>
		</li>
		<li><strong>가중치 초기값 설정</strong><br>
			가중치 초기값의 분포가 이후의 은닉층의 결과 값 분포에도 큰 영향을 준다. 층과 층 사이에 연결된 가중치에 상관 없이 은닉층의 결과값이 모두 같다면 아무리 노드가 많고 은닉층이 많아도 결국 노드 1개, 은닉층 1개와 다를 바 없어진다.<br>
			이를 해결하기 위해 초기 가중치 설정에 대한 연구가 진행되고 있다. 현재 있는 방법으로는 Xavier, He 초기값 설정 방법 등이 있다.
		</li>
		<li><strong>optimizer : 지역최솟값에 빠지지 않게 도와줌</strong>
			<ul>
				<li><strong>momentum 방식</strong> : SGD 방식에 기울기의 누적값을 적용한 개념이라고 한다. 관성과 비슷하다. 한 방향으로 학습이 진행될수록 가속도가 붙어 최솟값에 이르렀을 때에도 가던 방향대로 지나가 지역최솟값에 빠지지 않게 된다. 마찬가지로 학습이 점차 멈추기 되는 plateau도 해결할 수 있다. 전역 최솟값을 찾아도 학습을 계속한다는 단점이 있다. 이 단점을 극복하고자 Nestreov Momentum이라는 optimizer가 등장했다.</li>
				<li><strong>Adaptive 방식</strong>
					<ul>
						<li><strong>AdaGrad</strong> : 가중치가 갑자기 크게 업데이트될 때 패널티를 주어 과적합을 방지. 단점은 제곱의 성질을 지니기 때문에 계속하다 보면 학습이 거의 진행되지 못하게 된다는 점. 이를 고치고자 RMSProp이라는 optimizer가 등장.</li>
						<li><strong>RMSProp</strong> : AdaGrad에서 문제가 되었던 값(G)에 지수평균을 적용하여 비중을 조절했다.</li>
					</ul>
				</li>
				<li><strong>Adaptive + Momentum 방식</strong>
					<ul>
						<li><strong>Adam</strong> : RMSProp에 Momentum 적용.</li>
					</ul>
				</li>
			</ul>
		</li>
		<li><strong>Hyperparameter</strong> : DNN 모델을 학습시킬 때 사전에 정의해 주어야 하는 상수값. 예를 들어 학습률, 각 층의 노드 수, 배치사이즈 등이 있다. 이 값들을 학습시킬 수는 없지만 경험적으로 최적의 값을 추론할 수는 있다.</li>
		<li><strong>Dataset 구성</strong> : 전체 데이터셋을 10이라 치면 학습용 데이터는 5, validation 데이터는 3, 테스트 데이터는 2로 설정한다고 한다. validation과 test의 차이는 학습 중간중간 평가하기 위해 사용하는 것(val)인지, 학습이 끝난 이후에 평가하기 위해 사용하는 것(test)인지 정도.</li>
	</ul>
</p>

<p><h2>DNN 구현</h2>
	<ul>
		<li><strong>개요</strong>
			<ol>
				<li>기본 파라미터 설정 <span class="x-understand">→ 무슨 파라미터?</span> <span class="understand">→ 가중치 설정, 배치 사이즈 설정, 규제항 결정 등을 말하는 것 같음</span></li>
				<li>분류, 회귀 DNN 모델 구현</li>
				<li>데이터 준비</li>
				<li>학습 및 성능 평가</li>
			</ol>
		</li>
		<li>
			<strong>모듈</strong>
			<div class="colorscripter-code" style="color:#f0f0f0;font-family:Consolas, 'Liberation Mono', Menlo, Courier, monospace !important; position:relative !important;overflow:auto"><table class="colorscripter-code-table" style="margin:0;padding:0;border:none;background-color:#272727;border-radius:4px;" cellspacing="0" cellpadding="0"><tr><td style="padding:6px;border-right:2px solid #4f4f4f"><div style="margin:0;padding:0;word-break:normal;text-align:right;color:#aaa;font-family:Consolas, 'Liberation Mono', Menlo, Courier, monospace !important;line-height:130%"><div style="line-height:130%">1</div></div></td><td style="padding:6px 0;text-align:left"><pre style="margin:0;padding:0;color:#f0f0f0;font-family:Consolas, 'Liberation Mono', Menlo, Courier, monospace !important;line-height:130%"><div style="padding:0 6px; white-space:pre; line-height:130%">Dense(nodes,&nbsp;input_dim<span style="color:#0086b3"></span><span style="color:#ff3399">=</span>ind,&nbsp;activation<span style="color:#0086b3"></span><span style="color:#ff3399">=</span><span style="color:#ffd500">'relu'</span>)</div></pre></td><td style="vertical-align:bottom;padding:0 2px 4px 0"><a href="http://colorscripter.com/info#e" target="_blank" style="text-decoration:none;color:white"><span style="font-size:9px;word-break:normal;background-color:#4f4f4f;color:white;border-radius:10px;padding:1px">cs</span></a></td></tr></table></div>
			<em>nodes</em> : 이 은닉층의 노드 수<br>
			<em>input_dim</em> : 입력되는 노드의 수(== 입력값의 차원)<br>
			<em>activation</em> : 활성화 함수 지정
		</li>
		<li><strong>Dropout</strong> : 무작위로 일부 노드를 빼고 학습 진행. 과적합 방지 효과 있음.</li>
	</ul>
</p>

<p><h2>DNN 실습 데이터셋</h2>
	<ol>
		<li><strong>CIFAR-10</strong>
			<ul>
				<li>총 10개의 클래스로 구성된 이미지 데이터셋</li>
				<li>(32, 32) 크기의 컬러 이미지</li>
				<li>5만 개의 학습용 데이터와 만 개의 테스트용 데이터</li>
			</ul>
		</li>
		<li><strong>CIFAR-100</strong>
			<ul>
				<li>100개의 클래스로 구성되며, 각각의 클래스에는 600개의 이미지가 있고(학습:테스트 비율 5:1) 총 만 개의 이미지로 구성된 데이터셋</li>
				<li>100개의 클래스는 20개의 슈퍼클래스로 다시 분류됨</li>
			</ul>
		</li>
	</ol>
</p>

<p><h3>참고자료</h3>
	<ul>
		<li><a href="https://ebbnflow.tistory.com/119" target="_blank" title="">[인공지능] ANN, DNN, CNN, RNN 개념과 차이</a></li>
		<li><a href="http://contents2.kocw.or.kr/KOCW/data/document/2020/edu1/bdu/hongseungwook1118/031.pdf" target="_blank" title="">DNN 원리</a></li>
		<li><a href="https://89douner.tistory.com/36" target="_blank" title="">딥러닝 모델 요약</a></li>
		<li><a href="https://skyil.tistory.com/138" target="_blank" title="">6. 규제, 정규화 (Regularization)</a></li>
		<li><a href="https://opentutorials.org/module/3653/22071" target="_blank" title="">Bias and Variance (편향과 분산)</a></li>
		<li><a href="https://light-tree.tistory.com/125" target="_blank" title="">딥러닝 용어 정리, L1 Regularization, L2 Regularization 의 이해, 용도와 차이 설명</a></li>
		<li><a href="https://89douner.tistory.com/43" target="_blank" title="">9. Mini-Batch (데이터가 많은 경우에는 학습을 어떻게 시키나요?)</a></li>
		<li><a href="https://89douner.tistory.com/54" target="_blank" title="">13. DNN(Deep Neural Network) 학습 최종정리</a></li>
	</ul>
</p>