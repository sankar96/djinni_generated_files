//
// Created by Sankaranarayanan G on 01/03/18.
//

#include "cell.hpp"
#include "updated_values.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <android/log.h>
#include <stack>
#include <algorithm>

static class SheetFunctions {
public:
    static void storeCellValue (const std::string& expression,
                                std::vector<std::vector<::dependency_evaluator::Cell>> (&cellValues),
                                int32_t row,
                                int32_t column) {
        cellValues[row][column].actualValue = expression;
    }

    static std::string evaluateExpression (const std::vector<std::string>& expression,
                                           int32_t row,
                                           int32_t column,
                                           std::vector<std::vector<::dependency_evaluator::Cell>> (&cellValues),
                                           std::string curr_cell,
                                           int32_t errorCode) {
        if (errorCode == -1)
            return "#CIRCULARREF";
        std::stack<std::string> operands;
        std::stack<std::string> operators;


        std::cout << "Current expression " << curr_cell << std::endl;

        for (auto it = expression.begin (); it != expression.end (); it++) {
            switch (checkType (*it)) {
                case 1: {
                    std::string temp = *it;
                    if (temp[0] == 'N' && temp[1] == 'U' && temp[2] == 'M')
                        operands.push (getOperandForAbsolute (*it));
                    else {
                        operands.push (getOperandForReference (*it, cellValues, curr_cell));
                        cellValues[row][column].precedents.push_back (*it);
                    }
                    break;
                }
                case 2:
                    while (!operators.empty () && calcPrecedence (*it) <= calcPrecedence (operators.top ())) {
                        performFunction (operands, operators, cellValues);
                    }
                    operators.push (*it);
                    break;
                default:
                    // Invalid
                    break;
            }
        }
        while (!operators.empty ())
            performFunction (operands, operators, cellValues);
        return operands.top ();
    }

    static int checkType (std::string token) {
        if (token == "+" || token == "\-" || token == "*" || token == "\/")
            return 2;
        return 1;
    }

    static int calcPrecedence (std::string oper) {
        if (oper == "+" || oper == "\-")
            return 1;
        if (oper == "*" || oper == "\/")
            return 2;
        return -1;
    }

    static void performFunction (std::stack<std::string>& operands,
                                 std::stack<std::string>& operators,
                                 std::vector<std::vector<::dependency_evaluator::Cell>> (&cellValues)) {
        std::string opr =
                (std::basic_string<char, std::char_traits<char>, std::allocator<char>> &&) operators.top ();
        operators.pop ();
        std::string operand1 =
                (std::basic_string<char, std::char_traits<char>, std::allocator<char>> &&) operands.top ();
        operands.pop ();
        std::string operand2 =
                (std::basic_string<char, std::char_traits<char>, std::allocator<char>> &&) operands.top ();
        operands.pop ();
        operands.push (performActualFunction (operand1, operand2, opr, cellValues));
    }

    static std::string
    performActualFunction (std::string op1,
                           std::string op2,
                           std::string opr,
                           std::vector<std::vector<::dependency_evaluator::Cell>> (&cellValues)) {
        int operand1 = getOperand (op1, cellValues);
        int operand2 = getOperand (op2, cellValues);
        int performedValue = 0;
        __android_log_print(ANDROID_LOG_DEBUG, "VALUESOPER", "%d %d %s", operand1, operand2, opr.c_str());
        if (opr == "+") {
            performedValue = operand2 + operand1;
        } else if (opr == "-") {
            performedValue = operand2 - operand1;
        } else if (opr == "*") {
            performedValue = operand2 * operand1;
        } else if (opr == "/") {
            performedValue = operand2 / operand1;
        }
        std::shared_ptr<std::string> val = convertIntToString (performedValue);
        std::string temp = "";
        for (int i = 0; i < val->length (); i++) {
            temp += (*val)[i];
        }
        return temp;
    }

    static int getOperand (std::string operand,
                           std::vector<std::vector<::dependency_evaluator::Cell>> (&cellValues)) {
        int returnValue = 0;
        //        if (operand[0] == 'C') {
        //            int column = operand[2] - 'A';
        //            int row = convertStringToInt (operand);
        //            returnValue = convertStringToInt(cellValues[row][column].actualValue);
        //            cellValues[row][column].dependents.push_back (operand);
        //            //Assign dependencies here
        //        }
        //        else if (operand[0] == 'N' && operand[1] == 'U' && operand[2] == 'M') {
        //            returnValue = convertStringToInt (operand);
        //        }

        int i = (int) (operand.length () - 1), ten = 1;
        while (i >= 0) {
            returnValue += (operand[i] - 48) * ten;
            i--;
            ten *= 10;
        }
        return returnValue;
    }


