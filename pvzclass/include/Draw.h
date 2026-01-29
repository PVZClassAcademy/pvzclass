#pragma once
#include "../PVZ.h"

namespace PVZ
{ 
	class Font : public BaseClass
	{
	public:
		Font(uint32_t address) :BaseClass(address) {};
		INT_PROPERTY(mAscent, __get_mAscent, __set_mAscent, 0x4);
		INT_PROPERTY(mAscentPadding, __get_mAscentPadding, __set_mAscentPadding, 0x8);
		INT_PROPERTY(mHeight, __get_mHeight, __set_mHeight, 0xC);
		INT_PROPERTY(mLineSpacingOffset, __get_mLineSpacingOffset, __set_mLineSpacingOffset, 0x10);
	};
	class Graphics : public BaseClass
	{
	public:
		Graphics(uint32_t address) : BaseClass(address) {};
		/// @brief 缩放比例
		T_PROPERTY(float, ScaleX, __get_ScaleX, __set_ScaleX, 0x10);
		T_PROPERTY(float, ScaleY, __get_ScaleY, __set_ScaleY, 0x14);
		/// @brief 颜色
		INT_PROPERTY(Red, __get_Red, __set_Red, 0x30);
		INT_PROPERTY(Green, __get_Green, __set_Green, 0x34);
		INT_PROPERTY(Blue, __get_Blue, __set_Blue, 0x38);
		INT_PROPERTY(Alpha, __get_Alpha, __set_Alpha, 0x3C);
		/// @brief 获取Graphics使用的字体
		/// @return 字体
		Font GetFont();
		/// @brief 设置颜色
		void SetColor(int red, int green, int blue, int alpha = 0xFF);
		/// @brief 设置是否着色
		void SetColorizeImages(bool value);
		/// @brief 设置裁剪矩形
		/// @note 参数 x 和 y 采用以自身的偏移坐标为参考的相对坐标
		void ClipRect(int x, int y, int width, int height);
		/// @brief 在指定位置绘制字体
		/// @param just 文本的对齐方式：0(左对齐)|1(右对齐)|2(居中对齐)|3(左对齐，垂直居中)|4(右对齐，垂直居中)|5(完全居中)
		void DrawString(int x, int y, PVZString str, Font font, int just, int r, int g, int b, int a);
		/// @brief 在指定坐标绘制图片
		/// @param image 绘制的图片
		/// @param x X 坐标
		/// @param y Y 坐标
		void DrawImage(PVZ::Image image, int x, int y);
		/// @brief 在指定位置绘制一条线
		void DrawLine(int start_x, int start_y, int end_x, int end_y);
		/// @brief 绘制空心矩形
		void DrawRect(int x, int y, int width, int height);
		/// @brief 绘制实心矩形
		void FillRect(int x, int y, int width, int height);
		/// @brief 绘制Edit的黄色输入框背景
		void DrawTextBox(DWORD edit);
		/// @brief 绘制动画缓存的僵尸贴图，若无缓存的贴图则会制取贴图并写入缓存。
		/// @param cache 为 PVZApp 中的 ReanimatorCache
		void DrawZombie(ZombieType::ZombieType type, float x, float y, DWORD cache);
		/// @brief 在指定坐标拉伸地绘制贴图。拉伸原点为贴图左上顶点。
		/// @param image 绘制的图片
		/// @param x X 坐标
		/// @param y Y 坐标
		/// @param scale_x X 方向拉伸
		/// @param scale_y Y 方向拉伸
		void TodDrawImageScaledF(PVZ::Image image, float x, float y, float scale_x, float scale_y);
		/// @brief 在指定坐标拉伸地绘制贴图。拉伸原点为贴图中心。
		/// @param image 绘制的图片
		/// @param x X 坐标
		/// @param y Y 坐标
		/// @param scale_x X 方向拉伸
		/// @param scale_y Y 方向拉伸
		void TodDrawImageCenterScaledF(PVZ::Image image, float x, float y, float scale_x, float scale_y);
		/// @brief 在指定坐标拉伸地绘制分割贴图。
		/// @param row 分割贴图的行
		/// @param col 分割贴图的列
		void TodDrawImageCelScaledF(PVZ::Image image, float x, float y, float scale_x, float scale_y, int row, int col);
	};
}

// 请与DrawUITopEvent配合使用
namespace Draw
{
	typedef DWORD PSharedImageRef;
	typedef DWORD PImage;

	// 将字符串转化为字符数组
	char* ToChar(PVZ::PVZString str);

	// 加载字体，由于汉化版的特殊处理，这个函数实际上调用的是计算字符串长度
	void StringWidth(PVZ::PVZString str, DWORD imageFontAddress);

	// 从指定路径加载图像文件
	// isnewAddress存放了这个图像文件是否已经存在
	PSharedImageRef GetSharedImage(DWORD isnewAddress, PVZ::PVZString variant, PVZ::PVZString filename);

	// 将sharedImageRef转换为Image*返回
	PImage SharedImageRefToImage(PSharedImageRef imageRef);

	// 释放图像文件资源
	void FreeImage(PSharedImageRef imageRef);

	// 在指定位置绘制字体
	void DrawString(DWORD x, DWORD y, PVZ::PVZString str, DWORD graphics);
}