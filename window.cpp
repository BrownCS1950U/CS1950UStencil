#include "window.h"

Window::Window(){
    std::cout<<"Start"<<std::endl;
    start();
    std::cout<<"Loop"<<std::endl;
    loop();
    std::cout<<"End"<<std::endl;
    end();
}

Window::~Window(){

}

void Window::start(){
    // Testing glfw
    if(!glfwInit()){
        std::cout<<"GLFW init failed :("<<std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    m_GLFWwindow = glfwCreateWindow(640, 480, "CS1950U Engine", NULL, NULL);
    if (!m_GLFWwindow)
    {
        std::cout<<"Window Creation Failed :("<<std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_GLFWwindow);

    Global::graphics.initializeGLEW(); // IMPORTANT: Can't make ANY OpenGL calls before this occurs!

    glfwSwapInterval(1);

    // Set up core now that windowing and opengl are set up
    m_core = new Core();

    // Stores variable in glfw to reference our m_core object. This allows it to be accessed
    // even in static methods such as keyCallback and windowSizeCallback
    glfwSetWindowUserPointer(m_GLFWwindow, m_core);

    glfwSetKeyCallback(m_GLFWwindow, keyCallback);

    glfwSetWindowSizeCallback(m_GLFWwindow, windowSizeCallback);

    glfwSetInputMode(m_GLFWwindow, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Window::loop(){
    while (!glfwWindowShouldClose(m_GLFWwindow))
    {
        if(glfwGetTime() > 1.f/60){
            m_core->update(glfwGetTime());
            glfwSetTime(0);
            glfwSwapBuffers(m_GLFWwindow);
        }
        // Keep running
        //glfwSwapBuffers(m_GLFWwindow);
        glfwPollEvents();
    }
}

void Window::end(){
    glfwDestroyWindow(m_GLFWwindow);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    Core* ptr = (Core*)glfwGetWindowUserPointer(window);
    ptr->keyEvent(key, action);
}

void Window::windowSizeCallback(GLFWwindow* window, int width, int height){
    Core* ptr = (Core*)glfwGetWindowUserPointer(window);
    ptr->resizeEvent(width, height);
}