    static std::string getOperandForReference (std::string operand,
                                               std::vector<std::vector<::dependency_evaluator::Cell>> (&cellValues),
                                               std::string dep_Value) {
        int column;
        if (operand[2] >= 65 && operand[2] <= 90)
            column = operand[2] - 'A';
        else
            column = operand[2] - 'a';
        int row = convertStringToInt (operand);

        std::cout << "dep row " << row << " dep col " << column << dep_Value << "  " << operand << std::endl;
        std::string temp;
        if (dep_Value[0] == 'C' && dep_Value[1] == 'F') {
            temp = dep_Value;
        } else {
            temp = "CF";
            temp += dep_Value;
        }
        for (auto& it : cellValues[row][column].dependents) {
            if (temp == it) {
                return cellValues[row][column].actualValue;
            }
        }
        cellValues[row][column].dependents.push_back (temp);
        return cellValues[row][column].actualValue;
    }

    static std::string getOperandForAbsolute (std::string operand) {
        int i = (int) (operand.length () - 1), ten = 1, ans = 0;
        while (i >= 3) {
            ans += (operand[i] - 48) * ten;
            i--;
            ten *= 10;
        }

        std::string myString = "";
        std::string reversedString = "";
        while (ans) {
            myString += (ans % 10) + '0';
            ans /= 10;
        }
        for (int j = (int) (myString.length () - 1); j >= 0; j--) {
            reversedString += myString[j];
        }
        return reversedString;
    }

    static int convertStringToInt (std::string value) {
        int i = (int) (value.length () - 1), ten = 1, ans = 0;
        while (i >= 3) {
            ans += (value[i] - 48) * ten;
            i--;
            ten *= 10;
        }
        return ans;
    }

    static std::shared_ptr<std::string> convertIntToString (int value) {
        std::shared_ptr<std::string> myString = std::make_shared<std::string> ();
        std::shared_ptr<std::string> reversedString = std::make_shared<std::string> ();
        while (value) {
            *myString += (value % 10) + '0';
            value /= 10;
        }
        for (int i = (int) (myString->length () - 1); i >= 0; i--) {
            *reversedString += (*myString)[i];
        }
        return reversedString;
    }

