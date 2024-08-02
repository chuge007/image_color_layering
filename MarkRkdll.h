#ifndef MARKRKDLL_H
#define MARKRKDLL_H
#include <Windows.h>//#include <QWidget>

//所有函数都返回一个整形值
#define RKLM_ERR_SUCCESS         0  //成功
#define RKLM_ERR_RKCADRUN        1  //发现RKCAD在运行
#define RKLM_ERR_NOFINDCFGFILE   2  //找不到RKCAD配置文件
#define RKLM_ERR_FAILEDOPEN      3  //打开RKLM失败
#define RKLM_ERR_NODEVICE        4  //没有有效的RKLM设备
#define RKLM_ERR_HARDVER         5  //RKLM版本错误
#define RKLM_ERR_DEVCFG          6  //找不到设备配置文件
#define RKLM_ERR_STOPSIGNAL      7  //报警信号
#define RKLM_ERR_USERSTOP        8  //用户停止
#define RKLM_ERR_UNKNOW          9  //不明错误
#define RKLM_ERR_OUTTIME         10 //超时
#define RKLM_ERR_NOINITIAL       11 //未初始化
#define RKLM_ERR_READFILE        12 //读文件错误
#define RKLM_ERR_OWENWNDNULL     13 //窗口为空
#define RKLM_ERR_NOFINDFONT      14 //找不到指定名称的字体
#define RKLM_ERR_PENNO           15 //错误的笔号
#define RKLM_ERR_NOTTEXT         16 //指定名称的对象不是文本对象
#define RKLM_ERR_SAVEFILE        17 //保存文件失败
#define RKLM_ERR_NOFINDENT       18 //找不到指定对象
#define RKLM_ERR_STATUE          19 //当前状态下不能执行此操作
#define RKLM_ERR_PARAM           20 //参数错误
#define RKLM_ERR_DEVICE          21 //硬件错误

//初始化RKLM控制卡
//输入参数: rkcadPath  RKCad软件的执行路径
//          isTestMode=true 表示测试模式  isTestMode=false 表示正常模式，默认true
//          owenWnd  表示父窗口对象，如果需要实现停止打标，则系统会从此窗口截取消息
typedef int(*RKLM_INITIAL)(char* rkcadPath,//rkcad的工作目录
                           bool isTestMode,//是否是测试模式
                           HWND owenWnd);//父窗口

//显示RKCAD主界面UI
typedef int(*RKLM_SETVISIBLE)(bool visible);

//关闭RKLM控制卡
typedef int(*RKLM_CLOSE)();

//调用设置设备参数的对话框
typedef int(*RKLM_SETDEVCFG)();

//调用设置设备参数的对话框,显示扩展轴参数
typedef int(*RKLM_SETDEVCFG2)(bool isAxisShow0, bool isAxisShow1);

//调用设置设备参数的对话框,显示IO端口参数
typedef int(*RKLM_SETDEVCFG3)();

//调用设置设备参数的对话框,显示校正参数
typedef int(*RKLM_SETDEVCFG4)();

//标刻当前数据库里的所有数据
//输入参数: isFlyMark=true 使能飞动打标  isFlyMark=false 使能飞动打标
//此函数一直等待设备加工完毕后，或者用户停止才返回。即函数结束表示加工结束
typedef int(*RKLM_MARK)(bool isFlyMark);

//多位置旋转偏移标刻
//输入参数: cmdstr格式: [entName,times,x1,y1,angle1,x2,y2,angle2,...]
//entName 要加工的指定对象的名称 times:执行次数 ptBuf:对象中心点坐标x,y旋转角度angle
//此函数一直等待设备加工完毕后，或者用户停止才返回。即函数结束表示加工结束
typedef int(*RKLM_PRMMMARK)(char* cmdstr);

//多对象旋转偏移标刻
//输入参数: cmdstr格式: [times,entName1,x1,y1,angle1,entName2,x2,y2,angle2,...]
//entName 要加工的指定对象的名称 times:执行次数 ptBuf:对象中心点坐标x,y旋转角度angle
//此函数一直等待设备加工完毕后，或者用户停止才返回。即函数结束表示加工结束
typedef int(*RKLM_ORMMMARK)(char* cmdstr);

//多点校正视觉录入
typedef int (*RKLM_VISIONPOINTSINPUT)(int pointcnt, double ptBuf[][2]);

//标刻当前数据库里的指定对象
//输入参数: entName 要加工的指定对象的名称
//此函数一直等待设备加工完毕后才返回
typedef int(*RKLM_MARKENTITY)(char* entName);

//标刻指定线段
//输入参数 x1,y1起点坐标，x2y2终点坐标，pen 使用的笔号
typedef int(*RKLM_MARKLINE)(double x1, double y1, double x2, double y2, int pen);

//标刻指定点
//输入参数 x,y点坐标，delay打标时间，pen 使用的笔号
typedef int(*RKLM_MARKPOINT)(double x, double y, double delay, int pen);

//标刻指定的多个点
//输入参数 ptBuf点坐标组；ptBuf[n][0]表示第n个点的x坐标
//ptBuf[n][1]表示第n个点的y坐标，pen 使用的笔号
//laserOnTimeMs点的打标时间，单位ms
typedef int(*RKLM_MARKPOINTBUF2)(double ptBuf[][2], double laserOnTimeMs, int pen);

//判断卡正在处于工作状态
typedef int(*RKLM_ISMARKING)();

//强制停止当前标刻
typedef int(*RKLM_STOPMARK)();

