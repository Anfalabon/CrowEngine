

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>



//#include "../src/core/Filesystem.hpp"   //will see this later(we don't want to use relative path)
//#include "../src/debug/RenderingInfoLog.hpp"

#include <core/Filesystem.hpp>
//#include <debug/RenderingInfoLog.hpp>

#include <iostream>
#include <vector>


//To compile this code in my machine type : cake && LD_LIBRARY_PATH=../vendor/imageLoader/lib && ./myGL in the terminal


typedef struct Vertex
{
public:
    Vertex() = default;
    ~Vertex() = default;

public:
    glm::vec3 m_position;
    glm::vec3 m_color;
    glm::vec2 m_textureCoordinate;
    glm::vec3 m_normal;

} Vertex;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


namespace //anonymous namespace instead of bunch of 'satics'
{

    float g_deltaTime = 0.0f;
    float g_lastFrame = 0.0f;

    void CalculateDeltaTime()
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        g_deltaTime = currentFrame - g_lastFrame;
        g_lastFrame = currentFrame;
    }

}


unsigned int SetShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    const std::string vertexShaderSourceStr = CrowEngine::Filesystem::ReadFileContent(vertexShaderFilePath);
    const std::string fragmentShaderSourceStr = CrowEngine::Filesystem::ReadFileContent(fragmentShaderFilePath);

    const char* vertexShaderSource = vertexShaderSourceStr.c_str();
    const char* fragmentShaderSource = fragmentShaderSourceStr.c_str();


    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    return shaderProgram;
}


//here after a really long time :)
//let's build something...

unsigned int InitializeBufferObjects(const float* vertices, const unsigned int* indices)
{
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.


    glBindVertexArray(0);


    return VAO;
}


unsigned int LoadTexture(const char* filePath, bool enableOptions)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    if (enableOptions)
    {
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    //free the image data we longer need it(cause the data was sent to the GPU storage(OpenGL server buffer storage))
    stbi_image_free(data);

    return texture;
}




unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            //stbi_image_free(data);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}


void processInputCameraMovement(GLFWwindow* window, glm::vec3& cameraPos, const glm::vec3& cameraFront,
                                const glm::vec3& cameraUp)
{
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


inline double lastX = double(SCR_WIDTH) / 2.0f;
inline double lastY = double(SCR_HEIGHT) / 2.0f;
inline bool firstMouse = true;
inline double yaw = 0.0f;
inline double pitch = 0.0f;
inline glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);


    //    glm::vec4 direction = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
    //    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    //    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraFront));
    //
    //    //glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //
    //    glm::mat4 rotationAroundY = glm::rotate(glm::mat4(1.0f), glm::radians(float(yaw)), -up);
    //    glm::mat4 rotationAroundXZ = glm::rotate(glm::mat4(1.0f), glm::radians(float(pitch)), -cameraRight);
    //
    //    direction = rotationAroundXZ * rotationAroundY * direction;
    //
    //    glm::vec3 temp;
    //    temp.x = direction.x;
    //    temp.y = direction.y;
    //    temp.z = direction.z;
    //
    //    cameraFront = glm::normalize(temp);
}


void LoadSkybox(unsigned int& cubemapShaderProgram, unsigned int& cubemapTexture, unsigned int& cubemapVAO)
{
    cubemapShaderProgram = SetShader("../../assets/shaderPrograms/skybox.vert", "../../assets/shaderPrograms/skybox.frag");


    float cubemapVertices[] = {
        // positions
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f
    };


    unsigned int cubemapVBO;
    glGenVertexArrays(1, &cubemapVAO);
    glGenBuffers(1, &cubemapVBO);

    glBindVertexArray(cubemapVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubemapVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubemapVertices), cubemapVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    std::vector<std::string> faces = {

        "../../assets/skybox/right.jpg",
        "../../assets/skybox/left.jpg",
        "../../assets/skybox/top.jpg",
        "../../assets/skybox/bottom.jpg",
        "../../assets/skybox/front.jpg",
        "../../assets/skybox/back.jpg"

    };

    cubemapTexture = loadCubemap(faces);
}


void RunMouseControl(GLFWwindow* window, glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp);


