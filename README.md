# 📂 Chen_Kun - Atlas Project Mechanical Engineering

> **Maintainer**: Kun Chen (Chief Mechanical Designer)  
> **Content Type**: 3D Printing Files (.stl) & Mechanical Design  
> **Last Updated**: 2026-01-05

## 📖 目录简介 (Overview)

本目录 **`Chen_Kun/`** 存放 Atlas 机器人的所有机械结构模型文件。核心工程分为“移动底盘”与“作业机械臂”两大模块。

所有文件均为 **STL 格式**，已完成公差调整，可直接导入切片软件（Cura/PrusaSlicer）进行 3D 打印。

---

## 📂 文件结构说明 (File Structure)

```text
Chen_Kun/
│
├── 📂 Chassis_System/         # 【底盘系统】车架与移动结构 (WBS 2.1)
│   ├── Main_Frame.stl        # 主车架主体 (承载电池与主控)
│   ├── Motor_Mount_L.stl     # 左侧电机固定座
│   ├── Motor_Mount_R.stl     # 右侧电机固定座
│   ├── Lidar_Bracket.stl     # 雷达/传感器支架
│   └── Caster_Wheel_Mount.stl# 万向轮连接件
│
└── 📂 Robotic_Arm_System/     # 【机械臂系统】抓取与自由度结构 (WBS 2.2)
    ├── Base_Rotator.stl      # 旋转底座 (连接底盘)
    ├── Arm_Link_Main.stl     # 主力臂
    ├── Servo_Horn_Adapter.stl# 舵机舵盘转接件
    ├── Gripper_Left.stl      # 机械爪-左指
    └── Gripper_Right.stl     # 机械爪-右指
