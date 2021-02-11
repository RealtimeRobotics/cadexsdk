cmake_minimum_required(VERSION 3.13)

project(baseviewer_winforms LANGUAGES CSharp)

include(CSharpUtilities)

add_executable(${PROJECT_NAME} App.config
                               Program.cs
                               ../../common/BaseViewerApplication.cs
                               BaseViewer.cs
                               BaseViewer.Designer.cs
                               BaseViewerWindow.cs
                               BaseViewerWindow.Designer.cs
                               ./../../../cadex_license.cs
                               ./../../../Properties/AssemblyInfo.cs)

csharp_set_designer_cs_properties(../../../Properties/AssemblyInfo.cs)

set_property(SOURCE App.xaml PROPERTY VS_XAML_TYPE "ApplicationDefinition")

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7")
set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)

# examples always link to win64 csharp libraries
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES
                                             "System"
                                             "System.Core"
                                             "System.Drawing"
                                             "System.Windows.Forms"
                                             "Microsoft.CSharp"
                                             "WindowsBase"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExCoreNet.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExViewNet.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExViewOpenGlNet.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExViewWinForms.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExSTEPNet.dll")

include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