//标刻一次红光显示框
//预览一次全部对象的打标范围,即数据的包围盒
typedef int(*RKLM_REDLIGHTMARK)();

//红光预览当前数据库里面所有数据轮廓一次
//预览轨迹与打标轨迹一致。如果预览圆，轨迹就是一个圆
typedef int(*RKLM_REDLIGHTMARKCONTOUR)();

//红光预览当前数据库里面指定对象
//输入参数 entName对象名称;isContour显示的是否是轮廓，true显示轮廓，false显示范围
typedef int(*RKLM_REDLIGHTMARKBYENT)(char* entName, bool isContour);

//载入rkq文件，并清除数据库所有对象
//输入参数: fileName  RKCad文件名称
typedef int(*RKLM_LOADRKQFILE)(char* fileName);

//保存当前数据库里所有对象到指定rkq文件里
//输入参数: fileName rkq文件名称
typedef int(*RKLM_SAVEENTLIBTOFILE)(char* fileName);


//得到当前数据库里的所有数据的预览图像
//输入参数: hwnd需要显示当前图像的窗口句柄,BMPWidth 需要生成的图像的像素宽度,BMPHeight
//在程序中调用RKLM_getprevbitmap得到当前数据库里的所有对象的预览图像的指针，可以用于更新界面显示
typedef  HBITMAP* (*RKLM_GETPREVBITMAP)(HWND hwnd, int BMPWidth, int BMPHeight);

//得到当前数据库里的指定对象数据的预览图像
//输入参数: hwnd         预览图像显示到哪个窗口
//         BMPWidth    预览图像的宽度
//         BMPHeight   预览图像的高度
//         entName   指定对象的名称
typedef  HBITMAP* (*RKLM_GETPREVBITMAPBYNAME)(char* entName, HWND hwnd, int BMPWidth, int BMPHeight);


//得到指定对象的最大最小坐标,如果entName==NULL表示读取数据库所有对象的最大最小坐标
typedef int(*RKLM_GETENTSIZE)(char* entName,    //字符串对象名称
                              double& dMinx,    //最小x坐标
                              double& dMiny,    //最小y坐标
                              double& dMaxx,    //最大x坐标
                              double& dMaxy,    //最大y坐标
                              double& dZ);      //对象的z坐标

//移动指定对象相对坐标
typedef int(*RKLM_MOVEENT)(char* entName,   //字符串对象名称
                           double dMovex,   //对象移动x距离
                           double dMovey);  //对象移动y距离

//缩放指定对象，
typedef int(*RKLM_SCALEENT)(char* entName,  //字符串对象名称
                            double dCenx,   //缩放的X中心
                            double dCeny,   //缩放的Y中心
                            double dScaleX, //缩放的X比例
                            double dScaleY);//缩放的Y比例

//镜像指定对象
typedef  int(*RKLM_MIRRORENT)(char* entName,    //字符串对象名称
                              double dCenx,     // 镜像的X中心
                              double dCeny,     //镜像的Y中心
                              bool   bMirrorX,  //是否X方向镜像，true表示镜像
                              bool   bMirrorY); //是否Y方向镜像，true表示镜像

//旋转指定对象
typedef  int(*RKLM_ROTATEENT)(char* entName,    //字符串对象名称
                              double dCenx,     //旋转的X中心
                              double dCeny,     //旋转的Y中心
                              double dAngle);   //旋转的角度，(逆时针为正，单位为度)

//复制粘贴指定对象，并对新对象命名
//输入参数：PEntName要复制的对象，newEntName复制后的对象名称
typedef int(*RKLM_COPYENT)(char* entName, char* newEntName);

//得到当前数据库中的对象总数
//输出参数:  对象总数
typedef  int(*RKLM_GETENTITYCOUNT)();

//得到指定序号的对象名称
//输入参数: entityIndex 指定对象的序号(范围: 0 － (RKLM_GetEntityCount()-1))
//输出参数: szEntName 对象的名称
typedef int(*RKLM_GETENTITYNAME)(int entityIndex, char szEntName[256]);

//设置指定序号的对象名称
typedef int(*RKLM_SETENTITYNAME)(int entityIndex, char* entName);

//修改对象名称
typedef int(*RKLM_CHANGEENTNAME)(char* entName, char* newEntName);

//设置旋转变换参数
//输入参数: dCenterX 旋转中心x坐标
//          dCenterY 旋转中心y坐标
//          dRotateAng 旋转角度(弧度值)
//typedef void(*RKLM_SETROTATEPARAM)(double dCenterX, double dCenterY, double dRotateAng);

//设置旋转变换参数 不影响数据的显示,只是加工时才对对象进行旋转。
//typedef void(*RKLM_SETROTATEMOVEPARAM)( double dMoveX,//X方向移动距离
//                                        double dMoveY,//Y方向移动距离
//                                        double dCenterX, //旋转中心X坐标
//                                        double dCenterY,//旋转中心Y坐标
//                                        double dRotateAng); //旋转角度(弧度值)

//更改当前数据库里的指定文本对象的文本
//输入参数: textEntName     要更改内容的文本对象的名称
//          strTextNew      新的文本内容
typedef int(*RKLM_CHANGETEXTBYNAME)(char* textEntName, char* strTextNew);

//得到指定对象的文本
//textEntName     要获取内容的文本对象的名称,szEntText  文本内容
typedef int(*RKLM_GETTEXTBYNAME)(char* textEntName, char strText[256]);

