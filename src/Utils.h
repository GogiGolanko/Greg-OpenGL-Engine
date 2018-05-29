#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
using namespace std;

namespace glUtils {
	class Utils {
	public:
		static string get_file_string(string fileName) {
			ifstream ifs(fileName);
			return string((istreambuf_iterator<char>(ifs)),
				(istreambuf_iterator<char>()));
		}

		static string get_shader_source(string shaderName) {
			return get_file_string("resources/shaders/" + shaderName);
		}
	};
}

#endif
