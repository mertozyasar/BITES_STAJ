
#include <iostream>
#include "libraries/include/glad/glad.h"
#include <GLFW/glfw3.h>


class Grid {

private:
	GLFWwindow* window;
	int height, width;

public:
	Grid(int height ,int lenght );
	void createwindow();
	GLFWwindow*  getwindow();




};