//序列号复位为开始序号
//输入参数：textEntName文本对象名称
typedef int(*RKLM_TEXTRESETSN)(char* textEntName);

//群组2个对象，并设置群组新的对象名称，以及笔号
typedef int(*RKLM_GROUPENT)(char* entName1,     //群组对象1名称
                            char* entName2,     //群组对象2名称
                            char* entNameNew,   //群组后新对象名称
                            int pen);           //新对象使用的笔号

//解散群组
//输入参数：grouentName群组对象名称
typedef int(*RKLM_UNGROUPENT)(char* grouentName);

//群组N个对象，并设置群组新的对象名称，以及笔号
typedef int(*RKLM_GROUPENT2)(char** entNameList, //对象名称列表
                             int entCount,       //群组对象数量
                             char* groupName,    //群组后对象名
                             int groupPen);      //新对象使用的笔号

//彻底解散群组对象为曲线
typedef int(*RKLM_UNGROUPENT2)(char* grouentName,//群组对象名称
                               int nFlag);       //标志位，默认=0

//向前移动对象
typedef int(*RKLM_MOVEENTITYBEFORE)(int moveEnt, //要移动的对象在对象列表中的位置
                                    int goalEnt); //对象要在对象列表中移动到的位置

//向后移动对象
typedef int(*RKLM_MOVEENTITYAFTER)(int moveEnt,    //要移动的对象在对象列表中的位置
                                   int goalEnt);    //对象要在对象列表中移动到的位置

//颠倒所有对象在对象列表中的顺序
typedef int(*RKLM_REVERSEALLENTORDER)();

//获取指定位图的参数
typedef int(*RKLM_GETBITMAPENTPARAM)(char*    entName,          //位图对象名称
                                     char     BmpPath[256],     //位图对象路径
                                     bool&    isReverse,        //灰度反转
                                     bool&    isMirrorX,        //镜像X
                                     bool&    isMirrorY,        //镜像Y
                                     int&     minMarkGreyValue, //灰度值以下不标刻[0, 255]
                                     int&     markMethod,       //标刻模式 0:单点 1:半色调 2:二值化 3:动态功率模式
                                     int&     hatchMethod,      //填充模式 0:弓形 1:双向 2:回形 3:螺旋
                                     double&  angle,            //填充模式 0:弓形 1:双向 2:回形 3:螺旋
                                     int&     thrshould);       //阈值

//设置指定位图的参数
typedef int(*RKLM_SETBITMAPENTPARAM)(  char*   entName,          //位图对象名称
                                       char    BmpPath[256],     //位图对象路径
                                       bool    isReverse,        //灰度反转
                                       bool    isMirrorX,        //镜像X
                                       bool    isMirrorY,        //镜像Y
                                       int     minMarkGreyValue, //灰度值以下不标刻[0, 255]
                                       int     markMethod,       //标刻模式 0:单点 1:半色调 2:二值化 3:动态功率模式
                                       int     hatchMethod,      //填充模式 0:弓形 1:双向 2:回形 3:螺旋
                                       double  angle,            //填充模式 0:弓形 1:双向 2:回形 3:螺旋
                                       int     thrshould);       //阈值

//获取指定文本的字体参数
typedef int(*RKLM_GETTEXTENTPARAM)(char*    textName,      //文本名称
                                   char     fontName[256], //字体名称
                                   double&  charWidthRatio,//字符宽度
                                   double&  charHeight,    // 字符高度
                                   int&     textSpaceMode, //文本间距模式
                                   double&  charSpace,     //字符间距
                                   double&  lineSpace,     //行间距
                                   int&     textAlign,     //文本对齐方式
                                   int&     direction,     //文本排列方向 0:横向 1:竖向
                                   bool&    isBold,        //粗体
                                   bool&    isItalic);     //斜体

//设置指定文本的字体参数
typedef int(*RKLM_SETTEXTENTPARAM)(char*    textName,      //文本名称
                                   char     fontName[256], //字体名称
                                   double   charWidthRatio,//字符宽度
                                   double   charHeight,    //字符高度
                                   int      textSpaceMode, //文本间距模式
                                   double   charSpace,     //字符间距
                                   double   lineSpace,     //行间距
                                   int      textAlign,     //文本对齐方式
                                   int      direction,     //文本排列方向 0:横向 1:竖向
                                   bool     isBold,        //粗体
                                   bool     isItalic);     //斜体


//删除对象库里指定对象
typedef int(*RKLM_DELETEENT)(char* entName);

//清除对象库里所有数据
typedef int(*RKLM_CLEARENTLIB)();

//对齐方式时数字代表的意义
//   6 ---  5 --- 4
//   |            |
//   |            |
//   7      8     3
//   |            |
//   |            |
//   0 ---  1 --- 2
//加入新文本到数据库中
typedef int(*RKLM_ADDTEXTTOLIB)(char* pStr,         //要添加的字符串
                                char* entName,      //字符串对象名称
                                double dPosX,       //字符串的左下角基点的x坐标
                                double dPosY,       //字符串的左下角基点的y坐标
                                double dPosZ,       //字符串对象的z坐标
                                int    nAlign,      //对齐方式0－8
                                double textRotateAngle,//字符串绕基点旋转的角度值(弧度值)
                                int nPenNo,         //对象使用的加工参数
                                bool bHatchText);   //是否填充文本对象

#define CIRTEXTFLAG_REVERSE  	0x0001	//反转
#define CIRTEXTFLAG_UPDOWN  	0x0002	//上下反转

