/************************************
 * Автор: Важенин С.С               *
 * Дата:  03.12.2024                *
 * Название: Лабораторная работа №4 *
 ************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int compareTwoBigInt(vector<int> firstVector, vector<int> secondVector) {
    if (firstVector.size() != secondVector.size()) {
        if (firstVector.size() > secondVector.size()) {
            return 1;
        } else {
            return -1;
        }
    }

    for (int i = firstVector.size() - 1; i >= 0; --i) {
        if (firstVector[i] != secondVector[i]) {
            if (firstVector[i] > secondVector[i]) {
                return 1;
            } else {
                return -1;
            }
        }
    }
    return 0;
}

vector<int> plusTwoBigInt(vector<int> firstVector, vector<int> secondVector) {
    vector<int> result;
    int carry = 0;
    int length = max(firstVector.size(), secondVector.size());
    for (int i = 0; i < length; ++i) {
        int digitFirstVector = 0;
        int digitSecondVector = 0;
        if (i < firstVector.size()) {
            digitFirstVector = firstVector[i];
        }
        if (i < secondVector.size()) {
            digitSecondVector = secondVector[i];
        }
        int sum = digitFirstVector + digitSecondVector + carry;
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    if (carry > 0) {
        result.push_back(carry);
    }
    return result;
}

vector<int> minusTwoBigInt(vector<int> firstVector, vector<int> secondVector) {
    if (compareTwoBigInt(firstVector, secondVector) < 0) {
        swap(firstVector, secondVector);
    }
    vector<int> result;
    int borrow = 0;
    int length = max(firstVector.size(), secondVector.size());
    for (int i = 0; i < length; ++i) {
        int digitFirstVector = 0;
        int digitSecondVector = 0;
        if (i < firstVector.size()) {
            digitFirstVector = firstVector[i];
        }
        if (i < secondVector.size()) {
            digitSecondVector = secondVector[i];
        }
        int diff = digitFirstVector - digitSecondVector - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff);
    }
    return result;
}

vector<int> stringToVector(string number) {
    vector<int> digits;
    for (int i = number.size() - 1; i >= 0; --i) {
        digits.push_back(number[i] - '0');
    }
    return digits;
}

string vectorToString(vector<int> digits) {
    string number;
    for (int i = digits.size() - 1; i >= 0; --i) {
        number += digits[i] + '0';
    }
    return number;
}

bool strIsDigit(string num) {
    int count = 0;
    for (int i = 0; i < num.size(); ++i) {
        if (isdigit(num[i])) {
            count += 1;
        }
    }
    if (count == num.size() && count != 0) {
        return true;
    }
    return false;
}

void inputBigInt(vector<int>& digits, bool& isNegative) {
    string num;
    isNegative = false;
    while (true) {
        getline(cin, num);
        if (num[0] == '-') {
            isNegative = true;
            num = num.substr(1);
        }
        if (strIsDigit(num)) {
            digits = stringToVector(num);
            return;
        } else {
            cout << "Вы ввели не число (попробуйте ещё раз): ";
        }
    }
}

int main() {
    vector<int> firstVector;
    vector<int> secondVector;
    bool firstIsNegative;
    bool secondIsNegative;

    cout << "Введите первое число: ";
    inputBigInt(firstVector, firstIsNegative);

    cout << "Введите второе число: ";
    inputBigInt(secondVector, secondIsNegative);

    int numChoice = -1;
    while (numChoice != 0) {
        cout << endl;
        cout << "[1]Сложение [2]Вычитание [3]Какое число больше? [0]Выйти\nДействия над числами (выберите цифру): ";
        cin >> numChoice;

        switch (numChoice) {
        case 1: {
            vector<int> sum;
            bool resultIsNegative = false;
            if (firstIsNegative && secondIsNegative) {
                sum = plusTwoBigInt(firstVector, secondVector);
                resultIsNegative = true;
            } else if (firstIsNegative) {
                sum = minusTwoBigInt(secondVector, firstVector);
            } else if (secondIsNegative) {
                sum = minusTwoBigInt(firstVector, secondVector);
            } else {
                sum = plusTwoBigInt(firstVector, secondVector);
            }
            if (resultIsNegative) {
                cout << "Сумма: -" << vectorToString(sum) << endl;
            } else {
                cout << "Сумма: " << vectorToString(sum) << endl;
            }
            break;
        }
        case 2: {
            vector<int> minus;
            bool resultIsNegative = false;
            if (firstIsNegative && secondIsNegative) {
                minus = minusTwoBigInt(secondVector, firstVector);
                resultIsNegative = true;
            } else if (firstIsNegative) {
                minus = plusTwoBigInt(firstVector, secondVector);
                resultIsNegative = true;
            } else if (secondIsNegative) {
                minus = plusTwoBigInt(firstVector, secondVector);
            } else {
                minus = minusTwoBigInt(firstVector, secondVector);
            }
            if (resultIsNegative) {
                cout << "Разность: -" << vectorToString(minus) << endl;
            } else {
                cout << "Разность: " << vectorToString(minus) << endl;
            }
            break;
        }
        case 3: {
            if (firstIsNegative && !secondIsNegative) {
                cout << "Второе число больше" << endl;
            } else if (!firstIsNegative && secondIsNegative) {
                cout << "Первое число больше" << endl;
            } else if (firstIsNegative && secondIsNegative) {
                int comparison = compareTwoBigInt(secondVector, firstVector);
                if (comparison > 0) {
                    cout << "Первое число больше" << endl;
                } else if (comparison < 0) {
                    cout << "Второе число больше" << endl;
                } else {
                    cout << "Числа равны" << endl;
                }
            } else {
                int comparison = compareTwoBigInt(firstVector, secondVector);
                if (comparison > 0) {
                    cout << "Первое число больше" << endl;
                } else if (comparison < 0) {
                    cout << "Второе число больше" << endl;
                } else {
                    cout << "Числа равны" << endl;
                }
            }
            break;
        }
        default:
            break;
        }
    }

}
