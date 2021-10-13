#include "Header.h";

using namespace std;

class field {
private:
	int size;
	/*int field[size][size];
public:
	int GetSize() { return size; }
	int GetField() { return field; }

	void SetSize(int size) { this->size = size; }
	void SetField() {}*/
};

void showField(const string field[3][3]) {

	cout << "-" <<		'-'		<< '-' <<		'-'		<< "-" <<		'-'		<< '-' << endl;
	cout << "|" <<	field[0][0]	<< '|' <<	field[0][1]	<< "|" <<	field[0][2]	<< '|' << endl;
	cout << "-" <<		'-'		<< '-' <<		'-'		<< "-" <<		'-'		<< '-' << endl;
	cout << "|" <<	field[1][0]	<< '|' <<	field[1][1]	<< "|" <<	field[1][2]	<< '|' << endl;
	cout << "-" <<		'-'		<< '-' <<		'-'		<< "-" <<		'-'		<< '-' << endl;
	cout << "|" <<	field[2][0]	<< '|' <<	field[2][1]	<< "|" <<	field[2][2]	<< '|' << endl;
	cout << "-" <<		'-'		<< '-' <<		'-'		<< "-" <<		'-'		<< '-' << endl;

}

void myPause() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Press [Enter] or any character to continue.\n";
	cin.get();
}

vector<pair<int, int>> evenDiffBtwZeroAndNumberInPair(int num1) {
	vector<pair<int, int>> arrayOfPair;
	int n, diff, first, second;

	first = 0;
	second = num1;
	n = num1;
	diff = num1 / 2;
	for (int i = 0; i < n+1; i++) {
		arrayOfPair.push_back(make_pair(first, second));
		first += diff;
		second -= diff;
	}
	return arrayOfPair;
}

bool isItWrongPlace(int place, char reservedPlace[10]) {
	if (place > 9 || place < 1) {
		return 1;
	}
	if (reservedPlace[place] == '*'){
		return 1;
	}

	return 0;
}

bool isThereWinner(const string field[3][3]) {
	int k_r, k_c, k_d, k_antid;
	string check_r, check_c, check_d, check_antid;
	vector<pair<int, int>> arrayOfPair;
	pair<int, int> pair;

	k_r = k_c = k_d = k_antid = 0;
	arrayOfPair = evenDiffBtwZeroAndNumberInPair(2);

	/*for (int i = 0; i < 3; i++) {
		cout << arrayofpair[i].first << " " << arrayofpair[i].second << endl;
	}*/

	/*for (int i = 0; i < 3; i++) {
		check_r = check_c = check_d = field[i][0];
		for (int j = 0; j < 3; j++) {
			if (check_r == field[i][j]) {
				k_r++;
			}
		}
	}	
	return 0;*/
	
	for (int j = 0; j < 3; j++) {
		k_c = 0;
		check_c = field[0][j];

		for (int i = 0; i < 3; i++) {
			if (check_c == field[i][j])	k_c++;
		}
		if (k_c == 3) return 1;
	}

	check_antid = field[0][2];
	check_d = field[0][0];
	for (int i = 0; i < 3; i++) {
		k_r = 0;
		check_r = field[i][0];

		for (int j = 0; j < 3; j++) {
			if (arrayOfPair[i].first == i && arrayOfPair[i].second == j && check_antid == field[i][j]) k_antid++;
			if (i == j && check_d == field[i][j]) k_d++;
			if (check_r == field[i][j]) k_r++;
		}

		if (k_r == 3) return 1;
		if (k_d == 3) return 1;
		if (k_antid == 3) return 1;
	}

	return 0;
}

int main()
{
	string firstTurn, winner = "noone";
	int place, k = 0;
	bool gameEnds = false;
	string field[3][3];
	char reservedPlace[10] = {'0'};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			field[i][j] = to_string(i*3 + j + 1);
		}
	}

	cout << endl;

	while (1) {
		system("cls");
		showField(field);
		cout << "Choose your destiny: X or 0!?" << endl;
		cin >> firstTurn; // Выбираем кто ходит первым.

		if (firstTurn != "X" && firstTurn != "0") {
			cout << "It's not correct answer!" << endl;
			myPause();
			continue;
		}
		else {
			break;
		}
	}

	string turn = firstTurn;
	while (!gameEnds) {
		system("cls");
		showField(field);
		cout << turn << "'s turn! Choose number from the field." << endl;
		cin >> place;
		//int* pointPlace = &place;

		if (isItWrongPlace(place, reservedPlace)) {	// должна быть проверка в условии на занятые поля.
			cout << "Wrong input! Choose number from the field!" << endl;
			myPause();
			continue;
		}

		switch (place) {
			case 1:	field[0][0] = turn; reservedPlace[1] = '*'; k++; break;
			case 2: field[0][1] = turn; reservedPlace[2] = '*'; k++; break;
			case 3:	field[0][2] = turn; reservedPlace[3] = '*'; k++; break;
			case 4:	field[1][0] = turn; reservedPlace[4] = '*'; k++; break;
			case 5:	field[1][1] = turn; reservedPlace[5] = '*'; k++; break;
			case 6:	field[1][2] = turn; reservedPlace[6] = '*'; k++; break;
			case 7:	field[2][0] = turn; reservedPlace[7] = '*'; k++; break;
			case 8:	field[2][1] = turn; reservedPlace[8] = '*'; k++; break;
			case 9:	field[2][2] = turn; reservedPlace[9] = '*'; k++; break;
			default: break;
		}

		if (isThereWinner(field)) {
			gameEnds = true;
			winner = turn;
		}
		else if (k == 9) {
			gameEnds = true;
		}

		if (turn == "X") turn = "0";
		else turn = "X";	

	}

	system("cls");
	showField(field);
	if (winner == "noone") {
		cout << "The Winner is " << winner << ". Draw." << endl;
	} 
	else {
		cout << "The Winner is " << winner << endl;
	}

	return 0;
}