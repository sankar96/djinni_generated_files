#include <iostream>
#include "WorkBook.hpp"


std::vector<string> getParsed () {
	std::string expression;
	std::cin >> expression;
	void *buffer = setUpBuffer(expression.c_str());
    int return_value;
    std::string ans = "";
    std::vector <std::string> parsedVector;
    while ((return_value = yylex()) != 0) {
        switch (return_value) {
            case 1: parsedVector.emplace_back("+"); break;

            case 2: parsedVector.emplace_back("-");break;

            case 3: parsedVector.emplace_back("*"); break;

            case 4: parsedVector.emplace_back("/"); break;

            case 5: {
                std::string temp = "CF";
                temp += yytext;
                parsedVector.emplace_back (temp);
                break;
            }

            case 6: {
                std::string temp = "NUM";
                temp += yytext;
                parsedVector.emplace_back(temp);
                break;
            }

            default:break;
        }
    } 
	for (auto &it: parsedVector) {
		std::cout << it << std::endl;
	}
	return parsedVector;
}

void evalExpr() {

	std::string expr;

	WorkBook *workBook = WorkBook::getInstance();
    if (workBook == nullptr)
        return;
    int k = row;
    int j = column;
    workBook -> evaluteExpression (getParsed(expression), row, column);
}

void storeCellValue() {
 	WorkBook *workBook = WorkBook::getInstance();
    workBook -> storeCellInformation(constant, row, column);
   	delete workBook;
}


void updatedvalues() {
	WorkBook *workBook = WorkBook::getInstance();
    std::vector <UpdatedValues> updatedValues;
    std::vector <std::unique_ptr<UpdatedValues>> temp = workBook -> evaluateDepsAndReturnUpdatedValues (expression, row, column, source);
    for (auto &it : temp) {
        updatedValues.push_back (*it);
    }
    delete workBook;
    for (auto &it : updatedValues) {
    	std::cout << it.row << it.column << std::endl;
    }
}

int main() {

	int input;

	while (1) {
		std::cin >> input;
		if (input == -1)
			break;
		switch (input) {
			case 1:
				getParsed();
				break;
			case 2:
				evalExpr();
				break;
			case 3:
				storeCellValue();
				break;
			case 4:
				updatedvalues();
				break;
			default:
				break;
		}
	}
	return 0;
}