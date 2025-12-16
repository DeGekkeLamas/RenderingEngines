#include "gladHelper.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <__msvc_ranges_to.hpp>

#include "core/mesh.h"
#include "core/assimpLoader.h"
#include "core/texture.h"
#include "Scripts/Camera.hpp"
#include "iostream"
#include "Scripts/GameObject.hpp"
#include "Scripts/List.hpp"
#include "Scripts/PointLight.hpp"
#include "Scripts/RenderableObject.hpp"
#include "Scripts/Scene.hpp"

//#define MAC_CLION
#define VSTUDIO

#ifdef MAC_CLION
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#endif

#ifdef VSTUDIO
// Note: install imgui with:
//     ./vcpkg.exe install imgui[glfw-binding,opengl3-binding]
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif

int g_width = 800;
int g_height = 600;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow *window,
                             int width, int height) {
    g_width = width;
    g_height = height;
    glViewport(0, 0, width, height);
}

std::string readFileToString(const std::string &filePath) {
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream.is_open()) {
        printf("Could not open file: %s\n", filePath.c_str());
        return "";
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

GLuint generateShader(const std::string &shaderPath, GLuint shaderType) {
    printf("Loading shader: %s\n", shaderPath.c_str());
    const std::string shaderText = readFileToString(shaderPath);
    // TODO: search for "#include", and replace it! (maybe)
    const GLuint shader = glCreateShader(shaderType);
    const char *s_str = shaderText.c_str();
    glShaderSource(shader, 1, &s_str, nullptr);
    glCompileShader(shader);
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error! Shader issue [%s]: %s\n", shaderPath.c_str(), infoLog);
    }
    return shader;
}