//添加圆弧文本
typedef int(*RKLM_ADDCIRCLETEXTTOLIB)(char* pStr,//要添加的字符串
                                      char* entName,//字符串对象名称
                                      double dPosX,//文本所在基准圆的x坐标
                                      double dPosY,//文本所在基准圆的y坐标
                                      double dPosZ,//字符串对象的z坐标
                                      int nPenNo,//文本对象使用的笔号
                                      int bHatchText,//是否填充文本
                                      double dCirDiameter,//基准圆直径
                                      double dCirBaseAngle,//文字基准角度
                                      bool bCirEnableAngleLimit,//是否使能角度限制
                                      double dCirAngleLimit, //限制的角度
                                      bool   isreverse,     //文字反排
                                      bool   ishandstand,   //文字倒立
                                      int    arcmode);      //0:圆弧外侧分布 1:圆弧内侧分布

//获得指定圆弧文本对象的参数
typedef int(*RKLM_GETCIRCLETEXTPARAM)(  char* entName,//字符串对象名称
                                        double& dCenX,//文本所在基准圆的x坐标
                                        double& dCenY,//文本所在基准圆的y坐标
                                        double &dCenZ,//字符z坐标
                                        double& dCirDiameter,//基准圆直径
                                        double& dCirBaseAngle,//文字基准角度
                                        bool& bCirEnableAngleLimit,//是否使能角度限制
                                        double & dCirAngleLimit,//限制的角度
                                        bool&   isreverse,     //文字反排
                                        bool&   ishandstand,   //文字倒立
                                        int&    arcmode);      //0:圆弧外侧分布 1:圆弧内侧分布

//设置指定圆弧文本对象的参数
typedef int(*RKLM_SETCIRCLETEXTPARAM)(  char* entName,//字符串对象名称
                                        double dCenX,//文本所在基准圆的x坐标
                                        double dCenY,//文本所在基准圆的y坐标
                                        double dCenZ,//字符z坐标
                                        double dCirDiameter,//基准圆直径
                                        double dCirBaseAngle,//文字基准角度
                                        bool bCirEnableAngleLimit,//是否使能角度限制
                                        double dCirAngleLimit,//限制的角度
                                        bool   isreverse,     //文字反排
                                        bool   ishandstand,   //文字倒立
                                        int    arcmode);      //0:圆弧外侧分布 1:圆弧内侧分布

//加入指定文件到数据库中
//支持的文件有rkq,dxf,plt,ai,dwg,bmp,jpg,png,gif等
typedef int(*RKLM_ADDFILETOLIB)(char* fileName,     //文件名称
                                char* entName,      //字符串对象名称
                                double dPosX,       //文件左下角基点x坐标
                                double dPosY,       //文件左下角基点y坐标
                                double dPosZ,       //文件z坐标
                                int    nAlign,      //对齐方式0－8
                                double dRatio,      //文件缩放比例
                                int nPenNo,         //对象使用的加工笔号参数
                                bool bHatchFile);   //是否填充文件对象 如果是位图文件此参数无效

//加入曲线到数据库中
typedef int(*RKLM_ADDCURVETOLIB)(double ptBuf[][2], //曲线顶点数组
                                 int  ptNum,        //曲线顶点数
                                 char* entName,     //曲线对象名称
                                 int nPenNo,        //曲线对象使用的笔号
                                 int bHatch);       //曲线是否填充

//加入一组点到数据库中
typedef int(*RKLM_ADDCURVETOLIB2)(double* ptBuf,//曲线顶点数组
                                  int  ptNum,//曲线顶点数
                                  char* entName,//曲线对象名称
                                  int nPenNo,//曲线对象使用的笔号
                                  int bHatch);//曲线是否填充

//加入延时到数据库中
//输入参数：延时时长，单位ms
typedef int(*RKLM_ADDDELAYTOLIB)(double dDelayMs);

//加入输出口到数据库中
typedef int(*RKLM_ADDWRITEPORTTOLIB)(int nOutPutBit,//输出口的值，0到15
                                     bool bHigh, //是否是高电平
                                     bool bPluse, //是否是脉冲
                                     double dPulseTimeMs);//脉冲长的，单位ms

#define BARCODETYPE_39      0
#define BARCODETYPE_93      1
#define BARCODETYPE_128A    2
#define BARCODETYPE_128B    3
#define BARCODETYPE_128C    4
#define BARCODETYPE_128OPT  5
#define BARCODETYPE_EAN128A 6
#define BARCODETYPE_EAN128B 7
#define BARCODETYPE_EAN128C 8
#define BARCODETYPE_EAN13   9
#define BARCODETYPE_EAN8    10
#define BARCODETYPE_UPCA    11
#define BARCODETYPE_UPCE    12
#define BARCODETYPE_25      13
#define BARCODETYPE_INTER25 14
#define BARCODETYPE_CODABAR 15
#define BARCODETYPE_PDF417  16
#define BARCODETYPE_DATAMTX 17
#define BARCODETYPE_USERDEF  18
#define BARCODETYPE_QRCODE 19
#define BARCODETYPE_MINIDATAMTX  20

#define BARCODEATTRIB_REVERSE          0x0008 //条码反转
#define BARCODEATTRIB_HUMANREAD        0x1000 //显示人识别字符
#define BARCODEATTRIB_CHECKNUM         0x0004 //需要校验码
#define BARCODEATTRIB_PDF417_SHORTMODE 0x0040 //PDF417为缩短模式
#define BARCODEATTRIB_DATAMTX_DOTMODE  0x0080 //DataMtrix为点模式
#define BARCODEATTRIB_CIRCLEMODE       0x0100 //自定义二维码为圆模式

