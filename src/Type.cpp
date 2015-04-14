#include "Type.h"

Type::Type() {
	indirection = 0;
	baseType = none;
	typeDefinition = NULL;
	templateDefinition = NULL;
}

Type::Type(ValueType typeIn, int indirectionIn) {
	indirection = indirectionIn;
	baseType = typeIn;
	typeDefinition = NULL;
	templateDefinition = NULL;
}

Type::Type(ValueType typeIn, std::set<std::string> traitsIn) {
	indirection = 0;
	baseType = typeIn;
    traits = traitsIn;
	typeDefinition = NULL;
	templateDefinition = NULL;
}

Type::Type(NodeTree<ASTData>* typeDefinitionIn, int indirectionIn) {
	indirection = indirectionIn;
	baseType = none;
	typeDefinition = typeDefinitionIn;
	templateDefinition = NULL;
}

Type::Type(NodeTree<ASTData>* typeDefinitionIn, std::set<std::string> traitsIn) {
	indirection = 0;
	baseType = none;
	typeDefinition = typeDefinitionIn;
    traits = traitsIn;
	templateDefinition = NULL;
}

Type::Type(ValueType typeIn, NodeTree<ASTData>* typeDefinitionIn, int indirectionIn, std::set<std::string> traitsIn) {
	baseType = typeIn;
	indirection = indirectionIn;
	typeDefinition = typeDefinitionIn;
    traits = traitsIn;
    templateDefinition = NULL;
}

Type::Type(ValueType typeIn, NodeTree<Symbol>* templateDefinitionIn, std::set<std::string> traitsIn) {
	indirection = 0;
	baseType = typeIn;
	typeDefinition = NULL;
	templateDefinition = templateDefinitionIn;
    traits = traitsIn;
}


Type::~Type() {
}

const bool Type::operator==(const Type &other) const {
	return( baseType == other.baseType && indirection == other.indirection && typeDefinition == other.typeDefinition && templateDefinition == other.templateDefinition && other.traits == traits);
}

const bool Type::operator!=(const Type &other) const {
	return(!this->operator==(other));
}

std::string Type::toString(bool showTraits) {
	std::string typeString;
	switch (baseType) {
		case none:
			if (typeDefinition)
				typeString = typeDefinition->getDataRef()->symbol.getName();
			else
				typeString = "none";
			break;
		case template_type:
			typeString = "template: " + templateDefinition->getDataRef()->toString();
			break;
		case template_type_type:
			typeString = "template_type_type";
			break;
		case void_type:
			typeString = "void";
			break;
		case boolean:
			typeString = "bool";
			break;
		case integer:
			typeString = "int";
			break;
		case floating:
			typeString = "float";
			break;
		case double_percision:
			typeString = "double";
			break;
		case character:
			typeString = "char";
			break;
		default:
			if (typeDefinition)
				typeString = typeDefinition->getDataRef()->symbol.getName();
			else
				typeString = "unknown_type";
	}
	for (int i = 0; i < indirection; i++)
		typeString += "*";
    if (traits.size() && showTraits) {
        typeString += "[ ";
        for (auto i : traits)
            typeString += i + " ";
        typeString += "]";
    }
	//std::cout << "Extra components of " << typeString << " are " << indirection << " " << typeDefinition << " " << templateDefinition << std::endl;
	return typeString;
}

Type* Type::clone() {
	return new Type(baseType, typeDefinition, indirection, traits);
}

int Type::getIndirection() {
	return indirection;
}

void Type::setIndirection(int indirectionIn) {
	indirection = indirectionIn;
}

void Type::increaseIndirection() {
	setIndirection(indirection+1);
}
void Type::decreaseIndirection() {
	setIndirection(indirection-1);
}

void Type::modifyIndirection(int mod) {
	setIndirection(indirection + mod);
}