#include <iostream>
#include <tuple>

using namespace std;

namespace {

tuple<string, string> MESSAGES[] = {
    // Lexer errors
    {"UnicodePointTooLarge", "invalid Unicode codepoint (too large)"},
    {"InvalidEscape", "invalid escape character syntax"},
    {"IncompleteEscape", "incomplete character syntax"},
    {"InvalidHexEscape", "invalid hex escape"},
    {"InvalidUnicodeEscape", "invalid Unicode escape"},
    {"UnterminatedUnicode", "unterminated Unicode escape"},
    {"EscapeEof", "escape sequence meets end of file"},
    {"StringEof", "unterminated string meets end of file"},
    {"RegexpOptions", "unknown regexp options: {}"},
    {"CvarName", "`{}` is not allowed as a class variable name"},
    {"IvarName", "`{}` is not allowed as an instance variable name"},
    {"TrailingInNumber", "trailing `{}` in number"},
    {"EmptyNumeric", "numeric literal without digits"},
    {"InvalidOctal", "invalid octal digit"},
    {"NoDotDigitLiteral", "no .<digit> floating literal anymore; put 0 before dot"},
    {"BareBackslash", "bare backslash only allowed before newline"},
    {"Unexpected", "unexpected `{}`"},
    {"EmbeddedDocument", "embedded document meets end of file (and they embark on a romantic journey)"},

    // Lexer warnings
    {"InvalidEscapeUse", "invalid character syntax; use ?{}"},
    {"AmbiguousLiteral", "ambiguous first argument; put parentheses or a space even after the operator"},
    {"AmbiguousPrefix", "`{}` interpreted as argument prefix"},

    // Parser errors
    {"NthRefAlias", "cannot define an alias for a back-reference variable"},
    {"BeginInMethod", "BEGIN in method"},
    {"BackrefAssignment", "cannot assign to a back-reference variable"},
    {"InvalidAssignment", "cannot assign to a keyword"},
    {"ModuleNameConst", "class or module name must be a constant literal"},
    {"UnexpectedToken", "unexpected token {}"},
    {"ArgumentConst", "formal argument cannot be a constant"},
    {"ArgumentIvar", "formal argument cannot be an instance variable"},
    {"ArgumentGvar", "formal argument cannot be a global variable"},
    {"ArgumentCvar", "formal argument cannot be a class variable"},
    {"DuplicateArgument", "duplicate argument name {}"},
    {"EmptySymbol", "empty symbol literal"},
    {"EndlessSetter", "setter method cannot be defined in an endless method definition"},
    {"OddHash", "odd number of entries for a hash"},
    {"SingletonLiteral", "cannot define a singleton method for a literal"},
    {"DynamicConst", "dynamic constant assignment"},
    {"ConstReassignment", "constant re-assignment"},
    {"ModuleInDef", "module definition in method body"},
    {"ClassInDef", "class definition in method body"},
    {"UnexpectedPercentStr", "{}: unknown type of percent-literal"},
    {"BlockAndBlockarg", "both block argument and literal block are passed"},
    {"MasgnAsCondition", "multiple assignment in conditional context"},
    {"BlockGivenToYield", "block given to yield"},
    {"InvalidRegexp", "{}"},
    {"InvalidReturn", "invalid return in class/module body"},
    {"CSendInLHSOfMAsgn", "&. inside multiple assignment destination"},
    {"OrdinaryParamDefined", "can't use numbered params when ordinary params were also defined"},
    {"NumparamUsedInOuterScope", "numbered parameter is already used in an outer scope"},
    {"CircularArgumentReference", "circular argument reference {}"},
    {"PatternInterpInVarName", "symbol literal with interpolation is not allowed"},
    {"PatternLVarName", "{} is not allowed as a local variable name"},
    {"PatternLVarUndefined", "no such local variable: {}"},
    {"PatternDuplicateVariable", "duplicate variable name {}"},
    {"PatternDuplicateKey", "duplicate hash pattern key {}"},

    // Parser warnings
    {"UselessElse", "else without rescue is useless"},

    // Parser errors that are not Ruby errors
    {"InvalidEncoding", "literal contains escape sequences incompatible with UTF-8"},

    // Rewriter diagnostics
    {"InvalidAction", "cannot {}"},
    {"Clobbered", "clobbered by: {}"},

    // TypedRuby diagnostics
    {"NotStaticCpathInGeninst", "type name in generic instance must be a static constant path"},
};

void generateDclass() {
    cout << "// This file is autogenerated by generate_diagnostics.cc\n";
    cout << "#ifndef RUBY_PARSER_DIAGNOSTICS\n";
    cout << "#define RUBY_PARSER_DIAGNOSTICS\n";
    cout << "namespace ruby_parser {\n";
    cout << "// DO NOT MODIFY\n";
    cout << "enum class dclass {\n";
    for (auto [err, _msg] : MESSAGES) {
        cout << "    " << err << ",\n";
    }
    cout << "};\n";
    cout << "}\n";
    cout << "#endif\n";
}

void generateDclassStrings() {
    cout << "namespace sorbet {\n";
    cout << "namespace parser {\n";
    cout << "const char * dclassStrings[] = {\n";
    for (auto [_err, msg] : MESSAGES) {
        cout << "    \"" << msg << "\",\n";
    }
    cout << "};\n";
    cout << "}\n";
    cout << "}\n";
}

} // namespace

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: {} (dclass|dclassStrings)\n", (string)argv[0];
        return 1;
    }

    if ((string)argv[1] == "dclass") {
        generateDclass();
    } else if ((string)argv[1] == "dclassStrings") {
        generateDclassStrings();
    } else {
        cout << "Usage: {} (dclass|dclassStrings)\n", (string)argv[0];
        return 1;
    }
    return 0;
}
