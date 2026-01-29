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
#include "Scripts/PointLight.hpp"
#include "Scripts/RenderableObject.hpp"

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

bool windowSizeChanged=false;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    // printf("Window resized!\n");
    g_width = width;
    g_height = height;
    glViewport(0, 0, width, height);
    windowSizeChanged = true;

    glBindTexture(GL_TEXTURE_2D, 0);
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
    const GLuint colorPostProcessingShader = generateShader("shaders/MSPaintColorPostprocessing.fs", GL_FRAGMENT_SHADER);
    const GLuint outlinePostProcessingShader = generateShader("shaders/outlinePostprocessing.fs", GL_FRAGMENT_SHADER);
    const GLuint defaultPostprocessingShader = generateShader("shaders/defaultPostprocessing.fs", GL_FRAGMENT_SHADER);

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

    Material* normalMat = new Material(nullptr, modelVertexShader, fragmentShader);
    // Quad
    core::Mesh quad = core::Mesh::generateQuad();
    core::Model* quadModel = new core::Model({quad});
    std::shared_ptr<core::Texture> cmgtGatoTexture =
        std::shared_ptr<core::Texture>( new core::Texture("textures/CMGaTo_crop.png") );
    Material* cmGatoMaterial = new Material(cmgtGatoTexture, modelVertexShader, textureShader);
    RenderableObject quadObj("Quad", glm::vec3(0,0,-2.5), nullptr, quadModel, cmGatoMaterial);
    quadObj.transform.Scale(glm::vec3(5, 5, 1));
    // Susanne
    RenderableObject suzanneObj = RenderableObject::Create("Suzanne", glm::vec3(), glm::vec3(1,1,1), nullptr,
    "models/nonormalmonkey.obj", normalMat);
    // Dinner demon
    // RenderableObject dinnerDemonObj = RenderableObject::Create("Dinner demon", glm::vec3(1,-5,5), glm::vec3(0.05f,0.05f,0.05f), nullptr,
    // "models/DinnerDemon.fbx", normalMat);
    // // Mystifying Pan
    // RenderableObject mystifyingPanObj = RenderableObject::Create("Mystifying Pan", glm::vec3(-10,0,0), glm::vec3(0.1f,0.1f,0.1f), nullptr,
    // "models/MystifyingPan.fbx", normalMat);
    // // Backflip beerend
    // RenderableObject backflipBeerendObj = RenderableObject::Create("Backflip beerend", glm::vec3(10,0,0), glm::vec3(0.1f,0.1f,0.1f), nullptr,
    // "models/backflipBeerend.fbx", normalMat);
    // Rey
    RenderableObject reyObj = RenderableObject::Create("Rey", glm::vec3(0,0,30), glm::vec3(0.5f,0.5f,0.5f), nullptr,
    "models/ReyRetopologized.fbx", normalMat);
    reyObj.transform.Rotate(glm::vec3(0, 3.1415f, 0));
    // // Planet
    // RenderableObject planet = RenderableObject::Create("Planet", glm::vec3(30,0,0), glm::vec3(0.5f,0.5f,0.5f), nullptr,
    // "models/Planet.fbx", normalMat);
    // Terrain
    RenderableObject terrain = RenderableObject::Create("Terrain", glm::vec3(0,-10,0), glm::vec3(0.5f,0.25f,0.5f), nullptr,
    "models/Terrain.fbx", normalMat);
    // Engine
    RenderableObject engineObj = RenderableObject::Create("Engine", glm::vec3(0,0,-10), glm::vec3(.1f, .1f, .1f), nullptr,
    "models/engine.fbx", "textures/initialShadingGroup_albedo.jpg", modelVertexShader, textureShader);
    // Horse
    RenderableObject horseObj = RenderableObject::Create("Horse", glm::vec3(0,0,0), glm::vec3(.01f, .01f, .01f), nullptr,
        "models/Horse.obj", "textures/HorseTex.jpg", modelVertexShader, textureShader);
    // Tenna
    RenderableObject tenna = RenderableObject::Create("Tenna", glm::vec3(0,0,30), glm::vec3(.1f, .1f, .1f), nullptr,
        "models/Tenna_Sketchfab.fbx", "textures/Tenna_Sketchfab_BakedTexture.png", modelVertexShader, textureShader);
    tenna.transform.Rotate(glm::vec3(3.1415f/2, 0, 3.1415f));

    // Scene
    std::vector<RenderableObject*>* currentScene;
    std::vector<RenderableObject*> SceneA;
    std::vector<RenderableObject*> SceneB;
    std::vector<GameObject*> persistentObjects;
    SceneA.push_back(&suzanneObj);
    SceneA.push_back(&quadObj);
    // SceneA.push_back(&dinnerDemonObj);
    // SceneA.push_back(&mystifyingPanObj);
    // SceneA.push_back(&backflipBeerendObj);
    SceneA.push_back(&reyObj);
    SceneA.push_back(&horseObj);
    SceneB.push_back(&engineObj);
    SceneB.push_back(&tenna);
    // SceneB.push_back(&planet);
    SceneB.push_back(&terrain);

    currentScene = &SceneA;

    PointLight pointLight = PointLight("Light", glm::vec3(1,1,0),
        nullptr, glm::vec4(1,1,1,1), 1);
    float lightStrength = 1;
    // Light model
    RenderableObject sphereObj = RenderableObject::Create("lightSphere", glm::vec3(), glm::vec3(1,1,1), &pointLight.transform,
        "models/Sphere.fbx", normalMat);
    SceneA.push_back(&sphereObj);
    SceneB.push_back(&sphereObj);
    persistentObjects.push_back(&pointLight);

    glm::vec4 outlineColor(1,1,1,1);
    glm::vec4 clearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearColor(clearColor.r,
                 clearColor.g, clearColor.b, clearColor.a);

    Camera cam;
    persistentObjects.push_back(&cam);
    // cam.transform.Rotate(glm::vec3(0, 3.1415f, 0));

    //VP
    glm::mat4 view;
    glm::mat4 projection;

    GLint mvpMatrixUniform = glGetUniformLocation(modelShaderProgram, "mvpMatrix");
    GLint textureModelUniform = glGetUniformLocation(textureShaderProgram, "mvpMatrix");
    GLint textureUniform = glGetUniformLocation(textureShaderProgram, "text");

    double currentTime = glfwGetTime();
    double finishFrameTime = 0.0;
    float deltaTime = 0.0f;
    constexpr float rotationStrength = 10;

    // PP
    RenderableObject renderQuad = quadObj;
    Material* noPostProcessingMat = new Material(nullptr, vertexShader, defaultPostprocessingShader);
    Material* outlinePostProcessingMat = new Material(nullptr, vertexShader, outlinePostProcessingShader);
    Material* colorPostProcessingMat = new Material(nullptr, vertexShader, colorPostProcessingShader);
    renderQuad.material = colorPostProcessingMat;

    unsigned int fbo;
    glGenFramebuffers(1, &fbo);

    unsigned int tcb;
    glGenTextures(1, &tcb);

    unsigned int depthBuffer;
    glGenTextures(1, &depthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Texture
    glBindTexture(GL_TEXTURE_2D, tcb);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, g_width,
    g_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D,
    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tcb, 0);
    // Depth
    glDepthFunc(GL_LESS);
    glBindTexture(GL_TEXTURE_2D, depthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, g_width, g_height, 0,
    GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
    GL_TEXTURE_2D, depthBuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is NOT complete!" << std::endl;
    }

    while (!glfwWindowShouldClose(window)) {
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);

        cam.ProcessInput(window, deltaTime);
        view = glm::lookAt(cam.transform.position(),
            cam.transform.position() + cam.transform.forward(), cam.transform.up() );
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(g_width) /
        static_cast<float>(g_height), 0.1f, 100.0f);

        if (windowSizeChanged) {
            // Color texture
            glBindTexture(GL_TEXTURE_2D, tcb);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB8, g_width, g_height,
                0, GL_RGB,
                GL_UNSIGNED_BYTE,
                nullptr);

            // Depth-stencil texture
            glBindTexture(GL_TEXTURE_2D, depthBuffer);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_DEPTH24_STENCIL8,
                g_width,
                g_height,
                0,
                GL_DEPTH_STENCIL,
                GL_UNSIGNED_INT_24_8,
                nullptr);
            windowSizeChanged = false;
        }


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        // Inspector
        ImGui::NewFrame();
        ImGui::Begin("Cooked Engine v2");
        ImGui::Text("%d FPS", static_cast<int>(1 / deltaTime));
        ImGui::Text("Hello :)");
        ImGui::DragFloat("Light Strength", &lightStrength);
        ImGui::ColorEdit3("Light Color", glm::value_ptr(pointLight.color));
        if (ImGui::Button("Switch scene")) {
            if (currentScene == &SceneA) {
                currentScene = &SceneB;
            }
            else {
                currentScene = &SceneA;
            }
        }
        if (ImGui::Button("Horse")) {
            RenderableObject* newHorse = new RenderableObject( horseObj.Clone() );
            currentScene->push_back(newHorse);
        }
        ImGui::Text("Post-processing");
        if (ImGui::Button("None")) {
            renderQuad.material = noPostProcessingMat;
        }
        if (ImGui::Button("Outline")) {
            renderQuad.material = outlinePostProcessingMat;
        }
        if (ImGui::Button("Color filter")) {
            renderQuad.material = colorPostProcessingMat;
        }
        ImGui::ColorEdit3("Outline color", glm::value_ptr(outlineColor));
        ImGui::End();
        pointLight.intensity = lightStrength;
        // Hierarchy
        ImGui::Begin("Hierarchy");
        ImGui::PushID("PersistentObjects");
        for (int j = 0; j < persistentObjects.size(); j++) {
            ImGui::PushID(j);
            persistentObjects[j]->RenderToIMGUI();
            ImGui::PopID();
        }
        ImGui::PopID();
        ImGui::PushID("SceneObjects");
        for (int i = 0; i < currentScene->size(); i++) {
            ImGui::PushID(i);
            (*currentScene)[i]->RenderToIMGUI();
            ImGui::PopID();
        }
        ImGui::PopID();

        ImGui::End();

        processInput(window);
        suzanneObj.transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f) * rotationStrength * (deltaTime));
        pointLight.transform.TranslateObjectSpace(pointLight.transform.right() * static_cast<float>(sin(currentTime) * deltaTime * 10));

        // PP
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);

        // Render
        for (int i = 0; i < currentScene->size(); i++) {
            (*currentScene)[i]->Render(view, projection, textureModelUniform, pointLight, cam);
        }

        // PP
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        renderQuad.Render(tcb);
        renderQuad.SetUniform("outlineCol", outlineColor);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
        finishFrameTime = glfwGetTime();
        deltaTime = static_cast<float>(finishFrameTime - currentTime);
        currentTime = finishFrameTime;
    }

    glDeleteProgram(modelShaderProgram);
    glDeleteProgram(textureShaderProgram);
    delete noPostProcessingMat;
    delete outlinePostProcessingMat;
    delete colorPostProcessingMat;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}