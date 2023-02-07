# cmake

cmake是用于构建、测试和软件打包的跨平台工具



# 优势

1. 避免硬编码路径
2. 可在多台计算机上构建一个包
3. 可做持续集成
4. 支持不同操作系统
5. 支持多个编译器
6. 可使用IDE
7. 使用库
8. 描述程序的逻辑结构
9. 单元测试



# 持续集成

自动化（提交、发布、自动化测试），准确发现集成错误



# cmake工作原理

![image-20230206095728442](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302060957599.png)



# cmake安装

https://blog.csdn.net/u011231598/article/details/80338941



# 构建和运行

创建src源码文件和build编译文件

![image-20230206102032253](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061020300.png)

进入build目录下，指定版本编译src

```bash
cmake -G "MinGW Makefiles" ..\src
```

不指定版本默认为vs

```bash
cmake ..\src
```

构建:在当前目录下

```bash
cmake --build .
```

![image-20230206103356852](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061033894.png)



# 说明

- cmake命令不区分大小写，但是变量和参数区分
- 参数用空格或者分号隔开
- 使用```${VAR}```引用变量
- 引号可加可不加，如果有字符串就必须加



# 概念

- 目标文件（target）：可执行文件（add_eexecutable）、库文件（add_library）
- 命令（cmake-command）：下面要讲的函数
- 变量（cmake-variable）：以```CMake_```开头
- 属性（cmake-properties）：文件/文件夹都有各自的属性



# 命令

https://cmake.org/cmake/help/latest/

https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html



## project

设置项目名

```bash
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
		[VERSION <major>[.<minor>[].<patch>[.<tweak>]]])
		[LANGUAGES <language-name>...]
		
		
# 项目名会被存储在变量 PROJECT_NAME 和 CMAKE_PROJECT_NAME中
# PROJECT_SOURCE_DIR 等价于 <project-name>_SOURCE_DIR
# 可使用message函数输出
message(${PROJECT_NAME})
message(${PROJECT_SOURCE_DIR})
message(${demo_SOURCE_DIR})
```

![image-20230206104853988](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061048030.png)

![image-20230206105023098](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061050130.png)



## add_executable

```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
# <name>为可执行文件的名字，与项目名称无关
# win会生成<name>.exe文件

# 如：
add_executable(demo main.cpp)
```



## message

```cmake
message([<mode>] "message text" ...)
# 如：
message(STATUS "${PROJECT_VERSION_MAJOR}")
```





## set

设置变量

```cmake
set(<variable> <value>... [PARENT_SCOPE])

# 如：
set(a 1)
```

 

设置c++标准

```cmake
set(CMAKE_CXX_STANDARD 11)
```



设置输出目录

```cmake
# 设置exe文件出书目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置存档目标文件的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
```

![image-20230206110055402](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061100444.png)



## option

定义一个开关

```cmake
option(<variable> "<help_text>" [value])

# value的值为ON 或者 OFF，默认为OFF
# 如：
option(VERSION_ENABLE "output version" ON)
```



## configure_file

将输入文件进行替换并生成输出文件

```cmake
configure_file(<input> <output>
               [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
                FILE_PERMISSIONS <permissions>...]
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])

# 输入文件中的 @VAR@ 或 ${VAR} 的字符串会被替换成这些变量的当前值，未定义则是空字符串
```

config.h.in

```c
#define PROJECT_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define PROJECT_VERSION_MINOR @PROJECT_VERSION_MINOR@
```

编译后

config.h

```c
#define PROJECT_VERSION_MAJOR 1
#define PROJECT_VERSION_MINOR 0
```



```cmake
#cmakedefine VAR
// 会被替换成一下两者之一，取决于VAR是否被设置
#define VAR
#undef VAR
```

![image-20230206150448125](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061504200.png)

![image-20230206150402269](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061504341.png)



## include_directories

将给定的目录添加到编译器用于搜索包含文件的目录中。

```cmake
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])

# 目录会被添加到当前文件的 INCLUDE_DIRECTORIES 属性中
# 当前文件的每一个目标文件的INCLUDE_DIRECTORIES 属性也会添加该目录
```





## target_include_directories

将包含目录添加到目标。

```cmake
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

# 目标文件有 INCLUDE_DIRECTORIES 和 INTERFACE_INCLUDE_DIRECTORIES 两个属性
# INCLUDE_DIRECTORIES 对内头文件目录
# INTERFACE_INCLUDE_DIRECTORIES 对外头文件目录

# 包含src目录到目标
target_include_directories(demo PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(demo INTERFACE "${PROJECT_BINARY_DIR}")
target_include_directories(demo PUBLIC "${PROJECT_BINARY_DIR}")
```

|           | INCLUDE_DIRECTORIES | INTERFACE_INCLUDE_DIRECTORIES |
| :-------: | :-----------------: | :---------------------------: |
|  PRIVATE  |          √          |                               |
| INTERFACE |                     |               √               |
|  PUBLIC   |          √          |               √               |



