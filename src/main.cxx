#include <iostream>
#include <memory>


//OPENGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "linmath.h"

// #include "ImGuiUtils.h"

#include "baseline/ShaderProgram.h"
#include "baseline/Gui.h"
#include "baseline/Renderer.h"
#include "baseline/Scene.h"
#include "baseline/Simulation.h"






static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**){


    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);


    //Objects
    std::shared_ptr<Scene> scene (new Scene);
    std::shared_ptr<Renderer> renderer (new Renderer);
    std::shared_ptr<Simulation> sim (new Simulation);
    renderer->init(scene);
    sim->init(scene,renderer);


    //Imgui
    ImGui_ImplGlfwGL3_Init(window, true);
    std::unique_ptr<Gui> gui (new Gui(sim));
    gui->init_fonts(); //needs to be initialized inside the context



    //Shaders
    std::shared_ptr<ShaderProgram> shader_program (new ShaderProgram);
    shader_program->initFromFiles("shaders/vert_shader.glsl", "shaders/frag_shader.glsl");
    shader_program->addUniform("MVP");
    shader_program->addAttribute("vCol");
    shader_program->addAttribute("vPos");



    while(true){
      glfwPollEvents();
      ImGui_ImplGlfwGL3_NewFrame();
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);


      gui->update();
      sim->update();
      renderer->draw();



      ImGui::Render();
      glfwSwapBuffers(window);




    }



    // GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    // GLint mvp_location, vpos_location, vcol_location;
    //
    // // glfwSwapInterval(0);
    //
    //
    //
    //
    //
    //
    //
    // GLuint VertexArrayID;
    // glGenVertexArrays(1, &VertexArrayID);
    // glBindVertexArray(VertexArrayID);
    //
    //
    // glGenBuffers(1, &vertex_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    //
    //
    // glEnableVertexAttribArray(shader_program->attribute("vPos"));
    // glVertexAttribPointer(shader_program->attribute("vPos"), 2, GL_FLOAT, GL_FALSE,
    //                      sizeof(float) * 5, (void*) 0);
    // glEnableVertexAttribArray(shader_program->attribute("vCol"));
    // glVertexAttribPointer(shader_program->attribute("vCol"), 3, GL_FLOAT, GL_FALSE,
    //                      sizeof(float) * 5, (void*) (sizeof(float) * 2));
    //
    // ImVec4 clear_color = ImColor(114, 144, 154);
    //
    //
    //
    //
    //
    // // Main loop
    //
    // float speed=0.0;
    // float translate_x=0.0,translate_y=0.0,translate_z=0.0;
    // float rotate_x=0.0;
    //
    // while (!glfwWindowShouldClose(window))
    // {
    //   // printf("%s\n", glGetString(GL_VERSION));
    //     glfwPollEvents();
    //     ImGui_ImplGlfwGL3_NewFrame();
    //     ImGui::Text("%s Search", ICON_FA_SEARCH);
    //     gui->update();
    //
    //
    //
    //
    //     float ratio;
    //     int width, height;
    //     mat4x4 m, p, mvp;
    //     glfwGetFramebufferSize(window, &width, &height);
    //     ratio = width / (float) height;
    //     glViewport(0, 0, width, height);
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    //     mat4x4_identity(m);
    //
    //
    //     // if (ImGui::SliderFloat("speed", &speed, 0.0f, 10.0f)){
    //     //   std::cout << "value has been modified" << '\n';
    //     // }
    //     // ImGui::SliderFloat("translate_x", &translate_x, -10.0f, 10.0f);
    //     // ImGui::SliderFloat("translate_y", &translate_y, -10.0f, 10.0f);
    //     // ImGui::SliderFloat("translate_z", &translate_z, -10.0f, 10.0f);
    //     // ImGui::SliderFloat("rotate_x", &rotate_x, -10.0f, 10.0f);
    //
    //     mat4x4_translate_in_place(m,translate_x, translate_y, translate_z);
    //
    //     mat4x4_rotate_Z(m, m, (float) glfwGetTime()+speed);
    //     mat4x4_rotate_X(m, m, rotate_x);
    //     // mat4x4_rotate_Z(m, m, speed);
    //
    //
    //     mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    //     mat4x4_mul(mvp, p, m);
    //
    //
    //     shader_program->use();
    //     glUniformMatrix4fv(shader_program->uniform("MVP"), 1, GL_FALSE, (const GLfloat*) mvp);
    //
    //     glDrawArrays(GL_TRIANGLES, 0, 3);
    //
    //
    //     ImGui::Render();
    //     // ImGui::GetDrawData();
    //     glfwSwapBuffers(window);
    // }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}
