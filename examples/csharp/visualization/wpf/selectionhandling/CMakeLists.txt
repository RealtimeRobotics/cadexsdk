cmake_minimum_required(VERSION 3.13)

project(selectionhandling_wpf LANGUAGES CSharp)

include(CSharpUtilities)

add_executable(${PROJECT_NAME} App.config
                               App.xaml
                               App.xaml.cs
                               SelectionHandlingApplication.cs
                               SelectionHandlingWindow.xaml
                               SelectionHandlingWindow.xaml.cs
                               ../../common/BaseViewerApplication.cs
                               ../baseviewer/BaseViewer.xaml
                               ../baseviewer/BaseViewer.xaml.cs
                               ./../../../cadex_license.cs
                               ./../../../Properties/AssemblyInfo.cs)

csharp_set_designer_cs_properties(../Properties/AssemblyInfo.cs)

csharp_set_xaml_cs_properties(App.xaml 
                              App.xaml.cs
                              SelectionHandlingApplication.cs
                              SelectionHandlingWindow.xaml
                              SelectionHandlingWindow.xaml.cs
                              ../../common/BaseViewerApplication.cs
                              ../baseviewer/BaseViewer.xaml
                              ../baseviewer/BaseViewer.xaml.cs)

set_property(SOURCE App.xaml PROPERTY VS_XAML_TYPE "ApplicationDefinition")

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7")
set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)

# examples always link to win64 csharp libraries
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES
                                             "System"
                                             "System.Core"
                                             "System.Xaml"
                                             "Microsoft.CSharp"
                                             "WindowsBase"
                                             "PresentationCore"
                                             "PresentationFramework"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExCoreNet.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExSTEPNet.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExViewNet.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExViewD3DNet.dll"
                                             "${CADEX_ROOT_DIR}/csharp/win64/CadExViewWPF.dll")

include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
