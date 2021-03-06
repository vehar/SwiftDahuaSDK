/************************************************************************/
/* dhplay   版本:  3.34			                                    */
/************************************************************************/

#ifndef _DHPLAY_H
#define _DHPLAY_H

#include "../dahua-play-defs.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
/************************************************************************/
/* 接口		                                                            */
/************************************************************************/

//------------------------------------------------------------------------
// 函数: PLAY_OpenFile
// 描述: 打开播放文件，用于在播放文件之前调用. 文件不能超过4G或小于4K
// 参数: nPort,通道号
//		 sFileName,文件名
// 返回: BOOL,成功返回TRUE,失败返回FALSE
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenFile(LONG nPort,LPSTR sFileName);

//------------------------------------------------------------------------
// 函数: PLAY_CloseFile
// 描述: 关闭文件, 在PLAY_Stop后调用
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseFile(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_OpenStream
// 描述: 打开流播放
// 参数: nPort,通道号
//		 pFileHeadBuf,目前不使用,填NULL.
//		 nSize,目前不适用,填0.
//		 nBufPoolSize,设置播放器中存放数据流的缓冲区大小.
//			范围是[SOURCE_BUF_MIN,SOURCE_BUF_MAX].一般设为900*1024，如果数
//			据送过来相对均匀,可调小该值,如果数据传输不均匀,可增大该值.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);

//------------------------------------------------------------------------
// 函数: PLAY_CloseStream
// 描述: 关闭流
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStream(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_Play
// 描述: 开始播放.如果已经播放,改变当前播放状态为正常速度播放.
// 参数: nPort,通道号
//		 hWnd,播放窗口句柄
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Play(LONG nPort, HWND hWnd);

//------------------------------------------------------------------------
// 函数: PLAY_Stop
// 描述: 停止播放
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Stop(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_InputData
// 描述: 输入数据流,PLAY_Play之后使用
// 参数: nPort,通道号
//		 pBuf,缓冲区地址
//		 nSize,缓冲区大小
// 返回: BOOL,成功返回TRUE,失败返回FALSE.如失败,一般是缓冲区已满,用户可暂停
//			输入，一段时间之后再输入流，确保播放库不丢失数据。
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);

//------------------------------------------------------------------------
// 函数: PLAY_Pause
// 描述: 暂停或者恢复播放
// 参数: nPort,通道号
//		 nPause,TRUE暂停,FLASE恢复
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Pause(LONG nPort,DWORD nPause);

//------------------------------------------------------------------------
// 函数: PLAY_Fast
// 描述: 播放速度分为九级,播放速度分别为每秒播放1,3,6,12,25,50,75,100,125帧
//		 图像.每次调用播放速度提升一级,最多调用4次,要恢复正常播放调用
//		 PLAY_Play,从当前位置开始正常播放.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Fast(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_Slow
// 描述: 每次调用播放速度降一级,最多调用4次,要恢复正常播放调用PLAY_Play.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Slow(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_OneByOne
// 描述: 单桢播放,要恢复正常播放调用PLAY_ Play.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OneByOne(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayPos
// 描述: 设置文件播放指针的相对位置(百分比)
// 参数: nPort,通道号
//		 fRelativePos,文件长度的百分比
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayPos(LONG nPort,float fRelativePos);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayDirection
// 描述: 设置播放方向
// 参数: nPort,通道号
//		 emDirection,播放方向：0，向前，1，向后
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayDirection(LONG nPort, DWORD emDirection);

//------------------------------------------------------------------------
// 函数: PLAY_GetPlayPos
// 描述: 获取文件播放指针的相对位置(百分比)
// 参数: nPort,通道号
// 返回: float,文件长度的相对位置,范围0-100%
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetPlayPos(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetFileEndMsg
// 描述: 设置文件结束时要发送的消息
// 参数: nPort,端口号
//       hWnd,消息发送窗口
//       nMsg,用户自定义的输入的消息，当播放到文件结束时用户在hWnd窗口过程中
//			收到这个消息。此消息中的wParam或者lParam都可以获得nPort的值.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);

//------------------------------------------------------------------------
// 函数: PLAY_SetVolume
// 描述: 设置音量,设置的音量是指声卡输出的音量,会影响其他的声音应用.
// 参数: nPort,通道号
//		 nVolume,音量的值,范围[0,0xFFFF]
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVolume(LONG nPort,WORD nVolume);

//------------------------------------------------------------------------
// 函数: PLAY_StopSound
// 描述: 关闭独占方式声音
// 参数: 
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopSound();

//------------------------------------------------------------------------
// 函数: PLAY_PlaySound
// 描述: 独占方式打开声音,同一时刻只能有一路声音,如果现在已经有声音打开，则
//		 自动关闭原来已经打开的声音.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_PlaySound(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetFileTime
// 描述: 获取文件总时间
// 参数: nPort,通道号
// 返回: 文件总的时间长度值,单位秒.
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileTime(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetPlayedTime
// 描述: 获取当前文件播放时间
// 参数: nPort,通道号
// 返回: 文件当前播放的时间,单位秒
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedTime(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetPlayedFrames
// 描述: 获取已播放的桢数
// 参数: nPort,通道号
// 返回: 已经解码的视频帧数
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedFrames(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDecodeCallBack
// 描述: 设置解码回调,替换播放器中的显示部分,由用户自己控制显示,该函数在
//			PLAY_Play之前调用,在PLAY_Stop时自动失效,下次调用PLAY_Play之前
//			需要重新设置.解码部分不控制速度,只要用户从回调函数中返回,解码器
//			就会解码下一部分数据.适用于只解码不显示的情形。
// 参数: nPort,通道号
//		 cbDec,解码回调函数指针,不能为NULL.回调函数参数含义如下:
//			nPort,通道号
//			pFrameDecodeInfo,解码后的音视频数据
//			pFrameInfo,图像和声音信息,请参见FRAME_INFO结构体
//			pUser,用户自定义参数
//		 pUser,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fCBDecode)(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo, FRAME_INFO_EX* pFrameInfo, void* pUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeCallBack(LONG nPort, fCBDecode cbDec, void* pUser);

//------------------------------------------------------------------------
// 函数: PLAY_SetDisplayCallBack
// 描述: 设置视频抓图回调函数.如果要停止回调,可以把回调函数指针设为NULL,该
//			函数可以在任何时候调用
// 参数: nPort,通道号
//		 DisplayCBFun,抓图回调函数,可以为NULL,其参数含义如下
//			nPort,通道号
//			pBuf,返回图像数据
//			nSize,返回图像数据大小
//			nWidth,画面宽,单位像素
//			nHeight,画面高
//			nStamp,时标信息，单位毫秒
//			nType,数据类型,T_RGB32,T_UYVY,详见宏定义说明
//			nReceaved,对应用户自定义参数
//		 pUserData,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fDisplayCBFun)(LONG nPort,char * pBuf,LONG nSize,LONG nWidth,LONG nHeight,LONG nStamp,LONG nType, void* pReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayCallBack(LONG nPort, fDisplayCBFun DisplayCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_ConvertToBmpFile
// 描述: 图像格式转为BMP格式.
// 参数: pBuf,图像数据指针
//		 nSize,图像数据大小
//		 nWidth,图像宽度
//		 nHeight,图像高度
//		 nType,数据类型.T_RGB32,T_UYVY等.
//		 sFileName,要保存的文件名.最好以BMP作为文件扩展名.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToBmpFile(char * pBuf,LONG nSize,LONG nWidth,LONG nHeight,LONG nType, char *sFileName);

//------------------------------------------------------------------------
// 函数: PLAY_ConvertToJpegFile
// 描述: 图像格式转为JPEG格式.
// 参数: pYUVBuf,图像数据指针
//		 nWidth,图像宽度
//		 nHeight,图像高度
//		 YUVtype,YUV数据类型,如T_YV12,T_UYVY
//		 quality,图片压缩质量,范围(0, 100].
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToJpegFile(char *pYUVBuf, LONG nWidth, LONG nHeight, int YUVtype, int quality, char *sFileName);

//------------------------------------------------------------------------
// 函数: PLAY_GetFileTotalFrames
// 描述: 获取文件总帧数
// 参数: nPort,通道号
// 返回: DWORD,文件中的总帧数
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileTotalFrames(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetCurrentFrameRate
// 描述: 获取当前帧率
// 参数: nPort,通道号
// 返回: DWORD,当前码流中编码时的帧率值
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetCurrentFrameRate(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetPlayedTimeEx
// 描述: 获取文件当前播放时间
// 参数: nPort,通道号
// 返回: DWORD,文件当前播放的时间,单位毫秒.
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedTimeEx(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayedTimeEx
// 描述: 设置文件当前播放时间.
// 参数: nPort,通道号
//		 nTime,设置文件播放位置到指定时间,单位毫秒.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayedTimeEx(LONG nPort,DWORD nTime);

//------------------------------------------------------------------------
// 函数: PLAY_GetCurrentFrameNum
// 描述: 获取当前播放的帧序号,PLAY_GetPlayedFrames是总共解码的帧数.如果文件
//			播放位置不被改变，那么这两个函数的返回值应该非常接近，除非码流丢
//			失数据.
// 参数: nPort,通道号
// 返回: 当前播放的帧序号.
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetCurrentFrameNum(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetStreamOpenMode
// 描述: 设置流播放模式,必须在播放之前设置.
// 参数: nPort,通道号
//		 nMode,STREAME_REALTIME实时模式(默认);STREAME_FILE文件模式.实时模
//			式,适合播放网络实时数据;文件模式,适合用户把文件数据用流方式输入.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStreamOpenMode(LONG nPort,DWORD nMode);

//------------------------------------------------------------------------
// 函数: PLAY_GetSdkVersion
// 描述: 获取播放库SDK版本号,次版本号和补丁号
// 参数: 
// 返回: DWORD,高16位表示当前的主版本号;9~16位表示次版本号;1~8位表示次补丁号;
//			如:返回值0x00030107表示:主版本号是3,次版本号是1,补丁号是7.
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetSdkVersion();

//------------------------------------------------------------------------
// 函数: PLAY_GetLastError
// 描述: 获取错误码
// 参数: nPort,通道号
// 返回: DWORD,获得当前错误的错误码.请参见错误码宏定义.
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetLastError(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_RefreshPlay
// 描述: 刷新显示.当用户暂停时如果刷新了窗口,则窗口中的图像因为刷新而消失,
//			此时调用这个接口可以重新把图像显示出来.只有在暂停和单帧播放时才
//			执行,其它情况会直接返回.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RefreshPlay(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetPictureSize
// 描述: 获取原始图像大小,根据此大小来设置显示窗口的区域,可以不用显卡做缩放
//			工作,对于那些不支持硬件缩放的显卡来说非常有用.
// 参数: nPort,通道号
//		 pWidth,输出参数,返回图片宽度
//		 pHeight,输出参数,返回图片高度
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);

//------------------------------------------------------------------------
// 函数: PLAY_SetPicQuality
// 描述: 设置图像质量,当设置成高质量时画面效果好,但CPU利用率高.在支持多路播放时，
//			可以设为低质量,以降低CPU利用率.当某路放大播放时将该路设置成高质量，
//			以达到好的画面效果.
// 参数: nPort,通道号
//		 bHighQuality,为TRUE(1)时图像高质量,为FALSE(0)时低质量(默认值).
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPicQuality(LONG nPort,BOOL bHighQuality);

//------------------------------------------------------------------------
// 函数: PLAY_PlaySoundShare
// 描述: 以共享方式播放声音,播放本路声音而不去关闭其他路的声音.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_PlaySoundShare(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StopSoundShare
// 描述: 关闭声音(共享方式).在同一个进程中,所有通道必须使用相同的方式播放或关闭声音.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopSoundShare(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetStreamOpenMode
// 描述: 获取流播放模式
// 参数: nPort,通道号
// 返回: LONG,STREAME_REALTIME或STREAME_FILE.
//------------------------------------------------------------------------
PLAYSDK_API LONG CALLMETHOD PLAY_GetStreamOpenMode(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetVolume
// 描述: 获取音量,这里的音量是指声卡输出的音量.
// 参数: nPort,通道号
// 返回: WORD,音量值
//------------------------------------------------------------------------
PLAYSDK_API WORD CALLMETHOD PLAY_GetVolume(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetPictureQuality
// 描述: 获取图像质量
// 参数: nPort,通道号
//		 bHighQuality,输出参数,TRUE表示高质量,FALSE表示低质量.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPictureQuality(LONG nPort,BOOL *bHighQuality);

//------------------------------------------------------------------------
// 函数: PLAY_GetSourceBufferRemain
// 描述: 获取流播放模式下源缓冲区剩余数据大小
// 参数: nPort,通道号
// 返回: DWORD,当前源缓冲的大小单位BYTE(字节).
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetSourceBufferRemain(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_ResetSourceBuffer
// 描述: 清空流播放模式下源缓冲区的剩余数据
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBuffer(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_OneByOneBack
// 描述: 单帧回退,此接口只支持文件播放,必须在文件索引生成之后才能调用.每调
//			用一次倒退一帧
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OneByOneBack(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetCurrentFrameNum
// 描述: 设置文件当前帧播放帧号,此函数必须在文件索引生成之后才能调用.
// 参数: nPort,通道号
//		 nFrameNum,帧序号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetKeyFramePos
// 描述: 查找指定位置之前的关键帧位置,图像解码必须从关键帧开始，如果用户保存
//			的文件不是从关键帧开始的,那么倒下一个关键帧之前的数据会被忽略.如
//			果用户要截取文件中的一段数据,则应该考虑从关键帧开始截取.结束位置
//			则关系不大,最多丢失3帧数据.在文件索引建立完全的前提下,与
//			PLAY_GetNextKeyFramePos联合使用,可以用来实现剪辑录像文件,剪辑精度
//			与关键帧间隔有关.
// 参数: nPort,通道号
//		 nValue,当前位置,可以是时间或帧号,类型由nType指定.
//		 nType,指定nValue的类型.如果nType是BY_FRAMENUM,则nValue表示帧号;
//			如果nType是BY_FRAMTIME,则nValue表示时间,单位ms.
//		 pFramePos,查找到的关键帧的文件位置信息结构指针,详见PFRAME_POS.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);

//------------------------------------------------------------------------
// 函数: PLAY_GetNextKeyFramePos
// 描述: 查找指定位置之后的关键帧位置
// 参数: nPort,通道号
//		 nValue,当前位置,可以是时间或帧号,类型由nType指定.
//		 nType,指定nValue的类型.如果nType是BY_FRAMENUM,则nValue表示帧号;
//			如果nType是BY_FRAMTIME,则nValue表示时间,单位ms.
//		 pFramePos,查找到的关键帧的文件位置信息结构指针,详见PFRAME_POS.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);

//------------------------------------------------------------------------
// 函数: PLAY_SetDecCBStream
// 描述: 设置解码回调流类型,在PLAY_Play之前调用.
// 参数: nPort,通道号
//		 nStream,1 视频流;2 音频流;3 复合流.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCBStream(LONG nPort,DWORD nStream);

//------------------------------------------------------------------------
// 函数: PLAY_SetDisplayRegion
// 描述: 设置或增加显示区域,可以做局部放大显示.
// 参数: nPort,通道号
//		 nRegionNum,显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中.
//		 pSrcRect,局部显示区域
//		 hDestWnd,显示窗口句柄
//		 bEnable,打开(设置)或关闭显示区域
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, DISPLAYRECT *pSrcRect, HWND hDestWnd, BOOL bEnable);


//------------------------------------------------------------------------
// 函数: PLAY_GetRefValue
// 描述: 获取文件索引,以便下次打开同一个文件时直接使用这个信息.必须在索引建成后才能获得信息.
// 参数: nPort,通道号
//		 pBuffer,索引信息
//		 pSize,输入pBuffer的大小,输出索引信息大小.可以在第一次指定pSize=0,pBuffer=NULL,从
//			pSize的返回值获得需要的缓冲区大小.然后分配足够的缓冲,再调用一次.	 
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);

//------------------------------------------------------------------------
// 函数: PLAY_SetRefValue
// 描述: 设置文件索引,索引信息及其长度必须准确.如果已经有了文件索引信息,可以
//			不再调用生成索引的回调函数PLAY_SetFileRefCallBackEx,直接输入索引信息.
// 参数: nPort,通道号
//		 pBuffer,索引信息
//		 nSize,索引信息的长度
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);

//------------------------------------------------------------------------
// 函数: PLAY_RigisterDrawFun
// 描述: 注册一个回调函数,获得当前表面的device context,你可以在这个DC上画图(或文字),
//			就好像在窗口的客户区DC上绘图,但这个DC不是窗口客户区的DC,而是DirectDraw里
//			的Off-Screen表面的DC.注意,如果是使用overlay表面,这个接口无效,可以直接在
//			窗口上绘图,只要不是透明色就不会被覆盖.
// 参数: nPort,通道号
//		 DrawFun,画图回调函数,其参数含义如下:
//			nPort,通道号
//			hDc,OffScreen表面设备上下文.
//			pUserData,用户数据,就是上面输入的用户数据
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fDrawCBFun)(LONG nPort,HDC hDc, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_RigisterDrawFun(LONG nPort, fDrawCBFun DrawCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_ResetBuffer
// 描述: 清空指定缓冲区的剩余数据
// 参数: nPort,通道号
//		 nBufType,如下:
//			BUF_VIDEO_SRC 1 视频源缓冲
//			BUF_AUDIO_SRC 2 音频源缓冲
//			BUF_VIDEO_RENDER 3 解码后视频数据缓冲
//			BUF_AUDIO_RENDER 4 解码后音频数据缓冲
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetBuffer(LONG nPort,DWORD nBufType);

//------------------------------------------------------------------------
// 函数: PLAY_GetBufferValue
// 描述: 获取指定缓冲区的大小
// 参数: nPort,通道号
//		 nBufType,如下:
//			BUF_VIDEO_SRC 1 视频源缓冲
//			BUF_AUDIO_SRC 2 音频源缓冲
//			BUF_VIDEO_RENDER 3 解码后视频数据缓冲
//			BUF_AUDIO_RENDER 4 解码后音频数据缓冲
// 返回: DWORD,根据不同参数返回缓冲区值,源缓冲区返回byte,解码后缓冲区返回帧数.
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetBufferValue(LONG nPort,DWORD nBufType);

//------------------------------------------------------------------------
// 函数: PLAY_AdjustWaveAudio
// 描述: 调整WAVE波形,可以改变声音的大小.它和PLAY_SetVolume的不同在于,它是调整
//			声音数据,只对该路其作用,而PLAY_SetVolume是调整声卡音量,对整个系统起作用.
// 参数: nPort,通道号
//		 nCoefficient,调整的参数,范围从MIN_WAVE_COEF到MAX_WAVE_COEF,0是不调整
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustWaveAudio(LONG nPort,LONG nCoefficient);

//------------------------------------------------------------------------
// 函数: PLAY_SetAudioCallBack
// 描述: 音频解码后的WAVE数据回调.
// 参数: nPort,通道号
//		 funAudio,音频解码回调函数,其参数含义如下
//			nPort,通道号
//			pAudioBuf,wave格式音频数据
//			nSize,音频数据长度
//			nStamp,时标(ms)
//			nType,音频类型T_AUDIO16, 采样率8000，单声道，每个采样点16位表示
//			pUserData,用户自定义数据
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK * fAudioCBFun)(LONG nPort, char * pAudioBuf, LONG nSize, LONG nStamp, LONG nType, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioCallBack(LONG nPort, fAudioCBFun AudioCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetEncTypeChangeCallBack
// 描述: 设置图像分辨率改变通知回调,打开文件前使用.
// 参数: nPort,通道号
//		 funEncChange,回调函数
//			nPort,通道号
//			pUserData,用户自定义数据
//		 pUserData,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void(CALLBACK *fEncChangeCBFun)(LONG nPort, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncTypeChangeCallBack(LONG nPort, fEncChangeCBFun EncChangeCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetColor
// 描述: 设置视频参数
// 参数: nPort,通道号
//		 nRegionNum,显示区域,参考PLAY_SetDisplayRegion;如果只有一个显示区域(通常情况)设为0.
//		 nBrightness,亮度,默认64;范围0-128.
//		 nContrast,对比度,默认64;范围0-128.
//		 nSaturation,饱和度,默认64;范围0-128.
//		 nHue,色调,默认64;范围0-128.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);

//------------------------------------------------------------------------
// 函数: PLAY_GetColor
// 描述: 获取视频参数
// 参数: nPort,通道号
//		 nRegionNum,显示区域,参考PLAY_SetDisplayRegion;如果只有一个显示区域(通常情况)设为0.
//		 pBrightness,亮度,默认64;范围0-128.
//		 pContrast,对比度,默认64;范围0-128.
//		 pSaturation,饱和度,默认64;范围0-128.
//		 pHue,色调,默认64;范围0-128.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);

//------------------------------------------------------------------------
// 函数: PLAY_SetEncChangeMsg
// 描述: 设置分辨率改变通知消息
// 参数: nPort,通道号
//		 hWnd,消息发送的窗口
//		 nMsg,用户输入的消息,当解码时编码格式发生改变时用户在hWnd窗口过程中收到这个消息.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);

//------------------------------------------------------------------------
// 函数: PLAY_CatchPic
// 描述: 抓图,将BMP图片保存为指定的文件.PLAY_SetDisplayCallBack设置的视频数
//			据回调函数,只有在有视频数据解码出来时才调用,并由用户处理视频数
//			据(如抓图),如果不断有解码的数据,就不断调用这个回调函数.而PLAY_
//			CatchPic一次只抓一幅图,并能在暂停和单帧播放时实现抓图.建议:如果
//			用户想实现抓图(一次抓一幅图),调用PLAY_CatchPic,而如果想得到一段
//			时间内的视频数据,调用PLAY_SetDisplayCallBack.
// 参数: nPort,通道号
//		 sFileName,文件名称
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CatchPic(LONG nPort,char* sFileName) ;

//------------------------------------------------------------------------
// 函数: PLAY_CatchPicEx
// 描述: PLAY_CatchPic的扩展接口,用法请参详PLAY_CatchPic.可指定图片格式
// 参数: nPort,通道号
//		 sFileName,文件名称
//		 ePicfomat,图片格式,见tPicFormats.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CatchPicEx(LONG nPort,char* sFileName,tPicFormats ePicfomat);

//------------------------------------------------------------------------
// 函数: PLAY_SetFileEndCallBack
// 描述: 设置文件结束回调
// 参数: nPort,通道号
//		 pFileEnd,回调函数指针,其参数含义如下:
//			nPort,通道号
//			pUserData,用户自定义参数
//		 pUserData,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK *fpFileEndCBFun)(DWORD nPort, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileEndCallBack(LONG nPort, fpFileEndCBFun pFileEndCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_StartDataRecord
// 描述: 开始流数据录像,只对流模式有用,在PLAY_Play之后调用.
// 参数: nPort,通道号
//		 sFileName,录像文件名,如果文件名中有不存在的文件夹,就创建该文件夹.
//		 idataType,0表示原始视频流;1表示转换成AVI格式;2表示转换成ASF格式;3分段保存文件
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDataRecord(LONG nPort, char *sFileName, int idataType);

//------------------------------------------------------------------------
// 函数: PLAY_WriteData
// 描述: 保存原始码流
// 参数: nPort,通道号
//		 pBuf,流数据
//		 nSize,大小
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_WriteData(LONG nPort, PBYTE pBuf,DWORD nSize);

//------------------------------------------------------------------------
// 函数: PLAY_StopDataRecord
// 描述: 停止流数据录像
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDataRecord(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlaySpeed
// 描述: 改变图像播放的速度,
// 参数: nPort,通道号
//		 fCoff,播放速度,范围[1/64~64.0],小于1表示慢放，大于1表示正放.
//			   当播放速度较快时可能会抽帧播放.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlaySpeed(LONG nPort, float fCoff);

//------------------------------------------------------------------------
// 函数: PLAY_QueryInfo
// 描述: 目前实现了对当前时间和帧率信息的查询.
// 参数: nPort,通道号
//		 cmdType,指定状态查询指令,如下
//			PLAY_CMD_GetTime   获取编码中时间信息,单位ms.
//			PLAY_CMD_GetFileRate  获取帧率信息
//			PLAY_CMD_GetMediaInfo  获取媒体信息,信息结构为 MEDIA_INFO
//		 buf,存放信息的缓冲
//		 buflen,缓冲长度
//		 returnlen,获取的信息的有效数据长度
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_QueryInfo(LONG nPort , int cmdType, char* buf, int buflen, int* returnlen);

//------------------------------------------------------------------------
// 函数: PLAY_OpenAudioRecord
// 描述: 打开音频采集功能.
// 参数: pProc,音频采集数据回调指针,其参数含义如下:
//			pDataBuffer,回调数据指针
//			DataLength,回调数据长度
//			pUserData,用户数据
//		 nBitsPerSample,表示每个采样所需要的位数
//		 nSamplesPerSec,采样率
//		 nLength,数据缓冲的长度
//		 nReserved,保留
//		 pUserData,用户自定义数据
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK *pCallFunction)(LPBYTE pDataBuffer, DWORD DataLength, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenAudioRecord(pCallFunction pProc, LONG nBitsPerSample, LONG nSamplesPerSec, LONG nLength, LONG nReserved, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_CloseAudioRecord
// 描述: 关闭音频采集功能
// 参数: 
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseAudioRecord();

//------------------------------------------------------------------------
// 函数: PLAY_SetWaterMarkCallBack
// 描述: 设置水印数据回调。注意：水印校验回调设置后将不会进行解码显示
// 参数: nPort,通道号
//		 pFunc,水印信息获取回调函数,其参数含义如下:
//			buf,水印数据buffer指针
//			key,区分不同水印信息
//			len,缓冲的最大长度
//			reallen,缓冲的实际长度
//			type,数值范围[0,3],含义如下
//				0  I帧帧数据水印信息
//				1  帧水印
//				2  水印校验 
//				3  智能分析帧
//		 pUserData,用户自定义参数 
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef int (CALLBACK* GetWaterMarkInfoCallbackFunc)(char* buf, LONG key, LONG len, LONG reallen, LONG type, void* pUserData);	
PLAYSDK_API BOOL CALLMETHOD PLAY_SetWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_CreateFile
// 描述: 打开文件并自动分配通道号
// 参数: sFileName,文件名
// 返回: DWORD,失败返回0,否则返回通道号.
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_CreateFile(LPSTR sFileName);

//------------------------------------------------------------------------
// 函数: PLAY_DestroyFile
// 描述: 关闭播放文件并释放自动分配的通道号.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_DestroyFile(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_CreateStream
// 描述: 打开流接口并自动分配通道号
// 参数: nBufPoolSize,置播放器中存放数据流的缓冲区大小,范围是[SOURCE_BUF_MIN,SOURCE_BUF_MAX].
// 返回: DWORD,失败返回0,否则返回通道号.
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_CreateStream(DWORD nBufPoolSize);

//------------------------------------------------------------------------
// 函数: PLAY_DestroyStream
// 描述: 关闭数据流,并释放自动分配的通道号.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_DestroyStream(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetFreePort
// 描述: 获取空闲通道号,上限为501.与PLAY_ReleasePort匹对使用.
// 参数: plPort,输出参数,返回获取的通道号.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetFreePort(LONG *plPort);

//------------------------------------------------------------------------
// 函数: PLAY_ReleasePort
// 描述: 释放通道号,与PLAY_RealsePort匹对使用.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ReleasePort(LONG lPort);

//------------------------------------------------------------------------
// 函数: PLAY_VerticalSyncEnable
// 描述: 垂直同步显示开关.此接口需在PLAY_Play之后调用,重新播放时需重新设置.
//			在播放动态图像出现断层时,可以使用此接口打开垂直同步功能.
// 参数: nPort,通道号
//		 bEnable,TRUE打开垂直同步;FALSE关闭垂直同步.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API	BOOL CALLMETHOD PLAY_VerticalSyncEnable(LONG nPort, BOOL bEnable);

//------------------------------------------------------------------------
// 函数: PLAY_GetPicBMP
// 描述: 抓取BMP图像
// 参数: nPort,通道号
//		 pBmpBuf,存放BMP图像数据的缓冲地址,由用户分配,不得小于bmp 图像大小,
//			推荐大小:sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+w*h*4,
//			其中w和h分别为图像宽高.
//		 dwBufSize,缓冲区大小
//		 pBmpSize,获取到的实际bmp 图像大小
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPicBMP(LONG nPort, PBYTE pBmpBuf, DWORD dwBufSize, DWORD* pBmpSize);

//------------------------------------------------------------------------
// 函数: PLAY_GetPicBMPEx
// 描述: 抓取BMP图像
// 参数: nPort,通道号
//		 pBmpBuf,存放BMP图像数据的缓冲地址,由用户分配,不得小于bmp 图像大小,
//			推荐大小:sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+w*h*4,
//			其中w和h分别为图像宽高.
//		 dwBufSize,缓冲区大小
//		 pBmpSize,获取到的实际bmp 图像大小
//		 nWidth,指定的bmp的宽
//		 nHeight,指定的bmp的高
//		 nRgbType,指定RGB格式 0：RGB32;1：RGB24;
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPicBMPEx(LONG nPort, PBYTE pBmpBuf, DWORD dwBufSize, DWORD* pBmpSize, LONG nWidth, LONG nHeight, int nRgbType);

//------------------------------------------------------------------------
// 函数: PLAY_GetPicJPEG
// 描述: 抓取JPEG图像.
// 参数: nPort,通道号
//		 pJpegBuf,存放JPEG图像数据的缓冲地址,由用户分配,不得小于JPEG图像大小,
//			推荐大小:w*h*3/2,其中w和h分别为图像宽高.
//		 dwBufSize,缓冲区大小.
//		 pJpegSize,获取到的实际JPEG图像大小.
//		 quality,JPEG图像的压缩质量,取值范围为(0,100].
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPicJPEG(LONG nPort, PBYTE pJpegBuf, DWORD dwBufSize, DWORD* pJpegSize, int quality);

//------------------------------------------------------------------------
// 函数: PLAY_GetPicTIFF
// 描述: 抓取TIFF图像
// 参数: nPort,通道号
//		 pTiffBuf,存放TIFF图像数据的缓冲地址,由用户分配,不得小于tiff图像大小,
//			推荐大小:w*h*3+1024,
//			其中w和h分别为图像宽高.
//		 dwBufSize,缓冲区大小
//		 pTiffSize,获取到的实际TIFF图像大小
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPicTIFF(LONG nPort, PBYTE pTiffBuf, DWORD dwBufSize, DWORD* pTiffSize);

//------------------------------------------------------------------------
// 函数: PLAY_SetVisibleDecodeCallBack
// 描述: 解码回调.与PLAY_SetDecodeCallBack基本相同,不同的是解码回调的同时可以
//			显示视频,建议不要在回调函数里面做长时间的逻辑处理,以免增加显示的延时.
// 参数: nPort,通道号
//		 cbDec,解码回调函数指针,不能为NULL.回调函数参数含义如下:
//			nPort,通道号
//			pFrameDecodeInfo,解码后的音视频数据
//			pFrameInfo,图像和声音信息,请参见FRAME_INFO结构体
//			pUser,用户自定义参数
//		 pUser,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVisibleDecodeCallBack(LONG nPort, fCBDecode cbDec, void* pUser);

//------------------------------------------------------------------------
// 函数: PLAY_RigisterDrawFunEx
// 描述: 注册一个回调函数,获得当前表面的上下文(HDC),这个DC不是窗口客户区的DC,
//			而是DirectDraw里的Off-Screen表面的DC.注意.如果是使用overlay表面,
//			这个接口无效,overlay方式可以直接在窗口上绘图,只要不是透明色就不会被覆盖.
// 参数: nPort,通道号
//		 nReginNum,显示区域序号,范围[0,(MAX_DISPLAY_WND-1)].如果nRegionNum为0,
//			则将设置的区域显示在主窗口中.
//		 DrawFunEx,画图回调函数,其参数含义如下:
//			nPort,通道号
//			hDc,Off-Screen表面的设备上下文(DC)
//			pUserData,用户自定义参数
//		 pUserData,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fDrawCBFunEx)(LONG nPort,LONG nReginNum,HDC hDc, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_RigisterDrawFunEx(LONG nPort, LONG nReginNum, fDrawCBFunEx DrawFunEx, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_CatchResizePic
// 描述: 抓图,可选择格式并指定宽高.
// 参数: nPort,通道号
//		 sFileName,文件名称
//		 lTargetWidth,指定的图像宽度
//		 lTargetHeight,指定的图像高度
//		 ePicfomat,图片格式,详见tPicFomats
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CatchResizePic(LONG nPort, char* sFileName, LONG lTargetWidth, LONG lTargetHeight, tPicFormats ePicfomat);

//------------------------------------------------------------------------
// 函数: PLAY_GetRealFrameBitRate
// 描述: 获取视频实时码率
// 参数: nPort,通道号
//		 pBitRate,输出参数,返回视频码率.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetRealFrameBitRate(LONG nPort, double* pBitRate);


//------------------------------------------------------------------------
// 函数: PLAY_SetFileRefCallBackEx
// 描述: 设置建立索引回调,以返回索引创建情况.
// 参数: nPort,通道号
//		 pFileRefDoneEx,回调函数指针,其参数含义如下:
//			nPort,通道号
//			bIndexCreated,索引创建标志,TRUE索引创建成功;FALSE失败.
//			pUserData,用户自定义参数
//		 pUserData,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK *fpFileRefDoneCBFunEx)(DWORD nPort, BOOL bIndexCreated, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileRefCallBackEx(LONG nPort, fpFileRefDoneCBFunEx pFileRefDoneCBFunEx, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_StartAVIConvert
// 描述: 开始AVI转换并设置AVI转换状态回调.
// 参数: nPort,通道号
//		 pAVIFunc,回调函数,其参数含义如下:
//			nPort,通道号
//			lMediaChangeType,AVI_MEDIACHANGE_FRAMERATE表示帧率改变;AVI_MEDIACHANGE_RESOLUTION表示分辨率改变
//			lUser,用户自定义参数
//			pbIfContinue,TRUE继续转换;FALSE 停止转换
//			sNewFileName,如果继续转换,新的录像文件名
//		 lUser,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* AVIConvertCallback)(LONG nPort, LONG lMediaChangeType, void* pUserData, BOOL *pbIfContinue, char *sNewFileName);
PLAYSDK_API BOOL CALLMETHOD PLAY_StartAVIConvert(LONG nPort, char *sFileName, AVIConvertCallback pAVIFunc, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_StopAVIConvert
// 描述: 停止AVI转换.
// 参数: nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopAVIConvert(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetWaterMarkCallBackEx
// 描述: 设置水印数据回调。注意：水印校验回调设置后将不会进行解码显示
// 参数: nPort,通道号
//		 pFunc,函数指针,其参数含义如下:
//			nPort,通道号
//			buf,水印数据缓冲
//			lTimeStamp,水印的时间戳
//			lInfoType,水印信息类型,有三种类型,WATERMARK_DATA_TEXT,
//				WATERMARK_DATA_JPEG_BMP,WATERMARK_DATA_FRAMEDATA
//		 len,缓冲的最大长度
//		 reallen,缓冲的实际长度
//		 lCheckResult,1没有错误;2水印错误;3帧数据错误;4帧号错误
//		 pUserData,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef int (CALLBACK* GetWaterMarkInfoCallbackFuncEx)(LONG nPort, char* buf, LONG lTimeStamp, LONG lInfoType, LONG len, LONG reallen, LONG lCheckResult, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetWaterMarkCallBackEx(LONG nPort, GetWaterMarkInfoCallbackFuncEx pFunc, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetAudioRecScaling
// 描述: 设置音频采集数据缩放比例
// 参数: fRatio,缩放比例.大于0小于1为音频缩小;1为原始音频;大于1为音频放大.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioRecScaling(float fRatio);

//------------------------------------------------------------------------
// 函数: PLAY_GetAudioRecScaling
// 描述: 获取音频采集数据缩放比例
// 参数: pfRatio,缩放比例.大于0小于1为音频缩小;1为原始音频;大于1为音频放大.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioRecScaling(float* pfRatio);

//------------------------------------------------------------------------
// 函数: PLAY_SetAudioRenderScaling
// 描述: 设置音频解码缩放比例
// 参数: nPort,通道号
//		 fRatio,缩放比例.大于0小于1为音频缩小;1为原始音频;大于1为音频放大.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioRenderScaling(LONG nPort, float fRatio);

//------------------------------------------------------------------------
// 函数: PLAY_GetAudioRenderScaling
// 描述: 获取音频解码缩放比例
// 参数: nPort,通道号
//		 pfRatio,缩放比例.大于0小于1为音频缩小;1为原始音频;大于1为音频放大.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioRenderScaling(LONG nPort, float* pfRatio);

//------------------------------------------------------------------------
// 函数: PLAY_SetRotateAngle
// 描述: 图像翻转
// 参数: nrotateType,翻转类型,范围[0,3]. 0不旋转;1旋转90度;2旋转180度;3旋转270度.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRotateAngle(LONG nPort , int nrotateType);

//------------------------------------------------------------------------
// 函数: PLAY_SetDelayTime
// 描述: 设置延迟时间
// 参数: nDelay,延迟时间，缓冲多少时间开始播放，缓冲小于此值开始稍微慢放
//       nThreshold,阀值时间，到达阀值开始稍微快放
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDelayTime(LONG nPort, int nDelay, int nThreshold);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayMethod
// 描述: 设置播放策略参数，只对实时流有效
// 参数: nStartTime,开始播放的时间
//       nSlowTime,开始慢放的时间
//		 nFastTime,开始快放的时间
//		 nFailedTime,超过此时间投递数据失败
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayMethod(LONG nPort, int nStartTime, int nSlowTime, int nFastTime, int nFailedTime);

//------------------------------------------------------------------------
// 函数: PLAY_BackOne
// 描述: 与PLAY_OneByOneBack重复，请使用PLAY_OneByOneBack
// 参数: 
// 返回: 
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_BackOne(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDecCallBack(建议使用PLAY_SetDecodeCallBack)
// 描述: 设置解码回调,替换播放器中的显示部分,由用户自己控制显示,该函数在
//			PLAY_Play之前调用,在PLAY_Stop时自动失效,下次调用PLAY_Play之前
//			需要重新设置.解码部分不控制速度,只要用户从回调函数中返回,解码器
//			就会解码下一部分数据.适用于只解码不显示的情形。
// 参数: nPort,通道号
//		 DecCBFun,解码回调函数指针,不能为NULL.回调函数参数含义如下:
//			nPort,通道号
//			pBuf,解码后的音视频数据
//			nSize,解码后的音视频数据pBuf的长度
//			pFrameInfo,图像和声音信息,请参见FRAME_INFO结构体
//			nReserved1,保留参数
//			nReserved2,保留参数	
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fDecCBFun)(LONG nPort,char * pBuf,LONG nSize,FRAME_INFO * pFrameInfo, void* pUserData, LONG nReserved2);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCallBack(LONG nPort, fDecCBFun DecCBFun);

//------------------------------------------------------------------------
// 函数: PLAY_SetDecCallBackEx(建议使用PLAY_SetDecodeCallBack)
// 描述: 设置解码回调,替换播放器中的显示部分,由用户自己控制显示,该函数在
//			PLAY_Play之前调用,在PLAY_Stop时自动失效,下次调用PLAY_Play之前
//			需要重新设置.解码部分不控制速度,只要用户从回调函数中返回,解码器
//			就会解码下一部分数据.适用于只解码不显示的情形。
// 参数: nPort,通道号
//		 DecCBFun,解码回调函数指针,不能为NULL.回调函数参数含义如下:
//			nPort,通道号
//			pBuf,解码后的音视频数据
//			nSize,解码后的音视频数据pBuf的长度
//			pFrameInfo,图像和声音信息,请参见FRAME_INFO结构体
//			nReserved1,用户自定义参数
//			nReserved2,保留参数	
//		 pUserData,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCallBackEx(LONG nPort, fDecCBFun DecCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetVisibleDecCallBack(建议使用PLAY_SetVisibleDecodeCallBack)
// 描述: 解码回调.与PLAY_SetDecCallBackEx基本相同,不同的是解码回调的同时可以
//			显示视频,建议不要在回调函数里面做长时间的逻辑处理,以免增加显示的延时.
// 参数: nPort,通道号
//		 DecCBFun,回调函数指针,不能为NULL,其参数含义如下:
//			nPort,通道号
//			pBuf,解码后的音视频数据
//			nSize,数据长度
//			pFrameInfo,帧信息,详见FRAME_INFO结构体.
//			pUserData,用户自定义参数
//			pReserved1,保留参数.
//		 pUserData,用户自定义参数.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fVisibleDecCBFun)(LONG nPort,char * pBuf,LONG nSize,FRAME_INFO * pFrameInfo, void* pUserData, LONG nReserved1);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVisibleDecCallBack(LONG nPort, fVisibleDecCBFun DecCBFun, void* pUserData);


//------------------------------------------------------------------------
// 函数: PLAY_SetDisplayScale
// 描述: 设置显示比例大小，IOS专用以便适配不同的机型.
// 参数: nPort,通道号
//		 fScale，显示比例，默认为1.0
//		 nRegionNum,显示区域序号,0~(MAX_DISPLAY_WND-1),如果为0,则将设置的区域显示在主窗口中.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayScale(LONG nPort, float fScale, DWORD nRegionNum);


//------------------------------------------------------------------------
//	函数名: PLAY_SetSecurityKey
//	描述: 设置aes解密密钥
//  输入参数:   nPort:		解码通道。
//				szKey:		密钥的指针
//				nKeylen:	密钥的长度       
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSecurityKey(LONG nPort,const char* szKey,DWORD nKeylen);

//------------------------------------------------------------------------
// 函数: PLAY_StartFisheye
// 描述: 开启视频鱼眼算法功能，需要包含fisheye.dll库
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheye(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_OperateFisheyeParams
// 描述: 设置/获取鱼眼参数
// 参数: [in]nPort					:  通道号
//		 [in]operatetype			:  操作类型
//       [in]pOptParam	    		:  鱼眼参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//-----------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OptFisheyeParams(LONG nPort, FISHEYE_OPERATETYPE operatetype, FISHEYE_OPTPARAM* pOptParam);

//------------------------------------------------------------------------
// 函数: PLAY_FisheyeSecondRegion
// 描述: 用于浮动模式下开启或关闭第二个鱼眼窗口
// 参数: [in]nPort			: 通道号
//		 [in]hDestWnd		: 显示窗口句柄
//		 [in]pOptParam		: 第二个窗口对应的鱼眼参数
//		 [in]bEnable		: 打开或关闭显示区域
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeSecondRegion(LONG nPort, HWND hDestWnd, FISHEYE_OPTPARAM* pOptParam, BOOL bEnable);

//------------------------------------------------------------------------
// 函数: PLAY_FisheyeEptzUpdate
// 描述: 开启eptz(电子云台），进行缩放移动
// 参数: [in]nPort           :  通道号
//       [in/out]pEptzParam  :  调节参数
//		 [in]bSecondRegion	 ：	是否为浮动模式下的第二个窗口，1为真，默认填0
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeEptzUpdate(LONG nPort, FISHEYE_EPTZPARAM* pEptzParam, BOOL bSecondRegion);

//------------------------------------------------------------------------
// 函数: PLAY_StopFisheye
// 描述: 停止视频鱼眼算法功能
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopFisheye(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetFishEyeInfoCallBack
// 描述: 设置获取鱼眼回调
// 参数: nPort,通道号
//		 pFishEyeInfoFun,回调函数指针,不能为NULL,其参数含义如下:
//			nPort,通道号
//          byCorrectMode,矫正模式
//          wRadius,半径
//          wCircleX,圆心横坐标
//          wCircleY,圆心纵坐标
//			widthRatio, 宽比率
//			heightRatio,高比率
//			gain, 增益
//			denoiseLevel, 降噪等级
//			InstallStyle, 鱼眼安装方式
//		 pUserData,用户自定义参数.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fCBFishEyeInfoFun)( 
	LONG nPort,
	BYTE byCorrectMode,
	WORD wRadius,
	WORD wCircleX,
	WORD wCircleY,
	UINT widthRatio,
	UINT heightRatio,
	BYTE gain,
	BYTE denoiseLevel,
	BYTE installStyle,
	void* pUserData );
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFishEyeInfoCallBack(
	LONG nPort, 
	fCBFishEyeInfoFun pFishEyeInfoFun, 
	void* pUserData );

    
    
// Extension API




/********************************************************************
 *	函数名: 	    	PLAY_SetupPrepareTime
 *	目的:				设置预录的环境
 *   输入参数:           nPort:		解码通道。
 nTime:		预录多少秒
 tmpDir:		临时的预录目录
 *   输出参数:
 *   返回值:             TRUE:	成功.
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息记录:	    2012/12/21:YeYamin:modify......
 *********************************************************************/

PLAYSDK_API BOOL	CALLMETHOD PLAY_SetupPrepareTime(LONG nPort,int nTime,const char* tmpDirectory);

/********************************************************************
 *	函数名: 	    	PLAY_StartPrepareRecord
 *	目的:				开始预录
 *   输入参数:		     nPort:		解码通道。
 pFileName:	录像位置
 *   输出参数:
 *   返回值:             TRUE:	成功.
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息:			2012/12/21:YeYamin:modify......
 *********************************************************************/

PLAYSDK_API BOOL	CALLMETHOD PLAY_StartPrepareRecord(LONG nPort,const char* pFileName);

/********************************************************************
 *	函数名: 	    	PLAY_StopPrepareRecord
 *	目的:
 *   输入参数:			port:		解码通道。
 *   输出参数:
 *   返回值:             TRUE:	成功.
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息记录:		2012/12/21:YeYamin:modify......
 *********************************************************************/

PLAYSDK_API BOOL	CALLMETHOD PLAY_StopPrepareRecord(LONG nPort);

//
//
#define IVSINFOTYPE_PRESETPOS		1
#define IVSINFOTYPE_MOTINTRKS		2
#define IVSINFOTYPE_MOTINTRKS_EX	3
#define IVSINFOTYPE_LIGHT			4
#define IVSINFOTYPE_RAWDATA			5
#define IVSINFOTYPE_TRACK			6
#define IVSINFOTYPE_MOTIONFRAME		9 /*动态监测数据帧*/
#define PSIVS						240
/********************************************************************
 *	函数名: 	    	PLAY_SetIVSCallBack
 *	目的:
 *   输入参数:	        nPort:		解码通道
 pFunc:		设置解码回调
 nUser:		上下文，用于回调回来的参数
 *   输出参数:
 *   返回值:             TRUE:	成功
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *	版本信息记录:	    2012/12/21:YeYamin:modify......
 *********************************************************************/

typedef void (CALLMETHOD *GetIVSInfoCallbackFunc)(char* buf, LONG type, LONG len, LONG reallen, void* pReserved, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIVSCallBack(LONG nPort, GetIVSInfoCallbackFunc pFunc, void* pUserData);

/********************************************************************
 *	函数名: 	    	PLAY_CatchResizePic
 *	目的:				改变分辨率的抓图
 *   输入参数:			nPort:		解码通道
 sFileName:	图片地址.
 lTargetWidth & lTargetHeight: 图片的宽跟高
 ePicfomat:	picture format (jpeg/bmp)	图片的类型
 *   输出参数:
 *   返回值:             TRUE:	成功
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息记录:	    2012/12/21:YeYamin:modify......
 *********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_CatchResizePic(LONG nPort, char* sFileName, LONG lTargetWidth, LONG lTargetHeight, tPicFormats ePicfomat);

/********************************************************************
 *	函数名: 	    	PLAY_GetRealFrameBitRate
 *	目的:				获取码�
 *   输入参数:           nPort:		解码通道。
 *   输出参数:	        pBitRate:
 *   返回值:             TRUE:	成功
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息记录:	    2012/12/21:YeYamin:modify......
 *********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_GetRealFrameBitRate(LONG nPort, double* pBitRate);

/********************************************************************
 *	函数名: 	    	PLAY_StartAVIResizeConvert
 *	目的:				改变分辨率的AVI转换
 *   输入参数:           nPort:		解码通道。
 sFileName:	AVI的录像存放地址
 lWidth & lHeight:AVI的录像的宽跟高
 *   输出参数:
 *   返回值:             TRUE:	成功
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息记录:	    2012/12/21:YeYamin:modify......
 *********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_StartAVIResizeConvert(LONG nPort, char *sFileName, LONG lWidth, LONG lHeight);

/********************************************************************
 *	函数名: 	    	PLAY_StopAVIResizeConvert
 *	目的:				结束AVI转换
 *   输入参数:           nPort:		解码通道。
 *   输出参数:
 *   返回值:             TRUE:	成功
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息记录:	    2012/12/21:YeYamin:modify......
 *********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_StopAVIResizeConvert(LONG nPort);

/********************************************************************
 *	函数名: 	    	PLAY_SetPandoraWaterMarkCallBack
 *	目的:				无效
 *   输入参数:
 *   输出参数:
 *   返回值:             TRUE:	成功
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息记录:	    2012/12/21:YeYamin:modify......
 *********************************************************************/

PLAYSDK_API BOOL CALLMETHOD PLAY_SetPandoraWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, void* pUserData);


/********************************************************************
 *	函数名: 	    	PLAY_SetDigitalSignCallBack
 *	目的:				设置数字签名回调.
 *   输入参数:           nPort:		解码通道。
 nFrameID:	帧序号
 bSuccess:	校验是否通过
 pUserData   用户数据
 *   输出参数:
 *   返回值:             TRUE:	成功
 FALSE:	失败
 *********************************************************************/
typedef void (CALLBACK* fCheckDigitalSignCB)(LONG nPort, int nFrameID, BOOL bSuccess, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDigitalSignCallBack(LONG nPort, fCheckDigitalSignCB pDigitalSignCB, void* pUserData);

/********************************************************************
 *	函数名: 	    	PLAY_GetTimePicture
 *	目的:				获得绝对时间点上面的图片
 *   输入参数:           filepath:	保存的文件路径
 time:		绝对时间
 DecCBFun:	设置进去的解码回调
 user:		用户上下文
 *   输出参数:
 *   返回值:             TRUE:	成功
 FALSE:	失败
 *   创建时间:	        2012:12:21
 *   版本信息记录:	    2012/12/21:YeYamin:modify......
 *********************************************************************/
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimePicture(const char* filepath, struct tm* time, fDecCBFun fcbDec, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_StartFisheyeEx
// 描述: 鱼球联动功能扩展接口，需要包含fisheye.dll MCL_FPTZ.dll库
// 参数: [in]nPort : 通道号
//		 [in] startType:  开启类型， 0只开启鱼眼校正, 1同时开启联动和校正, 2只开启鱼球联动算法
//       [in] ptzChannelParam: 鱼球联动初始化通道参数，startType为0时，ptzChannelParam填NULL
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartFisheyeEx(LONG nPort, int startType, MHFPTZ_INITPARAM* ptzChannelParam);

//------------------------------------------------------------------------
// 函数: PLAY_SetFisheyeParams, 兼容旧版本鱼眼接口
// 描述: 设置鱼眼参数
// 参数: [in]nPort           :  通道号
//		 [in]nX				 :  鱼眼圆心横坐标
//       [in]nY				 :  鱼眼圆心纵坐标
//       [in]nRadius         :  鱼眼半径
//       [in]nLensDirection  :  镜头方向
//       [in]mode            :  图像显示模式
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFisheyeParams(LONG nPort, int nX, int nY, int nRadius, int nLensDirection, FISHSHOWMODES mode);

//------------------------------------------------------------------------
// 函数: PLAY_FisheyeGetPosition, 兼容旧版本鱼眼接口
// 描述: 获得目标中心对应电子云台的焦点位置
// 参数: [in]nPort           :  通道号
//		 [in]row			 :  目标中心所在行
//       [in]column			 :  目标中心所在列
//		 [out]pX     		 :  目标中心所对应电子云台的焦点横坐标
//       [out]pY		     :  目标中心所对应电子云台的焦点纵坐标
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_FisheyeGetPosition(LONG nPort, int row, int column, int *pX, int *pY);

//------------------------------------------------------------------------
// 函数: PLAY_FisheyeEptzUpdate, 兼容旧版本鱼眼接口
// 描述: 开启eptz(电子云台），进行缩放移动
// 参数: [in]nPort           :  通道号
//		 [in/out]pX			 :  eptz（电子云台）的焦点横坐标
//       [in/out]pY			 :  eptz的焦点纵坐标
//		 [in/out]pHangle		 :  eptz的水平角度范围(0-3600)
//       [in/out]pVangle		 :  eptz的垂直角度范围(0-900)
//       [in]ops             :  FISHEPTZOPTS结构体,为0时对指定窗口设置焦点，为1表示放大，2表示缩小，3表示向上移动，
//                              4表示向下移动，5表示向左移动，6表示向右移动，7表示自动顺时针旋转，8表示自动逆时针旋转
//								9表示停止云台操作，10表示获取当前云台窗口所在位置
//       [in]nWinNum         :  要进行eptz的窗口编号，左上角win_num为1，从左到右递增
//       [in]nZoomStep       :  放大缩小的步长, 范围1-8
//       [in]nPtStep		 :  上下左右移动的步长, 范围1-8
//		 [in]nRotateStep	 :  旋转的步长, 范围1-8
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OldFisheyeEptzUpdate(LONG nPort, int *pX, int *pY, int *pHAngle, int *pVAngle, FISHEPTZOPTS ops, int nWinNum,
                                                      int nZoomStep, int nPtStep, int nRotateStep);

/******************************************************************************
 *
 * 函数名  : PLAY_FishEyeTransFromCoordinate
 * 描  述  : 校正图像和源图像之间坐标转换
 * 输  入  : - handle: 鱼眼算法实例句柄
 - x:需要转换的坐标
          y:需要转换的坐标
          winid:winid参数，当flag=0，这个为输入参数  当flag=1，这个参数为输出参数
          u:转换后的坐标
          v:转换后的坐标
          flag：0为校正后图像转原始图像坐标，1表示原始图像坐标转校正后图像坐标
 * 输  出  : 无
 * 返回值  : BOOL,成功返回TRUE,失败返回FALSE.
 *******************************************************************************/
PLAYSDK_API BOOL PLAY_FishEyeTransFromCoordinate(LONG nPort, int x, int y, int *winid, int *u, int *v, int flag);

/******************************************************************************
 *
 * 函数名  : PLAY_FishEyeTransFromCoordinateFSTA(from source to adjust)
 * 描  述  : 源图像坐标转校正后图像坐标
 * 输  入  : - handle: 鱼眼算法实例句柄
 - points:需要转换的原始图像上的坐标
          num:坐标个数
          points_adjust:转换后的坐标
          winid:转换后的坐标对应的窗口id
          points_adjust_num    输出点的个数
 * 输  出  : 无
 * 返回值  : BOOL,成功返回TRUE,失败返回FALSE.
 *           other: 这里如果1个原始图像上的点对应多个子窗口的点，那么这个点会有多个points_adjuest
 每个points_adjust对应一个winid；
 
 比如（10,10） 点属于窗口1和窗口2,在窗口1上的对应坐标是（100,100），在窗口2上的
 对应坐标是（1000,1000）
 那么	points_adjust[i].x = 100,		winid[i] = 1;
 points_adjust[i].y = 100,
 points_adjust[i+1].x = 1000,	winid[i+1] = 2;
 points_adjust[i+1].y = 1000,
 *******************************************************************************/
PLAYSDK_API BOOL PLAY_FishEyeTransFromCoordinateFSTA(LONG nPort, FISHEYE_POINT2D *points, int num, FISHEYE_POINT2D *points_adjust, int *winid, int *points_adjust_num);

/******************************************************************************
 *
 * 函数名  : PLAY_FishEyeTransFromCoordinateFATS(from adjust to source)
 * 描  述  : 校正后图像坐标转源图像坐标
 * 输  入  :	- handle: 鱼眼算法实例句柄
 - points:需要转换的校正后图像上的坐标
          num:坐标个数
          points_adjust:转换后的坐标
          winid:需要转换的坐标的窗口id
 * 输  出  : 无
 * 返回值  : BOOL,成功返回TRUE,失败返回FALSE.
 *******************************************************************************/
PLAYSDK_API BOOL PLAY_FishEyeTransFromCoordinateFATS(LONG nPort, FISHEYE_POINT2D *points, int num, FISHEYE_POINT2D *points_adjust, int winid);

/******************************************************************************
 *
 * 函数名  : PLAY_FishEyeTransFromLineFATS(from adjust to source)
 * 描  述  : 校正后图像折线转源图像曲线
 * 输  入  :	- handle: 鱼眼算法实例句柄
 - points:需要转换的校正后图像上折线点信息
          num:点个数
          points_adjust:转换后的曲线信息
          winid:需要转换的坐标的窗口id
          pOpt :配置信息,调用这个接口之前先调用Fisheye_GetParam获取
 * 输  出  : 无
 * 返回值  : BOOL,成功返回TRUE,失败返回FALSE.
 *******************************************************************************/
PLAYSDK_API BOOL PLAY_FishEyeTransFromLineFATS(LONG nPort, FISHEYE_POINT2D *points, int num, FISHEYE_POINT2D *points_adjust, int winid, FISHEYE_OPTPARAM *pOpt);


/******************************************************************************
 *
 * 函数名  : PLAY_FishEyeTransFromLineFSTA(from source to adjust)
 * 描  述  : 原始图像折线转校正后图像曲线
 * 输  入  : - handle: 鱼眼算法实例句柄
 - points:需要转换的原始图像上的坐标
 num:坐标个数
 points_adjust:转换后的坐标
 winid:转换后的坐标对应的窗口id
 points_adjust_num    输出点的个数
 pOpt:配置信息 调用这个接口之前先调用Fisheye_GetParam获取
 * 输  出  : 无
 * 返回值  : BOOL,成功返回TRUE,失败返回FALSE.
 *other: 这里如果1个原始图像上的点对应多个子窗口的点，那么这个点会有多个points_adjuest
 每个points_adjust对应一个winid；
 
 比如（10,10） 点属于窗口1和窗口2,在窗口1上的对应坐标是（100,100），在窗口2上的
 对应坐标是（1000,1000）
 那么	points_adjust[i].x = 100,		winid[i] = 1;
 points_adjust[i].y = 100,
 points_adjust[i+1].x = 1000,	winid[i+1] = 2;
 points_adjust[i+1].y = 1000,
 *******************************************************************************/
PLAYSDK_API BOOL PLAY_FishEyeTransFromLineFSTA(LONG nPort, FISHEYE_POINT2D *points, int num, FISHEYE_POINT2D *points_adjust, int *winid, int *points_adjust_num, FISHEYE_OPTPARAM *pOpt);

/******************************************************************************
 *
 * 函数名  : PLAY_FishEyeTransFromLineFSTS(from source to source)
 * 描  述  : 原始图像折线转原始图像曲线
 * 输  入  : - handle: 鱼眼算法实例句柄
 - points:需要转换的原始图像上的坐标
 num:坐标个数
 points_adjust:转换后的坐标
 points_adjust_num    输出点的个数
 pOpt:配置信息 调用这个接口之前先调用Fisheye_GetParam获取
 * 输  出  : 无
 * 返回值  : BOOL,成功返回TRUE,失败返回FALSE.
 *******************************************************************************/
PLAYSDK_API BOOL PLAY_FishEyeTransFromLineFSTS(LONG nPort, FISHEYE_POINT2D *points, int num, FISHEYE_POINT2D *points_adjust, int *points_adjust_num, FISHEYE_OPTPARAM *pOpt);

//------------------------------------------------------------------------
// 函数: PLAY_StartDeNoise
// 描述: 开启视频去噪算法功能,需要包含3dnr.dll库
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDeNoise(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDeNoiseParams
// 描述: 设置视频去噪参数
// 参数: [in]nPort           :  通道号
//		 [in]nTemporal		 :  时域去噪强度 [0,32]
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDeNoiseParams(LONG nPort, int nTemporal);

//------------------------------------------------------------------------
// 函数: PLAY_StopDeNoise
// 描述: 停止视频去噪算法功能
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDeNoise(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StartDeHaze
// 描述: 开启视频去雾算法功能，需要包含dehazing.dll库
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDeHaze(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDehazeParams
// 描述: 设置视频去雾参数
// 参数: [in]nPort           :  通道号
//		 [in]ALightValue	 :	设定的大气光强的值，范围0-255
//		 [in]AutoLightOn	 :  默认为1,代表开启自动寻找大气光强；0-关闭自动，开启手动
//       [in]AutoRun		 :	默认为1,代表一直开启去雾功能，0-自动判断是否雾天并去雾
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDehazeParams(LONG nPort, int ALightValue, int AutoLightOn, int AutoRun);

//------------------------------------------------------------------------
// 函数: PLAY_STOPDeHaze
// 描述: 停止视频去雾算法功能
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDeHaze(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StartIVSE
// 描述: 开启视频增强算法功能，需要包含IvseDll.dll库
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//
// 注意：此算法处理时间较长，不建议处理高清视频
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartIVSE(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetIVSEParams
// 描述: 设置视频增强参数，可以多次调用来组合使用多种IVSE库的功能
// 参数: [in]nPort           :  通道号
//		 [in]pIVSEParams	 :	IVSEPARAMS结构体参数
//		 [in]bEnable		 :  对应于IVSEPARAMS中的IVSEFUNCTYPE功能选项，使能开关
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIVSEParams(LONG nPort, IVSEPARAMS* pIVSEParams, BOOL bEnable);

//------------------------------------------------------------------------
// 函数: PLAY_StopIVSE
// 描述: 停止视频增强算法功能
// 参数: [in]nPort : 通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopIVSE(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_ConvertToBmpFile
// 描述: 图像格式转为BMP格式.
// 参数: pBuf,图像数据指针
//		 nSize,图像数据大小
//		 nWidth,图像宽度
//		 nHeight,图像高度
//		 nType,数据类型.T_RGB32,T_UYVY等.
//		 sFileName,要保存的文件名.最好以BMP作为文件扩展名.
//       nBmpType, BMP类型，PIC_BMP_32表示BMP32， PIC_BMP_24表示BMP24
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToBmpFileEx(char * pBuf,LONG nSize,LONG nWidth,LONG nHeight,LONG nType, char *sFileName,int nBmpType);

//------------------------------------------------------------------------
// 函数: PLAY_EnableLargePicAdjustment
// 描述: 是否启用高清图像内部调整策略，默认启用。该策略启用时，在快放4倍速以上时，只播放I帧，不启用时，则每帧都播放
// 参数: [in]nPort           :  通道号
//		 [in]bEnable		 :  TRUE表示启用此功能，FALSE表示关闭此功能
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableLargePicAdjustment(LONG nPort, BOOL bEnable);

//------------------------------------------------------------------------
// 同步播放接口
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 函数: PLAY_OpenPlayGroup
// 描述: 打开同步播放
// 参数: 无
// 返回: 同步播放控制句柄，在调用同步播放控制接口时需要传入该句柄，返回NULL表示失败
//------------------------------------------------------------------------
PLAYSDK_API void* CALLMETHOD PLAY_OpenPlayGroup();

//------------------------------------------------------------------------
// 函数: PLAY_AddToPlayGroup
// 描述: 添加一路已经代开的视频至同步播放中
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//       nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_AddToPlayGroup(void* hPlayGroup, LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_DelFromPlayGroup
// 描述: 从同步播放队列中删除指定通道号
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//       nPort,通道号
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_DelFromPlayGroup(void* hPlayGroup, LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayGroupDirection
// 描述: 从当前时间点正放或倒放
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//		 nDirection,播放方向：0，向前，1，向后
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupDirection(void* hPlayGroup, int nDirection);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayGroupSpeed
// 描述: 设置播放速度
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//		 fCoff,播放速度,范围[1/64~64.0],小于1表示慢放，大于1表示正放.
//			   当播放速度较快时可能会抽帧播放.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayGroupSpeed(void* hPlayGroup, float fSpeed);

//------------------------------------------------------------------------
// 函数: PLAY_PausePlayGroup
// 描述: 暂停或继续
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//		 bPause,TRUE暂停,FLASE恢复
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_PausePlayGroup(void* hPlayGroup, BOOL bPause);

//------------------------------------------------------------------------
// 函数: PLAY_StepPlayGroup
// 描述: 单帧播放
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StepPlayGroup(void* hPlayGroup);

//------------------------------------------------------------------------
// 函数: PLAY_StepPlayGroup
// 描述: 采用绝对时间进行定位
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
//	     pstDateTime,绝对时间
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SeekPlayGroup(void* hPlayGroup, DATETIME_INFO* pstDateTime);

//------------------------------------------------------------------------
// 函数: PLAY_ClosePlayGroup
// 描述: 关闭同步播放控制
// 参数: hPlayGroup,同步播放句柄，由PLAY_OpenPlayGroup返回
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ClosePlayGroup(void* hPlayGroup);


//------------------------------------------------------------------------
// 函数: PLAY_SetFileRefCallBack
// 描述: 设置建立索引回调,在文件打开时生成文件索引.这个过程耗时比较长,大约
//			每秒处理40M左右的数据,因为从硬盘读数据比较慢,建立索引的过程是在
//			后台完成,需要使用索引的函数要等待这个过程结束,其他接口不受影响.
// 参数: nPort,通道号
//		 pFileRefDone,回调函数指针,其参数含义如下:
//			nPort,通道号
//			pUserData,用户自定义参数
//		 pUserData,用户自定义参数
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void(CALLBACK *fpFileRefDoneCBFun)(DWORD nPort, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileRefCallBack(LONG nPort,
                                                    fpFileRefDoneCBFun pFileRefDoneCBFunc,
                                                    void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetDemuxCallBack
// 描述: 源数据分析完的数据回调
// 参数: nPort,通道号
//		 DecCBFun,分析数据回调指针
//			nPort,通道号
//			pBuf,数据指针
//			nSize,数据长度
//			pParam,帧信息  指向DEMUX_INFO这个结构体
//			nReserved,保留
//			pUserData,用户自定义数据
//		 pUserData,用户自定义数据
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fDemuxDecCBFun)(LONG nPort,char * pBuf,	LONG nSize,void * pParam,void* pReserved, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDemuxCallBack(LONG nPort, fDemuxDecCBFun DecCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetFileDoneTimeCallBack
// 描述: 文件开始、结束时间回调。分析出文件开始和结束时间后会调用该回调。
// 参数: nPort,通道号
//		 fFileTimeDoneCBFun,回调函数指针,不能为NULL,其参数含义如下:
//			nPort,通道号
//			nStartTime, 文件开始时间.自1970年1月1日0点0分0秒的秒数.
//			nEndTime, 文件结束时间.自1970年1月1日0点0分0秒的秒数.
//			pUserData, 用户自定义参数
//		 pUserData, 用户自定义参数.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fFileTimeDoneCBFun)(LONG nPort, DWORD nStarTime, DWORD nEndTime, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileTimeDoneCallBack(LONG nPort, fFileTimeDoneCBFun FileTimeCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_GetKeyFramePosByAbsoluteTime
// 描述: 按绝对时间查找指定位置之前的关键帧位置.
// 参数: nPort,通道号
//		 t,绝对时间,详见SYSTEMTIME.仅用到年月日时分秒.注：在执行成功后该值存储所返回I帧的时间戳
//		 framePos,查找到的关键帧的文件位置信息结构指针,详见PFRAME_POS.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_GetKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* t, FRAME_POS* framePos);

//------------------------------------------------------------------------
// 函数: PLAY_GetNextKeyFramePosByAbsoluteTime
// 描述: 按绝对时间查找指定位置之后的关键帧位置.
// 参数: nPort,通道号
//		 t,绝对时间,详见SYSTEMTIME.仅用到年月日时分秒.注：在执行成功后该值存储所返回的I帧的时间戳
//		 framePos,查找到的关键帧的文件位置信息结构指针,详见PFRAME_POS.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_GetNextKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* t, FRAME_POS* framePos);

//------------------------------------------------------------------------
// 函数: PLAY_QueryGroupPlayingTime
// 描述: 查询当前组中正在播放的时间.
// 参数: nPort,通道号
//		 pDateTime,时间
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
PLAYSDK_API BOOL CALLMETHOD PLAY_QueryGroupPlayingTime(void* hPlayGroup,  DATETIME_INFO *pDateTime);

//------------------------------------------------------------------------
// 函数: PLAY_GetAudioChannels
// 描述: 获取音频通道总数
// 参数: nPort,通道号
//       pChannels, 输出参数，[0-255].
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioChannels(LONG nPort, DWORD* pChannels);

//------------------------------------------------------------------------
// 函数: PLAY_ChooseAudio
// 描述: 选择音频通道
// 参数: nPort,通道号
//       nChannelID, 音频通道从0开始.
//       bFlag,TRUE打开,FALSE关闭
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChooseAudio(LONG nPort, DWORD nChannelID, BOOL bFlag);

//------------------------------------------------------------------------
// 函数: PLAY_GetAudioChooseState
// 描述: 获取音频通道打开关闭状态
// 参数: nPort,通道号
//       nChannelID, 音频通道[0-255].
//       pFlag,TRUE打开,FALSE关闭
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetAudioChooseState(LONG nPort, DWORD nChannelID, BOOL* bFlag);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayedAbsTime
// 描述: 按绝对时间设置播放时间
// 参数: nPort,通道号
//		 pDateTime,绝对时间
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayedAbsTime(LONG nPort, DATETIME_INFO *pDateTime);

//------------------------------------------------------------------------
// 函数: PLAY_SetPlayPosByFileOffset
// 描述: 按文件偏移设置播放位置
// 参数: nPort,通道号
//		 nFileOffset,文件偏移位置
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayPosByFileOffset(LONG nPort, UINT nFileOffset);

//------------------------------------------------------------------------
// 函数: PLAY_GetCurrentFrameRateEx
// 描述: 获得当前帧率（小数形式）
// 参数: nPort,通道号
// 返回: float,当前帧�
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetCurrentFrameRateEx(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_InitDDraw
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDraw(HWND hWnd);

//------------------------------------------------------------------------
// 函数: PLAY_GetCaps
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API int	CALLMETHOD PLAY_GetCaps();

//------------------------------------------------------------------------
// 函数: PLAY_GetFileHeadLength
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileHeadLength();

//------------------------------------------------------------------------
// 函数: PLAY_RealeseDDraw
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RealeseDDraw();

//------------------------------------------------------------------------
// 函数: PLAY_GetDDrawDeviceTotalNums
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDDrawDeviceTotalNums();

//------------------------------------------------------------------------
// 函数: PLAY_SetDDrawDevice
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetDDrawDeviceInfo
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,LONG *hhMonitor);

//------------------------------------------------------------------------
// 函数: PLAY_GetCapsEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API int	CALLMETHOD PLAY_GetCapsEx(DWORD nDDrawDeviceNum);

//------------------------------------------------------------------------
// 函数: PLAY_ThrowBFrameNum
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ThrowBFrameNum(LONG nPort,DWORD nNum);

//------------------------------------------------------------------------
// 函数: PLAY_InitDDrawDevice
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL	CALLMETHOD PLAY_InitDDrawDevice();

//------------------------------------------------------------------------
// 函数: PLAY_ReleaseDDrawDevice
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API void CALLMETHOD PLAY_ReleaseDDrawDevice();

//------------------------------------------------------------------------
// 函数: PLAY_Back
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Back(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDDrawDeviceEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);


//------------------------------------------------------------------------
// 函数: PLAY_SetOverlayMode
// 描述: 此接口无效，overlay模式已经过时
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);


//------------------------------------------------------------------------
// 函数: PLAY_GetOverlayMode
// 描述: 此接口无效，overlay模式已经过时
//------------------------------------------------------------------------
PLAYSDK_API LONG CALLMETHOD PLAY_GetOverlayMode(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_GetColorKey
// 描述: 此接口无效，overlay模式已经过时
//------------------------------------------------------------------------
PLAYSDK_API COLORREF CALLMETHOD PLAY_GetColorKey(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_ChangeRate
// 描述: 替代接口PLAY_SetPlaySpeed
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChangeRate(LONG nPort, int rate);

//------------------------------------------------------------------------
// 函数: PLAY_SetTimerType
// 描述: 此接口无效
PLAYSDK_API BOOL CALLMETHOD PLAY_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);

//------------------------------------------------------------------------
// 函数: PLAY_GetTimerType
// 描述: 此接口无效
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);

//------------------------------------------------------------------------
// 函数: PLAY_SetMDRange
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDRange(LONG nPort,DISPLAYRECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);

//------------------------------------------------------------------------
// 函数: PLAY_SetMDThreShold
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold);

//------------------------------------------------------------------------
// 函数: PLAY_GetMDPosition
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue);


//------------------------------------------------------------------------
// 函数: PLAY_CutFileSegment
// 描述: 此接口无效
//------------------------------------------------------------------------
typedef void (CALLBACK *CutProgressFunc)(DWORD nPort, int iProgress, DWORD dwUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_CutFileSegment(LONG nPort,
                                                LONG lBeginTime,
                                                LONG lEndTime,
                                                CutProgressFunc pFunc,
                                                char *sOutFilePath,
                                                DWORD dwUser);

//------------------------------------------------------------------------
// 函数: PLAY_SetVideoPerTimer
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVideoPerTimer(int iVal);


//------------------------------------------------------------------------
// 函数: PLAY_GetVideoPerTimer
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetVideoPerTimer(int* pVal);

//------------------------------------------------------------------------
// 函数: PLAY_InputVideoData
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);

//------------------------------------------------------------------------
// 函数: PLAY_InputAudioData
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);

//------------------------------------------------------------------------
// 函数: PLAY_SetVerifyCallBack
// 描述: 此接口无效
//------------------------------------------------------------------------
typedef void (CALLBACK * fVerifyCBFun)(LONG nPort, FRAME_POS * pFilePos, DWORD bIsVideo, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, fVerifyCBFun VerifyFun, void* pUserData);


//------------------------------------------------------------------------
// 函数: PLAY_SetSourceBufCallBack
// 描述: 此接口无效
//------------------------------------------------------------------------
typedef void (CALLBACK * fSourceBufCBFun)(LONG nPort,DWORD nBufSize, void* pUserData,void*pResvered);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSourceBufCallBack(LONG nPort,
                                                      DWORD nThreShold,
                                                      fSourceBufCBFun SourceBufCBFun,
                                                      void* pUserData,
                                                      void *pReserved);

//------------------------------------------------------------------------
// 函数: PLAY_ResetSourceBufFlag
// 描述: 此接口无效
//------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBufFlag(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetPandoraWaterMarkCallBack
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPandoraWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetDisplayBuf
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetDisplayBuf
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDisplayBuf(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_SetDisplayType
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayType(LONG nPort,LONG nType);

//------------------------------------------------------------------------
// 函数: PLAY_GetDisplayType
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API LONG CALLMETHOD PLAY_GetDisplayType(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_RefreshPlayEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_OpenStreamEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);

//------------------------------------------------------------------------
// 函数: PLAY_CloseStreamEx
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStreamEx(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_AdjustFluency
// 描述: 此接口无效
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustFluency(LONG nPort, int level);

//------------------------------------------------------------------------
// 函数: PLAY_SurfaceChange
// 描述: Android版本专用，Surface建立或变化通知
// 参数:
// 返回:
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SurfaceChange(LONG nPort, HWND hWnd);

//------------------------------------------------------------------------
// 函数: PLAYER_SetFileInfoFrameCallback
// 描述: 设置文件信息帧回调函数
// 参数:
// 返回:
//------------------------------------------------------------------------
typedef int (CALLBACK* fOnFileInfoFrame)(LONG nPort, FILE_INFO_IMAGE* pFileInfoImage, FILE_INFO_FRAME* pFileInfoFrame, void* pUserParam);
PLAYSDK_API BOOL CALLMETHOD	PLAY_SetFileInfoFrameCallback(LONG nPort, fOnFileInfoFrame fFileInfoFrame, tPicFormats imageType, void* pUserParam);

//------------------------------------------------------------------------
// 函数: PLAYER_SetAnalyzePositionCallback
// 描述: 设置文件信息帧分析进度回调函数
// 参数:
// 返回:
//------------------------------------------------------------------------
typedef int (CALLBACK *fOnAnalyzePosition)(LONG nPort, DATETIME_INFO* pstDateTime, void* pUserParam);
PLAYSDK_API BOOL CALLMETHOD	PLAY_SetAnalyzePositionCallback(LONG nPort, fOnAnalyzePosition fAnalyzePosition, void* pUserParam);

//------------------------------------------------------------------------
// 函数: PLAYER_StartFileFrameDetect
// 描述: 需要在索引建立完成之后，开始文件信息帧检测，输入搜索条件
// 参数:
// 返回:
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD	PLAY_StartFileFrameDetect(LONG nPort, FILE_INFO_FRAME_SEARCH* pFileInfoFrameSearch);

//------------------------------------------------------------------------
// 函数: PLAYER_StopFileFrameDetect
// 描述: 中止搜索
// 参数:
// 返回:
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD	PLAY_StopFileFrameDetect(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StartEdgeEnhance
// 描述: 开启图像锐化处理
// 参数: level	   -- 处理等级,0-关闭,6-最强,默认等级4
//		 algMode   -- 算法模式,预留接口,目前只支持0
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartEdgeEnhance(LONG nPort, int level, int algMode);

//------------------------------------------------------------------------
// 函数: PLAY_StopEdgeEnhance
// 描述: 关闭图像锐化处理
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopEdgeEnhance(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StartVideoStable
// 描述: 开启视频防抖
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StartVideoStable(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_StopEdgeEnhance
// 描述: 关闭视频防抖
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_StopVideoStable(LONG nPort);

//------------------------------------------------------------------------
// 函数: PLAY_Scale
// 描述: 手机版本图像缩放
// 参数: nPort  端口号
//       scale	缩放比例[1.0, 8.0]
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Scale(LONG nPort, float scale, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_Translate
// 描述: 手机版本图像平移
// 参数: nPort  端口号
//       x	x平移坐标，绝对值
//	     y	y平移坐标，绝对值
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_Translate(LONG nPort, float x, float y, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_SetIdentity
// 描述: 手机版本图像归一化，重置平移，缩放操作。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SetIdentity(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetScale
// 描述: 手机版本获取当前缩放值。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetScale(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetTranslateX
// 描述: 手机版本获取当前x轴平移坐标。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetTranslateX(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_GetTranslateX
// 描述: 手机版本获取当前y轴平移坐标。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API float CALLMETHOD PLAY_GetTranslateY(LONG nPort, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_CleanScreen
// 描述: 手机版本清屏功能
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_CleanScreen(LONG nPort, float red, float green, float blue, float alpha, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_ViewResolutionChanged
// 描述: Android版本,SurfaceView大小变化时调用
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ViewResolutionChanged(LONG nPort, int nWidth, int nHeight, DWORD nRegionNum);

//------------------------------------------------------------------------
// 函数: PLAY_StartDataRecordEx
// 描述: 开始流数据录像,只对流模式有用,在PLAY_Play之后调用.
// 参数: nPort,通道号
//		 sFileName,录像文件名,如果文件名中有不存在的文件夹,就创建该文件夹.
//		 idataType,0表示原始视频流;1表示转换成AVI格式;2表示转换成ASF格式;3分段保存文件
//		 fListenter, 回调函数，监听数据写过程中发生错误.
// 返回: BOOL,成功返回TRUE,失败返回FALSE.
//------------------------------------------------------------------------
typedef void (CALLBACK* fRecordErrorOccur)(LONG nPort, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDataRecordEx(LONG nPort, char *sFileName, int idataType, fRecordErrorOccur fListenter, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_SetMultiFrameDecCallBack
// 描述: 开启解码信息回调，针对SVAC码流中的些监控信息。
// 参数: nPort  端口号
//       nRegionNum,显示区域序号, 保留。
//		 DecInfoCallBack, 回调函数
//		 pUser, 用户回调数据
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
typedef void (CALLBACK* fMultiFrameDecCallBack)(LONG nPort, LONG nStreamID, char* pData, LONG nLen,
FRAME_INFO* stFrameInfo, void* pUserData, LONG nReserved1);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiFrameDecCallBack(LONG nPort, fMultiFrameDecCallBack DecInfoCallBack, void* pUser);

//------------------------------------------------------------------------
// 函数: PLAY_SetMultiFrameCallBack
// 描述: 开启多帧信息回调，目前主要针对SVAC编码，
//       SVC功能中，一份数据带有基本层和增强层两份数据
// 参数: nPort  端口号
//       MultiFrameCallBack, 回调函数。
//       pUser  用户数据
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
typedef void (CALLBACK* fMultiFrameCallBack)(LONG nPort, LONG nStreamID, void* pUserData, LONG nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMultiFrameCallBack(LONG nPort, fMultiFrameCallBack MultiFrameCallBack, void* pUser);

//------------------------------------------------------------------------
// 函数: PLAY_SetDecInfoCallBack
// 描述: 开启多帧信息回调，针对SVAC码流
// 参数: nPort  端口号
//       nFrameID, 选择进行播放的帧
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
typedef void (CALLBACK* fDecInfoCallBack)(LONG nPort, FRAME_DEC_EXT_INFO* pDecInfo, void* pUserData, LONG nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecInfoCallBack(LONG nPort, fDecInfoCallBack DecInfoCallBack, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_ChooseFrame
// 描述: 选择显示SVAC编码SVC的基本层或增强层
// 参数: nPort  端口号
//       nFrameID, 要显示的层(0: 基本层，1: 增强层)
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_ChooseFrame(LONG nPort, LONG nFrameID);

//------------------------------------------------------------------------
// 函数: PLAY_RenderPrivateData
// 描述: 显示私有数据，例如规则框，规则框报警，移动侦测等
// 参数: nPort  端口号
//       bTrue TRUE:打开 FALSE:关闭
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_RenderPrivateData(LONG nPort, BOOL bTrue, LONG nReserve);

//------------------------------------------------------------------------
// 函数: PLAY_SetFileIndexProgressCallBack
// 描述: 设置索引创建进度回调
// 参数: nPort  端口号
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
typedef void (CALLBACK* fIndexProgressCB)(LONG nPort, float fProgress, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileIndexProgressCallBack(LONG nPort, fIndexProgressCB IndexProgressCB, void* pUser);

//------------------------------------------------------------------------
// 函数: PLAY_GetLastYUVFrame
// 描述: 主动获取上一帧对应的YUV数据
// 参数: nPort  端口号
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_GetLastYUVFrame(LONG nPort, FRAME_DECODE_INFO* pFrameDecodeInfo);

//IOS特殊要求：内存减小版本
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMemMinimized(LONG nPort);

PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeThreadNum(LONG nPort, DWORD nNum);

//设置解密密钥，SVAC解码使用
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecodeKey(LONG nPort, const unsigned char *key, unsigned int key_len);

PLAYSDK_API BOOL CALLMETHOD PLAY_GetIRefValue(LONG nPort, BYTE *pBuffer, DWORD *pSize);

//------------------------------------------------------------------------
// 函数: PLAY_OutsideRender
// 描述: nacl ui线程调用此接口
// 参数: nPort  端口号
// 参数: nWidth  窗口宽
// 参数: nHeight  窗口高
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_OutsideRender(LONG nPort, int nWidth, int nHeight);


typedef void (CALLBACK* fDoubleVisibleDecCBFun)(LONG nPort,char * pBuf, int nSize, int nWidth, int nHeight, 
char* pSecondBuf, int nSecondSize, int nSecondWidth, int nSecondHeight, void* pUserData);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDoubleVisibleDecCallBack(LONG nPort, fDoubleVisibleDecCBFun DataCBFun, void* pUserData);

//------------------------------------------------------------------------
// 函数: PLAY_EnableAudioChannel
// 描述: 控制左右声道音频播放，仅对左右声道音频有效。
// 参数: nPort  端口号
// 参数: nChnNum  左右通道，0-左通道，1-右通道
// 参数: bEnable  使能 TRUE-启用， FALSE-禁用
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_EnableAudioChannel(LONG nPort, DWORD nChnNum, BOOL bEnable);

//------------------------------------------------------------------------
// 函数: PLAY_SplitProc
// 描述: yuv 拼接算法，用于4k大屏的显示
// 参数: nPort  端口号
// 参数: nMode 模式，0对应基本模式，1对应1+3模式，2对应1+5模式
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SplitProc(LONG nPort, int nMode);

//------------------------------------------------------------------------
// 函数: PLAY_SplitProcUpdate
// 描述: yuv 拼接算法，更新需要放大的矩形位置
// 参数: nPort  端口号
// 参数: pAreaRect 矩形坐标数组的起始地址
//       如果nMode是0，则应为NULL
//       如果nMode是1，则该数组的大小应为3
//       如果nMode是2，则该数组的大小应为5              | 
// 返回: TRUE 成功 FALSE 失败
//------------------------------------------------------------------------
PLAYSDK_API BOOL CALLMETHOD PLAY_SplitProcUpdate(LONG nPort, DISPLAYRECT* pAreaRect);
    
#ifdef	__cplusplus
}
#endif

#endif
