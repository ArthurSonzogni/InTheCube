#ifndef GL_CHECK_ERROR_HPP
#define GL_CHECK_ERROR_HPP

// Ask OpenGL for errors:
// Result is printed on the standard output
// usage :
//      GL_CHECK_ERROR(__FILE__,__LINE__);
void GL_CHECK_ERROR(const char* file, unsigned int line);

#endif  // GL_CHECK_ERROR_HPP
