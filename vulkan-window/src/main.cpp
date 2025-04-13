#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <iostream>

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

  uint32_t count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);

  VkExtensionProperties *extensions = new VkExtensionProperties[count];

  VkResult result =
      vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions);
  if (result != VkResult::VK_SUCCESS) {
    std::cout << "failure" << "\n";
  }

  for (uint32_t i = 0; i < count; ++i) {
    const auto &prop = extensions[i];
    std::cout << "Extension: " << prop.extensionName << "\n";
  }

  // Cleanup
  delete[] extensions;
  glm::mat4 matrix;
  glm::vec4 vec;
  auto test = matrix * vec;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();

  return 0;
}
