---
title: "[하천 쓰레기 프로젝트] 프로젝트 마무리"
author: dapin1490
date: 2022-12-03T23:20:00+09:00
categories: [지식, IT]
tags: [지식, IT, 자료구조, 과제, 프로젝트]
render_with_liquid: false
---

<style>
  .x-understand { color: #ccb833; }
  .understand { color: #1380da; }
  .tab { white-space: pre; }
  .underline { text-decoration: underline; }
  .cancle { text-decoration: line-through; }
  .green { color: forestgreen;}
  figure { text-align: center; }
</style>

<!--
<span class="x-understand"></span>
<span class="understand"></span>
<span class="tab"></span>
<span class="underline"></span>

[<a id="" href="">1</a>] #
[<a id="" href="" title="">2</a>] #, <a href="#" target="_blank">#</a>
<sup><a id="" href="" target="_blank" title=""></a></sup>

<figure>
  <img src="/assets/img/category-#/#">
  <figcaption>#</figcaption>
</figure>

<details>
  <summary>#</summary>
  <figure>
    <img src="/assets/img/category-#/#">
    <figcaption>#</figcaption>
  </figure>
</details>
-->

## 목차
- 이전 글 보기
- 초안과 달라진 점
- 구현된 프로젝트 구성
- 사용한 데이터
- 결과 및 효과
- 부족한 점

## 이전 글 보기
<a href="https://dapin1490.github.io/satinbower/posts/it-data-structure-training-project/" target="_blank">[하천 쓰레기 프로젝트] 프로젝트 개요</a>  
<a href="https://dapin1490.github.io/satinbower/posts/it-dst-project-plan/" target="_blank">[하천 쓰레기 프로젝트] 프로젝트 구현 계획</a>  

## 초안과 달라진 점
- 누적 민원 클래스를 따로 두지 않고 시스템 클래스에 멤버 변수로 포함했다.
- 기존 계획에는 없었던 드론을 이용한 쓰레기 경로 탐색 기능이 추가되었다.

## 구현된 프로젝트 구성
깃허브에서 보기 : <a href="https://github.com/dapin1490/waste-complain-system" target="_blank">dapin1490/waste-complain-system</a>  
  
- 민원 클래스  
  - 민원 id, 민원 사진 파일명, 신고 날짜, 사진 좌표, 포함된 쓰레기의 종류 등을 변수로 가진다.
  - 클래스에 포함된 각종 변수를 반환하는 getter와 쓰레기의 종류 수를 업데이트하는 setter가 있다.
  - 민원의 내용을 사용자가 알아볼 수 있게 출력하는 메소드를 갖는다.

<br>

- 민원 처리 시스템 클래스  
  - 민원이 새로 추가될 때 자동으로 id를 부여하기 위해 마지막으로 사용된 id의 다음 id를 멤버 변수로 저장한다.
  - 민원 처리 구역을 구분하기 위해 담당 구역의 좌표 기준점을 멤버 변수로 갖는다.
  - 모든 민원이 저장된 벡터, 각 쓰레기 종류별 누적 민원 벡터, 그리고 조회 기능을 위한 정렬 기준별 멀티맵 멤버 변수
  - 그 외에 시뮬레이터를 좀 더 원활하게 실행하기 위한 변수를 갖는다.
  - 업무 시작, 데이터 로드, 업무 진행 상황 저장, 민원 접수 등의 기능을 구현한 멤버 메소드가 있다.
  - 정렬 기준별 민원 조회를 위한 멤버 메소드
  - 민원 처리를 위해 드론의 쓰레기 수거 경로를 구하는 메소드와 민원 데이터를 처리하는 메소드가 있다.

<br>

- 드론의 경로 탐색을 위한 간선과 그래프 클래스
  - 드론은 공중을 날아 이동하므로 경로에 제한이 없다는 전제 하에, 모든 정점(민원)을 서로 연결하고 각 점 사이의 거리를 가중치로 갖는 그래프를 초기 그래프로 만들었다.
  - 프림 알고리즘을 이용해 최소 신장 트리를 구성하고, DFS 알고리즘으로 방문 순서를 정한다.
  - 모든 정점을 방문해야 하기 때문에 그래프 내의 모든 정점을 최소한의 비용으로 연결하는 최소 신장 트리를 찾아내는 것이 적절하다고 판단했다. 다익스트라는 시작점과 도착점의 방문만을 보장할 뿐 경로상에 거치는 정점이 그래프의 모든 점이 아니므로 사용하지 않았다.

### 코드로 보기
전체 코드가 1000줄이 넘기 때문에 선언 부분만 올린다. <a href="https://github.com/dapin1490/waste-complain-system/blob/main/River%20waste%20project/header/compl_system.h" target="_blank">깃허브</a>에 다 있다.  

```cpp
class complain { // 민원 클래스
private:
  unsigned id; // 민원을 구분하기 위한 id
  string pic_name; // 사진 이름(필요시 절대/상대 파일 경로 포함, 사진 크기를 비롯해 사진 파일 자체에 대한 각종 정보는 원본 파일의 정보에 포함된다고 본다)
  time_t rawtime; // 민원 신고 날짜(time_t)
  tm comp_date; // 민원 신고 날짜(tm)
  errno_t is_valid_date; // 민원 신고 날짜가 오류 없이 저장돼있는지 : 비주얼 스튜디오에서 지원하는 오류 코드다
  pair<double, double> coordinates; // 사진 좌표
  int waste_cnt; // 포함된 쓰레기의 종류 수
public:
  int wastes[5]; // 멤버 변수지만 어차피 getter를 써도 포인터로 전달되어 원본 수정이 가능하니 public 변수로 사용
  // 나중에 const를 쓰면 함수에서 사용하는 값을 바꿀 수 없다는 것을 배웠지만 이미 프로젝트를 상당부분 만들어둔 상태였다

public:
  // 기본 생성자 포함 3종류
  complain() { pic_name = "None"; }
  complain(unsigned id, string pn, int cdate, double x, double y, int wcnt, int* ws);
  complain(unsigned id, string pn, int cdate, double x, double y, int wcnt, string ws);

  unsigned get_id() { return id; } // 민원 id 반환
  string get_name() { return pic_name; } // 사진 이름 반환
  time_t get_date() { return rawtime; } // 민원 신고 날짜 반환
  pair<double, double> get_codi() { return coordinates; } // 사진 좌표 반환(pair)
  int get_wcnt() { return waste_cnt; } // 포함 쓰레기 종류 수 반환

  void rename(string new_name) { pic_name = new_name; } // 사진 이름 변경
  void update_wcnt(int num) { waste_cnt += num; } // 포함 쓰레기 종류 수 변경
  // 민원 정보 출력
  void print();
};

// 민원 삭제 처리를 할 때 벡터의 remove_if에서 사용하는데, 클래스 내부 함수로 선언하면 오류가 나서 전역 함수로 선언
bool is_wcnt_zero(complain c) {
  if (c.get_wcnt() == 0)
    return true;
  return false;
}

class compl_system { // 하천 쓰레기 민원 처리 시스템
private:
  unsigned latest_id; // 구역의 시작점을 id 0으로 하기 위해 1부터 시작
  pair<int, int> area_code; // 지역 코드(위도, 경도 정수 부분)
  unsigned thresh; // 민원 처리 최소 단위 : 누적된 민원의 수가 이 수보다 클 때 처리. 기본값은 20
  vector<vector<complain>> accumed_compls_list; // 쓰레기 분류별 누적 민원 배열
  unsigned file_checkpoint; // 전체 민원 파일 어디까지 읽었는지 표시

  vector<complain> all_compls; // 전체 민원 벡터
  multimap<string, complain> map_comp; // 사진 이름 기준 전체 민원 멀티맵
  multimap<double, complain> map_latitude; // 위도 기준 전체 민원 멀티맵
  multimap<double, complain> map_longitude; // 경도 기준 전체 민원 멀티맵
  multimap<time_t, complain, greater<time_t>> map_cdate_front; // 민원 접수 날짜 기준(최근순) 전체 민원 멀티맵
  multimap<time_t, complain> map_cdate_back; // 민원 접수 날짜 기준(오래된순) 전체 민원 멀티맵
  // 맵 내림차순(greater) 참고 : https://0xd00d00.github.io/2021/08/22/map_value_reverse.html

  // 두 민원이 서로 같은지 확인 : 민원 id 확인. 원래는 사진 이름과 민원 날짜 등 민원의 정보를 비교했지만 번거롭고 오류 가능성이 높아서 바꿈
  bool is_same(complain& a, complain& b);

  // 정상 실행 확인
  // 특정 분류의 쓰레기 민원이 충분히 많아 처리해도 될만한지 확인
  bool is_enough(int waste_code);
  
  // 사진 이름순 모든 민원 조회
  void view_all(multimap<string, complain>& mc);
  // 위도, 경도순 모든 민원 조회
  void view_all(multimap<double, complain> ml, int code);
  // 민원 날짜 오름차순 조회
  void view_all(multimap<time_t, complain, greater<time_t>> mcf);
  // 민원 날짜 내림차순 조회
  void view_all(multimap<time_t, complain> mcb);

  // 누적 민원 처리
  void clear_compls(int waste_code);

  // 누적 민원 물리적 처리(드론 경로 탐색 및 생성)
  void call_drone(vector<complain>& c_list);
public:
  // 기본 생성자 포함 2종류
  compl_system();
  compl_system(int x, int y);

  pair<int, int> get_acode() { return area_code; } // 지역 코드 반환
  void set_thresh(int n) { thresh = n; } // 누적 민원 처리 기준값 변경 : 구현 부족으로 실제 사용되지는 않음

  // 정상 실행 확인
  // 시스템 시작 : 사용자에게 지역 코드를 입력받고 기존 데이터 유무 확인, 새 로그 생성 등
  void system_on();

  // 일부 정상 실행 확인
  // 민원 접수
  void receive_compl();

  // 자동 민원 접수 : 민원 csv 파일 사용하기 위해 만듦
  void auto_receive_compl(int cnt = 0);

  // 기본 실행 확인
  // 정렬 기준(sort_by)에 따른 전체 민원 조회(출력하게 할 것이므로 반환값 없음)
  void view_all();

  /*// 우선순위 최하위. 구현하지 않을 가능성 높음
  // 미확인
  // 검색 기준(search_by)에 따른 특정 민원 검색
  void search_compl() {
    // 가능한 검색 기준 : 사진 이름(오타 불허), 위도, 경도, 접수 날짜
    // 벡터 정렬 후 순회
    return;
  }
  */

  // 정상 실행 확인
  // 특정 분류의 쓰레기 관련 민원 일괄 처리 : 처리 후 전체 민원 벡터나 다른 맵 등에서 NULL을 제거하는 과정이 필요함
  void clear_compls();

  // 정상 실행 확인
  // 파일에 기록된 데이터를 통한 이전 업무 기록 로드. 매번 새 시스템을 생성할 수는 없으니까.
  void load_save();

  // 정상 실행 확인
  // 업무 진행 상황을 파일로 기록. 업무를 종료하거나 중간 저장이 필요할 때 실행.
  void save_task();

  // 미구현
  // 승인 대기 목록을 확인하고 관할 구역에 속하는 민원을 추가 접수함
  void check_waiting();
};
```

## 사용한 데이터
**프로젝트를 위해 공유된 전체 수강생 59명의 데이터(csv) 중**, csv 파일을 얻을 수 없었던 2개와 파일을 병합하는 과정에서 오류가 발생했던 5개를 제외한 **52개의 데이터를 사용했다**.  
  
먼저 각각의 csv 파일을 판다스(파이썬)를 이용해 하나의 파일로 합치고, 지정된 column 이외의 데이터 / NaN / 불필요한 공백 등을 제거한 후 데이터타입을 지정하여 1차 전처리를 했다. 1차 전처리 파일의 통계를 확인해보니, 위도가 입력되어 있어야 할 열에 경도가 입력되어 있는 등 몇 가지 이상치가 있는 것이 발견되어 이상치를 제거한 2차 전처리 파일을 만들었다.  
2차 전처리 파일은 에브리타임과 카카오톡 오픈채팅을 통해 다른 수강생들에게도 공유하였다(2022년 12월 4일 오전 12시 25분 기준 11명).  
  
<div style="text-align:center;">
  <div style="width:30%; float:left;">
    <figure>
    <img src="https://raw.githubusercontent.com/dapin1490/waste-complain-system/main/Prepare%20data/processed%20data/outlier%20processed_info.png">
      <figcaption style="text-align:center">[이미지 1] 이상치 처리 데이터 정보</figcaption>
    </figure>
  </div>
  <div style="width:70%; float:left;">
    <figure>
    <img src="https://raw.githubusercontent.com/dapin1490/waste-complain-system/main/Prepare%20data/processed%20data/outlier%20processed_describe.png">
      <figcaption style="text-align:center">[이미지 2] 이상치 처리 데이터 통계</figcaption>
    </figure>
  </div>
</div>
<div style="clear:both"></div>
  
2차 전처리 파일을 이용해 본 프로젝트에 필요한 형식으로 조작하였다. 사용하지 않는 사진 크기 데이터를 제거하고, 날짜마다 다르게 들어오는 민원을 가정하기 위해 실제 사진이 찍혔을 것으로 예상되는 기간인 2022년 9월 1일부터 2022년 9월 30일까지 랜덤한 날짜를 부여했다. 먼저 만들어 둔 민원 처리 프로그램의 형식에 맞게 각 데이터가 갖고 있는 쓰레기의 종류 수도 추가하였다. 이후 민원의 입력에 바로 사용할 수 있게 column의 순서를 바꾸고 날짜순으로 정렬하여 마무리했다.  
  
<div style="text-align:center;">
  <div style="width:30%; float:left;">
    <figure>
    <img src="https://raw.githubusercontent.com/dapin1490/waste-complain-system/main/Prepare%20data/processed%20data/my%20total%20data_info.jpg">
      <figcaption style="text-align:center">[이미지 3] 프로젝트용 데이터 정보</figcaption>
    </figure>
  </div>
  <div style="width:70%; float:left;">
    <figure>
    <img src="https://raw.githubusercontent.com/dapin1490/waste-complain-system/main/Prepare%20data/processed%20data/my%20total%20data_describe%20and%20head.jpg">
      <figcaption style="text-align:center">[이미지 4] 프로젝트용 데이터 통계</figcaption>
    </figure>
  </div>
</div>
<div style="clear:both"></div>
  
데이터 전처리에 사용한 코드와 원본 데이터 모두 <a href="https://github.com/dapin1490/waste-complain-system/tree/main/Prepare%20data" target="_blank">깃허브</a>에서 확인할 수 있다.  

## 결과 및 효과
결과 및 효과를 서술하기에 앞서, 본 프로젝트에서 의미하는 결과 및 효과에 대해 정의한다. 본 프로젝트의 결과 및 효과는 본 프로젝트를 이용함으로써 얻을 수 있는 이득을 말하는 것으로 크게 유형 효과와 무형 효과로 나뉘며, 유형 효과는 설득력 있는 수치적 근거를 들어 계산할 수 있는 이득을 의미하고 무형 효과는 수치로 계산할 수 없는 이득을 의미한다.  

- 유형 효과  
  - 드론의 경로를 먼저 입력한 후 자동으로 운행하게 함으로써 드론 조종 인력의 인건비를 절감할 수 있다.
- 무형 효과  
  - 하천 쓰레기에 대한 민원 처리 과정 대부분을 프로그램이 자동으로 수행하게 함으로써 민원 처리 인력이 다른 업무에 더 집중할 수 있게 한다.

## 부족한 점
- 검색 기능 미구현
- 승인 대기 목록에 저장하는 기능은 구현했지만 시간 문제로 승인 대기 목록을 다시 불러오는 기능은 구현하지 않았다.
- 누적된 쓰레기 수가 지정치를 넘어서면 자동으로 쓰레기 처리를 권장하는 기능을 구현하고 싶었지만 시간이 부족했다.
- 누적 민원 처리 기준값을 변경하는 함수는 만들어 뒀지만 사용할 데를 안 만들었다.
