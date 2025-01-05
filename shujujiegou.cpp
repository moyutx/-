#include <iostream>
#include <windows.h> // 用于设置控制台编码
#include <limits>    // 用于处理输入错误

using namespace std;

// 定义多项式结构体
struct polynomial
{
  int coefarray[100]; // 系数数组，用于存储多项式的系数
  int highpower;      // 最高次项指数，表示多项式的最高次数
};

// 初始化多项式，将所有系数设置为0，最高次项指数设置为0
void initialize(polynomial *L)
{
  for (int i = 0; i < 100; i++)
  {
    L->coefarray[i] = 0; // 将系数数组中的每个元素初始化为0
  }
  L->highpower = 0; // 将最高次项指数初始化为0
}

// 创建多项式，输入最高次项指数和各项系数
void creatlist(polynomial *L)
{
  cout << "请输入多项式的最高次项指数：";
  while (!(cin >> L->highpower)) // 循环读取输入，直到输入一个有效的整数
  {
    cout << "输入无效，请输入一个整数：";
    cin.clear();                                         // 清除输入流的错误状态
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入后的所有字符，直到遇到换行符
  }

  for (int i = L->highpower; i >= 0; i--) // 从最高次项到常数项依次输入系数
  {
    cout << "请输入x^" << i << "的系数：";
    while (!(cin >> L->coefarray[i])) // 循环读取输入，直到输入一个有效的整数
    {
      cout << "输入无效，请输入一个整数：";
      cin.clear();                                         // 清除输入流的错误状态
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入后的所有字符，直到遇到换行符
    }
  }
}

// 打印多项式
void printout(polynomial *L)
{
  bool isZero = true;                     // 标记多项式是否为零多项式
  for (int i = L->highpower; i >= 0; i--) // 从最高次项到常数项依次输出
  {
    if (L->coefarray[i] != 0) // 如果系数不为0，则输出该项
    {
      isZero = false;        // 标记多项式不是零多项式
      if (i != L->highpower) // 如果不是最高次项，则输出加号
      {
        cout << " + ";
      }
      cout << L->coefarray[i]; // 输出系数
      if (i > 0)               // 如果次数大于0，则输出变量和指数
      {
        cout << "x^" << i;
      }
    }
  }
  if (isZero) // 如果是零多项式，则输出0
  {
    cout << "0";
  }
  cout << endl;
}

// 打印余数多项式（与打印多项式逻辑相同，单独定义函数以便调用）
void printout_remainder(polynomial *L)
{
  bool isZero = true;                     // 标记多项式是否为零多项式
  for (int i = L->highpower; i >= 0; i--) // 从最高次项到常数项依次输出
  {
    if (L->coefarray[i] != 0) // 如果系数不为0，则输出该项
    {
      isZero = false;        // 标记多项式不是零多项式
      if (i != L->highpower) // 如果不是最高次项，则输出加号
      {
        cout << " + ";
      }
      cout << L->coefarray[i]; // 输出系数
      if (i > 0)               // 如果次数大于0，则输出变量和指数
      {
        cout << "x^" << i;
      }
    }
  }
  if (isZero) // 如果是零多项式，则输出0
  {
    cout << "0";
  }
  cout << endl;
}

// 多项式相加
void add_polynomial(polynomial *L1, polynomial *L2, polynomial *L3)
{
  L3->highpower = max(L1->highpower, L2->highpower); // 结果多项式的最高次项指数为两个多项式中较高的那个
  for (int i = 0; i <= L3->highpower; i++)           // 从常数项到最高次项依次相加
  {
    L3->coefarray[i] = L1->coefarray[i] + L2->coefarray[i]; // 对应次数的系数相加
  }
}

// 多项式相减
void subtruct_polynomial(polynomial *L1, polynomial *L2, polynomial *L3)
{
  initialize(L3);                                    // 初始化结果多项式
  L3->highpower = max(L1->highpower, L2->highpower); // 结果多项式的最高次项指数为两个多项式中较高的那个

  bool isZero = true;                      // 标记结果多项式是否为零多项式
  for (int i = 0; i <= L3->highpower; i++) // 从常数项到最高次项依次相减
  {
    L3->coefarray[i] = L1->coefarray[i] - L2->coefarray[i]; // 对应次数的系数相减
    if (L3->coefarray[i] != 0)                              // 如果结果多项式中有非零系数，则标记为非零多项式
    {
      isZero = false;
    }
  }

  if (isZero) // 如果结果多项式是零多项式，则最高次项指数为0
  {
    L3->highpower = 0;
  }
}

// 多项式相乘
void multiply_polynomial(polynomial *L1, polynomial *L2, polynomial *L3)
{
  initialize(L3);                                // 初始化结果多项式
  L3->highpower = L1->highpower + L2->highpower; // 结果多项式的最高次项指数为两个多项式最高次项指数之和

  for (int i = 0; i <= L1->highpower; i++) // 遍历第一个多项式的每一项
  {
    for (int j = 0; j <= L2->highpower; j++) // 遍历第二个多项式的每一项
    {
      L3->coefarray[i + j] += L1->coefarray[i] * L2->coefarray[j]; // 将两个多项式中对应项的乘积累加到结果多项式中
    }
  }
}

