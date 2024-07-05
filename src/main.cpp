#include "config.h"
#include "cstring"
// https://www.youtube.com/watch?v=4m9RHfdUU_M

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// vertex shader string
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

// fragment shader string:
const char *fragmentShader1Source = "#version 330 core\n"
                                 "out vec4 FragColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                 "}\0";

const char *fragmentShader2Source = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                    "}\0";
GLenum wireframe = GL_FILL;
int main() {
    // glfw: initialize and configure
    // ------------------------------
    if(!glfwInit()){
        std::cout << "GLFW couldn't be loaded" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // allow for resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "GLAD couldn't be loaded" << std::endl;
        glfwTerminate();
        return -1;
    }

    // build shader program

    // vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // validate shader
    int success;
    char errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << errorLog << std::endl;
    }

    // fragment shader:
    unsigned int fragmentShader[2];
    fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[0], 1, &fragmentShader1Source, NULL);
    glShaderSource(fragmentShader[1], 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShader[0]);

    // validate shader
    success = 0;
    //memset(errorLog, 0, sizeof(errorLog));
    glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader[0], 512, NULL, errorLog);
        std::cout << "ERROR::SHADER::FRAGMENT[0]::COMPILATION_FAILED\n" << errorLog << std::endl;
    }

    glCompileShader(fragmentShader[1]);
    glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader[1], 512, NULL, errorLog);
        std::cout << "ERROR::SHADER::FRAGMENT[1]::COMPILATION_FAILED\n" << errorLog << std::endl;
    }

    unsigned int shaderProgram[2];
    shaderProgram[0] = glCreateProgram();
    shaderProgram[1] = glCreateProgram();
    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShader[0]);

    glAttachShader(shaderProgram[1], vertexShader);
    glAttachShader(shaderProgram[1], fragmentShader[1]);

    glLinkProgram(shaderProgram[0]);
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram[0], 512, NULL, errorLog);
        std::cout << "ERROR::SHADER::LINKING PROGRAM::COMPILATION_FAILED\n" << errorLog << std::endl;
    }


    glLinkProgram(shaderProgram[1]);
    glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram[1], 512, NULL, errorLog);
        std::cout << "ERROR::SHADER::LINKING PROGRAM::COMPILATION_FAILED\n" << errorLog << std::endl;
    }


    // delete shaders after linking??
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader[0]);
    glDeleteShader(fragmentShader[1]);

    // vertices:
    // basic triangle
//    float vertices[] = {
//            -0.5f, -0.5f, 0.0f, // left
//            0.5f, -0.5f, 0.0f, // right
//            0.0f,  0.5f, 0.0f  // top
//    };
    // rectangle
   /* float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };*/
   // 2 triangles
  /* float vertices[] = {
           // triangle 1
           -1.0f, -0.5f, 0.0f, // left
           0.0f, -0.5f, 0.0f, // right
           -0.5f,  0.5f, 0.0f, // top

           // triangle 2
           0.0f, -0.5f, 0.0f, // left
           1.0f, -0.5f, 0.0f, // right
           0.5f,  0.5f, 0.0f  // top
   };*/
    float vertices1[] = {
            // triangle 1
            -1.0f, -0.5f, 0.0f, // left
            0.0f, -0.5f, 0.0f, // right
            -0.5f,  0.5f, 0.0f, // top
    };
    float vertices2[] = {
            // triangle 2
            0.0f, -0.5f, 0.0f, // left
            1.0f, -0.5f, 0.0f, // right
            0.5f,  0.5f, 0.0f  // top
    };

    // VAO
    unsigned int vao[2];
    unsigned int vbo[2];

    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);

    // vao 1
    glBindVertexArray(vao[0]);

    // VBO1
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vao 2
    glBindVertexArray(vao[1]);

    // VBO2
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // EBO
    /*unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/


    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // wireframe mode or fill mode
        glPolygonMode(GL_FRONT_AND_BACK, wireframe);

        // input
        processInput(window);

        // rendering code goes here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // draw the first triangle
        glUseProgram(shaderProgram[0]);
        glBindVertexArray(vao[0]); // bind the VAO1
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram[1]);
        glBindVertexArray(vao[1]); // bind the VAO2
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

        // poll all events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(2, vbo);
    //glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(2, vao);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        if(wireframe == GL_LINE)
            wireframe = GL_FILL;
        else
            wireframe = GL_LINE;
    }
    else if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
