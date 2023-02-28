#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <iomanip>

using namespace std;

int a = 0;

// ��ǥ �̵�: 2���� �迭�� ����̹Ƿ�, 
// �Ʒ���(x): row����, ������(y): col����, �Լ� ��ǥ�� �ٸ�! �Ű澵 ��
const int V[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
const int U = 0, D = 1, L = 3, R = 2;
const int N = U, S = D, E = R, W = L;

vector<string> split(string input, char delimiter);
void print_90(vector<string> k, int index, int depth, string**& arr);
bool insert_list_check(string input, string* list, int size);
void make_htree(string str, int index, int i, int j, int depth, int U, int D, int R, int L, string**& H_tree_arr);
int h_center(int number) { return number <= 1 ? 0 : 2 * h_center(number / 4) + 1; }
int h_depth(int number) { return number <= 7 ? 1 : 2 * h_depth(number / 4); }

int main(void) {
	string token;								// ������ �������� ���е� ���ڿ� ��ū
	string input = "";							// �Է¹��� ���ڿ��� ������ ����
	int number = 0;								// Ʈ�� ���Ұ���
	int depth = 0;								// Ʈ���� ����
	int row_90 = 0, col_90 = 0;					// 90�� ���ư� Ʈ���� ������ �迭�� ��, ��
	int row = 0, col = 0;						// Ʈ���� ������ �迭�� ��, ��
	const int operation_num = 200;				// �ִ� ���� Ƚ��
	int operation_cnt = 0;						// ���� Ƚ�� ī��Ʈ

	// ���԰����� ���� ����Ʈ
	string insert_list[63] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "?", 
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", 
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
	};
	
	// Ű���� �Է��� �޴� �κ�(token���� ���� �ٺ� �Է��� input�� ����¥�� ���ڿ��� ����)
	while (true) {
		getline(cin, token);
		// �� ���� ������ �Է��� EOI�϶�
		if (token[token.size() - 3] == 'E' && token[token.size() - 2] == 'O' && token[token.size() - 1] == 'I') {
			if (input == "") {	// input�� ù �Է��̶�� ������ ����� �ʰ� input�� �ٷ� �߰�
				for (unsigned int i = 0; i < token.size() - 3; i++) {
					input += token[i];
				}
			}
			else {
				input += " ";	// �տ� �̹� �ٸ� ���� �����ϸ� �ƴ϶�� ������ ���� input�� �߰�
				for (unsigned int i = 0; i < token.size() - 3; i++) {
					input += token[i];
				}
			}
			break;
		}
		// �� ���� ������ �Է��� EOI�� �ƴ� ��
		else {	// ù �Է��̶�� ������ ����� �ʰ� input�� �ٷ� �߰�
			if (input == "") {
				input += token;
			}
			else { // �տ� �̹� �ٸ� ���� �����ϸ� �ƴ϶�� ������ ���� input�� �߰�
				input += ' ';
				input += token;
			}
		}
	}	

	vector<string> command;			// �Է¹��� heap operation�� ���� ������ ����
	command = split(input, ' ');	// ������ �������� ����
	vector<string> v;				// heap ���� v
	make_heap(v.begin(), v.end());	// v�� heap�� ����

	for (unsigned int i = 0; i < command.size(); i++) {
		if (operation_cnt > 200) {
			cout << "Error! Number of operations exceeded 200" << endl;
			return 0;
		}
		else {
			// INS�� ������ �ٷ� ���� ���� push_heap ����
			if (command[i] == "INS") {
				if (insert_list_check(command[i + 1], insert_list, sizeof(insert_list)/sizeof(string))) {
					v.push_back(command[i + 1]);
					push_heap(v.begin(), v.end());
					i++;
					number++;
					operation_cnt++;
				}
				else {
					return 0;
				}
			}
			// DEL�� ������ pop_heap ����
			else if (command[i] == "DEL") {
				pop_heap(v.begin(), v.end());
				v.pop_back();
				number--;
				operation_cnt++;
			}
			// �ٸ� �̻��� �Է��� ���� ��� 
			else {
				cout << "Error! Heap Operation Command is not correct. Try again!" << endl;
				return 0;
			}
		}
	}

	depth = log2(number + 1);	// ���� Ʈ���� ����
	row_90 = number;
	col_90 = depth+1;
	// Ʈ���� ��, ���� �ٲ�(ȸ�� ���� Ʈ��)
	row = col_90;				
	col = row_90;				

	// rotated form 2���� �迭 �����Ҵ� �� t�� �ʱ�ȭ
	string** rotated_tree_arr = new string* [row_90];
	for (int i = 0; i < row_90; i++) {
		rotated_tree_arr[i] = new string[col_90];
	}

	for (int i = 0; i < row_90; i++) {
		for (int j = 0; j < col_90; j++) {
			rotated_tree_arr[i][j] = 't';
		}
	}

	// not-rotated form 2���� �迭 �����Ҵ� �� t�� �ʱ�ȭ
	string** original_tree = new string * [row];
	for (int i = 0; i < row; i++) {
		original_tree[i] = new string[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			original_tree[i][j] = 't';
		}
	}
	
	// 1. rotated form ���
	cout << "1. rotated form" << endl;
	print_90(v, 0, 0, rotated_tree_arr);	// ȸ�� Ʈ���� �׸�


	// rotated form �ݽð� �������� 90�� ȸ��
	for (int i = 0; i < row_90; i++) {
		for (int j = 0; j < col_90; j++) {
			original_tree[j][row_90 - i - 1] = rotated_tree_arr[i][j];
		}
	}

	// 2. not-rotated form ���
	cout << "2. not-rotated form" << endl;
	// complete binary tree ���, t�� ��� �������� ���ó��
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (original_tree[i][j] == "t") {
				cout << " ";
			}
			else {
				cout << original_tree[i][j];
			}
		}
		cout << endl;
	}

	// H-Tree
	string h_tree_str;

	for (int i = 0; i < v.size(); i++) {
		h_tree_str += v[i];
	}

	int h_tree_center = 0;
	int h_tree_depth = 0;
	
	h_tree_center = h_center(h_tree_str.length());
	h_tree_depth = h_depth(h_tree_str.length());

	int h_tree_row = h_tree_center * 2 + 1;
	int h_tree_col = h_tree_row; // h-tree�� ���� �迭�� ����迭

	// H-Tree�� ���� 2���� �����迭 ����
	string** H_tree = new string * [h_tree_row];
	for (int i = 0; i < h_tree_row; i++) {
		H_tree[i] = new string[h_tree_col * 2 + 1];
	}

	for (int i = 0; i < h_tree_row; i++) {
		for (int j = 0; j < h_tree_col; j++) {
			H_tree[i][j] = 't';
		}
	}
	
	make_htree(h_tree_str, 1, h_tree_center, h_tree_center, h_tree_depth, N, S, E, W, H_tree);
	
	// 3. H-tree form ���
	cout << "3. H-tree form" << endl;
	for (int i = 0; i < h_tree_row; i++) {
		for (int j = 0; j < h_tree_col; j++) {
			if (H_tree[i][j] == "t") {
				cout << " ";
			}
			else {
				cout << H_tree[i][j];
			}
		}
		cout << endl;
	}

	return 0;
}

