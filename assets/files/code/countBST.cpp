#include <iostream>
#include <string>
using namespace std;

class node {
private:
	int data;
	node* left;
	node* right;

	int cnt = 1;

public:
	node(int d, node* l, node* r) {
		data = d;
		left = l;
		right = r;
	}
	~node() {}

	int getData() { return data; }
	node* getLeft() { return left; }
	node* getRight() { return right; }
	int getcnt() { return cnt; }

	void setLeft(node* le) { left = le; }
	void setRight(node* ri) { right = ri; }
	void upcnt() { cnt += 1; }
	void downcnt() { cnt -= 1; }
	void setData(int d) { data = d; }

	bool isLeaf() { return left == nullptr && right == nullptr; }
};

class bst {
private:
	node* root = nullptr;

private:
	node* find_impl(node* current, int value) { // private 탐색 메소드
		while (true) {
			if (current == nullptr) { // 현재 탐색하는 노드가 NULL인 경우
				cout << "No matching value found for " << value << ".\n";
				return NULL;
			}

			if (current->getData() == value) { // 원하는 값 찾음
				cout << value << " has been found.\n";
				return current;
			}
			else if (value < current->getData()) { // 원하는 값이 더 작음
				cout << "current is " << current->getData() << ". pointer moved to left.\n";
				current = current->getLeft(); // 왼쪽 서브트리로 이동
			}
			else { // 위의 모든 선택문을 패스했다면 원하는 값이 더 큰 경우임
				cout << "current is " << current->getData() << ". pointer moved to right.\n";
				current = current->getRight(); // 오른쪽 서브트리로 이동
			}
		}
	}

	void insert_impl(node* current, int value) { // private 삽입 메소드
		while (true) {
			current->upcnt(); // 노드가 삽입되는 경로를 따라 카운트 증가

			if (value < current->getData()) { // 삽입할 값이 현재 탐색하는 노드보다 작음
				if (current->getLeft() == nullptr) { // 왼쪽 서브트리 없음
					current->setLeft(new node{ value, NULL, NULL }); // 바로 붙임
					cout << "current is " << current->getData() << ", " << value << " is inserted left\n";
					return;
				}
				else { // 왼쪽 서브트리 있음
					current = current->getLeft(); // 왼쪽 서브트리로 이동
				}
			}
			else { // else: 삽입할 값이 현재 탐색하는 노드보다 크거나 같음
				if (current->getRight() == nullptr) { // 오른쪽 서브트리 없음
					current->setRight(new node{ value, NULL, NULL }); // 바로 붙임
					cout << "current is " << current->getData() << ", " << value << " is inserted right\n";
					return;
				}
				else { // else: 오른쪽 서브트리 있음
					current = current->getRight(); // 오른쪽 서브트리로 이동
				}
			}
		}
	}

	void inorder_impl(node* start) { // private 중위순회(LDR) 메소드
		if (start == nullptr) // 현재 탐색중인 노드가 NULL
			return; // 돌아감

		inorder_impl(start->getLeft()); // L: 왼쪽 서브트리 순회 호출
		cout << start->getData() << "(" << start->getcnt() << ") "; // D: 현재 노드 데이터 출력
		inorder_impl(start->getRight()); // R: 오른쪽 서브트리 순회 호출
	}

	node* delete_impl(node* start, int value) { // private 특정 값 삭제 메소드
		cout << "current node is " << (start ? to_string(start->getData()) : "NULL") << ".\n";

		if (!start) { // 현재 노드가 NULL
			cout << "No value matches " << value << ".\n";
			return NULL; // 삭제한 노드 없음, NULL 반환
		}

		if (value < start->getData()) // 삭제할 값이 현재 노드보다 작음
			start->setLeft(delete_impl(start->getLeft(), value)); // 왼쪽 서브트리에 삭제 메소드 다시 호출
		else if (value > start->getData()) // else if: 삭제할 값이 현재 노드보다 큼
			start->setRight(delete_impl(start->getRight(), value)); // 오른쪽 서브트리에 삭제 메소드 다시 호출
		else { // else: 삭제할 값이 현재 노드와 같음
			if (!start->getLeft()) { // 왼쪽 서브트리가 없음
				cout << "there is no left subtree. bring the right subtree.\n";
				auto tmp = start->getRight(); // 현재 노드의 오른쪽 서브트리를 가져옴
				cout << "delete " << value << ".\n";
				delete start; // 현재 노드를 지움
				return tmp; // 아까 가져온 오른쪽 서브트리 반환
			}

			if (!start->getRight()) { // 오른쪽 서브트리가 없음
				cout << "there is no right subtree. bring the left subtree.\n";
				auto tmp = start->getLeft(); // 현재 노드의 왼쪽 서브트리 가져옴
				cout << "delete " << value << ".\n";
				delete start; // 현재 노드를 지움
				return tmp; // 아까 가져온 왼쪽 서브트리 반환
			}
		}

		return start;
	}

