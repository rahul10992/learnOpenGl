#include "config.h"
#include "cstring"
#include "Shader.h"
// https://www.youtube.com/watch?v=4m9RHfdUU_M
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    stbi_set_flip_vertically_on_load(true);

    Shader textureShader("/Users/rahul/Desktop/repo/openGlGettingStarted/src/Shaders/Vertex/Xyz_Rgb_St_vert.glsl",
                         "/Users/rahul/Desktop/repo/openGlGettingStarted/src/Shaders/Fragment/Rgb_St_Frag.glsl");

    // vertices:
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
    };

    // VAO
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // vao
    glBindVertexArray(vao);

    // vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // load image
    int width, height, nrChannels;
    unsigned char *data = stbi_load(
            "/Users/rahul/Desktop/repo/openGlGettingStarted/src/Textures/container.jpg",
            &width, &height, &nrChannels, 0);

    // Texture - load and bind
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // Texture wrapping params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // set values and enable mipmaps
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // cleanup
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    unsigned char *dataNew = stbi_load("/Users/rahul/Desktop/repo/openGlGettingStarted/src/Textures/awesomeface.png",
                                       &width, &height, &nrChannels, 0);
    if (dataNew)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataNew);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(dataNew);

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

        textureShader.use();
        glUniform1i(glGetUniformLocation(textureShader.ID, "texture1"), 0); // set it manually
        textureShader.setInt("texture2", 1); // or with shader class

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // poll all events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

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
