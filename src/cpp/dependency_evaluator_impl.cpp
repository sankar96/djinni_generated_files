#include "dependency_evaluator_impl.hpp"
#include "WorkBook.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "my_record.hpp"


extern int yylex();
extern int yylex_destroy(void);
extern char *yytext;
extern void *setUpBuffer(char const *);
extern void tearDownBuffer(void *buffer);


namespace dependency_evaluator {
    
    std::shared_ptr<DependencyEvaluator> DependencyEvaluator::create() {
        return std::make_shared<DependencyEvaluatorImpl>();
    }
    
    DependencyEvaluatorImpl::DependencyEvaluatorImpl() {
 
    }
    
    std::vector<std::string> DependencyEvaluatorImpl::get_parsed_string(const std::string & expression) {
        
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
        return parsedVector;
    }

    void DependencyEvaluatorImpl::evaluate_expression (const std::string & actualExpression, const std::vector<std::string> & expression, int32_t row, int32_t column, const std::string & currentCell) {

        WorkBook *workBook = WorkBook::getInstance();
        if (workBook == nullptr)
            return;
        workBook -> evaluteExpression (expression, row, column, currentCell, actualExpression, 1);
        //delete  workBook;
    }

    void  DependencyEvaluatorImpl::store_cell_value_constant(const std::string & constant, int32_t row, int32_t column) {
        WorkBook *workBook = WorkBook::getInstance();
        workBook -> storeCellInformation(constant, row, column);
        //delete workBook;
    }

    void DependencyEvaluatorImpl::store_cell_value_formula(const std::string & expression) {

    }

    void DependencyEvaluatorImpl::create_huge_memory() {
        //std::unique_ptr< MyRecord> ptr = std::make_unique <MyRecord> ();
        //ptr = new MyRecord(1,2)
        //MyRecord myRecord[1000000];// = new MyRecord[1000000000];
    }
    std::vector<UpdatedValues> DependencyEvaluatorImpl::return_updated_values(const std::string & expression, int32_t row, int32_t column, const std::string & source, int32_t fromActivity) {
        WorkBook *workBook = WorkBook::getInstance();
        std::vector <UpdatedValues> updatedValues;
        updatedValues = workBook -> evaluateDepsAndReturnUpdatedValues (expression, row, column, source);
//        for (auto &it : temp) {
//            updatedValues.push_back (*it);
//        }
        //delete workBook;
        return updatedValues;
    }

}