// 多项式相除
void divide_polynomial(polynomial *L1, polynomial *L2, polynomial *L3, polynomial *remainder)
{
  if (L2->highpower == 0 && L2->coefarray[0] == 0) // 如果除数为0，则输出错误信息
  {
    cout << "除数不能为0！" << endl;
    return;
  }

  initialize(L3);        // 初始化商多项式
  initialize(remainder); // 初始化余数多项式

  bool isEqual = (L1->highpower == L2->highpower);    // 判断被除数和除数的最高次项是否相等
  for (int i = 0; i <= L1->highpower && isEqual; i++) // 如果相等，则检查每一项的系数是否相等
  {
    if (L1->coefarray[i] != L2->coefarray[i])
    {
      isEqual = false;
    }
  }

  if (isEqual) // 如果被除数和除数相等，则商为1，余数为0
  {
    L3->coefarray[0] = 1;
    L3->highpower = 0;
    remainder->highpower = 0;
    return;
  }

  for (int i = 0; i <= L1->highpower; i++) // 将被除数的系数复制到余数多项式中
  {
    remainder->coefarray[i] = L1->coefarray[i];
  }
  remainder->highpower = L1->highpower; // 设置余数多项式的最高次项指数

  for (int i = L1->highpower; i >= L2->highpower; i--) // 从最高次项开始进行除法运算
  {
    if (remainder->coefarray[i] == 0) // 如果余数多项式的当前项系数为0，则跳过
      continue;

    int quotient = remainder->coefarray[i] / L2->coefarray[L2->highpower]; // 计算商的当前项系数
    L3->coefarray[i - L2->highpower] = quotient;                           // 将商的当前项系数存储到商多项式中

    for (int j = 0; j <= L2->highpower; j++) // 遍历除数多项式的每一项
    {
      int index = i - L2->highpower + j;                          // 计算余数多项式中需要更新的项的索引
      remainder->coefarray[index] -= quotient * L2->coefarray[j]; // 更新余数多项式的系数
    }
  }

  // 更新商多项式的最高次项指数
  for (int i = L3->highpower; i >= 0; i--)
  {
    if (L3->coefarray[i] != 0) // 如果找到非零系数，则更新最高次项指数
    {
      L3->highpower = i;
      break;
    }
  }

  // 更新余数多项式的最高次项指数
  bool isZero = true; // 标记余数多项式是否为零多项式
  for (int i = remainder->highpower; i >= 0; i--)
  {
    if (remainder->coefarray[i] != 0) // 如果找到非零系数，则更新最高次项指数
    {
      remainder->highpower = i;
      isZero = false;
      break;
    }
  }
  if (isZero) // 如果余数多项式是零多项式，则最高次项指数为0
  {
    remainder->highpower = 0;
  }
}

// 显示菜单
void display()
{
  cout << "1. 创建多项式" << endl;
  cout << "2. 多项式相加" << endl;
  cout << "3. 多项式相减" << endl;
  cout << "4. 多项式相乘" << endl;
  cout << "5. 多项式相除" << endl;
  cout << "6. 退出" << endl;
}

int main()
{
  // 设置控制台输出编码为 UTF-8
  SetConsoleOutputCP(CP_UTF8);

  polynomial L1, L2, L3, L_remainder; // 定义四个多项式变量
  int n;                              // 用于存储用户选择的操作
  bool isCreated = false;             // 标记是否已创建多项式
  display();                          // 调用菜单函数
  while (true)
  {
    cout << "请输入要执行的操作：";
    while (!(cin >> n)) // 循环读取输入，直到输入一个有效的整数
    {
      cout << "输入无效，请输入一个整数：";
      cin.clear();                                         // 清除输入流的错误状态
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入后的所有字符，直到遇到换行符
    }

    if (n != 1 && !isCreated) // 如果用户未选择创建多项式且多项式尚未创建，则提示用户先创建多项式
    {
      cout << "请先使用功能1创建两个多项式。" << endl;
      continue;
    }

    switch (n) // 根据用户选择的操作执行相应的函数
    {
    case 1:
      creatlist(&L1); // 调用创建多项式函数创建第一个多项式
      cout << "第一个多项式为：";
      printout(&L1); // 打印第一个多项式
      cout << endl;
      creatlist(&L2); // 调用创建多项式函数创建第二个多项式
      cout << "第二个多项式为：";
      printout(&L2); // 打印第二个多项式
      cout << endl;
      isCreated = true; // 设置标记为已创建
      break;
    case 2:
      initialize(&L3);               // 初始化结果多项式
      add_polynomial(&L1, &L2, &L3); // 调用加法函数计算两个多项式的和
      cout << "相加后结果为：" << endl;
      printout(&L3); // 打印结果多项式
      cout << endl;
      break;
    case 3:
      initialize(&L3);                    // 初始化结果多项式
      subtruct_polynomial(&L1, &L2, &L3); // 调用减法函数计算两个多项式的差
      cout << "相减后结果为：" << endl;
      printout(&L3); // 打印结果多项式
      cout << endl;
      break;
    case 4:
      initialize(&L3);                    // 初始化结果多项式
      multiply_polynomial(&L1, &L2, &L3); // 调用乘法函数计算两个多项式的积
      cout << "相乘后结果为：" << endl;
      printout(&L3); // 打印结果多项式
      cout << endl;
      break;
    case 5:
      initialize(&L3);                                // 初始化商多项式
      initialize(&L_remainder);                       // 初始化余数多项式
      divide_polynomial(&L1, &L2, &L3, &L_remainder); // 调用除法函数计算两个多项式的商和余数
      cout << "商为：" << endl;
      printout(&L3); // 打印商多项式
      cout << "\n余数为：" << endl;
      printout_remainder(&L_remainder); // 打印余数多项式
      cout << endl;
      break;
    case 6:
      return 0; // 退出程序
    default:
      cout << "无效的操作，请重新输入。" << endl; // 提示用户输入无效操作
      break;
    }
  }
}