这是再引入config.h就不会报错了

![image-20230206145529693](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061455747.png)



## target_link_libraries

```
target_link_libraries(<target> ... <item>... ...)
```



## add_library

使用指定的源文件将库添加到项目中。

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
 
```





# 创建子库

![image-20230206170906539](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061709588.png)

```cmake
# calc/CMakeLists.txt

# 使用指定的源文件将库添加到项目中。
add_library(addition STATIC add.cpp)
```



```cmake
# CMakeLists.txt

# 设置静态文件存放目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加子目录
add_subdirectory(calc)

# 链接静态文件
target_link_libraries(demo PUBLIC addition)

# 将包含目录到目标
target_include_directories(demo PUBLIC ${PROJECT_SOURCE_DIR}/calc)

# target_link_libraries 这条命令一定得在add_executable后面，不然找不到target（demo）
```



```c++
#include<iostream>
#include "add.h"

int main()
{
    std::cout << "1+2=" << add(1,2)<<std::endl;
    return 0;
}
```



# 使用外部静态库

libaddition.a为静态库

与src同级目录创建other_lib，将.a和.h文件放进去

```cmake
# 链接静态文件(要使用绝对路径)
target_link_libraries(demo PUBLIC D:/Desktop/demo/other_li/libaddition.a)
```



# 使用外部动态库

动态库一定.dll文件一定得与exe文件同目录下



# 实例：Excel

创建目录，包含操作excel的文件

![image-20230206184121292](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302061841342.png)

```cmake
# src/excel/CMakeLists.txt

# 使用指定的源文件将库添加到项目中。
add_library(excel STATIC BasicExcel.cpp)
```



```cmake
# 添加子目录
add_subdirectory(excel)
```



```cmake
# 链接静态文件
target_link_libraries(demo PUBLIC excel)
```



```cmake
# 将包含目录到目标
target_include_directories(demo PUBLIC
                            ${PROJECT_BINARY_DIR}
                            ${PROJECT_SOURCE_DIR}/excel
                            )
