//
// Created by Sankaranarayanan G on 28/02/18.
//

#include "SheetFunctions.hpp"
#include <iostream>
#include <vector>
#define ROW_MAX 22
#define COL_MAX 6
#include <android/log.h>
#include <algorithm>
#include "cell.hpp"
// #include "android/log.h"
// #include <android/log.h>


std::vector<std::vector<::dependency_evaluator::Cell>>
        cell_values (ROW_MAX, std::vector<::dependency_evaluator::Cell> (COL_MAX));
class WorkBook {
public:
    static WorkBook* instance;

    //    static inline std::vector <std::vector<::dependency_evaluator::Cell>> cell_values ;


    WorkBook () {
    }

public:
    static WorkBook* getInstance ();

    static void storeCellInformation (std::string, int32_t, int32_t);

    static void evaluteExpression (std::vector<std::string>, int32_t, int32_t, std::string, std::string, int32_t);

    static std::vector<::dependency_evaluator::UpdatedValues>
    evaluateDepsAndReturnUpdatedValues (std::string source, int32_t row, int32_t column, const std::string&);

    static void SetSize (std::vector<std::vector<::dependency_evaluator::Cell>>::size_type n) {
        cell_values.resize (n);
    }

    static void justPrint ();
};


WorkBook* WorkBook::instance = nullptr;

WorkBook* WorkBook::getInstance () {
    if (instance == nullptr) {
        instance = new WorkBook ();
    }
    return instance;
}

void WorkBook::storeCellInformation (std::string cellValue, int32_t row, int32_t column) {
    SheetFunctions::storeCellValue (cellValue, cell_values, row, column);
}

void WorkBook::evaluteExpression (const std::vector<std::string> expression, int32_t row, int32_t column, std::string curr_cell, std::string actualFormula, int32_t errorCode) {

    cell_values[row][column].expressionTokens = expression;
    cell_values[row][column].formulaValue = actualFormula;

    // Clearing the dependencies
    std::string removeElt = "CF";
    removeElt += curr_cell;

    for (auto &it : cell_values[row][column].precedents) {
        int inc;
        if (it[2] >= 65 && it[2] <= 90)
            inc = it[2] - 'A';
        else
            inc = it[2] - 'a';
        int inr = SheetFunctions::convertStringToInt (it);

        cell_values[inr][inc].dependents.erase (std::remove (cell_values[inr][inc].dependents.begin(), cell_values[inr][inc].dependents.end(), removeElt), cell_values[inr][inc].dependents.end());
    }

    SheetFunctions::storeCellValue (SheetFunctions::evaluateExpression (expression, row, column,
                                                                        cell_values, curr_cell, errorCode),
                                    cell_values, row, column);

    // __android_log_print (ANDROID_LOG_INFO, "TRACKERSTITLE", "TITLE");

}

void WorkBook::justPrint () {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 4; j++) {
            if (cell_values[i][j].actualValue.length () == 0) {
                std::cout << "0 ";
            } else
                std::cout << cell_values[i][j].actualValue << " ";
        }
        std::cout << std::endl;
    }
}

std::string getRow (int r) {
    std::string temp = "";
    while (r) {
        int rem = r % 10;
        temp += rem + '0';
        r = r / 10;
    }
    std::string finalString = "";
    int i = 0;
    int j = (int) (temp.length () - 1);
    while (j >= 0) {
        finalString += temp[j];
        j--;
    }
    return finalString;
}

std::string getSourceNode (int val) {
    int col = val % 4;
    int row = val / 4;
    std::string temp = "CF";
    temp += (col + 'A');
    temp += getRow (row);
    std::cout << "Src " << temp << std::endl;
    return temp;
}

std::vector<::dependency_evaluator::UpdatedValues>
WorkBook::evaluateDepsAndReturnUpdatedValues (std::string source, int32_t row, int32_t column, const std::string& sourceNode) {
    int errorCode = 1;
    std::vector<int> topoList =
            SheetFunctions::updateDependenciesAndReturnValues (source, row, column, cell_values, sourceNode, &errorCode);
    std::unique_ptr<std::list<std::string>[]> string_list = std::make_unique<std::list<std::string>[]> (100);
    std::vector<::dependency_evaluator::UpdatedValues> finalVector;

    if (errorCode == -1) {
        ::dependency_evaluator::UpdatedValues *uv = new ::dependency_evaluator::UpdatedValues(
                row,
                column,
                "#CIRCULARREF",
                "#CIRCULARREF"
        );
        finalVector.push_back (*uv);
        return finalVector;
    }
    std::vector<std::unique_ptr<::dependency_evaluator::UpdatedValues>> updatedValues;
    bool calculateFlag = false;
    std::string tempSrc = "CF";
    tempSrc += sourceNode;
    for (auto& it : topoList) {

         __android_log_print (ANDROID_LOG_INFO, "TOPOLIST", "CHECKING %d %d", it,
                              SheetFunctions::getIndex (tempSrc));

        int curRow = it / 4;
        int curCol = it % 4;

        __android_log_print (ANDROID_LOG_INFO, "TOPOLIST", "CHECKING %d %d %s %s", curRow, curCol, getSourceNode (it).c_str(), cell_values[curRow][curCol].formulaValue.c_str());

        evaluteExpression (cell_values[curRow][curCol].expressionTokens, curRow, curCol, getSourceNode (it), cell_values[curRow][curCol].formulaValue, errorCode);
        std::unique_ptr<::dependency_evaluator::UpdatedValues> updatedNode =
                std::make_unique<::dependency_evaluator::UpdatedValues> (curRow, curCol,
                                                                         cell_values[curRow][curCol].actualValue,
                                                                         cell_values[curRow][curCol].formulaValue);
        updatedValues.push_back (std::move (updatedNode));
    }


    for (auto &it : updatedValues) {
        finalVector.push_back (*it);
    }
    return finalVector;
}
