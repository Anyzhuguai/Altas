# 🤖 Atlas Robotics (Group 10)

> **Mission**: Developing the next-generation autonomous mobile robot with obstacle avoidance and precision manipulation capabilities.  
> **Project Manager**: Luyang Chen  
> **Timeline**: 2025 - 2026

---

## 📖 关于我们 (About Us)

**Atlas Robotics** 是一个专注于智能机器人研发的工程团队。我们的核心产品 **Atlas** 是一款集成了全向移动底盘与多自由度机械臂的复合型机器人。

我们的目标是通过软硬件的高度协同，实现从环境感知、路径规划到物体抓取的全流程自动化。

---

## 🏢 组织架构 (Team Structure)

我们的团队采用矩阵式管理，并使用 **Neo4j 知识图谱** 来管理人员、任务与交付物的复杂关系。

| 部门 (Department) | 核心职责 (Core Responsibilities) | 负责人 (Lead) |
| :--- | :--- | :--- |
| **Project Management** | 进度控制、资源分配、WBS 分解 | Luyang Chen |
| **Mechanical Eng.** | 结构设计、CAD 建模、3D 打印与组装 | Kun Chen |
| **Electrical Eng.** | 电路设计、PCB 布线、传感器选型 | Xikai Wang |
| **Software Dev.** | 嵌入式开发、算法实现、运动控制 | Xuehao Shi |
| **Design & Ops** | 网页设计、文档管理、对外展示 | Mingfeng Pan, Haifeng Xia |

> 🧠 **Knowledge Graph**: 我们的团队分工详情与任务依赖关系已存储于内部 Neo4j 图谱中。

---

## 📂 工程目录导航 (Repository Navigation)

本仓库采用模块化结构，请根据你的职能进入相应目录：

*   **`/Chen_Kun`** (Mechanical) 🛠️
    *   包含所有 STL 打印文件、SolidWorks 源文件、装配指南。
    *   *关键内容*: 底盘车架、机械臂结构。
*   **`/Software`** (Code) 💻
    *   包含 Python/C++ 控制代码、传感器驱动、算法库。
*   **`/Electrical`** (Hardware) ⚡
    *   包含电路原理图、接线图、BOM 清单。
*   **`/Docs`** (Documentation) 📄
    *   包含项目周报、WBS 表格、最终报告。

---

## 🛠️ 技术栈 (Tech Stack)

*   **Management**: Neo4j (Knowledge Graph), GitHub Projects, Excel (WBS)
*   **Mechanical**: SolidWorks, Fusion 360, Cura (3D Printing)
*   **Software**: Python, C++, ROS (Robot Operating System)
*   **Hardware**: Arduino/STM32, Lidar, Servos

---

## 🤝 工作流规范 (Workflow)

为了保证多人协作的顺畅，请所有成员遵守以下规则：

1.  **Branching (分支策略)**:
    *   严禁直接推送到 `main` 分支。
    *   新功能开发请创建分支：`feature/WBS-任务号-描述` (例如 `feature/WBS-2.1-chassis`)。
2.  **Commit Message**:
    *   请清晰描述修改内容，例如 `"Update: 优化了机械臂底座的壁厚"`。
3.  **Digital Twin**:
    *   重要的交付物（代码、图纸）上传后，请同步更新 Neo4j 图谱中的属性，保持物理世界与数字世界的同步。

---

## 🚀 快速开始 (Getting Started)

```bash
# 1. 克隆仓库
git clone https://github.com/Anyzhuguai/Atlas.git

# 2. 进入目录
cd Atlas

# 3. 查看对应部门的 README (例如机械组)
cat Chen_Kun/README.md
