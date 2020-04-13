#include <gui/GuiElement.h>

#include <glm/glm.hpp>

namespace peach {

// clang-format off
/*static*/ const std::unordered_map<std::string, ___PropertyTree::DataTypeDescriptor> ___PropertyTree::mTypeMap { // NOLINT
    { typeid(char).name(), { "char", ImGuiDataType_S8, 1 } },
    { typeid(unsigned char).name(), { "unsigned char", ImGuiDataType_U8, 1 } },
    { typeid(int16_t).name(), { "int16_t", ImGuiDataType_S16, 1 } },
    { typeid(uint16_t).name(), { "uint16_t", ImGuiDataType_U16, 1 } },
    { typeid(int32_t).name(), { "int32_t", ImGuiDataType_S32, 1 } },
    { typeid(uint32_t).name(), { "uin32_t", ImGuiDataType_U32, 1 } },
    { typeid(int64_t).name(), { "int64_t", ImGuiDataType_S64, 1 } },
    { typeid(uint64_t).name(), { "uint64_t", ImGuiDataType_U64, 1 } },
    { typeid(float).name(), { "float", ImGuiDataType_Float, 1 } },
    { typeid(double).name(), { "double", ImGuiDataType_Double, 1 } },
    { typeid(bool).name(), { "bool", ImGuiDataType_U8, 1 } },
    { typeid(glm::vec4).name(), { "vec4", ImGuiDataType_Float, 4 } },
    { typeid(glm::vec3).name(), { "vec3", ImGuiDataType_Float, 3 } },
    { typeid(glm::vec2).name(), { "vec2", ImGuiDataType_Float, 2 } }
};
// clang-format on

} // namespace peach