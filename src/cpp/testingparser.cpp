#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

extern int yylex();
extern int yylex_destroy(void);
extern char *yytext;
extern void *setUpBuffer(char const *);
extern void tearDownBuffer(void *buffer);

int main () {
	std::string testingText = "A1+A2";
	void *buffer = setUpBuffer(testingText.c_str());
	int return_value;
	while ((return_value = yylex()) != 0) {
		std:: cout << return_value;
	}
	return 0;
}
