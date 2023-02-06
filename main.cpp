#include<iostream>
#include "config.h"
#include "add.h"
#include "sub.h"
#include "BasicExcel.hpp"
using namespace YExcel;

void createExcel();

void createExcel()
{
    // 实例化对象
    BasicExcel e;
    // 加载文件
    e.Load("test1.xls");
    // 指向“Sheet1”工作薄的指针
    BasicExcelWorksheet *sheet1 = e.GetWorksheet("Sheet1");

    if(sheet1)
    {
        // 声明一个指向单元块的指针
        BasicExcelCell *cell;
        // 定义表格的表头内容列表
        const char *titleList[2] = {"压力","温度"};

        // sheet1->Cell(0,0)->SetString("han");

        // 向单元格添加表头
        for (size_t i = 0; i < 2; i++)
        {
            // 改变单元块指针的指向
            cell = sheet1->Cell(0,i+1);
            // 向单元格添加字符串内容
            cell->SetString(titleList[i]); 
        }

        // 向单元格添加列头
        for (size_t i = 0; i < 5; i++)
        {
            /* code */
            sheet1->Cell(i,0)->SetDouble(i+0.1);
        }
        
        // 向表格内添加元素
        double cont = 0.23;
        for (size_t i = 0; i < 2; i++)
        {
            /* code */
            for (size_t j = 0; j < 5; j++)
            {
                /* code */
                sheet1->Cell(j+1,i+1)->SetDouble(cont++);
            }
            
        }
    }
    e.SaveAs("test2.xls");

    // ofstream f("test.csv");
    // f.close();
    // e.SaveAs("test2.xls");
}

int main()
{
    // std::cout << "cmake nice"<<std::endl;
    // std::cout << PROJECT_VERSION_MAJOR<<std::endl;
    // #ifdef DATA
    //     std::cout << "date" << DATA <<std::endl;
    // #endif
    // std::cout << "1+2=" << add(1,2)<<std::endl;
    // std::cout << "2-1=" << sub(2,1)<<std::endl;

    
    createExcel();

    return 0;
}