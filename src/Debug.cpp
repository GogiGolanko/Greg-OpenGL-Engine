/*
 * debug.cpp
 *
 *  Created on: 9 kwi 2018
 *      Author: Greg
 */

#include "Debug.h"

namespace glDebug {

	DebugOutput::DebugOutput() {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(myCallback, NULL);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
	}

	DebugOutput::~DebugOutput() {}

	void DebugOutput::myCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data) {
		cout << "\nDebug Output:\n"
		     << "source:     " << getStringForSource(source).c_str()     << endl
		     << "type:       " << getStringForType(type).c_str()         << endl
		     << "severity:   " << getStringForSeverity(severity).c_str() << endl
		     << "debug call: " << msg 									 << endl;
	}

	string DebugOutput::getStringForType(GLenum type) {
		switch (type) {
			case GL_DEBUG_TYPE_ERROR:
				  return "Error";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				  return "Deprecated behavior";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				  return "Undefined behavior";
			case GL_DEBUG_TYPE_PORTABILITY:
				  return "Portability issue";
			case GL_DEBUG_TYPE_PERFORMANCE:
				  return "Performance issue";
			case GL_DEBUG_TYPE_MARKER:
				  return "Stream annotation";
			case GL_DEBUG_TYPE_OTHER_ARB:
				  return "Other";
			default:
				  return "";
		 };
	}

	string DebugOutput::getStringForSource(GLenum source) {
		switch (source) {
		   case GL_DEBUG_SOURCE_API:
				return "API";
		   case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				return "Window system";
		   case GL_DEBUG_SOURCE_SHADER_COMPILER:
				return "Shader compiler";
		   case GL_DEBUG_SOURCE_THIRD_PARTY:
				return "Third party";
		   case GL_DEBUG_SOURCE_APPLICATION:
				return "Application";
		   case GL_DEBUG_SOURCE_OTHER:
				return "Other";
		   default:
				return "";
		};
	}

	string DebugOutput::getStringForSeverity(GLenum severity) {
		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:
			   return "High";
			case GL_DEBUG_SEVERITY_MEDIUM:
			   return "Medium";
			case GL_DEBUG_SEVERITY_LOW:
			   return "Low";
			case GL_DEBUG_SEVERITY_NOTIFICATION:
			   return "Notification";
			default:
			   return "";
		};
	}

} /* namespace Core */