// delimiter�� ������� ���ڿ��� �ɰ��� �Լ�
vector<string> split(string input, char delimiter)
{
	vector<string> result;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter)) {
		result.push_back(temp);
	}
	return result;
}


// ȸ�� Ʈ���� �׸��� �Լ�
void print_90(vector<string> k, int index, int depth, string**& arr) {
	if (index < k.size()) {
		// ���� �ڽ� ��� ���
		print_90(k, 2 * index + 2, depth + 1, arr);
		// �ڱ� �ڽ� ���
		cout << setw(depth * 2 + 1) << k[index] << endl;
		if (depth == 0) {
			arr[a][0] = k[index];
		}
		else {
			arr[a][depth] = k[index];
		}
		a++;
		// ������ �ڽ� ���
		print_90(k, 2 * index + 1, depth + 1, arr);
	}
}

// �Է¹��� ���� ������ �Է°��� ���ϴ��� Ȯ��
bool insert_list_check(string input, string* list, int size) {
	for (int i = 0; i < size; i++) {
		if (input == list[i]) {
			return true;
		}
	}
	cout << "Error! Value is not on the insert list!" << endl;
	return false;
}

// H-Tree ����� �Լ�
void make_htree(string str, int index, int i, int j, int depth, int U, int D, int R, int L, string**& H_tree_arr) {
	if (index > str.length()) return;	// ����ó��
	H_tree_arr[i][j] = str[index - 1];	// 0 �ε��� ���� ������ ���
	// ��
	if (2 * index <= str.length()) {
		H_tree_arr[i + depth * V[L][0]][j + depth * V[L][1]] = str[2 * index - 1];	// �� ���
		make_htree(str, 4 * index, i + depth * (V[L][0] + V[U][0]), j + depth * (V[L][1] + V[U][1]), depth / 2, D, U, L, R, H_tree_arr);		// �»� ���
		make_htree(str, 4 * index + 1, i + depth * (V[L][0] + V[D][0]), j + depth * (V[L][1] + V[D][1]), depth / 2, U, D, R, L, H_tree_arr);	// ���� ���
	}
	// ��
	if (2 * index + 1 <= str.length()) {
		H_tree_arr[i + depth * V[R][0]][j + depth * V[R][1]] = str[2 * index];	// �� ���
		make_htree(str, 4 * index + 2, i + depth * (V[R][0] + V[D][0]), j + depth * (V[R][1] + V[D][1]), depth / 2, U, D, R, L, H_tree_arr);	// ���� ���
		make_htree(str, 4 * index + 3, i + depth * (V[R][0] + V[U][0]), j + depth * (V[R][1] + V[U][1]), depth / 2, D, U, L, R, H_tree_arr);	// ��� ����
	}
}