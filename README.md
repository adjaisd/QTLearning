# QT学习记录

&emsp;采用Qt6进行开发，开发环境为Clion，仓库中包含Qt的日常学习记录.

## 项目结构

&emsp;采用CMake集成多个模块.

```text
D:.
├───build           # 构建目录
├───modules         # 平时学习记录
│   ├───demo1
│   ├───demo2
    ....
│   ├───demo18
└───practice        # 运用之前所学知识的练习项目
    └───MineClearance   # 扫雷项目
```

&emsp;该项目关于CMake集成Qt项目有很多值得借鉴的地方，其中多模块、集成Qt6、文件分类(ui放于ui目录、资源文件放在resources等)都可参考本仓库的历史提交记录.

&emsp;由于习惯于将头文件和c文件放在不同目录，在集成Qt6时，经常遇到报错`undefined reference to 'vtable for xxx'`，也可参考本仓库.