int main() {
    List<int> testList = List<int>();

    for (int i = 0; i < 10; i++) {
        testList.Add(i);
    }
}
    /**
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(g_width, g_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    //Setup platforms
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const GLuint modelVertexShader = generateShader("shaders/modelVertex.vs", GL_VERTEX_SHADER);
    const GLuint vertexShader = generateShader("shaders/vertex.vs", GL_VERTEX_SHADER);
    const GLuint fragmentShader = generateShader("shaders/fragment.fs", GL_FRAGMENT_SHADER);
    const GLuint textureShader = generateShader("shaders/texture.fs", GL_FRAGMENT_SHADER);

    int success;
    char infoLog[512];
    const unsigned int modelShaderProgram = glCreateProgram();
    glAttachShader(modelShaderProgram, modelVertexShader);
    glAttachShader(modelShaderProgram, fragmentShader);
    glLinkProgram(modelShaderProgram);
    glGetProgramiv(modelShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(modelShaderProgram, 512, NULL, infoLog);
        printf("Error! Making Shader Program: %s\n", infoLog);
    }
    const unsigned int textureShaderProgram = glCreateProgram();
    glAttachShader(textureShaderProgram, modelVertexShader);
    glAttachShader(textureShaderProgram, textureShader);
    glLinkProgram(textureShaderProgram);
    glGetProgramiv(textureShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(textureShaderProgram, 512, NULL, infoLog);
        printf("Error! Making Shader Program: %s\n", infoLog);
    }

    // glDeleteShader(modelVertexShader);
    // glDeleteShader(fragmentShader);
    // glDeleteShader(textureShader);

    // Quad
    core::Mesh quad = core::Mesh::generateQuad();
    core::Model quadModel({quad});
    core::Texture cmgtGatoTexture("textures/CMGaTo_crop.png");
    Material cmGatoMaterial(&cmgtGatoTexture, modelVertexShader, textureShader);
    Material normalMat(nullptr, modelVertexShader, fragmentShader);
    RenderableObject quadObj("Quad", glm::vec3(0,0,-2.5), nullptr, &quadModel, &cmGatoMaterial);
    quadObj.transform.Scale(glm::vec3(5, 5, 1));
    // Susanne
    core::Model suzanne = core::AssimpLoader::loadModel("models/nonormalmonkey.obj");
    RenderableObject suzanneObj("Suzanne", glm::vec3(), nullptr, &suzanne, &normalMat);
    // Dinner demon
    core::Model dinnerDemon = core::AssimpLoader::loadModel("models/DinnerDemon.fbx");
    RenderableObject dinnerDemonObj("Dinner demon", glm::vec3(1,-5,5), nullptr, &dinnerDemon, &normalMat);
    dinnerDemonObj.transform.Scale(glm::vec3(0.05f,0.05f,0.05f));
    // Mystifying Pan
    core::Model mystifyingPan = core::AssimpLoader::loadModel("models/MystifyingPan.fbx");
    RenderableObject mystifyingPanObj("Mystifying Pan", glm::vec3(-10,0,0), nullptr, &mystifyingPan, &normalMat);
    mystifyingPanObj.transform.Scale(glm::vec3(0.1f,0.1f,0.1f));
    // Backflip beerend
    core::Model backflipBeerend = core::AssimpLoader::loadModel("models/backflipBeerend.fbx");
    RenderableObject backflipBeerendObj("Backflip beerend", glm::vec3(10,0,0), nullptr, &backflipBeerend, &normalMat);
    backflipBeerendObj.transform.Scale(glm::vec3(0.1f,0.1f,0.1f));
    // Rey
    core::Model rey = core::AssimpLoader::loadModel("models/ReyRetopologized.fbx");
    RenderableObject reyObj("Rey", glm::vec3(0,0,30), nullptr, &rey, &normalMat);
    reyObj.transform.Rotate(glm::vec3(0, 3.1415f, 0));
    reyObj.transform.Scale(glm::vec3(0.5f,0.5f,0.5f));
    // Engine
    core::Model engine = core::AssimpLoader::loadModel("models/engine.fbx");
    core::Texture engineTexture("textures/initialShadingGroup_albedo.jpg");
    Material engineMaterial(&engineTexture, modelVertexShader, textureShader);
    RenderableObject engineObj("Engine", glm::vec3(0,-20,0), nullptr, &engine, &engineMaterial);
    engineObj.transform.Scale(glm::vec3(.1f, .1f, .1f));

    // Scene
    std::vector<RenderableObject*> modelsInScene;
    modelsInScene.push_back(&suzanneObj);
    modelsInScene.push_back(&quadObj);
    modelsInScene.push_back(&dinnerDemonObj);
    modelsInScene.push_back(&mystifyingPanObj);
    modelsInScene.push_back(&backflipBeerendObj);
    modelsInScene.push_back(&reyObj);
    modelsInScene.push_back(&engineObj);

    PointLight pointLight = PointLight("Light", glm::vec3(1,1,0), nullptr, glm::vec4(1,1,1,1), 1);
    float lightStrength = 1;
    // Light model
    core::Model sphere = core::AssimpLoader::loadModel("models/Sphere.fbx");
    // &pointLight.transform
    RenderableObject sphereObj("lightSphere", pointLight.transform.position(), &pointLight.transform, &sphere, &normalMat);
    // sphereObj.transform.Scale(glm::vec3(0.5f,0.5f,0.5f));
    modelsInScene.push_back(&sphereObj);

    glm::vec4 clearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearColor(clearColor.r,
                 clearColor.g, clearColor.b, clearColor.a);

    Camera cam;
    cam.transform.Rotate(glm::vec3(0, 3.1415f, 0));

    //VP
    glm::mat4 view;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(g_width) /
        static_cast<float>(g_height), 0.1f, 100.0f);

    GLint mvpMatrixUniform = glGetUniformLocation(modelShaderProgram, "mvpMatrix");
    GLint textureModelUniform = glGetUniformLocation(textureShaderProgram, "mvpMatrix");
    GLint textureUniform = glGetUniformLocation(textureShaderProgram, "text");

    double currentTime = glfwGetTime();
    double finishFrameTime = 0.0;
    float deltaTime = 0.0f;
    constexpr float rotationStrength = 10;

    for (int i = 0; i < modelsInScene.size(); i++) {
        modelsInScene[i]->material->Bind();
    }

    // PP
    RenderableObject renderQuad = quadObj;
    renderQuad.material->vertexShader = vertexShader;
    renderQuad.material->texture = nullptr;
    renderQuad.material->Bind();

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);

    unsigned int tcb;
    glGenTextures(1, &tcb);

    unsigned int depthBuffer;
    glGenTextures(1, &depthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Texture
    glBindTexture(GL_TEXTURE_2D, tcb);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
    height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D,
    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tcb, 0);
    // Depth
    // glEnable(GL_DEPTH_TEST);
    // // glEnable(GL_STENCIL_TEST);
    // glDepthFunc(GL_LESS);
    // glBindTexture(GL_TEXTURE_2D, depthBuffer);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0,
    // GL_DEPTH_COMPONENT, GL_UNSIGNED_INT_24_8, nullptr);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
    // GL_TEXTURE_2D, depthBuffer, 0);

    while (!glfwWindowShouldClose(window)) {

        cam.ProcessInput(window, deltaTime);
        view = glm::lookAt(cam.transform.position(),
            cam.transform.position() + cam.transform.forward(), cam.transform.up() );

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        // Inspector
        ImGui::NewFrame();
        ImGui::Begin("Raw Engine v2");
        ImGui::Text("%d FPS", static_cast<int>(1 / deltaTime));
        ImGui::Text("Hello :)");
        ImGui::SliderFloat("Light Strength", &lightStrength, 0, 10.0f);
        ImGui::ColorEdit3("Light Color", glm::value_ptr(pointLight.color));
        ImGui::End();
        pointLight.intensity = lightStrength;
        // Hierarchy
        ImGui::Begin("Hierarchy");
        for (int i = 0; i < modelsInScene.size(); i++) {
            RenderableObject* obj = modelsInScene[i];
            ImGui::Text("%s", obj->name.c_str());
            // pos
            glm::vec3 tempPos = obj->transform.position();
            ImGui::PushID(i);
            ImGui::DragFloat3("Position", glm::value_ptr(tempPos));
            ImGui::PopID();
            obj->transform.SetPosition(tempPos);
        }
        ImGui::End();

        processInput(window);
        suzanneObj.transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f) * rotationStrength *
            static_cast<float>(deltaTime));
        pointLight.transform.TranslateObjectSpace(pointLight.transform.right() * static_cast<float>(sin(currentTime) * deltaTime * 10));

        // PP
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        // glViewport(0, 0, width, height);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);

        // Render
        for (int i = 0; i < modelsInScene.size(); i++) {
            modelsInScene[i]->Render(view, projection, textureModelUniform, pointLight, cam);
        }

        // PP
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        renderQuad.Render(view, projection, textureModelUniform, pointLight, cam, tcb);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
        finishFrameTime = glfwGetTime();
        deltaTime = static_cast<float>(finishFrameTime - currentTime);
        currentTime = finishFrameTime;
    }

    glDeleteProgram(modelShaderProgram);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}