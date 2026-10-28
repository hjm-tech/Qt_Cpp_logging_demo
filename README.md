# Qt User Login & Register Demo
> C++ Qt实现的本地账号注册登录小Demo，文件存储账号密码，GUI图形界面。

## 项目简介
基于 **Qt6(C++)** 开发的桌面小程序。
账号密码保存在本地txt文本文件；实现注册、登录校验、查看全部账号列表功能。
适合Qt初学者练习布局、Lambda信号槽、文件IO、QWidget内存管理。

## 功能特性
-  用户注册：读取输入框账号密码，检测账号是否重复，追加写入本地文本
-  用户登录：读取文本文件校验账号密码，使用QFrame色块反馈登录结果（绿色成功 / 红色失败）
-  查看账号列表：弹窗窗口读取txt，动态生成QLabel展示全部账号密码
-  Qt布局：QHBoxLayout / QVBoxLayout嵌套布局
-  文件自动创建：程序启动检测，不存在data.txt会自动新建

## 技术栈
- 语言：C++17
- GUI框架：**Qt6**（QWidget组件）
- 文件处理：`std::ifstream / std::ofstream`
- 核心知识点：信号槽Lambda表达式、布局管理、父对象内存树、std字符串与QString互转

## 编译运行
### 环境要求
- Qt6开发环境（Qt Creator）
- C++编译器(gcc/MinGW/MSVC)

### 运行步骤
- 1.打开main.cpp文件，将filename变量更改为data目录的绝对路径
- 2.cd到logging_demo目录下
- 3.cmake .
- 4.make
- 5.在logging_demo目录下输入bin/running

##缺陷
- 点击显示按钮的时候会产生内存泄漏
- 显示的QWight在进行注册操作以后会显示重影