# Data Structure Visualizer (Qt)

一个基于 **Qt** 开发的数据结构可视化工具，帮助学习与演示常见的数据结构操作逻辑。  
目前支持 **链表、栈、队列（含循环队列）** 的基本可视化功能。

## ✨ 功能特性

- **链表 (Linked List)**
  - 插入、删除、遍历动画
  - 支持右键删除与节点高亮
- **栈 (Stack)**
  - 栈满 / 栈空状态提示
  - 压栈 / 出栈操作演示
- **队列 (Queue & Circular Queue)**
  - 循环队列可视化
  - 入队 / 出队逻辑优化
  - 队满 / 队空提示
- **通用**
  - 简洁的可视化界面
  - 操作即时反馈，提升学习体验

## 🛠️ 环境依赖

- Qt 5.12+ (建议 Qt 5.15 或更高版本)
- C++11 或以上标准
- 支持 Windows / Linux / macOS

## 🚀 使用方法

1. 克隆项目到本地：
   ```bash
   git clone https://github.com/yourname/DataStructureVisualizer.git
   cd DataStructureVisualizer

2. 使用 Qt Creator 或 qmake/cmake 打开项目：
     ```bash
    qmake && make
3.运行程序：



## 📖 版本更新

更新记录详见 [CHANGELOG.md](./CHANGELOG.md)

### 最近更新
**[1.2.0] - 2025-08-28**  
- 优化链表遍历与删除动画，高亮选中节点  
- 栈满与栈空提示逻辑优化  
- 循环队列 Data 层逻辑优化，可视化修复若干问题，操作体验提升  

---

## 📷 界面预览

![界面预览](images/preview.png)


---

## 📜 许可证

本项目基于 **MIT License** 开源，欢迎自由使用与二次开发。