#define DATAMTX_SIZEMODE_SMALLEST  0
#define DATAMTX_SIZEMODE_10X10     1
#define DATAMTX_SIZEMODE_12X12     2
#define DATAMTX_SIZEMODE_14X14     3
#define DATAMTX_SIZEMODE_16X16     4
#define DATAMTX_SIZEMODE_18X18     5
#define DATAMTX_SIZEMODE_20X20     6
#define DATAMTX_SIZEMODE_22X22     7
#define DATAMTX_SIZEMODE_24X24     8
#define DATAMTX_SIZEMODE_26X26     9
#define DATAMTX_SIZEMODE_32X32     10
#define DATAMTX_SIZEMODE_36X36     11
#define DATAMTX_SIZEMODE_40X40     12
#define DATAMTX_SIZEMODE_44X44     13
#define DATAMTX_SIZEMODE_48X48     14
#define DATAMTX_SIZEMODE_52X52     15
#define DATAMTX_SIZEMODE_64X64     16
#define DATAMTX_SIZEMODE_72X72     17
#define DATAMTX_SIZEMODE_80X80     18
#define DATAMTX_SIZEMODE_88X88     19
#define DATAMTX_SIZEMODE_96X96     20
#define DATAMTX_SIZEMODE_104X104   21
#define DATAMTX_SIZEMODE_120X120   22
#define DATAMTX_SIZEMODE_132X132   23
#define DATAMTX_SIZEMODE_144X144   24
#define DATAMTX_SIZEMODE_8X18     25
#define DATAMTX_SIZEMODE_8X32     26
#define DATAMTX_SIZEMODE_12X26     27
#define DATAMTX_SIZEMODE_12X36     28
#define DATAMTX_SIZEMODE_16X36     29
#define DATAMTX_SIZEMODE_16X48     30

//加入条码到数据库中
typedef int(*RKLM_ADDBARCODETOLIB)( char* pStr,	//字符串
                                    char* entName,//字符串对象名称
                                    double posX,    //字符左下角基点x坐标
                                    double posY,    //字符左下角基点y坐标
                                    double posZ,    //字符z坐标
                                    int    align,   //对齐方式0－8
                                    int    penNo,
                                    int    isHatchBarcode,
                                    int    barcodeType,             //条码类型
                                    unsigned short wBarCodeAttrib,  //条码属性
                                    double height,                  //整个条码的高
                                    double narrowWidth,             //最窄模块宽
                                    double barWidthScale[4],        //条宽比例(与最窄模块宽相比)
                                    double spaceWidthScale[4],      //空宽比例(与最窄模块宽相比)
                                    double midCharSpaceScale,       //字符间隔比例(与最窄模块宽相比)
                                    double quietLeftScale,          //条码左空白宽度比例(与最窄模块宽相比)
                                    double quietRightScale,         //条码右空白宽度比例(与最窄模块宽相比)
                                    double quietTopScale,           //条码上空白宽度比例(与最窄模块宽相比)
                                    double quietBottomScale,        //条码下空白宽度比例(与最窄模块宽相比)
                                    int    row,                     //二维码行数
                                    int    col,                     //二维码列数
                                    int    checkLevel,              //pdf417错误纠正级别0-8
                                    int    sizeMode,                //DataMatrix尺寸模式0-30
                                    int    fillIndex,               //模块填充方式 0:无 1:点 2:圆 3:矩形
                                    int modulePercent,              //模块占比
                                    double textHeight,              //人识别字符字体高度
                                    double textWidth,               //人识别字符字体宽度
                                    double textOffsetX,             //人识别字符X方向偏移
                                    double textOffsetY,             //人识别字符Y方向偏移
                                    double textSpace,               //人识别字符间距
                                    char* textFontName);            //文本字体名称

//获取条码参数
typedef int(*RKLM_GETBARCODEPARAM)( char* entName,//对象名称
                                    unsigned short&wBarCodeAttrib,//条码属性
                                    int& nSizeMode,//尺寸模式
                                    int& nCheckLevel,//错误纠正级别
                                    int& nLangPage,//语言编码页
                                    int& fillIndex,      //模块填充方式 0:无 1:点 2:圆 3:矩形
                                    int& modulePercent); //模块占比

//语言编码                   int
//Default                     0
//ANSI(7Bit 1252)             437
//Latin - 1(ISO 8859 - 1)          850
//Japanese(SHIFT - JIS, 932)      932
//Korea(Hangul, 949)           949
//Simple Chinses(GB2312, 936)   936
//Trad chinese(BIG5, 950)       950
//UNICODE(UTF8)            65001

//设置条码参数
typedef int(*RKLM_SETBARCODEPARAM)( char* entName,//对象名称
                                    unsigned short  wBarCodeAttrib,//条码属性
                                    int  nSizeMode,// 尺寸模式
                                    int  nCheckLevel,//错误纠正级别
                                    int  nLangPage,//语言编码页
                                    int fillIndex,      //模块填充方式 0:无 1:点 2:圆 3:矩形
                                    int modulePercent); //模块占比


// 读RKLM的输入端口
//输入参数: 读入的输入端口的数据
typedef int(*RKLM_READPORT)(unsigned short& data);

// 读RKLM的输出端口
//输入参数: 读入的输出端口的数据
typedef int(*RKLM_GETOUTPORT)(unsigned short& data);