int main()
{

    #include <filesystem>
    std::cout << std::filesystem::current_path() << '\n';

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "testGL", NULL, NULL);
    if (window == NULL)
    {
        std::clog << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader

    unsigned int shaderProgram = SetShader("../../assets/shaderPrograms/vertexShader.vert", "../../assets/shaderPrograms/fragmentShader.frag");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    float vertices[] = {
        // Position           // Texture Coords (U, V)
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // Front Top Right
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // Front Bottom Right
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // Front Bottom Left
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // Front Top Left

        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // Back Top Right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // Back Bottom Right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Back Bottom Left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // Back Top Left
    };

    float lightVertices[] = {
        // Position
        0.5f, 0.5f, 0.5f, // Front Top Right
        0.5f, -0.5f, 0.5f, // Front Bottom Right
        -0.5f, -0.5f, 0.5f, // Front Bottom Left
        -0.5f, 0.5f, 0.5f, // Front Top Left

        0.5f, 0.5f, -0.5f, // Back Top Right
        0.5f, -0.5f, -0.5f, // Back Bottom Right
        -0.5f, -0.5f, -0.5f, // Back Bottom Left
        -0.5f, 0.5f, -0.5f // Back Top Left
    };

    unsigned int indices[] = {
        // Front Face
        0, 1, 2,
        2, 3, 0,
        // Back Face
        4, 5, 6,
        6, 7, 4,
        // Left Face
        3, 2, 6,
        6, 7, 3,
        // Right Face
        0, 1, 5,
        5, 4, 0,
        // Top Face
        0, 3, 7,
        7, 4, 0,
        // Bottom Face
        1, 2, 6,
        6, 5, 1,
    };


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.


    glBindVertexArray(0);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //unsigned int VAO = InitializeBufferObjects(vertices, indices);

    unsigned int texture = LoadTexture("../../assets/images/brickTexture2.jpg", GL_TRUE);

    ///////////////////////////////////////////////////LOAD CUBEMAP/////////////////////////////////////////////////////////


    unsigned int cubemapShaderProgram;
    unsigned int cubemapTexture;
    unsigned int cubemapVAO;

    LoadSkybox(cubemapShaderProgram, cubemapTexture, cubemapVAO);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    unsigned int lightSourceShaderProgram = SetShader("../../assets/shaderPrograms/lightSource.vert", "../../assets/shaderPrograms/lightSource.frag");

    unsigned int lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    glm::mat4 lightSourceModel = glm::mat4(1.0f);
    lightSourceModel = glm::translate(lightSourceModel, glm::vec3(1.0f, 3.0f, 2.0f));


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //glUseProgram(shaderProgram);


    typedef struct Entity
    {
        Entity(const glm::mat4& model = glm::mat4(1.0f), const unsigned int indicies = 0)
            : model(model), indices(indicies)
        {
        }

        glm::mat4 model;
        unsigned int indices;

    } Entity;

    std::vector<Entity> entities;
    entities.push_back(Entity(glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)), 36));
    entities.push_back(Entity(glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f)), 36));
    entities.push_back(Entity(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f)), 36));


    glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    //glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);                 //up here is the OpenGL coordinate up. Not neccessarily camera up. so it's a const or should be a const
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraFront));
    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));


    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor = glm::vec3(1.0f);


    while (!glfwWindowShouldClose(window))
    {
        CalculateDeltaTime();
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glEnable(GL_DEPTH_TEST); //enables DEPTH TESTING
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the previous DEPTH BUFFER along with Color Buffer


        cameraRight = glm::normalize(glm::cross(up, cameraFront));
        cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));

        RunMouseControl(window, cameraPos, cameraFront, cameraUp);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        glDepthMask(GL_FALSE);
        glUseProgram(cubemapShaderProgram);

        glm::mat4 cubemapView = glm::mat4(glm::mat3(view));

        glUniformMatrix4fv(glGetUniformLocation(cubemapShaderProgram, "view"), 1, GL_FALSE,
                           glm::value_ptr(cubemapView));
        glUniformMatrix4fv(glGetUniformLocation(cubemapShaderProgram, "projection"), 1, GL_FALSE,
                           glm::value_ptr(projection));


        glBindVertexArray(cubemapVAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        glUseProgram(lightSourceShaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram, "projection"), 1, GL_FALSE,
                           glm::value_ptr(projection));

        glBindVertexArray(lightVAO);

        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram, "model"), 1, GL_FALSE,
                           glm::value_ptr(lightSourceModel));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        glUseProgram(shaderProgram);


        glUniform3fv(glGetUniformLocation(shaderProgram, "uLightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shaderProgram, "uObjectColor"), 1, glm::value_ptr(objectColor));
        objectColor += 0.001f;


        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // both of the objecst where translated in the same way because the translation vector was same for both
        // (we need different translation vector for different objects) and more importantly different draw calls
        // something my mind never got

        //if there's only one texture currently in use then no need to do these(activating and binding texture)
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);


        for (std::size_t i = 0; i < entities.size(); ++i) [[likely]]
        {
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE,
                               glm::value_ptr(entities[i].model));
            glDrawElements(GL_TRIANGLES, entities[i].indices, GL_UNSIGNED_INT, (void*)0);
        }


        //        Synapse::renderingInfo::FramesPerSecond(g_deltaTime);
        //        Synapse::renderingInfo::AverageFramePerSecond();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteProgram(shaderProgram);


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


void RunMouseControl(GLFWwindow* window, glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp)
{
    processInputCameraMovement(window, cameraPos, cameraFront, cameraUp);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) [[unlikely]]
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