```



案例

```c++
//实例化一个表格对象
	BasicExcel e;
	//加载一个文件，
	e.Load("test1.xls");
	//指向"Sheet1"工作簿的指针
	BasicExcelWorksheet* sheet1 = e.GetWorksheet("Sheet1");
    double sum = 0;
	if (sheet1)
	{
		//当前excel的总行数
		size_t maxRows = sheet1->GetTotalRows();
		//当前excel的总列数
		size_t maxCols = sheet1->GetTotalCols();
		//输出当前工作表名称(char)，采用unicode编码，没有则返回0.
		cout << "Dimension of " << sheet1->GetAnsiSheetName() <<"(" <<maxRows << "," << maxCols << ")" << endl;
		//制表
		for (size_t c = 0; c < maxCols; ++c)
			printf("%10d", c + 1);
		cout << endl;
		/*
		要想得到EXCEL表格内的值，1、获取指向某行某列的指针类型为BasicExcelCell*
								 2、根据调用的成员函数Type(),查看单元格内的数据类型
								 3、根据数据类型的不同，选择不一样的获取数据的类函数
		*/
		for (size_t r = 0; r < maxRows; ++r)
		{
			printf("%d", r + 1);
			for (size_t c = 0; c < maxCols; ++c)
			{
				//返回指向excel单元格的指针，行如果超过65535或列超过255，则返回00.
				BasicExcelCell* cell = sheet1->Cell(r, c);
				//获取单元格指针内容的类型
				switch (cell->Type())
				{
					//undefined
					case BasicExcelCell::UNDEFINED:
						printf("          ");
						break;
					//int
					case BasicExcelCell::INT:
						printf("%10d", cell->GetInteger());		//获取值
						break;
					//double
					case BasicExcelCell::DOUBLE:
						printf("%10.6lf", cell->GetDouble());	//获取值
						break;
					//string
					case BasicExcelCell::STRING:
						printf("%10s", cell->GetString());		//获取值
						break;
					//wstrig
					case BasicExcelCell::WSTRING:
						wprintf(L"%10s", cell->GetWString());	//获取值
						break;
				}
			}
			std::cout << endl;
		}
		/*计算出第二列数据的总和，并替换单元格第二列最后一行的数据*/
		for (int i = 1; i < maxRows; ++i)
		{
			BasicExcelCell* cell = sheet1->Cell(i, 1);
			sum += cell->GetDouble();
		}
		BasicExcelCell* cell2 = sheet1->Cell(maxRows-1, 1);
		cell2->Set(sum);
		
	}
	std::cout << endl;
	
	//e.Save();
	//将修改的文件保存为"test2.xls"
	e.SaveAs("test2.xls");
	//创建新的工作簿，此时打开的文件中有两个excel工作簿，分别为Sheet1，Sheet2.
	e.New(2);
	//将ANSI编码格式的EXCEL工作表重命名为另一个ANSI名称，成功返回true，失败返回false
	e.RenameWorksheet("Sheet1", "city");
	e.RenameWorksheet("Sheet2", "weather");
	//创建类对象e的另一个工作簿
	BasicExcelWorksheet* sheet2 = e.GetWorksheet("city");

	if (sheet2)
	{
		//声明一个指向单元格块的指针
		BasicExcelCell* cell;
		//表格的表头
		const char *title[4] = { "china", "english", "american", "japan" };
		//向单元格添加表头
		for (size_t c = 0; c < 4; ++c)
		{
			cell = sheet2->Cell(0, c+1);
			cell->SetString(title[c]);
		}
		//向单元格添加列头
		for (size_t r = 1; r < 9; ++r)
			sheet2->Cell(r, 0)->Set((int)r);
		//向表格内添加元素
		double cont = 0.23;
		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < 8; ++j)
				sheet2->Cell( j + 1, i + 1)->SetDouble(cont++);
		}
	}
	e.SaveAs("text3.xls");
	
	e.Load("text3.xls");
	//得到当前文件内一共有多少工作簿
	size_t maxSheets = e.GetTotalWorkSheets();
	cout << "Total number of worksheets:" << e.GetTotalWorkSheets() << endl;
	//对工作簿进行遍历
	for (size_t i = 0; i < maxSheets; ++i)
	{
		//获取工作簿
		BasicExcelWorksheet* sheet = e.GetWorksheet(i);
		if (sheet)
		{
			//获取最大行列数
			size_t maxRows = sheet->GetTotalRows();
			size_t maxCols = sheet->GetTotalCols();
			cout << "Dimension of " << sheet->GetAnsiSheetName() << "(" << maxRows << "," << maxCols << ")" << endl;

			//列表
			if (maxRows > 0)
			{
				for (size_t c = 0; c < maxCols; ++c)
					printf("%10d", c );
				cout << endl;
			}
			//打印表格内容
			for (size_t r = 0; r < maxRows; ++r)
			{
				for (size_t c = 0; c < maxCols; ++c)
				{
					BasicExcelCell* cell = sheet->Cell(r, c);
					switch (cell->Type())
					{
							//undefined
						case BasicExcelCell::UNDEFINED:
							printf("          ");
							break;
							//int
						case BasicExcelCell::INT:
							printf("%10d", cell->GetInteger());		//获取值
							break;
							//double
						case BasicExcelCell::DOUBLE:
							printf("%10.6lf", cell->GetDouble());	//获取值
							break;
							//string
						case BasicExcelCell::STRING:
							printf("%10s", cell->GetString());		//获取值
							break;
							//wstrig
						case BasicExcelCell::WSTRING:
							wprintf(L"%10s", cell->GetWString());	//获取值
							break;
					}
				}
				cout << endl;
			}
			//将文件以csv格式保存
			if (i == 0)
			{
				ofstream f("text.csv");
				sheet->Print(f, ',', '\0');
				f.close();
			}
		}
		cout << endl;
	}
```



# 安装

## cmake代码

```cmake
install(TARGETS <target>DESTINATION <dir>)
install(FILES <file>DESTINATION <dir>)
insta11(PROGRAMS<非目标文件的可执行程序>DESTINATION<dir>)
#如脚本
insta11(DIRECTORY<dir>DESTINATION<dir>)#安装目录
```

实例

```cmake
install(TARGETS MathFunctions DESTINATION 1ib)
install(FILES MathFunctions.h DESTINATION include)
instal1(DIRECTORY doc/DESTINATION d)
```



## 命令行

```cmake
cmake --install.
#安装到默认目录
CMAKE_INSTALL_PREFIX
cmake --install.--prefix <dir>
#安装到指定目录
```



## 实例

```cmake
CMakeLists.txt
# 安装exe文件
install(TARGETS demo DESTINATION bin)
# 安装外部头文件
# 安装外部静态文件
# 安装外部动态文件

calc/CMakeListx.txt
# 使用指定的源文件将库添加到项目中。
add_library(addition STATIC add.cpp)
add_library(sub SHARED sub.cpp)

install(TARGETS addition DESTINATION lib)
install(FILES add.h DESTINATION include)
```



![image-20230206203723235](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302062037306.png)

![image-20230206203859289](https://test-123456-md-images.oss-cn-beijing.aliyuncs.com/img/202302062038349.png)





# clash使用git

设置代理

```bash
git config --global http.proxy 'socks5://127.0.0.1:7890'
git config --global https.proxy 'socks5://127.0.0.1:7890'
```

取消代理

```bash
git config --global --unset http.proxy
git config --global --unset https.proxy
```