// 写RKLM的输出端口
//输入参数: 要写到的输出端口的数据
typedef int(*RKLM_WRITEPORT)(unsigned short data);


const int HATCHATTRIB_ALLCALC = 0x01;//全部对象整体计算
const int HATCHATTRIB_EDGE = 0x02;//绕边走一次
const int HATCHATTRIB_MINUP = 0x04;//最少起笔
const int HATCHATTRIB_BIDIR = 0x08;//双向填充
const int HATCHATTRIB_LOOP = 0x10;//环行填充
const int HATCHATTRIB_OUT = 0x20;//环行由内向外
const int HATCHATTRIB_AUTOROT = 0x40;//自动角度旋转
const int HATCHATTRIB_AVERAGELINE = 0x80;//自动分布填充线
const int HATCHATTRIB_CROSELINE = 0x400;//交叉填充

typedef int(*RKLM_GETHATCHPARAM3)(int   paramIndex,            //填充参数序号值为1,2,3
                                  int&  enableHatch,           //使能填充
                                  int&  penNo,                 //填充参数笔号
                                  int&  hatchType,             //填充类型 0单向 1双向 2弓形 3弓形优化
                                  bool& enableContour,         //使能轮廓本身
                                  bool& hatchAllCalc,          //是否全部对象作为整体一起计算
                                  bool& hatchEdge,             //绕边一次
                                  bool& contourFirst,          //轮廓优先
                                  bool& isHatchCross,          //交叉填充
                                  bool& hatchAverageLine,      //平均分布填充线
                                  double& hatchLineDist,       //填充线间距
                                  double& hatchEdgeDist,       //填充线边距
                                  double& hatchAngle);         //填充线角度


typedef int(*RKLM_SETHATCHPARAM3)(int   paramIndex,           //填充参数序号值为1,2,3
                                  int  enableHatch,           //使能填充
                                  int  penNo,                 //填充参数笔号
                                  int  hatchType,             //填充类型 0单向 1双向 2弓形 3弓形优化
                                  bool enableContour,         //使能轮廓本身
                                  bool hatchAllCalc,          //是否全部对象作为整体一起计算
                                  bool hatchEdge,             //绕边一次
                                  bool contourFirst,          //轮廓优先
                                  bool isHatchCross,          //交叉填充
                                  bool hatchAverageLine,      //平均分布填充线
                                  double hatchLineDist,       //填充线间距
                                  double hatchEdgeDist,       //填充线边距
                                  double hatchAngle);         //填充线角度

typedef int(*RKLM_GETHATCHENTPARAM2)(char* HatchName,
                                     int nParamIndex,
                                     int& bEnableHatch,
                                     int& nPenNo,
                                     int& nHatchType,
                                     bool& bEnableContour,
                                     bool&  bContourFirst,
                                     bool& bHatchAllCalc,
                                     bool& bHatchEdge,
                                     bool& isHatchCross,          //交叉填充
                                     bool& bHatchAverageLine,
                                     double& dHatchLineDist,
                                     double& dHatchEdgeDist,
                                     double& hatchAngle);


typedef int(*RKLM_SETHATCHENTPARAM2)(char* HatchName,
                                     int nParamIndex,
                                     int bEnableHatch,
                                     int nPenNo,
                                     int nHatchType,
                                     bool bEnableContour,
                                     bool  bContourFirst,
                                     bool bHatchAllCalc,
                                     bool bHatchEdge,
                                     bool isHatchCross,          //交叉填充
                                     bool bHatchAverageLine,
                                     double dHatchLineDist,
                                     double dHatchEdgeDist,
                                     double hatchAngle);

typedef int(*RKLM_HATCHENT)(char*  entName, char*  strHatchEntName);
typedef int(*RKLM_UNHATCHENT)(char*  strHatchEntName);


//获取当前默认的字体参数
typedef int(*RKLM_GETFONTPARAM3)(char*     fontName,   //字体名称
                                 double&   charWidth,  //字体宽度
                                 double&   charHeight, //字符高度
                                 double&   lineSpacingFactor,  //行间距
                                 double&   letterSpacing,//字符间距
                                 int&      textAlign,    //文本对齐方式 4:左对齐 5:中心对齐 6:右对齐
                                 int&      textDirection,//文本朝向 0:从左到右 1:从上到下
                                 int&      sizeMode, //字符间距模式 2:auto 3:字符边缘间距 4:字符中心间距模式
                                 bool&     bBold,    //粗体
                                 bool&     bItalic);  //斜体

//设置当前默认的字体参数
typedef int(*RKLM_SETFONTPARAM3)(char*    fontName,   //字体名称
                                 double   charWidth,  //字体宽度
                                 double   charHeight, //字符高度
                                 double   lineSpacingFactor,  //行间距
                                 double   letterSpacing,//字符间距
                                 int      textAlign,    //文本对齐方式 4:左对齐 5:中心对齐 6:右对齐
                                 int      textDirection,//文本朝向 0:从左到右 1:从上到下
                                 int      sizeMode, //字符间距模式 2:auto 3:字符边缘间距 4:字符中心间距模式
                                 bool     bBold,    //粗体
                                 bool     bItalic);  //斜体


                                                        //字体类型属性定义
#define FONTATB_JSF        0x0001        //JczSingle字型
#define FONTATB_TTF        0x0002        //TrueType字型
#define FONTATB_DMF        0x0004        //DotMatrix字型
#define FONTATB_BCF        0x0008        //BarCode字型

                                                        //字型记录
