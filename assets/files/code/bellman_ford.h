#pragma once

#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <queue>
using namespace std;

enum class _error : int { shut_down, ValueErrorInt, ValueErrorChar, UnknownError };

// C++ 에러 메시지 참고 : https://learn.microsoft.com/ko-kr/cpp/error-messages/compiler-errors-1/c-cpp-build-errors?view=msvc-170
void error(_error code, string message = "") {
	if (!message.empty())
		cout << "error: " << message << "\n";

	switch (code) {
	case _error::shut_down:
		cout << "프로그램 비정상 종료\n";
		break;
	case _error::ValueErrorInt: // 잘못된 입력 - int
		cout << "ValueErrorInt: int 값이 입력되어야 합니다.\n";
		break;
	case _error::ValueErrorChar: // 잘못된 입력 - char
		cout << "ValueErrorChar: char 값이 입력되어야 합니다.\n";
		break;
	default:
		cout << "UnknownError: 알 수 없는 오류\n";
	}

	exit(1); // 프로그램 비정상 종료
}

struct cmp { // 다익스트라 우선순위 큐 비교 연산자 : 가중치가 적고 정점 번호가 적은 것을 우선으로 함
	bool operator()(pair<int, int> a, pair<int, int> b) {
		if (a.second == b.second)
			return a.first >= b.first;
		else
			return a.second > b.second;
	}
};

struct Edge {
	int w;
	int from;
	int to;
};

class route_search {
private:
	int vnum; // 정점 수
	vector<Edge> graph; // 간선 저장 그래프
	vector<int> dist; // 거리 벡터
public:
	route_search() { vnum = 0; }
	route_search(int v) { vnum = v; dist.resize(vnum + 1); }

	int size() { return vnum; } // 그래프가 갖는 정점의 수 반환
	vector<Edge>& edges_from() { return this->graph; } // 그래프가 갖는 간선 반환
	vector<Edge> edges_from(int key); // 특정 정점에 연결된 간선 반환
	auto& distance() { return dist; }

	// 방향 간선 추가
	void add(Edge e);
	// 무방향 간선 추가
	void add_undir(Edge e);

	// 그래프 출력
	void print();

	// 벨만-포드
	vector<int> bellman(int s);

	// 기본 : 시작점으로부터의 최소 거리만 구하는 다익스트라
	vector<int> dijkstra(int s);
};

vector<Edge> route_search::edges_from(int key) {
	vector<Edge> edge_from_i;
	for (auto& e : graph) {
		if (e.from == key)
			edge_from_i.push_back(e);
	}
	return edge_from_i;
}

// 방향 간선 추가
void route_search::add(Edge e) {
	if (e.from > 0 && e.from <= this->vnum && e.to > 0 && e.to <= this->vnum)
		this->graph.push_back(e);
	else
		error(_error::shut_down, "정점 범위 초과");

	return;
}
// 무방향 간선 추가
void route_search::add_undir(Edge e) {
	if (e.from > 0 && e.from <= this->vnum && e.to > 0 && e.to <= this->vnum) {
		this->graph.push_back(e);
		this->graph.push_back(Edge{ e.w, e.to, e.from });
	}
	else
		error(_error::shut_down, "정점 범위 초과");

	return;
}

// 그래프 출력
void route_search::print() {
	for (int i = 1; i <= vnum; i++) {
		cout << "# " << i << " : "; // 정점 번호
		vector<Edge> edge = this->route_search::edges_from(i); // 정점에 연결된 간선 가져오기
		for (auto& e : edge)
			cout << "(" << e.to << ", " << e.w << ")  "; // 정점에 연결된 간선 출력
		cout << "\n";
	}
	return;
}

// 벨만-포드
vector<int> route_search::bellman(int s) {
	dist.assign(vnum + 1, INT_MAX); // 클래스 멤버 변수 거리 벡터. 정점 번호가 1부터 시작함
	dist[s] = 0; // 시작점은 거리 0
	dist[0] = INT_MIN; // 안 쓰는 정점 표시

	// 최단거리 구하기
	for (int i = 1; i < vnum; i++) {
		for (auto& e : graph) {
			dist[e.to] = dist[e.to] > dist[e.from] + e.w ? dist[e.from] + e.w : dist[e.to];
		}
	}

	// 음수 사이클 확인
	for (int i = 1; i < vnum; i++) {
		for (auto& e : graph) {
			if (dist[e.to] > dist[e.from] + e.w) {
				cout << "error_non-parametical: 경로상에 음수 사이클 존재\n";
				dist.assign(vnum + 1, -1);
				return dist;
			}
		}
	}

	return dist;
}

// 기본 : 시작점으로부터의 최소 거리만 구하는 다익스트라
vector<int> route_search::dijkstra(int s) {
	dist.assign(vnum + 1, INT_MAX); // 클래스 멤버 변수 거리 벡터. 정점 번호가 1부터 시작함
	vector<bool> visited(vnum + 1, false); // 방문 여부 초기화
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> next_visit; // 다음에 방문할 정점 : (정점, 거리)

	int vert = s; // 이제 방문할 정점 : 아직 시작하지 않았으므로 시작점으로 초기화
	visited[0] = true; // 안 쓰는 인덱스 방문할 일 없게 미리 표시
	/*
	1. 시작점 방문
	2. 거리 파악
	3. 가장 가까운 곳으로 이동
	4. 반복
	*/
	dist[s] = 0; // 시작점은 거리 0
	dist[0] = INT_MIN; // 안 쓰는 정점 표시
	next_visit.push(make_pair(s, dist[s]));

	while (true) { // 다음 방문 정점 큐가 비어있지 않을 동안
		if (!visited[vert]) {
			visited[vert] = true; // 정점 방문
			vector<Edge> v_edge = edges_from(vert); // 지금 방문한 정점에 연결된 간선들 가져오기

			for (auto& e : v_edge) {
				if (dist[vert] + e.w < dist[e.to]) { // 거리를 업데이트할 필요가 있을 때에만
					dist[e.to] = dist[vert] + e.w; // 거리 업데이트
					next_visit.push(make_pair(e.to, dist[e.to])); // 다음 방문 정점 큐에 추가
				}
			}
		}

		if (!next_visit.empty()) {
			pair<int, int> next = next_visit.top(); // (정점, 거리)
			next_visit.pop();
			vert = next.first;
		}
		else
			break;
	}

	return dist; // 거리 벡터 반환
}
