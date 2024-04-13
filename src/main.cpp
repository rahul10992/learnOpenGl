#include "config.h"
// https://www.youtube.com/watch?v=4m9RHfdUU_M
int main() {
    
    GLFWwindow* window;

    if(!glfwInit()){
        std::cout << "GLFW couldn't be loaded" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Hello openGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "GLAD couldn't be loaded" << std::endl;
        glfwTerminate();
        return -1;
    }

    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}