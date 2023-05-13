#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cmath> 

using namespace std;

//����ָ����Χ�ڵ����������С��
double random(double min, double max, bool canFraction) {
    double result = 0.0;
    if (canFraction) {
        //���С��������λ��С��λ
        int integer = rand() % (int)max;
        //double fraction = ((double)rand() / RAND_MAX) * pow(0.1, rand() % 4 + 1); //����С��λ�����ֵ��������ȡ��
        double fraction = ((double)rand() / RAND_MAX) * 9 + 1; //����1��9֮�����������
        fraction += ((double)rand() / RAND_MAX); //����1λС��
        fraction = floor(fraction * 10) / 10; //����1λС��λ��������ȡ��
        result = integer + fraction;
    }
    else {
        //�������
        result = rand() % (int)max + min;
    }
    return result;
}

//���������ʽ
string generateExpression(bool add, bool sub, bool mul, bool div, bool hasBrackets, bool canFraction, int maxNum) {
    //����������ֺ������
    double num1 = random(1, maxNum, canFraction);
    char op1 = '+';
    int op1Index = 0;
    if (add) {
        op1Index++;
    }
    if (sub) {
        op1Index++;
    }
    if (mul) {
        op1Index++;
    }
    if (div) {
        op1Index++;
    }
    op1Index = rand() % op1Index;
    if (op1Index == 0) {
        op1 = '+';
    }
    else if (op1Index == 1) {
        op1 = '-';
    }
    else if (op1Index == 2) {
        op1 = '*';
    }
    else if (op1Index == 3) {
        op1 = '/';
    }
    double num2 = random(1, maxNum, canFraction);
    char op2 = '+';
    int op2Index = 0;
    if (add) {
        op2Index++;
    }
    if (sub) {
        op2Index++;
    }
    if (mul) {
        op2Index++;
    }
    if (div) {
        op2Index++;
    }
    op2Index = rand() % op2Index;
    if (op2Index == 0) {
        op2 = '+';
    }
    else if (op2Index == 1) {
        op2 = '-';
    }
    else if (op2Index == 2) {
        op2 = '*';
    }
    else if (op2Index == 3) {
        op2 = '/';
    }
    double num3 = random(1, maxNum, canFraction);
    char op3 = '+';
    int op3Index = 0;
    if (add) {
        op3Index++;
    }
    if (sub) {
        op3Index++;
    }
    if (mul) {
        op3Index++;
    }
    if (div) {
        op3Index++;
    }
    op3Index = rand() % op3Index;
    if (op3Index == 0) {
        op3 = '+';
    }
    else if (op3Index == 1) {
        op3 = '-';
    }
    else if (op3Index == 2) {
        op3 = '*';
    }
    else if (op3Index == 3) {
        op3 = '/';
    }
    double num4 = random(1, maxNum, canFraction);
    //�ȼ��������ڵĲ���
    string expression = "";
    if (hasBrackets && rand() % 2 == 1) {
        int bracketType = rand() % 4;
        if (bracketType == 0) {
            expression.append("(");
            expression.append(to_string(num1));
            expression.append(" ");
            expression.append(string(1, op1));
            expression.append(" ");
            expression.append(to_string(num2));
            expression.append(")");
            expression.append(" ");
            expression.append(string(1, op2));
            expression.append(" ");
            expression.append(to_string(num3));
            expression.append(" ");
            expression.append(string(1, op3));
            expression.append(" ");
            expression.append(to_string(num4));
        }
        else if (bracketType == 1) {
            expression.append(to_string(num1));
            expression.append(" ");
            expression.append(string(1, op1));
            expression.append(" ");
            expression.append("(");
            expression.append(to_string(num2));
            expression.append(" ");
            expression.append(string(1, op2));
            expression.append(" ");
            expression.append(to_string(num3));
            expression.append(")");
            expression.append(" ");
            expression.append(string(1, op3));
            expression.append(" ");
            expression.append(to_string(num4));
        }
        else if (bracketType == 2) {
            expression.append(to_string(num1));
            expression.append(" ");
            expression.append(string(1, op1));
            expression.append(" ");
            expression.append(to_string(num2));
            expression.append(" ");
            expression.append(string(1, op2));
            expression.append(" ");
            expression.append("(");
            expression.append(to_string(num3));
            expression.append(" ");
            expression.append(string(1, op3));
            expression.append(" ");
            expression.append(to_string(num4));
            expression.append(")");
        }
        else if (bracketType == 3) {
            expression.append(to_string(num1));
            expression.append(" ");
            expression.append(string(1, op1));
            expression.append(" (");
            expression.append(to_string(num2));
            expression.append(" ");
            expression.append(string(1, op2));
            expression.append(" ");
            expression.append(to_string(num3));
            expression.append(") ");
            expression.append(string(1, op3));
            expression.append(" ");
            expression.append(to_string(num4));
        }
    }
    else {
        expression.append(to_string(num1));
        expression.append(" ");
        expression.append(string(1, op1));
        expression.append(" ");
        expression.append(to_string(num2));
        expression.append(" ");
        expression.append(string(1, op2));
        expression.append(" ");
        expression.append(to_string(num3));
        expression.append(" ");
        expression.append(string(1, op3));
        expression.append(" ");
        expression.append(to_string(num4));
    }
    return expression;
    }

int main() {
    srand((unsigned int)time(NULL));
    //��ȡ�û�������
    int numProblems = 10;
    int maxNum = 10;
    bool hasAdd = true;
    bool hasSub = true;
    bool hasMul = true;
    bool hasDiv = true;
    bool hasBrackets = true;
    bool canFraction = false;
    string outputType = "console";

    cout << "������Ҫ���ɵ���Ŀ������" << endl;
    cin >> numProblems;
    cout << "������������֣�" << endl;
    cin >> maxNum;
    cout << "�빴ѡҪ��������������ɶ�ѡ����" << endl;
    cout << "�ӷ���+����";
    cin >> hasAdd;
    cout << "������-����";
    cin >> hasSub;
    cout << "�˷���*����";
    cin >> hasMul;
    cout << "������/����";
    cin >> hasDiv;
    cout << "�Ƿ�������ţ�1Ϊ�ǣ�0Ϊ�񣩣�" << endl;
    cin >> hasBrackets;
    cout << "�Ƿ����С����1Ϊ�ǣ�0Ϊ�񣩣�" << endl;
    cin >> canFraction;
    cout << "�����������ʽ��console �� file����" << endl;
    cin >> outputType;

    //������ļ������̨
    if (outputType == "file") {
        string fileName = "problems.txt";
        ofstream fout(fileName, ios::out);
        if (!fout.is_open()) {
            cout << "�ļ���ʧ�ܣ�";
        }
        for (int i = 1; i <= numProblems; i++) {
            fout << i << ". ";
            fout << generateExpression(hasAdd, hasSub, hasMul, hasDiv, hasBrackets, canFraction, maxNum);
            fout << " = " << endl;
        }
        fout.close();
        cout << "��Ŀ�����ɣ��������ļ� " << fileName << " �С�" << endl;
    }
    else {
        for (int i = 1; i <= numProblems; i++) {
            cout << i << ". ";
            cout << generateExpression(hasAdd, hasSub, hasMul, hasDiv, hasBrackets, canFraction, maxNum);
            cout << " = " << endl;
        }
    }

    return 0;
}