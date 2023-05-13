#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cmath> 

using namespace std;

//生成指定范围内的随机整数或小数
double random(double min, double max, bool canFraction) {
    double result = 0.0;
    if (canFraction) {
        //随机小数的整数位和小数位
        int integer = rand() % (int)max;
        //double fraction = ((double)rand() / RAND_MAX) * pow(0.1, rand() % 4 + 1); //生成小数位的随机值，并向下取整
        double fraction = ((double)rand() / RAND_MAX) * 9 + 1; //生成1到9之间的整数部分
        fraction += ((double)rand() / RAND_MAX); //生成1位小数
        fraction = floor(fraction * 10) / 10; //保留1位小数位，并向下取整
        result = integer + fraction;
    }
    else {
        //随机整数
        result = rand() % (int)max + min;
    }
    return result;
}

//生成随机算式
string generateExpression(bool add, bool sub, bool mul, bool div, bool hasBrackets, bool canFraction, int maxNum) {
    //生成随机数字和运算符
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
    //先计算括号内的部分
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
    //获取用户的输入
    int numProblems = 10;
    int maxNum = 10;
    bool hasAdd = true;
    bool hasSub = true;
    bool hasMul = true;
    bool hasDiv = true;
    bool hasBrackets = true;
    bool canFraction = false;
    string outputType = "console";

    cout << "请输入要生成的题目数量：" << endl;
    cin >> numProblems;
    cout << "请输入最大数字：" << endl;
    cin >> maxNum;
    cout << "请勾选要包含的运算符（可多选）：" << endl;
    cout << "加法（+）：";
    cin >> hasAdd;
    cout << "减法（-）：";
    cin >> hasSub;
    cout << "乘法（*）：";
    cin >> hasMul;
    cout << "除法（/）：";
    cin >> hasDiv;
    cout << "是否包含括号（1为是，0为否）：" << endl;
    cin >> hasBrackets;
    cout << "是否包含小数（1为是，0为否）：" << endl;
    cin >> canFraction;
    cout << "请输入输出方式（console 或 file）：" << endl;
    cin >> outputType;

    //输出到文件或控制台
    if (outputType == "file") {
        string fileName = "problems.txt";
        ofstream fout(fileName, ios::out);
        if (!fout.is_open()) {
            cout << "文件打开失败！";
        }
        for (int i = 1; i <= numProblems; i++) {
            fout << i << ". ";
            fout << generateExpression(hasAdd, hasSub, hasMul, hasDiv, hasBrackets, canFraction, maxNum);
            fout << " = " << endl;
        }
        fout.close();
        cout << "题目已生成，保存在文件 " << fileName << " 中。" << endl;
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