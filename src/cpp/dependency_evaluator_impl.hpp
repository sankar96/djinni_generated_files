#pragma once
 
#include "dependency_evaluator.hpp"
 
namespace dependency_evaluator {
    
    class DependencyEvaluatorImpl : public dependency_evaluator::DependencyEvaluator {
        
    public:
        
        // Constructor
        DependencyEvaluatorImpl();
        
        std::vector<std::string> get_parsed_string(const std::string & expression);

        void evaluate_expression(const std::string & actualExpression, const std::vector<std::string> & expression, int32_t row, int32_t column, const std::string & currentCell);

        void store_cell_value_constant(const std::string & constant, int32_t row, int32_t column);

    	void store_cell_value_formula(const std::string & expression);

        void create_huge_memory();

        std::vector<UpdatedValues> return_updated_values(const std::string & expression, int32_t row, int32_t column, const std::string & source, int32_t fromActivity);

    };
    
}