	void recount(node* value) { // 노드 삭제를 위해 누적 노드 개수를 수정하는 메소드
		node* current = root; // 루트에서 시작

		while (true) {
			if (!current) { // 현재 탐색하는 노드가 NULL인 경우
				cout << "error: No matching value found for " << value->getData() << ".\n";
				return; // 끝
			}

			current->downcnt(); // 현재 노드의 카운트 감소

			if (value->getData() > current->getData()) { // 원하는 값이 더 큼
				cout << "current is " << current->getData() << ". pointer moved to right.\n";
				current = current->getRight(); // 오른쪽 서브트리로 이동
				continue;
			}

			if (value->getData() < current->getData()) { // 원하는 값이 더 작음
				cout << "current is " << current->getData() << ". pointer moved to left.\n";
				current = current->getLeft(); // 왼쪽 서브트리로 이동
				continue;
			}

			/*
			원하는 값 찾음:
			후계자가 선정되어 값이 바뀌었거나 값이 같은 노드가 중복하여 존재하는 경우,
			삭제할 노드를 헷갈리지 않기 위해 객체 자체를 비교함
			*/
			if (current == value) {
				cout << value->getData() << " has been found.\n";
				return;
			}

			// 원래 삭제하려던 노드의 후계자가 대신 삭제되어야 하는 경우
			// data는 같지만 노드 자체는 달라서 위의 선택문을 모두 통과하는 경우가 있음
			// 그럴 때는 후계자 선정 규칙에 따라 오른쪽 서브트리로 이동
			cout << "current is " << current->getData() << ". pointer moved to right.\n";
			current = current->getRight(); // 오른쪽 서브트리로 이동
			continue;
		}
	}

public:
	node* getRoot() { return root; }

	node* find(int value) { // 특정 값 탐색 메소드
		return find_impl(root, value); // 따로 구현된 private 탐색 메소드 호출
	}

	void insert(int value) { // 삽입 메소드
		if (root == nullptr) { // 루트가 비어있다면
			root = new node{ value, nullptr, nullptr }; // 루트에 바로 넣음
			cout << value << " is inserted into root\n";
		}
		else // else: 루트가 비어있지 않다면
			insert_impl(root, value); // 따로 구현된 private 삽입 메소드 호출
	}

	void inorder() { // 중위순회 메소드
		inorder_impl(root); // private 중위순회 메소드 호출
	}

	node* successor(node* start) { // 후계자 반환 메소드
		auto current = start->getRight(); // 현재 노드의 오른쪽 서브트리 가져옴

		while (current != nullptr && current->getLeft() != nullptr) // 지금 갖고있는 노드와 그 노드의 왼쪽 서브트리가 모두 존재하는 동안 반복
			current = current->getLeft(); // 왼쪽 서브트리로 이동

		cout << "successor is " << (current != nullptr ? to_string(current->getData()) : "NULL") << ".\n";
		return current; // 결과: 오른쪽 서브트리 왼쪽 맨 아래 리프노드 반환
	}

	void deleteValue(int value) { // 특정 값 삭제
		node* del_node = find(value); // 삭제할 노드 찾기
		node* succ;

		if (del_node != NULL) { // 삭제할 노드가 있다면
			if (del_node->getLeft() != NULL && del_node->getRight() != NULL) { // 후계 필요
				succ = successor(del_node); // 후계 선정
				recount(succ); // 노드 삭제를 위해 누적 노드 개수를 수정하는 메소드
				del_node->setData(succ->getData()); // 삭제할 노드의 데이터를 후계의 데이터로 대체
				root->setRight(delete_impl(root->getRight(), succ->getData())); // 후계 노드 삭제
			}
			else { // 후계 필요 없음
				recount(del_node); // 노드 삭제를 위해 누적 노드 개수를 수정하는 메소드
				root = delete_impl(root, value); // private 삭제 메소드 호출
			}
		}
		else { // 삭제할 노드가 없음
			cout << "delete error: No value matches " << value << ".\n";
			return; // 돌아감
		}
	}