    static std::vector<int>
    updateDependenciesAndReturnValues (std::string source,
                                       int32_t row,
                                       int32_t column,
                                       std::vector<std::vector<::dependency_evaluator::Cell>> (&cellValues),
                                       const std::string& sourceNode,
                                       int *errorCode) {
        std::unique_ptr<std::list<std::string>[]> string_list =
                std::make_unique<std::list<std::string>[]> (100);
        std::unique_ptr<std::list<int>[]> adjacency_list = std::make_unique<std::list<int>[]> (100);
        int currentRow = row, currentColumn = column;
        std::queue<std::string> nodes;
        std::string tempSrc = "CF";
        tempSrc += sourceNode;
        nodes.push (tempSrc);
        int index = 0;
        bool visited[22][6];
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 6; j++) {
                visited[i][j] = false;
            }
        }
        int indices[100];
        indices[index++] = getIndex (tempSrc);
        while (!nodes.empty ()) {

            std::string topNode =
                    (std::basic_string<char, std::char_traits<char>, std::allocator<char>> &&) nodes.front ();
            if (topNode[2] >= 65 && topNode[2] <= 90)
                currentColumn = topNode[2] - 'A';
            else
                currentColumn = topNode[2] - 'a';
            currentRow = convertStringToInt (topNode);
            visited[currentRow][currentColumn] = true;
            nodes.pop ();
            for (auto it = cellValues[currentRow][currentColumn].dependents.begin ();
                 it != cellValues[currentRow][currentColumn].dependents.end (); it++) {
                int tempColumn;
                std::cout << "Dep " << *it << std::endl;
                if ((*it)[2] >= 65 && (*it)[2] <= 90) {
                    tempColumn = (*it)[2] - 'A';
                } else
                    tempColumn = (*it)[2] - 'a';
                int tempRow = convertStringToInt (*it);
                std::cout << tempRow << "  " << tempColumn << std::endl;
                // __android_log_print(ANDROID_LOG_INFO, "TOPOLIST_INDEX", "%d %d", tempRow,
                // tempColumn);

                if (!visited[tempRow][tempColumn]) {
                    indices[index++] = getIndex(*it);
                    nodes.push(*it);
                    visited[tempRow][tempColumn] = true;
                }
                adjacency_list[getIndex (topNode)].push_back (getIndex (*it));


                //Alternate condition
/*
                    bool has = false;
                    for (int k = 0; k < index; k++)
                        if (indices[k] == getIndex (*it)) {
                            has = true;
                            break;
                        }
                    if (!has) {
                        indices[index++] = getIndex(*it);
                        nodes.push(*it);
                    }
                    adjacency_list[getIndex (topNode)].push_back (getIndex (*it));
                    visited[tempRow][tempColumn] = true;
                }



                else {
                    bool tmp = false;
                    for (auto &itr : adjacency_list[getIndex(*it)]) {
                        if (itr == getIndex(topNode)) {
                            tmp = true;
                            break;
                        }
                    }
                    if (tmp) {
                        __android_log_print(ANDROID_LOG_INFO, "CYCLIC_GRAPH", "%s", "CYCLE");
                        *errorCode = -1;
                    }
                    //return neg;
                }

                */
            }

        }

        for (int in = 0; in < index; in++)
            __android_log_print (ANDROID_LOG_DEBUG, "indices", "%d", indices[in]);
        if (checkingCyclicGraph (index, adjacency_list, indices)) {
            *errorCode = -1;
            __android_log_print (ANDROID_LOG_DEBUG, "hasCycle", "%d %d", row, column);
            std::string removeElt = "CF";
            removeElt += sourceNode;
            
            for (auto &it : cellValues[row][column].precedents) {
                int inc;
                if (it[2] >= 65 && it[2] <= 90)
                    inc = it[2] - 'A';
                else
                    inc = it[2] - 'a';
                int inr = SheetFunctions::convertStringToInt (it);
                cellValues[inr][inc].dependents.erase(std::remove (cellValues[inr][inc].dependents.begin(), cellValues[inr][inc].dependents.end(), removeElt), cellValues[inr][inc].dependents.end());
            }

            for (auto &it: cellValues[row][column].dependents) {
                int inc;
                if (it[2] >= 65 && it[2] <= 90)
                    inc = it[2] - 'A';
                else
                    inc = it[2] - 'a';
                int inr = SheetFunctions::convertStringToInt (it);
                cellValues[inr][inc].precedents.erase(std::remove (cellValues[inr][inc].precedents.begin(), cellValues[inr][inc].precedents.end(), removeElt), cellValues[inr][inc].precedents.end());
            }

            cellValues[row][column].precedents.clear();
            cellValues[row][column].dependents.clear();

        }
        return dependencySortDriver (adjacency_list, source, indices, index, errorCode);
    }

    static bool has (std::unique_ptr<std::list<int>[]> adjacency_list, int topNode, int childNode) {

    }

    static std::string getCellValue (int32_t row, int32_t col) {
    }
    static int getIndex (std::string cellRef) {
        int col;
        if (cellRef[2] >= 65 && cellRef[2] <= 90)
            col = cellRef[2] - 'A';
        else
            col = cellRef[2] - 'a';
        int row = convertStringToInt (cellRef);
        return ((row)*4) + col;
    }


    static std::vector<int> dependencySortDriver (std::unique_ptr<std::list<int>[]>& adjacency_list,
                                                  std::string source,
                                                  int indices[],
                                                  int index,
                                                    int *errorCode) {
        std::stack<int> Stack;
        std::vector<int> topoSortList;
        std::cout << "Index size " << index << std::endl;
        bool* visited = new bool[100];
        for (int i = 0; i < 100; i++)
            visited[i] = false;

        for (int i = 0; i < index; i++) {
            int ind = indices[i];
            if (!visited[ind])
                dependencySort (ind, adjacency_list, visited, Stack);
        }
        while (!Stack.empty ()) {
            topoSortList.push_back ((int&&)Stack.top ());
            Stack.pop ();
        }

        for (auto& it : topoSortList) {
            std::cout << "Topo elts " << it << std::endl;
        }
        return topoSortList;
    }

    static void dependencySort (int index,
                                std::unique_ptr<std::list<int>[]>& adjacency_list,
                                bool visited[],
                                std::stack<int>& stack) {
        visited[index] = true;
        for (auto it = adjacency_list[index].begin (); it != adjacency_list[index].end (); ++it)
            if (!visited[*it])
                dependencySort (*it, adjacency_list, visited, stack);
        stack.push (index);
    }

    static bool checkingCyclicGraph(int V, std::unique_ptr<std::list<int>[]> &adjacency_list, int indices[])  {
        bool *visited = new bool[V];
        bool *recStack = new bool[V];
        for(int i = 0; i < V; i++)  {
            visited[i] = false;
            recStack[i] = false;
        }
        for(int i = 0; i < V; i++)
            if (isCyclicGraphOrNot(indices[i], visited, recStack, adjacency_list))
                return true;

        return false;
    }

    static bool isCyclicGraphOrNot(int v, bool visited[], bool *recStack, std::unique_ptr<std::list<int>[]> &adjacency_list)
    {
        if(!visited[v])
        {
            visited[v] = true;
            recStack[v] = true;

            std::list<int>::iterator i;
            for(i = adjacency_list[v].begin(); i != adjacency_list[v].end(); ++i)
            {
                if ( !visited[*i] && isCyclicGraphOrNot(*i, visited, recStack, adjacency_list) )
                    return true;
                else if (recStack[*i])
                    return true;
            }

        }
        recStack[v] = false;
        return false;
    }
};