struct RKLM_FontRecord
{
        char   szFontName[256];     //字体名字
        unsigned long   dwFontAttrib;       //字体属性
};

typedef int(*RKLM_GETFONTRECORDCOUNT)(int& nFontNum);

//得到当前系统支持的所有字体参数
//输入参数: 无
//输出参数: nFontNum 字体数目
//返回参数: RKLM_FontRecord* 字体记录数组
typedef RKLM_FontRecord* (*RKLM_GETALLFONTRECORD)(int Index, char*FontName, unsigned long & FontAttrib);


//得到指定笔号对应的加工参数
typedef int(*RKLM_GETPENPARAM)( int       nPenNo,//要设置的笔号(0-255)
                                int&      nMarkLoop,//加工次数
                                double&   dMarkSpeed,//标刻次数mm/s
                                double&   dPowerRatio,//功率百分比(0-100%)
                                double&   dCurrent,//电流A
                                int&      nFreq,//频率HZ
                                double&   dQPulseWidth,//Q脉冲宽度us
                                int&      nStartTC,//开始延时us
                                int&      nLaserOffTC,//激光关闭延时us
                                int&      nEndTC,//结束延时us
                                int&      nPolyTC,//拐角延时us
                                double&   dJumpSpeed, //跳转速度mm/s
                                int&      nJumpPosTC, //跳转位置延时us
                                int&      nJumpDistTC,//跳转距离延时us
                                double&   dEndComp,//末点补偿mm
                                double&   dAccDist,//加速距离mm
                                double&   dPointTime,//打点延时 ms
                                bool&     bPulsePointMode,//脉冲点模式
                                int&      nPulseNum);//脉冲点数目

//得到对应笔号的参数
typedef int(*RKLM_GETPENPARAM2)(int       nPenNo,//要设置的笔号(0-255)
                                int&      nMarkLoop,//加工次数
                                double&   dMarkSpeed,//标刻次数mm/s
                                double&   dPowerRatio,//功率百分比(0-100%)
                                double&   dCurrent,//电流A
                                int&      nFreq,//频率HZ
                                double&   dQPulseWidth,//Q脉冲宽度us
                                int&      nStartTC,//开始延时us
                                int&      nLaserOffTC,//激光关闭延时us
                                int&      nEndTC,//结束延时us
                                int&      nPolyTC,//拐角延时us   //
                                double&   dJumpSpeed, //跳转速度mm/s
                                int&      nJumpPosTC, //跳转位置延时us
                                int&      nJumpDistTC,//跳转距离延时us
                                double&   dPointTime,//打点延时 ms
                                bool&     bWobbleMode,//抖动模式
                                double&   bWobbleDiameter,//抖动直径
                                double&   bWobbleDist);//抖动间距

//得到对应笔号的参数
typedef int(*RKLM_GETPENPARAM4)(int      nPenNo,//要设置的笔号(0-255)
                                char   sPenName[256],// 笔名字，默认default
                                int&      clr,//笔颜色
                                bool&      bDisableMark,//是否使能笔号，true关闭笔号不标刻
                                bool&       bUseDefParam,//是否使用默认值
                                int&      nMarkLoop,//加工次数
                                double&   dMarkSpeed,//标刻次数mm/s
                                double&   dPowerRatio,//功率百分比(0-100%)
                                double&   dCurrent,//电流A
                                int&      nFreq,//频率HZ
                                double&      dQPulseWidth,//Q脉冲宽度us
                                int&      nStartTC,//开始延时us
                                int&      nLaserOffTC,//激光关闭延时us
                                int&      nEndTC,//结束延时us
                                int&      nPolyTC,//拐角延时us   //
                                double&   dJumpSpeed, //跳转速度mm/s
                                int&      nMinJumpDelayTCUs, //最小跳转延时us
                                int&      nMaxJumpDelayTCUs,//最大跳转延时us
                                double&   dJumpLengthLimit,//跳转长的极限
                                double&   dPointTime,//打点时间 ms
                                bool&   bPulsePointMode,//脉冲点模式
                                int&      nPulseNum,// 脉冲点数
                                bool&   bEnableACCMode,//使能加速模式
                                double &   dEndComp,//末点补偿
                                double&    dAccDist,//加速距离
                                double&    dBreakAngle,//中断角度，角度值
                                bool&   bWobbleMode,//抖动模式
                                double &   bWobbleDiameter,//抖动直径
                                double&    bWobbleDist);//抖动间距


//设置指定笔号对应的加工参数
typedef int(*RKLM_SETPENPARAM)( int      nPenNo,//要设置的笔号(0-255)
                                int      nMarkLoop,//加工次数
                                double   dMarkSpeed,//标刻次数mm/s
                                double   dPowerRatio,//功率百分比(0-100%)
                                double   dCurrent,//电流A
                                int      nFreq,//频率HZ
                                double   dQPulseWidth,//Q脉冲宽度us
                                int      nStartTC,//开始延时us
                                int      nLaserOffTC,//激光关闭延时us
                                int      nEndTC,//结束延时us
                                int      nPolyTC,//拐角延时us   //
                                double   dJumpSpeed, //跳转速度mm/s
                                int      nJumpPosTC, //跳转位置延时us
                                int      nJumpDistTC,//跳转距离延时us
                                double   dEndComp,//末点补偿mm
                                double   dAccDist,//加速距离mm
                                double   dPointTime,//打点延时 ms
                                bool     bPulsePointMode,//脉冲点模式
                                int      nPulseNum);//脉冲点数目


