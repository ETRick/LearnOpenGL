# 张立铜OpenGL课程(https://edu.csdn.net/course/play/3512/)学习的记录

### 环境
- 系统： win10
- IDE: VS2015
### 环境配置

加入OpenGL的依赖文件，所有依赖在本仓库的Dependencies中
在 工程属性->配置属性/C++/常规 中，添加 *附加包含目录* 为Dependencies/include的相对路径
在 工程属性->配置属性/连接器/常规 中， 添加 *附加库目录*， 为Dependencies/lib/($PlatformName) 的相对路径
在 工程属性->配置属性/连接器/输入 中，*附加依赖项* 添加"OpenGL32.lib;libEGL.lib;libGLESv2.lib"