	int countGreater(int key) { // 특정 값(key)보다 큰 요소의 개수 셈
		int cnt = 0;
		node* current = root;

		while (true) { // 반복 탐색
			cout << "current value is " << (current != NULL ? to_string(current->getData()) : "NULL") << "\n";

			if (current == NULL) // 더 탐색할 노드가 없음
				break; // 반복 종료

			if (key == current->getData()) { // key와 같은 값 찾음
				// 오른쪽에 더 큰 값이 남아있을 수 있으므로 오른쪽으로 이동
				cout << "find key value. go right.\n";
				current = current->getRight();
				continue;
			}
			else if (key < current->getData()) { // key보다 큰 값 찾음
				cnt += 1; // 일단 현재 노드를 카운트에 추가

				if (current->getRight() != NULL) // 오른쪽 서브트리가 있다면
					cnt += current->getRight()->getcnt(); // 오른쪽 서브트리의 노드 수도 추가

				// 왼쪽에 더 큰 값이 남아있을 수 있으므로 왼쪽으로 이동
				cout << "current value " << current->getData() << " is greater than key value. add right count and go left\n";
				current = current->getLeft();
				continue;
			}
			else if (key > current->getData()) { // key보다 작은 값 찾음
				// 오른쪽에 더 큰 값이 남아있을 수 있으므로 오른쪽으로 이동
				cout << "current value " << current->getData() << " is lesser than key value. Don't add count and go right\n";
				current = current->getRight();
				continue;
			}
		}

		return cnt; // 반복 종료 후 결과 반환
	}

	int countLesser(int key) { // 특정 값(key)보다 작은 요소의 개수 셈
		int cnt = 0;
		node* current = root;

		while (true) { // 반복 탐색
			cout << "current value is " << (current != NULL ? to_string(current->getData()) : "NULL") << "\n";

			if (current == NULL) // 더 탐색할 노드가 없음
				break; // 반복 종료

			if (key == current->getData()) { // key와 같은 값 찾음
				// 왼쪽에 더 작은 값이 남아있을 수 있으므로 왼쪽으로 이동
				cout << "find key value. go left.\n";
				current = current->getLeft();
				continue;
			}
			else if (key > current->getData()) { // key보다 작은 값 찾음
				cnt += 1; // 현재 노드를 카운트에 추가

				if (current->getLeft() != NULL) // 왼쪽에 서브트리가 있다면
					cnt += current->getLeft()->getcnt(); // 왼쪽 서브트리의 노드 수도 추가

				// 오른쪽에 더 작은 값이 남아있을 수 있으므로 오른쪽으로 이동
				cout << "current value " << current->getData() << " is lesser than key value. add left count and go right.\n";
				current = current->getRight();
				continue;
			}
			else if (key < current->getData()) {
				// 왼쪽에 더 작은 값이 남아있을 수 있으므로 왼쪽으로 이동
				cout << "current value " << current->getData() << " is greater than key value. Don't add count and go left\n";
				current = current->getLeft();
				continue;
			}
		}

		return cnt; // 반복 종료 후 결과 반환
	}
};

int main()
{
	bst tree;
	int tmp = 11;
	int tmp_res;

	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);
	tree.insert(27);
	cout << "\n";

	tmp_res = tree.countGreater(tmp);
	cout << "count value greater than " << tmp << " : " << tmp_res << "\n";
	cout << "\n";
	tmp_res = tree.countLesser(tmp);
	cout << "count value lesser than " << tmp << " : " << tmp_res << "\n";
	cout << "\n";

	cout << "Inorder Traversal: ";
	tree.inorder();
	cout << "\n";

	tree.deleteValue(12);
	cout << "Delete 12 and Do Inorder Traversal: ";
	tree.inorder();
	cout << "\n";

	if (tree.find(12))
		cout << "Value 12 is in the tree.\n";
	else
		cout << "Value 12 is not in the tree.\n";
	cout << "\n";

	tree.deleteValue(11);
	tree.deleteValue(4);
	tree.deleteValue(0);
	tree.inorder();
}