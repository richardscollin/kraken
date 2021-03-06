#ifndef ASTDATA_H
#define ASTDATA_H

#include <vector>
#include <map>
#include <set>

#include "Symbol.h"
//Circular dependency
class Type;
#include "Type.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

enum ASTType {undef, translation_unit, import, identifier, type_def, adt_def,
	function, code_block, typed_parameter, expression, boolean_expression, statement,
	if_statement, match_statement, case_statement, while_loop, for_loop, return_statement, break_statement,
    continue_statement, defer_statement, assignment_statement, declaration_statement, if_comp, simple_passthrough,
    passthrough_params, in_passthrough_params, out_passthrough_params, opt_string, param_assign, function_call, value};

class ASTData {
	public:
		ASTData();
		ASTData(ASTType type, Type *valueType = NULL);
		ASTData(ASTType type, Symbol symbol, Type *valueType = NULL);
		~ASTData();
		std::string toString();
		static std::string ASTTypeToString(ASTType type);

		ASTType type;
		Type* valueType;
		Symbol symbol;
		std::map<std::string, std::vector<NodeTree<ASTData>*>> scope;
        std::set<NodeTree<ASTData>*> closedVariables;
	private:

};

#endif
