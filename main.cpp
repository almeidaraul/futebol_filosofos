#include "util.hpp"
using namespace std;

int main(int argc, char **argv) {
	char **argv_c = (char **)malloc(argc*sizeof(char*));
	for (int i = 0; i < argc; ++i) {
		argv_c[i] = (char *)malloc(sizeof(argv[i]));//strdup(argv[i]);
		strcpy(argv_c[i], argv[i]);
	}
	campo_conecta(argc, argv);
	config c;
	while (c = read_move(), !c.over)
		c.play();
}
