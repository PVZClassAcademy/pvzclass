# 贡献指南

在对本项目进行代码前，必须先阅读此贡献指南。

# 项目结构

```bash
┌build \\ pvzclass 构建相关
├──general.props \\ MSBuild 项目属性文件，所有项目均包含
└──pvzclass.props \\ MSBuild 项目属性文件，pvzclass 项目专用

┌devscript \\ pvzclass 开发相关
├──AStyle.bat \\ 调用 AStyle 对脚本进行初始化
└──Doxyfile \\ Doxygen 配置文件

┌docs \\ pvzclass 开发参考文档
└──Events说明.md \\ Events 组件参考文档

┌pvzclass \\ pvzclass 主体，静态链接库
├──Classes \\ 主要类
├──Enums \\ 枚举类型
├─┬include \\ 应当包含几乎所有头文件的文件夹
│ ├──Events \\ 事件系统的头文件
│ ├──Widgets \\ 控件类的头文件
│ └──Sexy.h \\ 包含部分与控件相关的类型与方法声明
├─┬src \\ 应当包含所有源代码文件的文件夹
│ ├──Events \\ 事件系统的源代码
│ ├──Widgets \\ 控件类的源代码
│ └──*.cpp \\ 对应 include 中对应头文件的源代码文件
├──Enums.h \\ 包含枚举类型
├──pvzclass.h \\ pvzclass 核心头文件（不含事件）
├──pvzevent.hpp \\ pvzclass 事件系统头文件
├──deprecated.hpp \\ 包含 pvzclass 中已弃用内容的头文件。不包含于 pvzclass.h 中，需要单独包含。
└──utils.h \\ 包含部分特殊功能的头文件。已弃用。

┌pvzdll \\ 基于 pvzclass 的动态链接库样例
└──pch.h \\ 预编译头

┌pvzmain \\ 基于 pvzclass 的控制台应用程序样例
└──pvzmain.cpp \\ 源代码文件
```

# 使用工具

本项目使用 [Doxygen](www.doxygen.nl) 作为 API 文档生成工具。

`Doxyfile` （Doxygen 配置文件）位于 docs 文件夹中，可直接加载。

# 代码规范

**!! 本项目使用制表符缩进 !!**

代码样式工具为 AStyle，具体参数请参见 `devScript/AStyle.bat`。

请在开启 Pull Request 前校正代码样式。不符合样式的 Pull Request **不会被合并**。

## 事件规范

所有从 `ThreeStateEventTemplate` 派生的事件类，应当具有 `_ts` 命名后缀（复合事件的成员事件除外）。