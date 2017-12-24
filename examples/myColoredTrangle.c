/*****************************************************************************
create by garryling
 *****************************************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "loadshader.h"

//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"uniform vec4 ourColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = ourColor;\n"
//"}\n\0";

const char *vertexShaderSourceForMultiColor = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char *fragmentShaderSourceForMultiColor = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("create window error\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("faild to load glad\n");
        return -1;
    }
    char infoLog[512];
    
    unsigned int vertexShader;
    Shader ourshader("myColoredTranglevertexShaderSource.vs", "myColoredTranglefragmentShaderSource.fs");
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
    int success;
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        return -1;
//    }
//
//    unsigned int fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        return -1;
//    }
    
    unsigned int vertexShaderForMultiColor;
    vertexShaderForMultiColor = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderForMultiColor, 1, &vertexShaderSourceForMultiColor, NULL);
    glCompileShader(vertexShaderForMultiColor);
    glGetShaderiv(vertexShaderForMultiColor, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderForMultiColor, 512, NULL, infoLog);
        return -1;
    }
    
    unsigned int fragmentShaderForMultiColor;
    fragmentShaderForMultiColor = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderForMultiColor, 1, &fragmentShaderSourceForMultiColor, NULL);
    glCompileShader(fragmentShaderForMultiColor);
    glGetShaderiv(fragmentShaderForMultiColor, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaderForMultiColor, 512, NULL, infoLog);
        return -1;
    }
    
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        return -1;
//    }
    
    unsigned int shaderProgramForMultiColor;
    shaderProgramForMultiColor = glCreateProgram();
    glAttachShader(shaderProgramForMultiColor, vertexShaderForMultiColor);
    glAttachShader(shaderProgramForMultiColor, fragmentShaderForMultiColor);
    glLinkProgram(shaderProgramForMultiColor);
    glGetProgramiv(shaderProgramForMultiColor, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramForMultiColor, 512, NULL, infoLog);
        return -1;
    }
    
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShaderForMultiColor);
    glDeleteShader(fragmentShaderForMultiColor);
    // trangle
    float verticals[] = {
        -0.5f, -0.0f, 0.0f,
        0.0f, -0.0f, 0.0f,
        -0.25f, 0.5f, 0.0f
    };

    unsigned int VBO;
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glBindVertexArray(0);
    
    // trangle with multicolor
    float vertexAndColor[] = {
        -0.0f, -0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,
        0.25f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
    };
    
    unsigned int VBO1, VAO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBindVertexArray(VAO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAndColor), vertexAndColor, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        float currentTime = glfwGetTime();
        float greenColor = sinf(currentTime) / 2 + 0.5f;
        
//        glUseProgram(shaderProgram);
        ourshader.use();
        int vertexLocation = glGetUniformLocation(ourshader.ID, "ourColor");
        glUniform4f(vertexLocation, 0.0f, greenColor, 0.0f, 1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shaderProgramForMultiColor);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
    
}
