/*
 * debug.h
 *
 *  Created on: 9 kwi 2018
 *      Author: Greg
 */

#ifndef DEBUGOUTPUT_H_
#define DEBUGOUTPUT_H_

#include <GL/glew.h>
#include <iostream>
#include <string>
using namespace std;

namespace glDebug {

	class DebugOutput {
		public:
			DebugOutput();
			virtual ~DebugOutput();
		private:
			static void myCallback(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, const void *);
			static string getStringForType(GLenum);
			static string getStringForSource(GLenum);
			static string getStringForSeverity(GLenum);
	};

} /* namespace Core */

#endif /* DEBUGOUTPUT_H_ */
