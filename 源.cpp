//流输入输出
#include <iostream>
#include <fstream>
#include <sstream>
#include <fcntl.h>//文件描述符控制
#include <io.h>
//输出控制操纵器
#include <iomanip>
//编码控制
#include <locale>
#include <codecvt>
//拓展数据结构
#include <string>
#include <vector>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
//拓展函数方法
#include <cstdlib>
#include <algorithm>
#include <cctype>//字符类型判断
#include <cmath>
#include <ctime>
using namespace std;

class Lesson
{
public:
    wstring name;  // 使用宽字符形式存储课程名
    int marks;     // 分数
    int times;     // 学分权重
    double point;  // 绩点

    Lesson(wstring str, int a, double t)
    {
        marks = t;
        times = a;
        name = str;
        calculatePoint(t);
    }

    void calculatePoint(double marks)
    {
        // 分数	绩级	绩点	等级含义
        // 90～100	A  	4.0	优Excellent
        // 85～89	A- 	3.7
        // 82～84	B+	3.3	良Good
        // 78～81	B  	3.0
        // 75～77	B- 	2.7
        // 72～74	C+	2.3	中Satisfactory
        // 68～71	C  	2.0
        // 65～67	C- 	1.7
        // 62～64	D+	1.3	合格Passed
        // 60～61	D  	1.0
        // 0～59	F	0	不合格Failed
        if (marks >= 90 && marks <= 100)
            point = 4.0;
        else if (marks >= 85 && marks <= 89)
            point = 3.7;
        else if (marks >= 82 && marks <= 84)
            point = 3.3;
        else if (marks >= 78 && marks <= 81)
            point = 3.0;
        else if (marks >= 75 && marks <= 77)
            point = 2.7;
        else if (marks >= 72 && marks <= 74)
            point = 2.3;
        else if (marks >= 68 && marks <= 71)
            point = 2.0;
        else if (marks >= 65 && marks <= 67)
            point = 1.7;
        else if (marks >= 62 && marks <= 64)
            point = 1.3;
        else if (marks >= 60 && marks <= 61)
            point = 1.0;
        else if (marks >= 0 && marks <= 59)
            point = 0;
        else
        {
            // 处理异常情况，例如输入超出范围的分数
            wcout << L"Invalid input for marks!" << endl;
            // 在这里你可以选择抛出异常、设定默认值等处理方式
        }
        // return point;
    }

    void displayInfo(wchar_t ctrlChar) const
    {
        //格式化控制
        const int maxNameShownLength = 12;
        int notCNchars = 0;
        wcout << L"课程: ";
        for (int i = 0; i < maxNameShownLength; i++)
            if (i < name.length())
            {
                wcout << name[i];
                if (isalnum(name[i]) || ispunct(name[i]))
                    notCNchars += 1;
            }
            else
                wcout << L"  ";
        for (int i = 0; i < notCNchars; i++)
            wcout << L' ';
        wcout << L"  ";

        wcout << L"学分: " << times << L' ';
        wcout << L"成绩: " << marks << L' ';
        wcout << L"绩点: " << point << ctrlChar;
        // wcout << L"Course: " << name << endl;
        //  if (marks != -1)
        // wcout << L"Marks: " << marks << endl;
        // wcout << L"Grade Point: " << point << endl;
        //  wcout << L"----------------------" << endl;
    }
};

vector<Lesson> readCoursesFromFile(const string& filename)
{
    vector<Lesson> courses;
    wifstream file(filename);  // 将wstring转换为const wchar_t*
    file.imbue(locale("chs"));
    if (file.is_open())
    {
        wstring line;
        while (getline(file, line))
        {
            //wcout << line << endl;
            //wcout << L"测试:" << line << endl;

            //wcout << line << endl;
            //wcout << line[0] << endl;
            if (line.empty() || line[0] == L'#')
                continue;
            
            wistringstream iss(line);
            wstring courseName, temp;
            int times;
            double marks;

            // 读取课程信息
            iss >> temp;                    // 序号
            iss >> temp;                    // 课程号
            iss >> temp;                    // 课序号
            iss >> ws;                      // 跳过可能存在的空格(ws:去除流的前导空格)
            //iss.ignore();
            getline(iss, courseName, L'\t'); // 课程名
            iss >> ws;                      // 跳过可能存在的空格(ws:去除流的前导空格)
            getline(iss, temp, L'\t');      // 课程属性
            iss >> ws;                      // 跳过可能存在的空格
            iss >> times;                   // 学分
            iss >> marks;                   // 成绩
            //iss.ignore();

            courses.emplace_back(courseName, times, marks);
            //courses.push_back({courseName, times, marks});
        }

        file.close();
    }
    else
    {
        wcout << L"Unable to open file";
        //cout << filename << endl;
    }

    return courses;
}

int main()
{
    // 设置中文显示
    //wcout.imbue(locale("ch-ZN.utf-8"));
    wcout.imbue(locale("Chinese-simplified"));
    //wcout.imbue(locale("chs"));

    string filename = "courses.ini";

    vector<Lesson> courses = readCoursesFromFile(filename);

    ////test show
    //for (const auto& course : courses)
    //    course.displayInfo(L'\n');

    //计算GPA
    double GPsum = 0;//绩点和
    double times = 0;//权重和
    for (const auto& course : courses)
    {
        GPsum += course.point * course.times;
        times += course.times;
    }
    //wcout << L"test:" << GPsum << L' ' << times << endl;
    wcout << L"经过计算, 得到您的GPA为:\t" << GPsum / times << endl;


    // 显示读取到的课程信息 与课程对权重的影响
    for (const auto& course : courses)
    {
        course.displayInfo(L' ');
        wcout << L"\t本科对绩点的影响: ";
        double affect = GPsum / times - (GPsum - course.point * course.times) / (times - course.times);
        if (affect > 0) 
            wcout << L"+";
        wcout << affect << endl;
    }

    system("pause");
    return 0;
}
