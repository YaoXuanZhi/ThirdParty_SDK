#include "yaml.h"
#include <fstream>
#include <iostream>

#if (_MSC_VER <= 1300)
#error "yaml-cpp并不支持VC 6.0编译哦"
#endif

int main(int argc, char **argv)
{
	std::ifstream fin;
	if(argc > 1)
		fin.open(argv[1]);
	
	std::istream& input = (argc > 1 ? fin : std::cin);
	try {
		YAML::ParserBase parser(input);
		YAML::Node doc;
		while(parser.GetNextDocument(doc)) {
			YAML::Emitter emitter;
			emitter << doc;
			std::cout << emitter.c_str() << "\n";
		}
	} catch(const YAML::Exception& e) {
		std::cerr << e.what() << "\n";
	}
	return 0;
}
