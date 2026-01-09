# 📂 Chen_Kun - Atlas Project Mechanical Design

> **Maintainer**: Chen Kun (Mechanical Designer)  
> **System**: Mechanical Structure & 3D Models  
> **Status**: Development & Prototyping

## 📖 简介 (Introduction)
本分支（`Chen_Kun`）主要负责 Atlas 机器人的机械结构设计与 3D 打印文件管理。包含机械臂的各个关节组件以及车架底盘的制造文件。

## 📂 文件目录说明 (File Structure)

### 1. 🦾 机械臂系统 (Robotic Arm System)
路径: `/机械臂stl文件`

该目录包含机械臂的所有打印组件，采用 STL 格式。

| 文件名 (Filename) | 描述 (Description) | 备注 (Notes) |
| :--- | :--- | :--- |
| **`base_updated.stl`** | **底座 (升级版)** | ✅ 推荐打印此版本，结构更稳固 |
| `base.stl` | 底座 (旧版) | 仅作备份，不建议使用 |
| `base_attach.stl` | 底座连接件 | 用于将机械臂固定到底盘 |
| **`first_arm.stl`** | **大臂 (第一臂)** | 机械臂主臂结构 |
| **`second_arm.stl`** | **小臂 (第二臂)** | 机械臂副臂结构 |
| `arm_gear.stl` | 大臂传动齿轮 | 负责关节传动 |
| `arm_servo_gear.stl` | 舵机齿轮 | 直接连接舵机输出轴 |
| `arduino_cover.stl` | 主控板保护壳 | 用于保护 Arduino 开发板 |
| `cube.stl` | 测试方块 | 用于测试机械臂抓取精度的校准物 |
| `scivolo.stl` | 滑轨/导向件 | 机械结构辅助件 |

### 2. 🏎️ 车架底盘系统 (Chassis System)
路径: `/车架stl文件`

| 文件名 (Filename) | 描述 (Description) | 备注 (Notes) |
| :--- | :--- | :--- |
| **`1.3mf`** | **车架整体工程文件** | ⚠️ 这是一个 3MF 格式文件，包含了车架的模型、甚至可能包含切片设置。请使用 PrusaSlicer 或 Bambu Studio 打开。 |

---

## 🛠️ 打印建议 (Printing Guide)

*   **材料 (Material)**: 建议使用 **PLA+** 或 **PETG** 以获得更好的结构强度。
*   **填充 (Infill)**: 
    *   受力部件（如 `first_arm`, `base_updated`）建议 **30% - 50%**。
    *   装饰或保护部件（如 `arduino_cover`）可使用 **15% - 20%**。
*   **支撑 (Supports)**: 
    *   `first_arm` 和 `second_arm` 悬空部位较多，**建议开启树状支撑 (Tree Supports)**。

## 📝 更新日志 (Changelog)
*   **Update**: 上传了机械臂的全套 STL 文件。
*   **Fix**: 更新了底座模型为 `base_updated.stl`，修复了安装孔位问题。
*   **Add**: 添加了车架的 `.3mf` 整合文件。
