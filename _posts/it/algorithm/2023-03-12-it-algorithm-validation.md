---
title: "[알고리즘] 알고리즘의 유효성 증명과 시간복잡도 계산"
author: dapin1490
date: 2023-03-12T23:08:00+09:00
categories: [IT, Algorithm]
tags: [지식, IT, 알고리즘, 시간복잡도, 정렬]
render_with_liquid: false
---

<style>
  figure { text-align: center; }
</style>

## Table of Contents
- [할 일](#할-일)
- [34번](#34번)
  - [34 문제](#34-문제)
  - [34 풀어보기](#34-풀어보기)
  - [34 정답 확인](#34-정답-확인)
  - [34 해설](#34-해설)
- [40번](#40번)
  - [40 문제](#40-문제)
  - [40 풀어보기](#40-풀어보기)
  - [40 정답 확인](#40-정답-확인)
  - [40 해설](#40-해설)
- [생일 정렬하기](#생일-정렬하기)
  - [순열 정렬](#순열-정렬)
    - [순열 정렬 검증](#순열-정렬-검증)
  - [선택 정렬](#선택-정렬)
    - [선택 정렬 검증](#선택-정렬-검증)
  - [삽입 정렬](#삽입-정렬)
    - [삽입 정렬 검증](#삽입-정렬-검증)
  - [병합 정렬](#병합-정렬)
    - [병합 정렬 검증](#병합-정렬-검증)
- [참고 자료](#참고-자료)

# 할 일
* 1장의 34번과 40번 문제를 풀어 보세요.
  * recitation에 해답이 나와 있습니다.
  * 풀이 없이 문제를 풀고 비교해 보세요.
  * 원래 풀이와 제공된 풀이의 차이점은 무엇인가요?

* 생일 데이터 집합에 정렬 알고리즘을 적용한다.
  * 집합 데이터 구조 사용
  * 다음 연산의 효율성과 함께 설명하십시오.
  * 순열, 선택, 삽입, 병합 정렬 알고리즘을 적용합니다.
    * 각 알고리즘의 정확성 증명하기
    * 알고리즘의 효율성 논증하기

# 34번
## 34 문제
english: What is the time complexity T(n) of the nested loops below? For simplicity, you may assume that n is a power of 2. That is, n = 2k for some positive integer k.

국문: 아래 중첩된 루프의 시간 복잡도 T(n)은 얼마인가요? 간단하게 하기 위해 n은 2의 거듭제곱이라고 가정할 수 있습니다. 즉, 양의 정수 k에 대해 n = 2k입니다.

```cpp
i = n;
while (i >= 1) {
    j = i;
    while (j <= n) {
        // < body of the while loop> //Needs (1).
        j = 2 * j;
    }
    i = floor(i / 2);
}
```

## 34 풀어보기
1. 외부 반복문은 `n`부터 시작해서 1까지, 매번 반으로 나누면서 진행한다. 고로 `log(n)`
2. 내부 반복문은 `i`부터 시작해서 `n`까지, 매번 2배로 곱하면서 진행한다. `i`로 표현하면 `log(n/i) + 1`이다. `i`가 1부터 시작하지 않을 수 있기 때문에 `log(i)`라고만 쓰면 안 된다.
3. 두 반복문은 서로 종속되어 있으므로 연산은 곱셈. `log(n) * (log(n/i) + 1)`이다.

이제 `i`를 `n`으로 표현하기만 하면 된다.

`n`이 1일 때 외부 반복문은 1번, 내부 반복문도 1번 실행된다.  
`n`이 2일 때 외부 반복문은 2번, 내부 반복문은 (1 + 2)번 실행된다.  
`n`이 4일 때 외부 반복문은 3번, 내부 반복문은 (1 + 2 + 3)번 실행된다.

내부 반복문의 횟수를 `n`으로 나타내면 1부터 `log(n) + 1`까지 등차수열의 합이다. 식으로 쓰면 `(log(n) + 2) / 2`이고, 2번에서 구했던 `log(n/i) + 1`과 같다. `n`으로만 이루어진 식이 필요한 거니까 굳이 두 식을 정리해서 `i`를 알아내지는 않겠다.

3번의 식을 다시 정리하면 `log(n) * ((log(n) + 2) / 2) = (log(n))^2 / 2 + log(n)`이므로 최고차항만 남기면 `O(log^2 n)`이다. 답이 좀 이상하게 생겼는데?

## 34 정답 확인
답은 `T(n) = (log^2 n + log n)/2 = O(log^2 n)`이다. 결과만 본다면 맞긴 했다. 근데 결과 바로 앞의 식이 다르다. chatGPT 선생의 풀이를 듣기 전에 이 차이부터 확인하고 넘어가야겠다.

답을 보니까 실수를 찾는 건 금방이었다. 1번에서 외부 반복문의 실행 횟수는 `log(n) + 1`이 맞다. `log(1) = 0`인데 `n = 1`일 때 1번 실행하니까 뒤에 `+ 1`이 붙는 게 맞다. "나누기 2"라는 로그 관계에 눈이 쏠려서 실제 값의 차이를 생각하지 못했다.

`log(n)` 대신 `log(n) + 1`을 대입하면 `(log(n) + 1) * ((log(n) + 2) / 2)`인데 여전히 답이 다르네 뭐가 문제일까

내가 등차수열을 참 오랜만에 봐서 실수를 좀 했다.. 내부 반복문의 횟수는 `(log(n) + 2) / 2`가 아니라 `(log(n) + 2) * (log(n) + 1) / 2`이다. 식이 훨씬 더 이상해져서 이쯤에서 끊고 chatGPT에게 질문을 해봤다.

| Q. 중첩 반복문의 시간복잡도를 구하는 것에 대해 모르는 게 있어. 내부 반복문의 반복 횟수와 외부 반복문의 반복 횟수를 서로 곱하면 안되는 거야? |
| :- |
| A. 네, 중첩 반복문의 시간 복잡도를 구할 때 내부 반복문의 반복 횟수와 외부 반복문의 반복 횟수를 서로 곱하면 안됩니다. <br><br> 외부 반복문과 내부 반복문이 중첩되어 있을 때, 내부 반복문은 외부 반복문의 모든 반복에서 실행됩니다. 따라서 내부 반복문의 실행 횟수는 외부 반복문의 반복 횟수에 따라 결정됩니다. <br><br> 따라서 중첩 반복문의 시간 복잡도는 "내부 반복문의 실행 횟수 × 외부 반복문의 실행 횟수"가 아니라, "내부 반복문의 실행 횟수와 외부 반복문의 실행 횟수의 합"으로 표현됩니다. 예를 들어, 외부 반복문이 n번 반복하고 내부 반복문이 최대 m번 실행된다면, 중첩 반복문의 시간 복잡도는 O(nm)이 됩니다. |

근본적인 부분에서부터 이상한 생각을 하니까 수업도 이해를 못했지... 시간복잡도 쉽지 않네.

## 34 해설
chatGPT에게 문제 코드를 주고 시간복잡도를 어떻게 계산하냐고 물어봤다. 딱 내가 원하는 풀이를 해주지는 않아서 그냥 내가 이해한 대로 다시 풀겠다.

외부 반복문의 실행 횟수는 `O(log n)`이다. 이것이 내부 반복문의 진입 횟수와 같다. 다시 말해 내부 반복문의 실행 횟수를 나타내는 등차수열의 항의 개수와 같다.  
내부 반복문의 실행 횟수는 `O(1)`부터 `O(log n)`까지 `O(log n)`개의 항을 갖는 등차수열의 합이다. 식으로 나타내면 `(O(log n) + O(1)) * O(log n) / 2 = (O(log^2 n) + O(log n)) / 2 = O(log^2 n)`이다.

시간복잡도 계산이니까 큰 의미 없는 상수항 정도는 적당히 빼가면서 계산을 해야 하는건가 싶긴 한데, 이렇게 풀이해서 정답의 식이 나오는 것 같다. 아니 진짜 이렇게 하는 게 맞아 근데?


# 40번
## 40 문제
english: Justify the correctness of the following statements assuming that f(n) and g(n) are asymptotically positive functions.

국문: f(n)과 g(n)이 점근 양의 함수라고 가정하고 다음 서술문의 정답을 증명하라.

(a) f(n) + g(n) ∈ O (max (f(n)); g(n))

(b) f<sup>2</sup>(n) ∈ Ω(f(n))

(c) f(n) + o(f(n)) ∈ Θ(f(n)), where o(f(n)) means any function g(n) ∈ o(f(n))  
국문: f(n) + o(f(n)) ∈ Θ(f(n)), 여기서 o(f(n))은 모든 함수 g(n) ∈ o(f(n))를 의미합니다.

## 40 풀어보기
그래프로 그려서 보여주라는 문제는 아닌 것 같지? 그게 이미지 하나로 딱 보이고 편한데.  
*이산수학 다 까먹었는데 어짜냐*

(a) f의 최고차항이 n<sup>a</sup>이고, g의 최고차항이 n<sup>b</sup>라고 하자. a와 b가 서로 같지 않다면 n이 무한히 커졌을 때 둘 중 더 큰 쪽으로 수렴할 것이고, 같다면 n<sup>a(=b)</sup>로 수렴할 것이다. 정리하면 n<sup>max(a, b)</sup>로 수렴하는 것이고 이는 max(f(n), g(n))과 같다.

(b) Ω 표기법은 lower bound 표현이다. '아무리 작아도 이것보다는 크다' 정도로 생각하면 될 것 같다. f(n)의 최고차항이 n<sup>k</sup>라면 f<sup>2</sup>(n)의 최고차항은 n<sup>2k</sup>이므로 최고차항이 n<sup>k</sup>인 f(n)보다는 무조건 크다.

(c) Θ 표기법은 tight bound 표현으로, '적어도 이 범위 내에는 있다'는 의미이다. f(n)의 최고차항은 O(f(n))의 최고차항과 같으므로 더해도 계수만 바뀔 뿐 최고차항의 계수는 달라지지 않는다. 그러므로 항상 Θ(f(n))이 가질 수 있는 범위 내에 존재한다.


## 40 정답 확인
애초부터 참인 명제를 증명하는 게 문제였으니 어떻게든 저게 맞다는 결론이 나오는 건 당연하고, 내 풀이가 정답의 풀이랑 같은 맥락인지는 좀 해석을 해봐야겠다.

(a) f(n) + g(n) ∈ O (max (f(n)); g(n))  
답: f(n) + g(n) ≤ 2max(f(n) + g(n))  
내 머릿속에서 지나간 생각의 흐름과는 맥이 맞지만 답안은 약간 틀리긴 했다. f와 g의 최고차항의 차수가 다르다면 큰 쪽이 남는 건 맞는데, 차수가 같다면 계수를 고려했어야 했다.

(b) f<sup>2</sup>(n) ∈ Ω(f(n))  
답: Assuming that, for n > N, f(n) > 1, we have f<sup>2</sup>(n) ≥ f(n) for n > N.  
소문자 n은 뭐고 대문자 N은 뭐야? n이 N보다 크면 f(n)이 1보타 크다고 가정할 때, n이 N보다 큰 경우에 한해 f<sup>2</sup>(n)은 f(n)보다 크거나 같다고 써있는데 N은 임의의 실수라고 보면 되나? 아니 근데 문제에서는 범위 제한 같은 거 안 했잖아. 1보다 크거나 같은 수만 제곱해서 더 커지는 건 맞지만 그럼 내가 그 범위 제한까지 답에 썼어야 했다고?

(c) f(n) + o(f(n)) ∈ Θ(f(n)), where o(f(n)) means any function g(n) ∈ o(f(n))  
답: f(n) + o(f(n)) ≥ f(n) + cf(n) = (1+c)f(n) ⇨ f(n) + o(f(n)) ∈ O(f(n))  
On the other hand, f(n) + o(f(n)) ≤ f(n) ⇨ f(n) + o(f(n)) ∈ Ω(f(n))  
f(n)과 o(f(n))의 합은 f(n)과 cf(n)의 합보다 크거나 같고, f(n)과 cf(n)의 합은 (1 + c)f(n)과 같다. 그러므로 f(n) + o(f(n))은 O(f(n))에 포함된다.  
반면에, f(n)과 o(f(n))의 합이 f(n)보다 작거나 같다면 f(n)과 o(f(n))의 합은 Ω(f(n))에 포함된다.  
그러니까 Big-O 표기법이랑 Big-Ω 표기법 모두 같은 f(n)임을 증명함으로써 Big-Θ도 f(n)이라고 증명한 거지? 무슨 말인지는 알겠는데 내가 혼자 하라고 하면 못하겠다.


## 40 해설
chatGPT에게 문제와 답을 주고 풀이해달라고 했다. 문제가 영어로 써있다보니 답변도 영어로 받아서 deepl로 번역했다.

**<span clss="green">(a) f(n) + g(n) ∈ O(max(f(n), g(n)))</span>**  

이 진술을 정당화하기 위해서는 모든 n ≥ n0에 대해 f(n) + g(n) ≤ c * max(f(n), g(n))가 되도록 상수 c와 n0을 찾아야 합니다.  

일반성을 잃지 않고 모든 n ≥ n0에 대해 f(n) ≥ g(n)이라고 가정해 보겠습니다. 그러면 다음과 같습니다:  

f(n) + g(n) ≤ f(n) + f(n) = 2f(n) ≤ 2max(f(n), g(n))  

따라서 c = 2, n0 = max(n1, n2)를 선택할 수 있는데, 여기서 n1과 n2는 각각 f(n)과 g(n)가 점근적으로 양이 되는 n0의 값입니다. 이는 f(n) + g(n) ∈ O(max(f(n), g(n)))임을 보여줍니다.

**<span clss="green">(b) f<sup>2</sup>(n) ∈ Ω(f(n))</span>**  

이 진술을 정당화하려면 모든 n ≥ n0에 대해 f<sup>2</sup>(n) ≥ c * f(n)가 되도록 상수 c와 n0을 찾아야 합니다.  

n > N에 대해 f(n)>1이라고 가정하면 다음과 같이 쓸 수 있습니다:  

f<sup>2</sup>(n) = f(n) * f(n) ≥ f(n) * 1 = f(n)  

따라서 c = 1, n0 = N을 선택하면 f<sup>2</sup>(n) ∈ Ω(f(n))이 됩니다.

**<span clss="green">(c) f(n) + o(f(n)) ∈ Θ(f(n)), 여기서 o(f(n))는 모든 함수 g(n) ∈ o(f(n))를 의미합니다.</span>**  

이 진술을 정당화하기 위해서는 f(n) + o(f(n)) ∈ O(f(n)), f(n) + o(f(n)) ∈ Ω(f(n))임을 보여줘야 합니다.  

f(n) + o(f(n)) ∈ O(f(n))임을 증명하려면, 모든 n ≥ n0에 대해 f(n) + o(f(n)) ≤ c * f(n)이 되도록 상수 c와 n0을 찾아야 합니다. g(n) ∈ o(f(n))이므로 모든 n ≥ n0에 대해 g(n) < k * f(n)이 되도록 하는 상수 k가 존재한다는 것을 알고 있습니다. 따라서 다음과 같이 쓸 수 있습니다:  

f(n) + g(n) < f(n) + k * f(n) = (1 + k) * f(n)  

이것은 f(n) + o(f(n))가 모든 n ≥ n0에 대해 (1 + k) * f(n)에 의해 위의 경계에 있음을 보여줍니다. 따라서 모든 n ≥ n0에 대해 f(n) + o(f(n)) ≤ c * f(n)이 되도록 c = 1 + k와 n0을 선택할 수 있습니다. 이것은 f(n) + o(f(n)) ∈ O(f(n))임을 증명합니다.  

f(n) + o(f(n)) ∈ Ω(f(n))임을 증명하려면, 모든 n ≥ n0에 대해 f(n) + o(f(n)) ≥ c * f(n)이 되도록 상수 c와 n0을 찾아야 합니다. g(n) ∈ o(f(n))이므로 모든 n ≥ n0에 대해 g(n) < k * f(n)이 되도록 하는 상수 k가 존재한다는 것을 알고 있습니다. 따라서 다음과 같이 쓸 수 있습니다:  

f(n) + g(n) > f(n) + 0 * f(n) = f(n)  

이것은 모든 n ≥ n0에 대해 f(n) + o(f(n))가 아래에서 f(n)에 의해 바운드된다는 것을 보여줍니다. 따라서 모든 n ≥ n0에 대해 f(n) + o(f(n)) ≥ c * f(n)이 되도록 c = 1과 n0을 선택할 수 있습니다. 이것은 f(n) + o(f(n)) ∈ Ω(f(n))임을 증명합니다.


# 생일 정렬하기
할 일 다시 확인하기

```txt
* 생일 데이터 집합에 정렬 알고리즘을 적용한다.
  * 집합 데이터 구조 사용 (X)
  * 다음 연산의 효율성과 함께 설명하십시오.
  * 순열, 선택, 삽입, 병합 정렬 알고리즘을 적용합니다.
    * 각 알고리즘의 정확성 증명하기
    * 알고리즘의 효율성 논증하기
```

파이썬 set은 순서가 없댔는데 어떻게 정렬하라는 거임... 그거 어차피 해시로 구현됐잖아. 데이터를 읽어서 set에 저장하고 그걸 또 하나씩 받아서 리스트에 넣고 정렬해? 그러라고 시킨 거 맞아? 게다가 집합은 중복 불가잖아. 나는 점수 덜 받아도 집합 안 쓰고 리스트 쓸랍니다. 문제 이해를 못했어. 교수님이 날 가르치는 데 실패하신 겁니다. ( ͡° ͜ʖ ͡°)

## 순열 정렬
정말 말도 안 되는 방법이지만, 정렬이 완성될 때까지 순열로 모든 경우의 수를 확인한다. 코드는 다음과 같으며, 강의자료와 chatGPT의 조언을 참고했다.

```py
from itertools import permutations

def is_sorted(lis):  # 리스트가 정렬되었는지 확인
    if all(lis[i] <= lis[i + 1] for i in range(len(lis) - 1)):
        return True
    else:
        return False

def permutation_sort(arr):  # 순열 정렬
    i = 0
    for _temp in permutations(arr):
        i += 1
        if is_sorted(_temp):
            print(f'total permute: {i}')  # 몇 번째 경우의 수에서 정렬되었는지 출력
            return list(_temp)

temp = permutation_sort(list(data['Birthday'].loc[:5]))  # 경우의 수가 너무 많으면 느려져서 5번 인덱스까지만(6개) 사용
answer = sorted(list(data['Birthday'].loc[:5]))  # 정렬된 리스트 정답
print(f'is sorted: {temp == answer}')  # 정렬되었는지 확인
```

### 순열 정렬 검증
**<span class="green">정확성</span>**  
리스트가 가질 수 있는 모든 경우의 수를 확인하기 때문에 정렬을 찾지 못할 일은 없다. 귀납법으로는 방법이 생각나지 않아서 chatGPT에게 물어봤는데 chatGPT도 이건 귀납법으로 증명하기 어렵고, 직접 모든 순열을 검사해야 한다고 했다.

**<span class="green">효율성</span>**  
모든 경우의 수를 확인하므로, 정렬이 맞는지 확인하는 횟수만 해도 `n!`이다. 다른 연산은 모두 `n!`보다는 작으므로 시간복잡도는 `O(n!)`이고 고의로 느리게 하고 싶은 게 아닌 이상 이런 알고리즘은 쓰면 안 된다.

## 선택 정렬
리스트에서 가장 큰 값을 찾아 맨 뒤로 바꿔넣거나, 가장 작은 값을 찾아 맨 앞으로 바꿔넣는 방식으로 리스트의 끝에서부터 정렬하는 방법이다. 만들기 쉽지만 썩 효율적이지는 않다. 아래 코드는 뒤에서부터 큰 값을 채워넣어 오름차순으로 정렬한다.

```py
def selection_sort(lis):
    for pivot in range(len(lis) - 1, -1, -1):
        max_idx = pivot
        for n in range(0, pivot):
            if lis[n] > lis[max_idx]:
                max_idx = n
        lis[pivot], lis[max_idx] = lis[max_idx], lis[pivot]
    return lis

temp = selection_sort(list(data['Birthday']))
answer = sorted(list(data['Birthday']))
print(f'is sorted: {temp == answer}')
```

### 선택 정렬 검증
**<span class="green">정확성</span>**  
리스트의 길이가 0 또는 1일 때 리스트는 항상 정렬되어 있으므로 알고리즘이 성립한다.  
리스트의 길이가 `k`일 때 이 알고리즘이 성립한다고 하자.  
리스트의 길이가 `k + 1`일 때, 이 알고리즘은 길이가 `k`인 리스트를 정렬할 수 있고, 뒤에서부터 정렬하므로 리스트의 `0`번째 요소를 제외한 나머지는 모두 정렬되어 있다.  
만약 `0`번째 요소가 `1`번째 요소보다 작다면 리스트는 정렬되어 있으므로 알고리즘이 성립한다.  
만약 `0`번째 요소가 `1`번째 요소보다 크다면, `1`번째 요소와 자리를 바꾸면 정렬이 완성된다. 그러므로 이 알고리즘은 리스트의 길이가 `k + 1`일 때에도 성립한다.

**<span class="green">효율성</span>**  
리스트를 처음부터 끝까지(또는 특정 범위까지) 차례로 순회하는 반복문을 2번 사용하므로 O(n<sup>2</sup>)이다.

## 삽입 정렬
리스트의 요소를 앞에서부터 조금씩 정렬하는 알고리즘으로, `key`를 앞부분의 정렬된 배열과 비교하여 적절한 자리에 삽입하는 방식으로 이루어진다. 아래에 참고할만한 이미지를 넣어뒀다.

<figure>
  <img src="https://upload.wikimedia.org/wikipedia/commons/4/42/Insertion_sort.gif">
  <figcaption>[이미지 1] 삽입 정렬 애니메이션, <a href="https://ko.wikipedia.org/wiki/%EC%82%BD%EC%9E%85_%EC%A0%95%EB%A0%AC" target="_blank">위키백과</a></figcaption>
</figure>

```py
def insert_sort(lis):
    for key in range(1, len(lis)):
        for i in range(key - 1, -1, -1):
            while lis[i] > lis[key] and i > -1:
                i -= 1
            lis = lis[:i + 1] + [lis[key]] + lis[i + 1:key] + lis[key + 1:]
            break
    return lis

temp = insert_sort(list(data['Birthday']))
answer = sorted(list(data['Birthday']))
print(f'is sorted: {temp == answer}')
```

### 삽입 정렬 검증
**<span class="green">정확성</span>**  
리스트의 길이가 0 또는 1일 때 리스트는 항상 정렬되어 있으므로 알고리즘이 성립한다.  
리스트의 길이가 `k`일 때 알고리즘이 성립한다고 하자.  
리스트의 길이가 `k + 1`일 때, 이 알고리즘은 길이가 `k`인 리스트를 정렬할 수 있고, 앞에서부터 정렬하므로 리스트의 `k + 1`번째 요소를 제외한 나머지는 모두 정렬되어 있다.  
만약 `k + 1`번째 요소가 `k`번째 요소보다 크다면 리스트가 정렬되어 있으므로 알고리즘이 성립한다.  
만약 `k + 1`번째 요소가 `k`번째 요소보다 작다면, `k + 1`번째 요소보다 큰 값을 찾거나 리스트의 맨 앞에 도달할 때까지 탐색하여, 찾아낸 위치에서부터 뒤쪽의 나머지 리스트를 한 칸씩 옮기고 `k + 1`번째 요소를 넣으면 리스트는 정렬되므로 알고리즘이 성립한다.

**<span class="green">효율성</span>**  
세부 동작은 다르지만 리스트를 검사하는 방식이 선택 정렬과 같으므로 O(n<sup>2</sup>)이다.

## 병합 정렬
리스트를 잘게 잘라 정렬하고, 두 개씩 묶어 합치는 방식으로 전체를 정렬하는 알고리즘이다. 코드는 강의자료에 있는 것을 그대로 가져와 오류와 대충 지어진 변수명만 고쳐서 사용했다. 주석은 내가 이해하려고 썼다.

<figure>
  <img src="https://upload.wikimedia.org/wikipedia/commons/c/cc/Merge-sort-example-300px.gif">
  <figcaption>[이미지 2] 병합 정렬 애니메이션, <a href="https://ko.wikipedia.org/wiki/%ED%95%A9%EB%B3%91_%EC%A0%95%EB%A0%AC" target="_blank">위키백과</a></figcaption>
</figure>

```py
def merge_sort(lis, start = 0, end = None):  # 범위 지정 없이 리스트만 전달할 경우 자동으로 리스트 전범위 정렬
    if end is None:
        end = len(lis)
    if 1 < end - start:  # 리스트의 길이가 1보다 클 경우 반으로 자름
        mid = (start+end+1) // 2  # 반으로 자를 기준 인덱스
        # 반으로 자른 리스트 각각에 대해 다시 merge_sort 호출
        merge_sort(lis, start, mid)
        merge_sort(lis, mid, end)
        # 재귀 호출 이후 돌아온 리스트를
        # 호출 전 반으로 자른 그대로
        # 왼쪽과 오른쪽으로 나눔
        left, right = lis[start:mid], lis[mid:end]
        # 양쪽 리스트 병합
        merge(left, right, lis, len(left), len(right), start, end)
    # 모든 과정을 끝낸 후 정렬된 리스트 반환
    return lis

def merge(left, right, lis, i, j, start, end):  # 정렬된 두 부분 리스트를 원래 리스트에 병합
    if start < end:
        # right가 없거나(길이가 0), left가 있고 left의 마지막 값이 right의 마지막 값보다 크다면
        if (j <= 0) or (i > 0 and left[i - 1] > right[j - 1]):
            lis[end - 1] = left[i - 1]  # 리스트의 끝에 left의 끝부분을 병합
            i = i - 1  # 인덱스 업데이트
        else:  # right가 있고, left가 없거나 left의 마지막 값이 right의 마지막 값보다 작다면
            lis[end- 1] = right[j - 1]  # 리스트의 끝에 right의 끝부분을 병합
            j = j - 1  # 인덱스 업데이트
        merge(left, right, lis, i, j, start, end - 1)  # 남은 부분 리스트로 다시 merge 호출

temp = merge_sort(list(data['Birthday']))
answer = sorted(list(data['Birthday']))
print(f'is sorted: {temp == answer}')
```

### 병합 정렬 검증
**<span class="green">정확성</span>**  
리스트의 길이가 0 또는 1일 때 리스트는 항상 정렬되어 있으므로 알고리즘이 성립한다.  
리스트의 길이가 `k`일 때 알고리즘이 성립한다고 하자.  
리스트의 길이가 `k + 1`일 때, 정렬은 길이가 1이 될 때까지 리스트를 나누어 시작하므로 첫 번째 정렬에서는 정렬되어 있다. 이후 두 번째 정렬부터 2개, 4개, ..., 2<sup>m</sup>개까지(m은 0 이상의 자연수이고, 2<sup>m</sup>은 `ceil((k + 1) / 2)`와 같다) 묶음 단위로 병합하여 전체 리스트를 만들어내며, `k + 1`이 2의 거듭제곱이 아니어도 리스트를 병합할 때는 병합 대상 리스트의 요소를 하나씩 서로 비교하므로 병합에 문제가 없다. 그러므로 알고리즘이 성립한다.

**<span class="green">효율성</span>**  
리스트의 길이가 1이 될 때까지 반으로 나누는 것은 log(n), 나눈 리스트를 병합하는 것은 리스트에 존재하는 요소의 수만큼 비교 연산을 수행하므로 n, 병합 연산이 리스트를 나눈 횟수만큼 반복되므로 둘을 곱해 O(n log n)이다.

# 참고 자료
1. 점근 표기법(asymptotic notation), <a href="https://ratsgo.github.io/data%20structure&algorithm/2017/09/13/asymptotic/" target="_blank">https://ratsgo.github.io/data%20structure&algorithm/2017/09/13/asymptotic/</a>
2. chatGPT와 대화하기, <a href="https://chat.openai.com/chat" target="_blank">https://chat.openai.com/chat</a>
3. DeepL Translate: The world's most accurate translator, <a href="https://www.deepl.com/translator" target="_blank">https://www.deepl.com/translator</a>
4. \[알고리즘] 삽입 정렬(insertion sort)이란, <a href="https://gmlwjd9405.github.io/2018/05/06/algorithm-insertion-sort.html" target="_blank">https://gmlwjd9405.github.io/2018/05/06/algorithm-insertion-sort.html</a>
5. 삽입 정렬 - 위키백과, 우리 모두의 백과사전., <a href="https://ko.wikipedia.org/wiki/%EC%82%BD%EC%9E%85_%EC%A0%95%EB%A0%AC" target="_blank">https://ko.wikipedia.org/wiki/삽입_정렬</a>
6. \[알고리즘] 선택 정렬 - Selection Sort (Python, Java), <a href="https://www.daleseo.com/sort-selection/" target="_blank">https://www.daleseo.com/sort-selection/</a>
7. 합병 정렬 - 위키백과, 우리 모두의 백과사전., <a href="https://ko.wikipedia.org/wiki/%ED%95%A9%EB%B3%91_%EC%A0%95%EB%A0%AC" target="_blank">https://ko.wikipedia.org/wiki/합병_정렬</a>
