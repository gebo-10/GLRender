#include <Log.h>
Log::Log()
{

}

Log::~Log()
{
	google::ShutdownGoogleLogging();
}

bool Log::Init(char * name)
{
	google::InitGoogleLogging(name);
	FLAGS_log_dir = "./log";
	//FLAGS_logtostderr = true;
	FLAGS_alsologtostderr = true;
	FLAGS_colorlogtostderr = true;//设置输出到屏幕的日志显示相应颜色
	FLAGS_logbufsecs = 0; //缓冲日志输出，默认为30秒，此处改为立即输出
	FLAGS_max_log_size = 10;	//最大日志大小（MB）

	//google::SetStderrLogging(google::INFO); //设置级别高于 google::INFO 的日志同时输出到屏幕
	//google::SetLogDestination(google::ERROR,"log/error_");    //设置 google::ERROR 级别的日志存储路径和文件名前缀
	google::SetLogDestination(google::INFO, "./log/INFO_"); //设置 google::INFO 级别的日志存储路径和文件名前缀
	google::SetLogDestination(google::WARNING, "./log/WARNING_");   //设置 google::WARNING 级别的日志存储路径和文件名前缀
	google::SetLogDestination(google::ERROR, "./log/ERROR_");   //设置 google::ERROR 级别的日志存储路径和文件名前缀
	
	FLAGS_stop_logging_if_full_disk = true;	//当磁盘被写满时，停止日志输出
	google::SetLogFilenameExtension("game_");	//设置文件名扩展，如平台？或其它需要区分的信息
	//google::InstallFailureSignalHandler();	//捕捉 core dumped  glog-0.3.3\src\signalhandler.cc 里边进行了实现 把这个文件 加到 工程里 编译一下就可以了

	LOG(INFO) << "glog init success" << endl;
	return true;
}