//设置指定笔号对应的加工参数
typedef int(*RKLM_SETPENPARAM2)(int      nPenNo,//要设置的笔号(0-255)
                                int      nMarkLoop,//加工次数
                                double   dMarkSpeed,//标刻次数mm/s
                                double   dPowerRatio,//功率百分比(0-100%)
                                double   dCurrent,//电流A
                                int      nFreq,//频率HZ
                                double   dQPulseWidth,//Q脉冲宽度us
                                int      nStartTC,//开始延时us
                                int      nLaserOffTC,//激光关闭延时us
                                int      nEndTC,//结束延时us
                                int      nPolyTC,//拐角延时us   //
                                double   dJumpSpeed, //跳转速度mm/s
                                int      nJumpPosTC, //跳转位置延时us
                                int      nJumpDistTC,//跳转距离延时us
                                double   dPointTime,//打点延时 ms
                                bool     bWobbleMode,//是否开启抖动功能
                                double   bWobbleDiameter,//抖动直径
                                double   bWobbleDist);//抖动间距

//设置对应笔号的参数
typedef int(*RKLM_SETPENPARAM4)(int       nPenNo,//要设置的笔号(0-255)
                                char*     sPenName,// 笔名字，默认default
                                int       clr,//笔颜色
                                bool      bDisableMark,//是否使能笔号，true关闭不标刻
                                bool      bUseDefParam,//是否使用默认值
                                int       nMarkLoop,//加工次数
                                double    dMarkSpeed,//标刻次数mm/s
                                double    dPowerRatio,//功率百分比(0-100%)
                                double    dCurrent,//电流A
                                int       nFreq,//频率HZ
                                double    dQPulseWidth,//Q脉冲宽度us
                                int       nStartTC,//开始延时us
                                int       nLaserOffTC,//激光关闭延时us
                                int       nEndTC,//结束延时us
                                int       nPolyTC,//拐角延时us   //
                                double    dJumpSpeed, //跳转速度mm/s
                                int&      nMinJumpDelayTCUs, //最小跳转延时us
                                int       nMaxJumpDelayTCUs,//最大跳转延时us
                                double    dJumpLengthLimit,//跳转长的极限
                                double    dPointTime,//打点时间 ms
                                bool      bPulsePointMode,//脉冲点模式
                                int       nPulseNum,// 脉冲点数
                                bool      bEnableACCMode,//使能加速模式
                                double    dEndComp,//末点补偿
                                double    dAccDist,//加速距离
                                double    dBreakAngle,//中断角度
                                bool      bWobbleMode,//抖动模式
                                double    bWobbleDiameter,//抖动直径
                                double    bWobbleDist);//抖动间距


//复位扩展轴坐标
//输入参数:  enAxis0 = 使能轴0  enAxis1 = 使能轴1
//在程序中调用扩展轴相关的函数，必须先调用RKLM_Reset来设置使能对应的轴;当扩展轴运动到极限位置时，可以用此函数复位扩展轴坐标。
//typedef double(*RKLM_RESET)(bool enAxis0, bool enAxis1);

//轴是否在运动中
typedef bool (*RKLM_ISAXISRUNNING)(int axis);

//扩展轴移动到指定坐标位置
//输入参数: axis     扩展轴  0 = 轴0  1 = 轴1
//          goalPos  坐标位置
//         isabs    是否是绝对坐标
//在程序中调用RKLM_AxisMoveTo可以使扩展轴移动到指定坐标位置，扩展轴的运动速度使用设备参数里定义的最大速度。
typedef int(*RKLM_AXISMOVETO)(int axis, double GoalPos, bool isabs);

//扩展轴校正原点
//输入参数: axis     扩展轴  0 = 轴0  1 = 轴1
//在程序中调用RKLM_AxisCorrectOrigin可以使扩展轴自动校正原点。
typedef int(*RKLM_AXISCORRECTORIGIN)(int axis);

//设置当前为零点
typedef int (*RKLM_AXISSETZEROPOS)(int axis);

//得到扩展轴的当前坐标
//输入参数: axis扩展轴  0 = 轴0  1 = 轴1
typedef double(*RKLM_GETAXISCOOR)(int axis);

//扩展轴移动到指定脉冲坐标位置
//输入参数: axis     扩展轴  0 = 轴0  1 = 轴1
//          goalPos  脉冲坐标位置
//typedef int(*RKLM_AXISMOVETOPULSE)(int axis, int goalPos);

//得到扩展轴的当前脉冲坐标
//输入参数: axis扩展轴  0 = 轴0  1 = 轴1
//typedef int(*RKLM_GETAXISCOORPULSE)(int axis);

//飞行标刻当前数据库里的所有数据
//在使用此函数后，软件开始等待飞行硬件信号（IN8/IN9,在飞行界面中设置的），有信号后开始加工
//typedef int(*RKLM_MARKFLYBYSTARTSIGNAL)();

//飞动标刻当前数据库里的指定对象
//输入参数: entName 飞动打标指定对象的名称
//此函数一直等待设备加工完毕后才返回
//typedef int(*RKLM_MARKENTITYFLY)(char* entName);

//获取当前的飞行速度
//输入参数: flySpeed流水线当前速度
//在设备空闲时可查询流水线速度，即加工或红光过程中不可使用
//typedef int(*RKLM_GETFLYSPEED)(double& flySpeed);


#endif // MARKRKDLL_H
